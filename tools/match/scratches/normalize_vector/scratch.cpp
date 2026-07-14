// Vector3::normalize_vector @ 0x44cca0

#include "vector3.h"

double __stdcall dot_vectors(const Vector3* lhs, const Vector3* rhs);
float square_root(float value);

float Vector3::normalize_vector()
{
    float length = square_root((float)dot_vectors(this, this));
    if (length == 0.0f) {
        return 0.0f;
    }

    float scale = 1.0f / length;
    x = scale * x;
    y = scale * y;
    z = scale * z;
    return length;
}
