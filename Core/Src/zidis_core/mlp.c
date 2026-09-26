#include "zidis_core/mlp.h"
#include <math.h>

// 7-8-3 MLP architecture
#define INPUT_NODES  7
#define HIDDEN_NODES 8
#define OUTPUT_NODES 3

// Mock weights (in a real system, these would be exported from the Python training script)
// Weights for Hidden Layer (7 inputs * 8 nodes = 56 weights) + 8 biases
static const float w_hidden[HIDDEN_NODES][INPUT_NODES] = {
    {0.1f, -0.2f, 0.3f, -0.4f, 0.5f, -0.6f, 0.7f},
    {-0.1f, 0.2f, -0.3f, 0.4f, -0.5f, 0.6f, -0.7f},
    {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f},
    {-0.1f, -0.1f, -0.1f, -0.1f, -0.1f, -0.1f, -0.1f},
    {0.5f, 0.0f, -0.5f, 0.0f, 0.5f, 0.0f, -0.5f},
    {0.0f, 0.5f, 0.0f, -0.5f, 0.0f, 0.5f, 0.0f},
    {0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f},
    {-0.2f, -0.2f, -0.2f, -0.2f, -0.2f, -0.2f, -0.2f}
};
static const float b_hidden[HIDDEN_NODES] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};

// Weights for Output Layer (8 inputs * 3 nodes = 24 weights) + 3 biases
static const float w_output[OUTPUT_NODES][HIDDEN_NODES] = {
    {0.1f, 0.2f, 0.3f, 0.4f, -0.1f, -0.2f, -0.3f, -0.4f}, // Class 0: NOISE
    {-0.1f, -0.2f, -0.3f, -0.4f, 0.1f, 0.2f, 0.3f, 0.4f}, // Class 1: IMPULSE
    {0.2f, -0.2f, 0.2f, -0.2f, 0.2f, -0.2f, 0.2f, -0.2f}  // Class 2: EARTHQUAKE
};
static const float b_output[OUTPUT_NODES] = {0.0f, 0.0f, 0.0f};

void Mlp_Init(void) {
    // Initialization if required (e.g., loading weights from flash if not static)
}

EventClass_t Mlp_Classify(const ZidisFeatures_t *features, float *out_confidence) {
    float hidden_layer[HIDDEN_NODES];
    float output_layer[OUTPUT_NODES];

    // Forward pass: Hidden Layer (ReLU activation)
    for (int i = 0; i < HIDDEN_NODES; i++) {
        float sum = b_hidden[i];
        for (int j = 0; j < INPUT_NODES; j++) {
            sum += features->features[j] * w_hidden[i][j];
        }
        // ReLU
        hidden_layer[i] = (sum > 0.0f) ? sum : 0.0f;
    }

    // Forward pass: Output Layer (Linear, then Softmax)
    for (int i = 0; i < OUTPUT_NODES; i++) {
        float sum = b_output[i];
        for (int j = 0; j < HIDDEN_NODES; j++) {
            sum += hidden_layer[j] * w_output[i][j];
        }
        output_layer[i] = sum;
    }

    // Softmax to get probabilities (confidence)
    float max_val = output_layer[0];
    for(int i=1; i<OUTPUT_NODES; i++) {
        if (output_layer[i] > max_val) max_val = output_layer[i];
    }
    
    float sum_exp = 0.0f;
    for(int i=0; i<OUTPUT_NODES; i++) {
        output_layer[i] = expf(output_layer[i] - max_val); // subtract max for numerical stability
        sum_exp += output_layer[i];
    }
    
    int best_class = 0;
    float best_prob = 0.0f;
    for(int i=0; i<OUTPUT_NODES; i++) {
        float prob = output_layer[i] / sum_exp;
        if (prob > best_prob) {
            best_prob = prob;
            best_class = i;
        }
    }

    *out_confidence = best_prob;

    // For testing/mocking, let's inject a fake logic based on STA/LTA ratio to simulate earthquake detection
    // If STA/LTA ratio is extremely high, we'll force it to EARTHQUAKE with high confidence
    if (features->features[6] > 10.0f) {
        *out_confidence = 0.95f;
        return EVENT_EARTHQUAKE;
    }

    return (EventClass_t)best_class;
}
