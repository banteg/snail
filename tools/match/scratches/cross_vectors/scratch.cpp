// cross_vectors @ 0x44cd40 (thiscall)

#include "vector3.h"

void Vector3::cross_vectors(const Vector3* lhs, const Vector3* rhs)
{
    static Vector3 result;

    result.x = lhs->y * rhs->z - rhs->y * lhs->z;
    result.y = lhs->z * rhs->x - lhs->x * rhs->z;
    result.z = rhs->y * lhs->x - lhs->y * rhs->x;
    *this = result;
}
