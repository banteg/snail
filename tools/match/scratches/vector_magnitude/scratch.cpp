// vector_magnitude @ 0x44ccf0 (thiscall)

#include "vector3.h"

float square_root(float value);

float Vector3::vector_magnitude()
{
    float magnitude = square_root(x * x + y * y + z * z);
    return magnitude;
}
