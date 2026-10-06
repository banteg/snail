// normalize_vector @ 0x44cca0 — tVector::Normalize()

#include "vector3.h"

float Sqrt(float value);

float tVector::Normalize()
{
    float length = Sqrt((float)tVector::Dot(*this, *this));
    if (length == 0.0f) {
        return 0.0f;
    }

    float scale = 1.0f / length;
    x = scale * x;
    y = scale * y;
    z = scale * z;
    return length;
}
