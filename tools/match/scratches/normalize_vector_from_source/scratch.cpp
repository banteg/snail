#include "vector3.h"

float Vector3::normalize_vector_from_source(const Vector3& source)
{
    *this = source;
    return normalize_vector();
}
