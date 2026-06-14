// update_active_bod @ 0x433e80 (thiscall, ret)

int report_errorf(char* format, ...);

struct ActiveBod {
    void update_active_bod();

    int unknown_00;
    unsigned int list_flags; // +0x04
    ActiveBod* list_prev;    // +0x08
    ActiveBod* list_next;    // +0x0c
    char unknown_10[0x38 - 0x10];
    float world_z;           // +0x38
};

struct BodList {
    int unknown_00;
    ActiveBod* first;    // +0x04
    ActiveBod* free_top; // +0x08
};

extern char* g_game_base; // data_4df904

void ActiveBod::update_active_bod()
{
    if (world_z + 24.0f < *(float*)(g_game_base + 0x4326fc)) {
        unsigned int flags = list_flags;
        BodList* list = (BodList*)(g_game_base + 0x5a8);
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            return;
        }

        ActiveBod* next = list_next;
        if (next != 0)
            next->list_prev = list_prev;

        ActiveBod* prev = list_prev;
        if (prev != 0)
            prev->list_next = list_next;
        else
            list->first = list_next;

        list_next = list->free_top;
        list->free_top = this;

        unsigned int updated = list_flags;
        updated &= ~0x200;
        list_flags = updated;
    }
}
