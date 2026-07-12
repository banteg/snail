// change_backdrop_real @ 0x410dc0 (thiscall, ret)
// Commits the staged backdrop texture/distort state.

#include "backdrop.h"

void Backdrop::change_backdrop_real()
{
    int texture_id = pending_primary_texture_id;

    if (texture_id != 0) {
        if (texture_id != active_primary_texture_id) {
            active_primary_texture_id = texture_id;
            active_secondary_texture_id = pending_secondary_texture_id;
        }

        zoom = 0.0f;
        set_backdrop_distort(pending_distort);
        backdrop_render_enabled = 1;
    } else {
        backdrop_render_enabled = 0;
    }

    active_flip = pending_flip;
    active_split_backdrop_pair = pending_split_backdrop_pair;
}
