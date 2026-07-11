// activate_landscape_entry @ 0x418870 (thiscall, ret 0x4)
// Activates the ten repeated landscape slices for the selected script record.

#include "landscape_manager.h"
#include "backdrop.h"
#include "border_runtime.h"
#include "runtime_config.h"

extern char* g_game_base; // data_4df904

int next_math_random_value(); // @ 0x44c900
int report_errorf(char* format, ...);

void LandscapeManager::activate_landscape_entry(int script_index)
{
    char flip;
    int mode = *(int*)(g_game_base + 0x74658);
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
            ActiveLandscapeEntry* head =
                (ActiveLandscapeEntry*)(g_game_base + 0x3ca25c);
            if ((entry->list_flags & 0x200) != 0) {
                report_errorf("List ADDafter");
            } else {
                entry->list_prev = head;
                entry->list_next = head->list_next;
                head->list_next = entry;
                if (entry->list_next != 0)
                    entry->list_next->list_prev = entry;
                entry->list_flags |= 0x200;
            }

            *(volatile int*)((char*)entry + 0x80) = 1;
            unsigned int flags = entry->list_flags;
            flags |= 0x20;
            entry->list_flags = flags;

            LandscapeObjectSlotRef* objects =
                (LandscapeObjectSlotRef*)(g_game_base + 0x48e2c);
            entry->set_bod_object(objects[scripts[script_index].object_index].object);
            LandscapeObjectBounds* landscape_object =
                (LandscapeObjectBounds*)entry->object;
            entry->repeat_z_span =
                landscape_object->max_z - landscape_object->min_z;
            set_matrix_identity(&entry->transform);
            entry->transform.position.z =
                ((float)staged_index - 0.5f) * entry->repeat_z_span;
            entry->reference_bod =
                (RenderableBod*)(g_game_base + 0x42fd7c);
        }
        index++;
        entry++;
        staged_index = index;
    } while (index < 10);

    ((Backdrop*)(g_game_base + 0x4ec10))->change_backdrop(
        &scripts[script_index],
        flip);
    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0);

    Color4f* source = &scripts[script_index].fog_color;
    Color4f* destination = (Color4f*)(g_game_base + 0x14);
    *destination = *source;
}
