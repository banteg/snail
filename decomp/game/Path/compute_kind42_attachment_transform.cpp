// compute_kind42_attachment_transform @ 0x42b920 (thiscall, ret 0x14)

#include "track_attachment_types.h"
#include "transform_matrix.h"

float Sqrt(float value);
float ATan(float y, float x);
float Sin(float angle);
float Cos(float angle);

void cRPath::compute_kind42_attachment_transform(
    float radius, float x, float y, TransformMatrix* transform, float* out_angle)
{
    float root = (float)Sqrt(radius * radius - 16.0f);
    float* angle_out = out_angle;
    TransformMatrix* target = transform;
    float angle = ATan(4.0f, root);
    *angle_out = angle * x * 0.25f;
    target->RotIdentity();
    target->RotLocalZ(*angle_out);

    x = radius - y;
    target->position.x = Sin(*angle_out) * x;
    target->position.y = radius - Cos(*angle_out) * x;
    *angle_out = -*angle_out;
}
