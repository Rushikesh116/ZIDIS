"""
ZIDIS Live P-Wave Plotter
==========================
Reads real-time sensor samples from the NUCLEO-H533RE board over serial (COM port)
and plots the P-Wave waveform live alongside a reference signal.

The firmware sends each sample as: D:<integer>\r\n (where integer = sample * 1000)

Requirements: pip install matplotlib numpy pyserial

Usage:
  python live_pwave_plotter.py          (auto-detects COM port)
  python live_pwave_plotter.py COM5     (specify COM port)
"""

import sys
import time
import threading
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# ── Configuration ──
BAUD_RATE = 115200
MAX_SAMPLES = 500       # Show last 5 seconds at 100Hz
SAMPLE_RATE = 100
STA_LTA_TRIG = 3.0
STA_LTA_DETRIG = 1.5

# ── Data buffers ──
samples = deque(maxlen=MAX_SAMPLES)
sta_vals = deque(maxlen=MAX_SAMPLES)
lta_vals = deque(maxlen=MAX_SAMPLES)
ratio_vals = deque(maxlen=MAX_SAMPLES)
log_messages = deque(maxlen=10)

# STA/LTA state
sta = 0.0
lta = 0.0
is_triggered = False
alpha_sta = 0.0198
alpha_lta = 0.001

def process_sample(val):
    """Compute STA/LTA on incoming sample (mirrors firmware DSP)"""
    global sta, lta, is_triggered
    abs_val = abs(val)
    sta = alpha_sta * abs_val + (1 - alpha_sta) * sta
    if not is_triggered:
        lta = alpha_lta * abs_val + (1 - alpha_lta) * lta
    lta_safe = max(lta, 0.0001)
    ratio = sta / lta_safe
    if not is_triggered and ratio > STA_LTA_TRIG:
        is_triggered = True
    elif is_triggered and ratio < STA_LTA_DETRIG:
        is_triggered = False
    return sta, lta, ratio

# ── Serial Reader Thread ──
def serial_reader(port):
    import serial
    try:
        ser = serial.Serial(port, BAUD_RATE, timeout=0.1)
        print(f"[PLOTTER] Connected to {port} at {BAUD_RATE} baud")
    except Exception as e:
        print(f"[PLOTTER] ERROR: Cannot open {port}: {e}")
        return
    
    while True:
        try:
            line = ser.readline().decode('ascii', errors='ignore').strip()
            if not line:
                continue
            
            if line.startswith('D:'):
                # Data sample line
                try:
                    raw_val = int(line[2:])
                    val = raw_val / 1000.0  # Undo the *1000 scaling
                    s, l, r = process_sample(val)
                    samples.append(val)
                    sta_vals.append(s)
                    lta_vals.append(l)
                    ratio_vals.append(r)
                except ValueError:
                    pass
            else:
                # Log message
                log_messages.append(line)
                print(f"[BOARD] {line}")
        except Exception:
            pass

# ── Auto-detect COM port ──
def find_com_port():
    import serial.tools.list_ports
    ports = serial.tools.list_ports.comports()
    stlink_port = None
    for p in ports:
        desc = (p.description or '').lower()
        mfr = (p.manufacturer or '').lower()
        if 'stlink' in desc or 'st-link' in desc or 'stmicroelectronics' in mfr:
            stlink_port = p.device
            break
    if stlink_port:
        return stlink_port
    # Fallback: return first available
    if ports:
        return ports[0].device
    return None

# ── Main ──
if __name__ == '__main__':
    # Determine COM port
    if len(sys.argv) > 1:
        com_port = sys.argv[1]
    else:
        com_port = find_com_port()
        if not com_port:
            print("[PLOTTER] ERROR: No COM port found! Connect NUCLEO board or specify port:")
            print("  python live_pwave_plotter.py COM5")
            sys.exit(1)
        print(f"[PLOTTER] Auto-detected: {com_port}")
    
    # Start serial reader thread
    reader_thread = threading.Thread(target=serial_reader, args=(com_port,), daemon=True)
    reader_thread.start()
    
    # Wait for first data
    print("[PLOTTER] Waiting for data from board...")
    time.sleep(1)
    
    # ── Setup Plot ──
    plt.style.use('dark_background')
    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(14, 10), 
                                          gridspec_kw={'height_ratios': [3, 2, 1]})
    fig.patch.set_facecolor('#0a0a1a')
    fig.suptitle('ZIDIS Live P-Wave Monitor', fontsize=16, fontweight='bold', 
                 color='#00e5ff', fontfamily='monospace')
    
    BG = '#0d0d24'
    GRID = '#1a1a3a'
    CYAN = '#00e5ff'
    GREEN = '#76ff03'
    RED = '#ff1744'
    YELLOW = '#ffab00'
    
    for ax in [ax1, ax2, ax3]:
        ax.set_facecolor(BG)
        ax.grid(True, color=GRID, alpha=0.5)
        ax.tick_params(colors='white')
    
    # Lines
    line_sample, = ax1.plot([], [], color=CYAN, linewidth=1.0, label='P-Wave Signal')
    ax1.set_ylabel('Acceleration (g)', color='white', fontsize=11)
    ax1.set_title('Live Sensor Data', color=CYAN, fontsize=13, fontweight='bold')
    ax1.legend(loc='upper right', fontsize=9, framealpha=0.3)
    ax1.set_ylim(-2.0, 2.0)
    
    line_sta, = ax2.plot([], [], color=GREEN, linewidth=1.0, label='STA')
    line_lta, = ax2.plot([], [], color=YELLOW, linewidth=1.0, label='LTA')
    ax2.set_ylabel('Average', color='white', fontsize=11)
    ax2.set_title('STA / LTA Averages', color=GREEN, fontsize=13, fontweight='bold')
    ax2.legend(loc='upper right', fontsize=9, framealpha=0.3)
    ax2.set_ylim(0, 1.5)
    
    line_ratio, = ax3.plot([], [], color=GREEN, linewidth=1.2, label='STA/LTA Ratio')
    trigger_line = ax3.axhline(y=STA_LTA_TRIG, color=RED, linestyle='--', 
                                linewidth=1.5, label=f'Trigger = {STA_LTA_TRIG}')
    ax3.set_ylabel('Ratio', color='white', fontsize=11)
    ax3.set_xlabel('Sample Index', color='white', fontsize=11)
    ax3.set_title('STA/LTA Ratio (Earthquake Detection)', color=RED, fontsize=13, fontweight='bold')
    ax3.legend(loc='upper right', fontsize=9, framealpha=0.3)
    ax3.set_ylim(0, 15)
    
    # Status text
    status_text = ax1.text(0.02, 0.95, '', transform=ax1.transAxes, fontsize=12,
                           verticalalignment='top', color='white', fontfamily='monospace',
                           bbox=dict(boxstyle='round', facecolor='#1a1a3a', alpha=0.8))
    
    def animate(frame):
        if len(samples) < 2:
            return line_sample, line_sta, line_lta, line_ratio, status_text
        
        x = np.arange(len(samples))
        
        line_sample.set_data(x, list(samples))
        line_sta.set_data(x, list(sta_vals))
        line_lta.set_data(x, list(lta_vals))
        line_ratio.set_data(x, list(ratio_vals))
        
        for ax in [ax1, ax2, ax3]:
            ax.set_xlim(0, max(len(samples), 100))
        
        # Auto-scale Y
        if samples:
            s_max = max(abs(min(samples)), abs(max(samples)), 0.5)
            ax1.set_ylim(-s_max * 1.2, s_max * 1.2)
        if sta_vals:
            ax2.set_ylim(0, max(max(sta_vals), max(lta_vals), 0.1) * 1.3)
        if ratio_vals:
            ax3.set_ylim(0, max(max(ratio_vals), STA_LTA_TRIG + 1) * 1.1)
        
        # Status
        current_ratio = ratio_vals[-1] if ratio_vals else 0
        status = "TRIGGERED" if is_triggered else "Normal"
        color = RED if is_triggered else GREEN
        status_text.set_text(f"Samples: {len(samples)}  |  Ratio: {current_ratio:.1f}  |  {status}")
        status_text.set_color(color)
        
        return line_sample, line_sta, line_lta, line_ratio, status_text
    
    ani = animation.FuncAnimation(fig, animate, interval=50, blit=False, cache_frame_data=False)
    
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    print("[PLOTTER] Live plot started! Press the USER button on the board to trigger P-Wave.")
    plt.show()
