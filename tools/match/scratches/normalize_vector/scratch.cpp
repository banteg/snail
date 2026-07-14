// Vector3::normalize_vector @ 0x44cca0

#include "vector3.h"

float square_root(float value);

float Vector3::normalize_vector()
{
    float length = square_root((float)Vector3::dot_vectors(this, this));
    if (length == 0.0f) {
        return 0.0f;
    }

    float scale = 1.0f / length;
    x = scale * x;
    y = scale * y;
    z = scale * z;
    return length;
}
