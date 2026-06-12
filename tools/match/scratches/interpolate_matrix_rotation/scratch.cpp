// interpolate_matrix_rotation @ 0x44d920 (thiscall, ret 0x4)
// Quaternion-based rotation interpolation: extract quat from the matrix,
// snap near-zero imaginary lanes, convert to axis-angle, scale the angle
// by alpha, recompose. When the axis collapses, rebuild from the snapped
// quaternion directly; when the angle is exactly zero, leave the matrix.

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix;

struct Quaternion {
    Quaternion(); // out-of-line default ctor in the image
    Quaternion(const float* matrix_rows); // initialize_quaternion_from_matrix

    float x;
    float y;
    float z;
    float w;
};

struct AxisAngle {
    AxisAngle(); // out-of-line default ctor in the image

    float x;
    float y;
    float z;
    float angle;
};

void initialize_axis_from_quaternion(AxisAngle* axis, const Quaternion* quaternion);
void initialize_quaternion_from_axis(Quaternion* quaternion, const AxisAngle* axis);
TransformMatrix* initialize_matrix_from_quaternion(TransformMatrix* out, const Quaternion* quaternion);

struct TransformMatrix {
    void interpolate_matrix_rotation(float alpha);

    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

void TransformMatrix::interpolate_matrix_rotation(float alpha)
{
    Quaternion working;
    AxisAngle axis;
    Quaternion extracted(&basis_right.x);
    working.x = extracted.x;
    working.y = extracted.y;
    working.z = extracted.z;
    working.w = extracted.w;
    if (working.x > -0.001f && working.x < 0.001f)
        working.x = 0.0f;
    if (working.y > -0.001f && working.y < 0.001f)
        working.y = 0.0f;
    if (working.z > -0.001f && working.z < 0.001f)
        working.z = 0.0f;
    if (working.x == 0.0f && working.y == 0.0f && working.z == 0.0f) {
        TransformMatrix rebuilt;
        initialize_matrix_from_quaternion(&rebuilt, &working);
        *this = rebuilt;
    } else {
        initialize_axis_from_quaternion(&axis, &working);
        if (axis.angle != 0.0f) {
            axis.angle = axis.angle * alpha;
            initialize_quaternion_from_axis(&working, &axis);
            TransformMatrix rebuilt;
            initialize_matrix_from_quaternion(&rebuilt, &working);
            *this = rebuilt;
        }
    }
}
