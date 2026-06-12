struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
};

void __fastcall set_matrix_rotation_identity(TransformMatrix* transform)
{
    transform->position.w = 1.0f;
    transform->basis_forward.z = 1.0f;
    transform->basis_up.y = 1.0f;
    transform->basis_right.x = 1.0f;
    transform->basis_forward.w = 0.0f;
    transform->basis_forward.y = 0.0f;
    transform->basis_forward.x = 0.0f;
    transform->basis_up.w = 0.0f;
    transform->basis_up.z = 0.0f;
    transform->basis_up.x = 0.0f;
    transform->basis_right.w = 0.0f;
    transform->basis_right.z = 0.0f;
    transform->basis_right.y = 0.0f;
}
