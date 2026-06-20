// Shared four-float quaternion view used by the rotation conversion helpers.
#ifndef QUATERNION_H
#define QUATERNION_H

struct Axis;

struct Quaternion {
    Quaternion(); // out-of-line default constructor used by interpolation
    Quaternion(const float* matrix_rows); // initialize_quaternion_from_matrix

    void initialize_quaternion_from_axis(const Axis* axis); // @ 0x44d530
    Quaternion* initialize_quaternion_from_matrix(const float* matrix_rows); // @ 0x44d5d0

    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0c
};

typedef char Quaternion_must_be_0x10[(sizeof(Quaternion) == 0x10) ? 1 : -1];

#endif
