// Narrow view of the owning game used by track pickups.
#ifndef TRACK_PICKUP_OWNER_GAME_VIEW_H
#define TRACK_PICKUP_OWNER_GAME_VIEW_H

struct TrackPickupOwnerGameView {
    char unknown_00[0x09];
    unsigned char pause_gate; // +0x09
};

#endif
