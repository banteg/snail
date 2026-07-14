// update_overlay @ 0x40a1b0 (thiscall)

#include "overlay.h"

void Overlay::update_overlay()
{
    camera.overlay_rotation_angle += rotation_step;
    if (camera.overlay_rotation_angle > 6.2831855f) {
        camera.overlay_rotation_angle -= 6.2831855f;
    } else if (camera.overlay_rotation_angle < 0.0f) {
        camera.overlay_rotation_angle += 6.2831855f;
    }

    transform.set_matrix_identity();
    transform.rotate_matrix_local_z(camera.overlay_rotation_angle);
    camera.transform = transform;
    camera.view_matrix.invert_matrix_from_source(transform);
}
