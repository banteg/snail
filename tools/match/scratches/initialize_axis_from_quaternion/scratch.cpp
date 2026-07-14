// initialize_axis_from_quaternion @ 0x44d580 (thiscall)

#include "axis.h"
#include "quaternion.h"

float sine(float angle);
float arccosine(float value);

void AxisAngle::initialize_axis_from_quaternion(const Quaternion* quaternion)
{
    float half_angle = arccosine(quaternion->w);
    x = quaternion->x / sine(half_angle);
    y = quaternion->y / sine(half_angle);
    z = quaternion->z / sine(half_angle);
    angle = half_angle + half_angle;
}
