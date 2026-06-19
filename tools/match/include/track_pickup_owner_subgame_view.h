// Narrow subgame view used by track pickups. This is the embedded subgame gate
// at +0x09, not the UI/global pause gate at root Game +0x74621.
#ifndef TRACK_PICKUP_OWNER_SUBGAME_VIEW_H
#define TRACK_PICKUP_OWNER_SUBGAME_VIEW_H

struct TrackPickupOwnerSubgameView {
    char unknown_00[0x09];
    unsigned char subgame_pause_gate; // +0x09
};

#endif
