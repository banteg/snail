#include "vector3.h"

double Vector3::dot_vector(const Vector3* rhs)
{
    return rhs->z * z + rhs->y * y + rhs->x * x;
}
