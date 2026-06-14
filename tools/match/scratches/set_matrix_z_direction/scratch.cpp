// set_matrix_z_direction @ 0x44d410 (thiscall)

struct Vec3 {
    float x;
    float y;
    float z;

    float normalize_vector_from_source(const Vec3* source);
    float normalize_vector();
    void cross_vectors(const Vec3* lhs, const Vec3* rhs);
};

struct TransformMatrix {
    Vec3 basis_right;
    float pad_0c;
    Vec3 basis_up;
    float pad_1c;
    Vec3 basis_forward;

    void set_matrix_z_direction(const Vec3* direction);
};

void TransformMatrix::set_matrix_z_direction(const Vec3* direction)
{
    Vec3 right;
    Vec3 forward;
    Vec3* up = &basis_up;

    if (forward.normalize_vector_from_source(direction) != 0.0f) {
        basis_forward.x = forward.x;
        basis_forward.y = forward.y;
        basis_forward.z = forward.z;

        if (forward.x == 0.0f && forward.z == 0.0f) {
            right.x = 1.0f;
            right.z = 0.0f;
        } else {
            right.z = -forward.x;
            right.x = forward.z;
        }

        right.y = 0.0f;
        right.normalize_vector();
        basis_right.x = right.x;
        basis_right.y = right.y;
        basis_right.z = right.z;
        up->cross_vectors(&forward, &right);
    }
}
