// Small damped spring helper reset from initialize_subgoldy.
#ifndef SPRING_FLOAT_H
#define SPRING_FLOAT_H

class SpringFloat {
public:
    void reset_spring_float(); // @ 0x41aa30

    float output;          // +0x00
    float velocity;        // +0x04
    float phase;           // +0x08
    float target_output;   // +0x0c
    float target_velocity; // +0x10
};

typedef char SpringFloat_must_be_0x14[(sizeof(SpringFloat) == 0x14) ? 1 : -1];

#endif
