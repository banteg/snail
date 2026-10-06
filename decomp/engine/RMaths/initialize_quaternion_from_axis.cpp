// initialize_quaternion_from_axis @ 0x44d530 (thiscall)

#include "axis.h"
#include "quaternion.h"

float Sin(float angle);
float Cos(float angle);

void tQuaternian::operator=(const tAxis& axis)
{
    double scale = Sin(axis.angle * 0.5f);
    x = (float)scale * axis.x;
    y = (float)scale * axis.y;
    z = (float)scale * axis.z;

    w = Cos(axis.angle * 0.5f);
}
