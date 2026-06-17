#ifndef VECTOR3_H
#define VECTOR3_H

struct TransformMatrix;

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    float normalize_vector(); // thiscall callsite view for @ 0x44cca0
    float normalize_vector_from_source(const Vector3* source); // callsite view for @ 0x44cd20
    double dot_vector(const Vector3* rhs); // @ 0x44cb70
    void cross_vectors(const Vector3* lhs, const Vector3* rhs); // @ 0x44cd40
    float vector_magnitude(); // @ 0x44ccf0, thiscall, returns st0
    void multiply_vector_by_matrix(TransformMatrix matrix); // @ 0x44cb90, matrix by value
    void rotate_vector_by_matrix(const float* matrix); // thiscall, matrix on stack
    Vector3* rotate_vector_by_matrix(const TransformMatrix* matrix); // @ 0x44cc20
};

#endif
