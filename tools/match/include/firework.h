#ifndef FIREWORK_H
#define FIREWORK_H

#include "vector3.h"

// Empty embedded service object. cRSubGoldy owns one immediately before its
// damage-retrigger timers; Shoot does not read the receiver, but native callers
// still use the C++ thiscall surface.
class FireworkController {
public:
    void firework_shoot(
        Vector3* position, int owner, int texture_id, int count); // @ 0x441dd0, cRFireWork::Shoot
};

typedef char FireworkController_must_be_1[
    (sizeof(FireworkController) == 1) ? 1 : -1];

#endif
