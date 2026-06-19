#include "vector3.h"

float __fastcall normalize_vector(void* vector);

float Vector3::normalize_vector_from_source(const Vector3* source)
{
    *this = *source;
    return ::normalize_vector(this);
}
