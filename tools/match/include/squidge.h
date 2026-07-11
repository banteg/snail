// Authored cRSquidge, exact 0x18-byte two-axis spring oscillator.
#ifndef SQUIDGE_H
#define SQUIDGE_H

class Squidge {
public:
    // Stable Windows harness name; cross-port source name is cRSquidge::Init.
    void initialize_score_stats(); // @ 0x444960
    void start_squidge_y(float amount); // @ 0x444980, cRSquidge::StartY
    void start_squidge_z(float amount); // @ 0x4449a0, cRSquidge::StartZ
    void update_squidge(); // @ 0x4449c0, cRSquidge::AI

    float y_output; // +0x00
    float y_velocity; // +0x04
    float y_phase; // +0x08
    float z_output; // +0x0c
    float z_velocity; // +0x10
    float z_phase; // +0x14
};

typedef char Squidge_must_be_0x18[(sizeof(Squidge) == 0x18) ? 1 : -1];

#endif
