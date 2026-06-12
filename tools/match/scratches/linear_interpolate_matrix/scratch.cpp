// linear_interpolate_matrix @ 0x44da90 (thiscall, ret 0xc)
// tMatrix::LinearInterpolate per Android symbols: rotation interpolated in
// matrix space (invert/multiply/interpolate/premultiply/orthogonalize),
// translation blended linearly.

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix {
    void linear_interpolate_matrix(const TransformMatrix* from, const TransformMatrix* to, float alpha);
    void invert_matrix_from_source(const TransformMatrix* source);
    void multiply_matrix_in_place(const TransformMatrix* rhs);
    void interpolate_matrix_rotation(float alpha);
    void premultiply_matrix_in_place(const TransformMatrix* lhs);
    void orthogonalize_matrix();

    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position; // +0x30
};

void TransformMatrix::linear_interpolate_matrix(
    const TransformMatrix* from, const TransformMatrix* to, float alpha)
{
    invert_matrix_from_source(from);
    multiply_matrix_in_place(to);
    interpolate_matrix_rotation(alpha);
    premultiply_matrix_in_place(from);
    orthogonalize_matrix();
    float ty = alpha * to->position.y;
    float tz = alpha * to->position.z;
    float inv = 1.0f - alpha;
    float fx = inv * from->position.x;
    float fy = inv * from->position.y;
    float fz = inv * from->position.z;
    float ox = fx + alpha * to->position.x;
    position.x = ox;
    float oy = fy + ty;
    position.y = oy;
    float oz = fz + tz;
    position.z = oz;
}
