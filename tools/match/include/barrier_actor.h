// Tutorial barrier actor embedded in cRSubGame.
#ifndef BARRIER_ACTOR_H
#define BARRIER_ACTOR_H

#include "bod_types.h"
#include "player.h"

class cRBarrier : public BodBase {
public:
    void update_barrier_ai(); // @ 0x440f80, cRBarrier::AI

    cRSubGoldy* owner_player; // +0x38, borrowed live-position source
};

typedef cRBarrier BarrierActor;
typedef char BarrierActor_must_be_0x3c[
    (sizeof(cRBarrier) == 0x3c) ? 1 : -1];

#endif
