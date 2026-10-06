// cross_vectors @ 0x44cd40 (thiscall) — tVector::Cross

#include "vector3.h"

void tVector::Cross(const tVector& lhs, const tVector& rhs)
{
    static tVector result;

    result.x = lhs.y * rhs.z - rhs.y * lhs.z;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = rhs.y * lhs.x - lhs.y * rhs.x;
    *this = result;
}
