#ifndef FIREWORK_H
#define FIREWORK_H

#include "vector3.h"

// Authored cRFireWork. This empty child occupies one byte immediately before
// cRSubGoldy's damage-retrigger timers; Shoot does not read the receiver, but
// native callers still use the C++ thiscall surface.
class FireWork {
public:
    void firework_shoot(
        Vector3* position, int owner, int texture_id, int count); // @ 0x441dd0, cRFireWork::Shoot
};

typedef char FireWork_must_be_1[(sizeof(FireWork) == 1) ? 1 : -1];

#endif
