// clear_active_landscape_entries @ 0x418a30 (thiscall, ret)
// Removes all linked active landscape slots from the active BOD list.

#include "game_root.h"
#include "landscape_manager.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

void LandscapeManager::clear_active_landscape_entries()
{
    ActiveLandscapeEntry* entry = active_entries;
    int count = sizeof(active_entries) / sizeof(active_entries[0]);
    do {
        unsigned int flags = entry->list_flags;
        if ((flags & 0x200) != 0) {
            entry->state = 0;
            BodList* list = &g_game->active_bod_list;
            flags = entry->list_flags;
            if ((flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                ActiveLandscapeEntry* next =
                    (ActiveLandscapeEntry*)entry->list_next;
                if (next != 0)
                    next->list_prev = entry->list_prev;

                ActiveLandscapeEntry* prev =
                    (ActiveLandscapeEntry*)entry->list_prev;
                if (prev != 0)
                    prev->list_next = entry->list_next;
                else
                    list->first = entry->list_next;

                entry->list_next = list->free_top;
                list->free_top = entry;

                unsigned int updated = entry->list_flags;
                updated &= ~0x200;
                entry->list_flags = updated;
            }
        }
        entry++;
        count--;
    } while (count != 0);
}
