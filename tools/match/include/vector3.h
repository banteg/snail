#ifndef VECTOR3_H
#define VECTOR3_H

#include "transform_matrix_fwd.h"

// Authored three-float vector owner retained by Android and iOS. Vector3
// remains a compatibility typedef for matcher sources not yet migrated.
struct tVector {
    float x;
    float y;
    float z;

    tVector() {}
    tVector(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    // Android retains this authored tVector(float*) constructor; Windows
    // inlines the same three-lane copy where it is used.
    tVector(float* values) : x(values[0]), y(values[1]), z(values[2]) {}

    tVector operator*(float scale) const
    {
        tVector result;
        result.x = x * scale;
        result.y = y * scale;
        result.z = z * scale;
        return result;
    }

    tVector& operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    tVector operator*(const tMatrix& matrix) const; // @ 0x44cac0
    void operator*=(tMatrix matrix); // @ 0x44cb90, matrix by value

    tVector& operator+=(const tVector& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    int zero_vector3(); // @ 0x410710, thiscall
    static double __stdcall Dot(
        const tVector& lhs, const tVector& rhs); // @ 0x44cb50
    float Normalize(); // @ 0x44cca0
    float Normalize(const tVector& source); // @ 0x44cd20
    float Dot(const tVector& rhs); // @ 0x44cb70
    void Cross(const tVector& lhs, const tVector& rhs); // @ 0x44cd40
    float Magnitude() const; // @ 0x44ccf0
    // ABI compatibility view for the exact Bod caller that dereferences the
    // hidden-return EAX pointer. The owned definition is operator* above.
    tVector* multiply_vector_by_matrix_copy(
        tVector* out, const tMatrix* matrix) const; // @ 0x44cac0
    tVector& Rotate(const tMatrix& matrix); // @ 0x44cc20
};

typedef tVector Vector3;
typedef char tVector_must_be_0x0c[(sizeof(tVector) == 0x0c) ? 1 : -1];

// Shared by-value tVector arithmetic, independently closed by exact callers.
inline tVector operator+(const tVector& lhs, const tVector& rhs)
{
    tVector result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

inline tVector operator-(const tVector& lhs, const tVector& rhs)
{
    tVector result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

#endif
