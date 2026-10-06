// build_sprite_tail @ 0x44e410 (thiscall)

#include "sprite.h"
#include "transform_matrix.h"

float ATan(float y, float x);

void cRSprite::BuildTail(tMatrix* matrix)
{
    Vector3 rotated;
    if ((flags & SPRITE_FLAG_THROTTLE_FACING_REFRESH) != 0) {
        if (facing_refresh_progress == 0.0f) {
            rotated = (position - previous_position).Rotate(*matrix);
            float angle = ATan(rotated.x, rotated.y) + 7.0685835f;
            facing_refresh_progress = 0.001f;
            facing_angle = angle;
        }
        facing_refresh_progress += facing_refresh_step;
        if (facing_refresh_progress > 1.0f) {
            facing_refresh_progress = 0.0f;
        }
    } else {
        rotated = (position - previous_position).Rotate(*matrix);
        facing_angle = ATan(rotated.x, rotated.y) + 7.0685835f;
    }
}
