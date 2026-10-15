// Shared four-float quaternion view used by the rotation conversion helpers.
#ifndef QUATERNION_H
#define QUATERNION_H

#include "axis_fwd.h"
#include "quaternion_fwd.h"
#include "transform_matrix_fwd.h"

struct tQuaternian {
    tQuaternian(); // folded trivial constructor @ 0x44db50
    // Windows emits this conversion as a void assignment. Android exposes
    // the analogous body as a constructor, but adding a receiver return here
    // would be fakematching rather than recovering the Windows source shape.
    void operator=(const tAxis& axis); // @ 0x44d530
    tQuaternian(const tMatrix& matrix); // @ 0x44d5d0

    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0c
};

typedef char tQuaternian_must_be_0x10[
    (sizeof(tQuaternian) == 0x10) ? 1 : -1];

#endif
