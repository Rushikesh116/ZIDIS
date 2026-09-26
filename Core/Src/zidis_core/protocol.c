#include "zidis_core/protocol.h"
#include <string.h>

#define BEACON_INTERVAL_MS 1000

void Protocol_Init(ProtocolState_t *state) {
    memset(state, 0, sizeof(ProtocolState_t));
    for (int i = 0; i < ZIDIS_MAX_NODES; i++) {
        state->nodes[i].status = NODE_DEAD;
        state->nodes[i].highest_claim.confidence = -1.0f;
    }
    // Self is always ALIVE
    state->nodes[ZIDIS_NODE_ID_SELF].status = NODE_ALIVE;
    state->current_alert = ALERT_NONE;
}

void Protocol_Tick(ProtocolState_t *state, uint32_t time_ms) {
    state->current_time_ms = time_ms;

    // 1. Ageing of nodes and claims
    for (int i = 0; i < ZIDIS_MAX_NODES; i++) {
        // Heartbeat timeout logic (Skip for self)
        if (i != ZIDIS_NODE_ID_SELF && state->nodes[i].status != NODE_DEAD) {
            uint32_t elapsed = time_ms - state->nodes[i].last_beacon_rx_time;
            if (elapsed > (BEACON_INTERVAL_MS * 5)) {
                state->nodes[i].status = NODE_DEAD;
                state->nodes[i].missed_beacons = 5;
            } else if (elapsed > (BEACON_INTERVAL_MS * 3)) {
                state->nodes[i].status = NODE_SUSPECT;
                state->nodes[i].missed_beacons = 3;
            }
        }
        
        // Claim sliding window logic
        if (state->nodes[i].highest_claim.confidence >= 0.0f) {
            uint32_t claim_age = time_ms - state->nodes[i].highest_claim.timestamp_ms;
            if (claim_age > ZIDIS_SLIDING_WINDOW_MS) {
                // Expire claim
                state->nodes[i].highest_claim.confidence = -1.0f;
                state->nodes[i].highest_claim.event_class = EVENT_NOISE;
            }
        }
    }
}

void Protocol_OnBeaconRx(ProtocolState_t *state, const BeaconPacket_t *beacon) {
    if (beacon->source_node < ZIDIS_MAX_NODES) {
        state->nodes[beacon->source_node].status = NODE_ALIVE;
        state->nodes[beacon->source_node].last_beacon_rx_time = state->current_time_ms;
        state->nodes[beacon->source_node].missed_beacons = 0;
    }
}

void Protocol_OnClaimRx(ProtocolState_t *state, const ClaimPacket_t *claim) {
    if (claim->source_node < ZIDIS_MAX_NODES) {
        // Only highest confidence per source per class is retained in window
        if (claim->event_class == EVENT_EARTHQUAKE) {
            if (claim->confidence >= state->nodes[claim->source_node].highest_claim.confidence) {
                state->nodes[claim->source_node].highest_claim = *claim;
            }
        }
    }
}

AlertLevel_t Protocol_EvaluateQuorum(ProtocolState_t *state) {
    int alive_count = 0;
    int agreeing_count = 0;
    float aggregate_confidence = 0.0f;

    // Count alive nodes
    for (int i = 0; i < ZIDIS_MAX_NODES; i++) {
        if (state->nodes[i].status == NODE_ALIVE) {
            alive_count++;
            if (state->nodes[i].highest_claim.event_class == EVENT_EARTHQUAKE && 
                state->nodes[i].highest_claim.confidence > 0.0f) {
                agreeing_count++;
                aggregate_confidence += state->nodes[i].highest_claim.confidence;
            }
        }
    }

    // Dynamic quorum threshold
    int quorum_threshold = alive_count / 2 + 1; // Simple majority
    if (quorum_threshold < ZIDIS_QUORUM_FLOOR) {
        quorum_threshold = ZIDIS_QUORUM_FLOOR;
    }

    AlertLevel_t new_alert = ALERT_NONE;

    if (agreeing_count > 0) {
        if (agreeing_count == 1 && state->nodes[ZIDIS_NODE_ID_SELF].highest_claim.event_class == EVENT_EARTHQUAKE) {
            // Only we saw it
            new_alert = ALERT_L1_LOCAL;
            if (alive_count == 1) {
                new_alert = ALERT_UNCONFIRMED; // Partitioned minority
            }
        } else if (agreeing_count >= quorum_threshold) {
            if (aggregate_confidence > (1.5f * quorum_threshold)) { // Arbitrary strength gate
                new_alert = ALERT_L3_SEVERE;
            } else {
                new_alert = ALERT_L2_CORROBORATED;
            }
        } else {
            new_alert = ALERT_L1_LOCAL;
        }
    }

    if (new_alert > state->current_alert || new_alert == ALERT_NONE) {
        state->current_alert = new_alert;
    }
    
    return state->current_alert;
}
