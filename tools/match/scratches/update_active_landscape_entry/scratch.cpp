// update_active_landscape_entry @ 0x418ac0 (thiscall, ret)
// Advances a repeated landscape slice and toggles its render visibility bit.

#include "active_landscape_entry.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void ActiveLandscapeEntry::update_active_landscape_entry()
{
    if (g_game->subgame.subgame_pause_gate == 0) {
        // Keep VC6's native switch gate while sharing the early-return label.
        switch (state) {
        case 0:
            goto done;
        case 1: {
            goto active;
        }
        default:
            goto done;
        }
    }
done:
    return;

active:
    Object* landscape_object = object;
    RenderableBod* reference = reference_bod;
    if (landscape_object->bounds_max.z + transform.position.z <
        reference->transform.position.z - 10.0f) {
        transform.position.z = repeat_z_span * 3.0f + transform.position.z;
    }

    if (landscape_object->bounds_min.z + transform.position.z >
        g_game->fog_end + reference->transform.position.z) {
        list_flags &= ~0x20;
    } else {
        list_flags |= 0x20;
    }
}
