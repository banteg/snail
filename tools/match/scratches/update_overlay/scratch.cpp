// update_overlay @ 0x40a1b0 (thiscall)

#include "overlay.h"

void Overlay::update_overlay()
{
    rotation_angle += rotation_step;
    if (rotation_angle > 6.2831855f) {
        rotation_angle -= 6.2831855f;
    } else if (rotation_angle < 0.0f) {
        rotation_angle += 6.2831855f;
    }

    set_matrix_identity(&screen_matrix);
    screen_matrix.rotate_matrix_world_z(rotation_angle);
    world_matrix = screen_matrix;
    inverse_screen_matrix.invert_matrix_from_source(&screen_matrix);
}
