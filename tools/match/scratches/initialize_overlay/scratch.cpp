// initialize_overlay @ 0x40a240 (thiscall, ret)

#include "overlay.h"

void Overlay::initialize_overlay()
{
    camera.overlay_rotation_angle = 0.0f;
    rotation_step = 0.00036547193f;
    transform.set_matrix_identity();
    camera.fov_degrees = 38.0f;
    camera.transform.set_matrix_identity();
    camera.view_matrix.invert_matrix_from_source(transform);
}
