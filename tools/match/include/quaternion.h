// Shared four-float quaternion view used by the rotation conversion helpers.
#ifndef QUATERNION_H
#define QUATERNION_H

struct AxisAngle;
struct TransformMatrix;

struct Quaternion {
    Quaternion(); // out-of-line default constructor used by interpolation
    void operator=(const AxisAngle& axis); // @ 0x44d530
    Quaternion(const TransformMatrix& matrix); // @ 0x44d5d0

    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0c
};

typedef char Quaternion_must_be_0x10[(sizeof(Quaternion) == 0x10) ? 1 : -1];

#endif
