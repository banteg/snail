#include "vector3.h"

float tVector::Normalize(const tVector& source)
{
    *this = source;
    return Normalize();
}
