// initialize_quaternion_from_axis @ 0x44d530 (thiscall)

#include "axis.h"

float sine(float angle);
float cosine(float angle);

struct Quaternion {
    float x;
    float y;
    float z;
    float w;

    void initialize_quaternion_from_axis(const Axis* axis);
};

void Quaternion::initialize_quaternion_from_axis(const Axis* axis)
{
    double scale = sine(axis->angle * 0.5f);
    x = (float)(scale * axis->x);
    y = (float)(scale * axis->y);
    z = (float)(scale * axis->z);

    w = cosine(axis->angle * 0.5f);
}
