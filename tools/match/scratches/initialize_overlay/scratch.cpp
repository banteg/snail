// initialize_overlay @ 0x40a240 (thiscall, ret)

#include "overlay.h"

void Overlay::initialize_overlay()
{
    rotation_angle = 0.0f;
    rotation_step = 0.00036547193f;
    set_matrix_identity(&screen_matrix);
    field_140 = 38.0f;
    set_matrix_identity(&world_matrix);
    inverse_screen_matrix.invert_matrix_from_source(&screen_matrix);
}
