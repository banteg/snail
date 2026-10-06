#include "vector3.h"

double __stdcall tVector::Dot(const tVector& lhs, const tVector& rhs)
{
    return lhs.z * rhs.z + lhs.y * rhs.y + lhs.x * rhs.x;
}
