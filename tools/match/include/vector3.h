#ifndef VECTOR3_H
#define VECTOR3_H

struct TransformMatrix;

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    Vector3 operator*(float scale) const
    {
        Vector3 result;
        result.x = x * scale;
        result.y = y * scale;
        result.z = z * scale;
        return result;
    }

    Vector3& operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3 operator*(const TransformMatrix& matrix) const; // @ 0x44cac0
    void operator*=(TransformMatrix matrix); // @ 0x44cb90, matrix by value

    Vector3& operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    int zero_vector3(); // @ 0x410710, thiscall
    static double __stdcall dot_vectors(
        const Vector3& lhs, const Vector3& rhs); // @ 0x44cb50, static tVector::Dot
    float normalize_vector(); // @ 0x44cca0, tVector::Normalize()
    float normalize_vector_from_source(const Vector3& source); // @ 0x44cd20
    float dot_vector(const Vector3& rhs); // @ 0x44cb70
    void cross_vectors(const Vector3& lhs, const Vector3& rhs); // @ 0x44cd40
    // Compatibility view for low-progress path-template callers. The owned
    // definition is the const-reference overload above.
    void cross_vectors(const Vector3* lhs, const Vector3* rhs);
    float vector_magnitude() const; // @ 0x44ccf0, tVector::Magnitude() const
    // ABI compatibility view for the exact Bod caller that dereferences the
    // hidden-return EAX pointer. The owned definition is operator* above.
    Vector3* multiply_vector_by_matrix_copy(Vector3* out, const TransformMatrix* matrix) const; // @ 0x44cac0
    Vector3& rotate_vector_by_matrix(const TransformMatrix& matrix); // @ 0x44cc20
};

// Shared by-value tVector arithmetic, independently closed by exact callers.
inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

#endif
