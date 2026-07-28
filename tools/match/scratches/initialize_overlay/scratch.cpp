// initialize_overlay @ 0x40a240 (thiscall, ret)

#include "overlay.h"

void Overlay::initialize_overlay()
{
    camera.overlay_rotation_angle = 0.0f;
    rotation_step = 0.00036547193f;
    transform.Identity();
    camera.fov_degrees = 38.0f;
    camera.transform.Identity();
    camera.view_matrix.Invert(transform);
}
