#include "vector3.h"

float Vector3::dot_vector(const Vector3* rhs)
{
    return rhs->z * z + rhs->y * y + rhs->x * x;
}
