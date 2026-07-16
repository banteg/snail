// activate_landscape_entry @ 0x418870 (thiscall, ret 0x4)
// Activates the ten repeated landscape slices for the selected script record.

#include "landscape_manager.h"
#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "runtime_config.h"

extern GameRoot* g_game; // data_4df904

int next_math_random_value(); // @ 0x44c900
int report_errorf(char* format, ...);

void LandscapeManager::activate_landscape_entry(int script_index)
{
    char flip;
    int mode = g_game->subgame.level_mode;
    if (mode == 7) {
        flip = 0;
    } else if (mode == 1) {
        if ((float)next_math_random_value() * 0.0000305175781f > 0.5f)
            flip = 0;
        else
            flip = 1;
    } else {
        flip = g_runtime_config.landscape_backdrop_variant_selector & 1;
    }

    int index = 0;
    int staged_index = 0;
    ActiveLandscapeEntry* entry = active_entries;
    do {
        if (scripts[script_index].object_index == -1) {
            entry->list_flags &= ~0x20;
            entry->set_bod_object(0);
        } else {
            BodNode* head = &g_game->subgame.landscape_slice_list_head;
            if ((entry->list_flags & BOD_FLAG_LINKED) != 0) {
                report_errorf("List ADDafter");
            } else {
                entry->list_prev = head;
                entry->list_next = head->list_next;
                head->list_next = entry;
                if (entry->list_next != 0)
                    entry->list_next->list_prev = entry;
                entry->list_flags |= BOD_FLAG_LINKED;
            }

            entry->state = 1;
            unsigned int flags = entry->list_flags;
            flags |= 0x20;
            entry->list_flags = flags;

            CachedXMeshSlot* objects =
                &g_game->directx_loader.cached_x_mesh_slots[0];
            entry->set_bod_object(objects[scripts[script_index].object_index].object);
            Object* landscape_object = entry->object;
            entry->repeat_z_span =
                landscape_object->bounds_max.z - landscape_object->bounds_min.z;
            set_matrix_identity(&entry->transform);
            entry->transform.position.z =
                ((float)staged_index - 0.5f) * entry->repeat_z_span;
            entry->reference_bod =
                (RenderableBod*)g_game->subgame.embedded_player();
        }
        index++;
        entry++;
        staged_index = index;
    } while (index < LANDSCAPE_ACTIVE_ENTRY_COUNT);

    g_game->backdrop.change_backdrop(&scripts[script_index], flip);
    g_game->border_manager.set_border_justify_centre(0.0f);

    tColour* source = &scripts[script_index].fog_color;
    tColour* destination = &g_game->fog_color;
    *destination = *source;
}
