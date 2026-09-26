#include "zidis_core/dsp.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846f

// Simple Radix-2 FFT (in-place)
// Assumes n is a power of 2. For ZIDIS, n = 128.
static void fft_radix2(float real[], float imag[], int n) {
    int i, j, k;
    float u_r, u_i, w_r, w_i, t_r, t_i;

    // Bit-reversal permutation
    j = 0;
    for (i = 0; i < n - 1; i++) {
        if (i < j) {
            float tmp = real[i];
            real[i] = real[j];
            real[j] = tmp;
            
            tmp = imag[i];
            imag[i] = imag[j];
            imag[j] = tmp;
        }
        k = n / 2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;
    }

    // Cooley-Tukey decimation-in-time radix-2 FFT
    for (k = 1; k < n; k *= 2) {
        w_r = cosf(PI / k);
        w_i = -sinf(PI / k);
        u_r = 1.0f;
        u_i = 0.0f;

        for (j = 0; j < k; j++) {
            for (i = j; i < n; i += 2 * k) {
                t_r = u_r * real[i + k] - u_i * imag[i + k];
                t_i = u_r * imag[i + k] + u_i * real[i + k];
                
                real[i + k] = real[i] - t_r;
                imag[i + k] = imag[i] - t_i;
                real[i] += t_r;
                imag[i] += t_i;
            }
            // Complex multiplication
            float tmp_u_r = u_r;
            u_r = tmp_u_r * w_r - u_i * w_i;
            u_i = tmp_u_r * w_i + u_i * w_r;
        }
    }
}

void Dsp_Init(DspState_t *state) {
    state->sta = 0.0f;
    state->lta = 0.0f;
    state->is_triggered = false;
    state->trigger_sta_lta_ratio = 0.0f;
    state->window_idx = 0;
    state->window_full = false;
    memset(state->window, 0, sizeof(state->window));
}

// Processes one sample (at 100Hz). Returns true if window is full and ready for extraction.
bool Dsp_ProcessSample(DspState_t *state, float sample) {
    float abs_sample = fabsf(sample);

    // Exponential moving average for STA and LTA
    // alpha = 1 - exp(-dt / tau)
    // dt = 0.01s (100Hz)
    // tau_sta = 0.5s -> alpha_sta = 1 - exp(-0.01/0.5) = 1 - exp(-0.02) = 0.0198
    // tau_lta = 10s -> alpha_lta = 1 - exp(-0.01/10) = 1 - exp(-0.001) = 0.001
    float alpha_sta = 0.0198f;
    float alpha_lta = 0.001f;

    state->sta = (alpha_sta * abs_sample) + ((1.0f - alpha_sta) * state->sta);
    
    // "Critically, the long-term average is frozen while triggered."
    if (!state->is_triggered) {
        state->lta = (alpha_lta * abs_sample) + ((1.0f - alpha_lta) * state->lta);
    }

    // Guard against division by zero
    float lta_safe = state->lta > 0.0001f ? state->lta : 0.0001f;
    float ratio = state->sta / lta_safe;

    // Trigger logic with hysteresis
    if (!state->is_triggered) {
        if (ratio > STA_LTA_TRIG_THRESH) {
            state->is_triggered = true;
            state->trigger_sta_lta_ratio = ratio; // Capture trigger ratio
            state->window_idx = 0;
            state->window_full = false;
        }
    } else {
        if (ratio < STA_LTA_DETRIG_THRESH) {
            state->is_triggered = false;
        }
    }

    // Collect 128 samples after trigger
    if (state->is_triggered && !state->window_full) {
        state->window[state->window_idx++] = sample;
        if (state->window_idx >= ZIDIS_WINDOW_SIZE) {
            state->window_full = true;
            // We do not de-trigger immediately, wait for ratio to drop.
            // But we do signal that we have a window ready for ML.
            return true; 
        }
    }
    
    return false;
}

void Dsp_ExtractFeatures(DspState_t *state, ZidisFeatures_t *out_features) {
    float real[ZIDIS_WINDOW_SIZE];
    float imag[ZIDIS_WINDOW_SIZE];

    // Apply simple windowing (e.g., Hanning) or just copy
    for (int i = 0; i < ZIDIS_WINDOW_SIZE; i++) {
        // Hanning window to reduce spectral leakage
        float multiplier = 0.5f * (1.0f - cosf(2.0f * PI * i / (ZIDIS_WINDOW_SIZE - 1)));
        real[i] = state->window[i] * multiplier;
        imag[i] = 0.0f;
    }

    fft_radix2(real, imag, ZIDIS_WINDOW_SIZE);

    // Compute power spectrum
    // 128-point FFT gives 64 bins (Nyquist = 50Hz, each bin = 50/64 = 0.78125Hz)
    // Bands: 0-2, 2-5, 5-10, 10-20, 20-35, 35-50 Hz
    float band_energies[6] = {0.0f};
    float total_energy = 0.0f;

    for (int i = 1; i < ZIDIS_WINDOW_SIZE / 2; i++) { // Skip DC (bin 0)
        float freq = i * 0.78125f;
        float power = (real[i]*real[i]) + (imag[i]*imag[i]);
        
        int band = -1;
        if (freq < 2.0f)       band = 0;
        else if (freq < 5.0f)  band = 1;
        else if (freq < 10.0f) band = 2;
        else if (freq < 20.0f) band = 3;
        else if (freq < 35.0f) band = 4;
        else if (freq <= 50.0f) band = 5;

        if (band >= 0) {
            band_energies[band] += power;
            total_energy += power;
        }
    }

    if (total_energy < 0.0001f) total_energy = 1.0f; // avoid div by zero

    for (int i = 0; i < 6; i++) {
        out_features->features[i] = band_energies[i] / total_energy; // Fractional energy
    }
    
    // 7th feature is STA/LTA ratio
    out_features->features[6] = state->trigger_sta_lta_ratio;
}
