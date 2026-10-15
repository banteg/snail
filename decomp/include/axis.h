#ifndef AXIS_H
#define AXIS_H

#include "axis_fwd.h"
#include "quaternion_fwd.h"

struct tAxis {
    tAxis(); // folded trivial constructor @ 0x44db50
    void operator=(const tQuaternian& quaternion); // @ 0x44d580

    float x;     // +0x00
    float y;     // +0x04
    float z;     // +0x08
    float angle; // +0x0c

};

typedef char tAxis_must_be_0x10[(sizeof(tAxis) == 0x10) ? 1 : -1];

#endif
