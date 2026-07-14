// Shared lifecycle used by the authored cRSubSpeedUp, cRSubHealth, and
// cRJetPack track-pickup owners.
#ifndef TRACK_PICKUP_STATE_H
#define TRACK_PICKUP_STATE_H

enum TrackPickupState {
    TRACK_PICKUP_STATE_INACTIVE = 0,
    TRACK_PICKUP_STATE_ACTIVE = 1,
    TRACK_PICKUP_STATE_TEARDOWN_PENDING = 2,
};

#endif
