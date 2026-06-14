// orthogonalize_matrix @ 0x44d3d0 (fastcall)

struct Vec3 {
    float x;
    float y;
    float z;

    void cross_vectors(const Vec3* lhs, const Vec3* rhs);
};

struct TransformMatrix {
    Vec3 basis_right;
    float pad_0c;
    Vec3 basis_up;
    float pad_1c;
    Vec3 basis_forward;
};

float __fastcall normalize_vector(Vec3* vector);

void __fastcall orthogonalize_matrix(TransformMatrix* transform)
{
    Vec3* right = &transform->basis_right;
    Vec3* up = &transform->basis_up;
    Vec3* forward = &transform->basis_forward;

    normalize_vector(right);
    normalize_vector(up);
    normalize_vector(forward);
    right->cross_vectors(up, forward);
    forward->cross_vectors(right, up);
}
