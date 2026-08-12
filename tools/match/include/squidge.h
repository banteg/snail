// Authored cRSquidge, exact 0x18-byte two-axis spring oscillator.
#ifndef SQUIDGE_H
#define SQUIDGE_H

class cRSquidge {
public:
    void Init();               // @ 0x444960
    void StartY(float amount); // @ 0x444980
    void StartZ(float amount); // @ 0x4449a0
    void AI();                 // @ 0x4449c0

    float y_output; // +0x00
    float y_velocity; // +0x04
    float y_phase; // +0x08
    float z_output; // +0x0c
    float z_velocity; // +0x10
    float z_phase; // +0x14
};

typedef cRSquidge Squidge;
typedef char Squidge_must_be_0x18[
    (sizeof(cRSquidge) == 0x18) ? 1 : -1];

#endif
