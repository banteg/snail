// update_sprite_facing_angle @ 0x44e410 (thiscall, ret 0x4)

#include "sprite.h"
#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
};

float atan2_positive(float y, float x);

void Sprite::update_sprite_facing_angle(const TransformMatrix* matrix)
{
    if ((flags & 0x400) != 0) {
        if (facing_refresh_progress == 0.0f) {
            Vector3 rotated;
            Vector3 delta_source;
            Vector3 delta;
            delta_source.x = position.x - previous_position.x;
            delta_source.y = position.y - previous_position.y;
            delta_source.z = position.z - previous_position.z;
            delta = delta_source;
            rotated = *delta.rotate_vector_by_matrix(matrix);
            float angle = atan2_positive(rotated.x, rotated.y) + 7.0685835f;
            facing_refresh_progress = 0.001f;
            facing_angle = angle;
        }
        facing_refresh_progress += facing_refresh_step;
        if (facing_refresh_progress > 1.0f) {
            facing_refresh_progress = 0.0f;
        }
    } else {
        Vector3 rotated;
        Vector3 delta_source;
        Vector3 delta;
        delta_source.x = position.x - previous_position.x;
        delta_source.y = position.y - previous_position.y;
        delta_source.z = position.z - previous_position.z;
        delta = delta_source;
        rotated = *delta.rotate_vector_by_matrix(matrix);
        facing_angle = atan2_positive(rotated.x, rotated.y) + 7.0685835f;
    }
}
