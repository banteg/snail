// Shared 4x4 transform matrix view. This is the row layout used by the math
// routines and by renderable bodies at +0x38.
#ifndef TRANSFORM_MATRIX_H
#define TRANSFORM_MATRIX_H

#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;   // +0x00
    Vec4 basis_up;      // +0x10
    Vec4 basis_forward; // +0x20
    Vec4 position;      // +0x30
};

typedef char TransformMatrix_must_be_0x40[(sizeof(TransformMatrix) == 0x40) ? 1 : -1];

void __fastcall set_matrix_identity(TransformMatrix* transform); // @ 0x44d210

#endif
