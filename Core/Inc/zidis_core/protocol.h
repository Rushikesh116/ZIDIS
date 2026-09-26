#ifndef ZIDIS_CORE_PROTOCOL_H
#define ZIDIS_CORE_PROTOCOL_H

#include "config.h"

typedef enum {
    NODE_ALIVE,
    NODE_SUSPECT,
    NODE_DEAD
} NodeStatus_t;

typedef enum {
    ALERT_NONE,
    ALERT_L1_LOCAL,
    ALERT_L2_CORROBORATED,
    ALERT_L3_SEVERE,
    ALERT_UNCONFIRMED
} AlertLevel_t;

typedef struct {
    NodeStatus_t status;
    uint32_t     last_beacon_rx_time;
    uint32_t     missed_beacons;
    
    // Claim window
    ClaimPacket_t highest_claim;
} NodeState_t;

typedef struct {
    NodeState_t nodes[ZIDIS_MAX_NODES];
    uint32_t    current_time_ms;
    
    AlertLevel_t current_alert;
} ProtocolState_t;

void Protocol_Init(ProtocolState_t *state);
void Protocol_Tick(ProtocolState_t *state, uint32_t time_ms);
void Protocol_OnBeaconRx(ProtocolState_t *state, const BeaconPacket_t *beacon);
void Protocol_OnClaimRx(ProtocolState_t *state, const ClaimPacket_t *claim);
AlertLevel_t Protocol_EvaluateQuorum(ProtocolState_t *state);

#endif // ZIDIS_CORE_PROTOCOL_H
