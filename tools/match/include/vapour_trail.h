// Vapour trail runtime view, partial.
#ifndef VAPOUR_TRAIL_H
#define VAPOUR_TRAIL_H

class VapourTrailOwner {
public:
    char unknown_00[0x54];
    int max_points; // +0x54
};

class VapourTrail {
public:
    virtual int update_vapour();
    int initialize_vapour(int unused, int point_stride); // @ 0x442500
    int reset_vapour(int mode);                          // @ 0x442540

    int flags; // +0x04
    char unknown_08[0x24 - 0x08];
    VapourTrailOwner* owner; // +0x24
    char unknown_28[0x80 - 0x28];
    int point_count;  // +0x80
    int capacity;     // +0x84
    int point_stride; // +0x88
    int mode;         // +0x8c
    void* points;     // +0x90
};

#endif
