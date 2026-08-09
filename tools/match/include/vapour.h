// Authored cRVapour trail renderer, exact Windows owner.
#ifndef VAPOUR_H
#define VAPOUR_H

#include "bod_types.h"
#include "object_fwd.h"

class cRVapour : public RenderableBod {
public:
    void Init(cRObject* unused, float half_width); // @ 0x442500
    void ReSet(float* z_floor); // @ 0x442540, authored capitalization
    void Add(tMatrix& point); // @ 0x442560
    void AI(); // @ 0x4425f0

    int point_count;  // +0x80
    int capacity;     // +0x84
    union {
        int half_width_bits; // +0x88, initializer/raw callsite view
        float half_width;    // +0x88, AI render width
    };
    float* z_floor; // +0x8c, optional position-z clamp source
    TransformMatrix* points; // +0x90
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRVapour Vapour;

typedef char cRVapour_must_be_0x94[
    (sizeof(cRVapour) == 0x94) ? 1 : -1];
typedef char Vapour_must_be_0x94[(sizeof(Vapour) == 0x94) ? 1 : -1];

#endif
