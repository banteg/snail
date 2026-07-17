// Authored cRVapour trail renderer, exact Windows owner.
#ifndef VAPOUR_H
#define VAPOUR_H

#include "bod_types.h"

struct Object;

class Vapour : public RenderableBod {
public:
    void update_vapour(); // @ 0x4425f0, cRVapour::AI
    void initialize_vapour(Object* unused, float half_width); // @ 0x442500
    void reset_vapour(float* z_floor);                    // @ 0x442540
    void add_vapour_point(const TransformMatrix* point);  // @ 0x442560

    int point_count;  // +0x80
    int capacity;     // +0x84
    union {
        int half_width_bits; // +0x88, initializer/raw callsite view
        float half_width;    // +0x88, update_vapour render width
    };
    float* z_floor; // +0x8c, optional position-z clamp source
    TransformMatrix* points; // +0x90
};

typedef char Vapour_must_be_0x94[(sizeof(Vapour) == 0x94) ? 1 : -1];

#endif
