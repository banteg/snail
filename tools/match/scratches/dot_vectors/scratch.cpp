#include "vector3.h"

double __stdcall Vector3::dot_vectors(const Vector3* lhs, const Vector3* rhs)
{
    return lhs->z * rhs->z + lhs->y * rhs->y + lhs->x * rhs->x;
}
