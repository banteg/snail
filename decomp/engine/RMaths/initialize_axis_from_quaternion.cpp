// initialize_axis_from_quaternion @ 0x44d580 (thiscall)

#include "axis.h"
#include "quaternion.h"
#include "rmath_random.h"

void tAxis::operator=(const tQuaternian& quaternion)
{
    float half_angle = ACos(quaternion.w);
    x = quaternion.x / Sin(half_angle);
    y = quaternion.y / Sin(half_angle);
    z = quaternion.z / Sin(half_angle);
    angle = half_angle + half_angle;
}
