#ifndef AXIS_H
#define AXIS_H

struct Quaternion;

struct Axis {
    float x;     // +0x00
    float y;     // +0x04
    float z;     // +0x08
    float angle; // +0x0c

    void initialize_axis_from_quaternion(const Quaternion* quaternion); // @ 0x44d580
};

typedef char Axis_must_be_0x10[(sizeof(Axis) == 0x10) ? 1 : -1];

#endif
