#ifndef TWINKLE_H
#define TWINKLE_H

#include "border_fwd.h"

class cRTwinkle {
public:
    int state; // +0x00
    int unused_04; // +0x04
    float delay_progress; // +0x08
    float delay_step; // +0x0c
    float alpha; // +0x10
    float target_alpha; // +0x14
    float angle; // +0x18
    float angle_step; // +0x1c
    float x; // +0x20
    float y; // +0x24
    float size; // +0x28
    cRBorder* owner_widget; // +0x2c, borrowed authored cRBorder

    void Draw(); // @ 0x404070
    void AI(); // @ 0x404080
};

typedef cRTwinkle Twinkle;
typedef char Twinkle_must_be_0x30[
    (sizeof(cRTwinkle) == 0x30) ? 1 : -1];

#endif
