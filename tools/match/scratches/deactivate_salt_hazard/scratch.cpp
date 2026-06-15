// deactivate_salt_hazard @ 0x441740 (thiscall, ret)
// Unlinks the slot from the live list and pushes it onto the free stack
// anchored at game+0x5a8; clears the live state either way.

struct SaltHazardSlot;

struct SaltListAnchor {
    char unknown_00[4];
    SaltHazardSlot* first;    // +0x04
    SaltHazardSlot* free_top; // +0x08
};

struct Game {
    char unknown_00[0x5a8];
    SaltListAnchor salt_free_anchor; // +0x5a8
};

extern Game* volatile g_game; // data_4df904
int report_errorf(char* format, ...);

struct SaltHazardSlot {
    int deactivate_salt_hazard();

    int unknown_00;
    unsigned int list_flags;   // +0x04, 0x200 = linked, 0x40 = iteration guard
    SaltHazardSlot* list_prev; // +0x08
    SaltHazardSlot* list_next; // +0x0c
    char unknown_10[0x80 - 0x10];
    int state;                 // +0x80
    char unknown_84[0x98 - 0x84];
};

int SaltHazardSlot::deactivate_salt_hazard()
{
    SaltListAnchor* anchor = &g_game->salt_free_anchor;
    int flags = list_flags;
    int result;
    if ((flags & 0x200) == 0) {
        result = report_errorf("List remove");
        state = 0;
    } else {
        if ((flags & 0x40) != 0) {
            result = report_errorf("List remove NEXTBOD");
            state = 0;
        } else {
            if (list_next)
                list_next->list_prev = list_prev;
            if (list_prev)
                list_prev->list_next = list_next;
            else
                anchor->first = list_next;
            list_next = anchor->free_top;
            anchor->free_top = this;
            int updated = list_flags;
            state = 0;
            updated &= ~0x200;
            list_flags = updated;
            result = updated;
        }
    }
    return result;
}
