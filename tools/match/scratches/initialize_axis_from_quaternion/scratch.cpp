// initialize_axis_from_quaternion @ 0x44d580 (thiscall)

#include "axis.h"

float sine(float angle);
float arccosine(float value);

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};

void Axis::initialize_axis_from_quaternion(const Quaternion* quaternion)
{
    float half_angle = arccosine(quaternion->w);
    x = quaternion->x / sine(half_angle);
    y = quaternion->y / sine(half_angle);
    z = quaternion->z / sine(half_angle);
    angle = half_angle + half_angle;
}
