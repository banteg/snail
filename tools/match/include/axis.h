#ifndef AXIS_H
#define AXIS_H

struct Quaternion;

// Windows constructor callsites preserve the AxisAngle owner name; Android's
// equivalent math type is tAxis, retained below as a compatibility alias.
struct AxisAngle {
    AxisAngle(); // folded trivial constructor @ 0x44db50

    float x;     // +0x00
    float y;     // +0x04
    float z;     // +0x08
    float angle; // +0x0c

    void initialize_axis_from_quaternion(const Quaternion* quaternion); // @ 0x44d580
};

typedef AxisAngle Axis;

typedef char AxisAngle_must_be_0x10[
    (sizeof(AxisAngle) == 0x10) ? 1 : -1];

#endif
