#include "vector3.h"

float tVector::Dot(const tVector& rhs)
{
    return rhs.z * z + rhs.y * y + rhs.x * x;
}
