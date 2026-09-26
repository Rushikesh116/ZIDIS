#ifndef ZIDIS_CORE_DSP_H
#define ZIDIS_CORE_DSP_H

#include "config.h"
#include <stdbool.h>

// Feature vector: 6 frequency bands + STA/LTA ratio
#define ZIDIS_NUM_FEATURES 7

typedef struct {
    float features[ZIDIS_NUM_FEATURES];
} ZidisFeatures_t;

// DSP State for continuous processing
typedef struct {
    float sta;
    float lta;
    bool  is_triggered;
    float trigger_sta_lta_ratio;
    
    // Circular buffer for 128 samples (triggered window)
    float window[ZIDIS_WINDOW_SIZE];
    int   window_idx;
    bool  window_full;
} DspState_t;

void Dsp_Init(DspState_t *state);
bool Dsp_ProcessSample(DspState_t *state, float sample);
void Dsp_ExtractFeatures(DspState_t *state, ZidisFeatures_t *out_features);

#endif // ZIDIS_CORE_DSP_H
