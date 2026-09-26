#ifndef ZIDIS_CORE_CONFIG_H
#define ZIDIS_CORE_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

// Sampling configuration
#define ZIDIS_SAMPLE_RATE_HZ 100
#define ZIDIS_WINDOW_SIZE    128

// STA/LTA Configuration
#define STA_WINDOW_SAMPLES   50   // 0.5s @ 100Hz
#define LTA_WINDOW_SAMPLES   1000 // 10s @ 100Hz
#define STA_LTA_TRIG_THRESH  3.0f
#define STA_LTA_DETRIG_THRESH 1.5f

// Network / Quorum configuration
#define ZIDIS_NODE_ID_SELF   1
#define ZIDIS_MAX_NODES      8
#define ZIDIS_QUORUM_FLOOR   2
#define ZIDIS_SLIDING_WINDOW_MS 5000

// Event Classes
typedef enum {
    EVENT_NOISE = 0,
    EVENT_IMPULSE = 1,
    EVENT_EARTHQUAKE = 2
} EventClass_t;

// Claim Structure
typedef struct {
    uint8_t  source_node;
    uint32_t sequence_num;
    uint32_t timestamp_ms;
    uint8_t  event_class;
    float    confidence;
} ClaimPacket_t;

// Beacon Structure
typedef struct {
    uint8_t  source_node;
    uint32_t sequence_num;
    uint32_t timestamp_ms;
} BeaconPacket_t;

#endif // ZIDIS_CORE_CONFIG_H
