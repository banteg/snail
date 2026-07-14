// compute_kind42_attachment_transform @ 0x42b920 (thiscall, ret 0x14)

#include "track_attachment_types.h"
#include "transform_matrix.h"

double square_root(float value);
float atan2_positive(float y, float x);
float sine(float angle);
float cosine(float angle);

void Path::compute_kind42_attachment_transform(
    float radius, float x, float y, TransformMatrix* transform, float* out_angle)
{
    float root = (float)square_root(radius * radius - 16.0f);
    float* angle_out = out_angle;
    TransformMatrix* target = transform;
    float angle = atan2_positive(4.0f, root);
    *angle_out = angle * x * 0.25f;
    target->set_matrix_rotation_identity();
    target->rotate_matrix_world_z(*angle_out);

    x = radius - y;
    target->position.x = sine(*angle_out) * x;
    target->position.y = radius - cosine(*angle_out) * x;
    *angle_out = -*angle_out;
}
