// Start/completion banner actors embedded in SubgameRuntime.
#ifndef BANNER_H
#define BANNER_H

#include "bod_types.h"
#include "player.h"

class Banner : public BodBase {
public:
    void update_banner(); // @ 0x441d40, cRBanner::AI

    // Android preserves this same tail immediately after its platform BodBase.
    int visibility_mode; // +0x38, 0 start row; 1 completion row
    char unknown_3c[0x54 - 0x3c];
    Player* owner_player; // +0x54, borrowed row-position source
    float phase; // +0x58
    float phase_step; // +0x5c
};

typedef char Banner_must_be_0x60[(sizeof(Banner) == 0x60) ? 1 : -1];

class BannerPool {
public:
    // Fixed start/completion storage owned by SubgameRuntime. The global BOD
    // list only links these objects while the subgame is live.
    Banner slots[2];
};

typedef char BannerPool_must_be_0xc0[
    (sizeof(BannerPool) == 0xc0) ? 1 : -1];

#endif
