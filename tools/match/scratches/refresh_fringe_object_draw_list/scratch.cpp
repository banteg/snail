// refresh_fringe_object_draw_list @ 0x439b00 (thiscall, ret)

struct Color4f {
    float r;
    float g;
    float b;
    float a;
};

class SubgameRuntime {
public:
    Color4f* get_track_skirt_color(Color4f* out);
};

int report_errorf(char* format, ...);

struct FringeObject {
    void refresh_fringe_object_draw_list();

    int unknown_00;
    unsigned int list_flags; // +0x04
    FringeObject* list_prev; // +0x08
    FringeObject* list_next; // +0x0c
    char unknown_10[0x18 - 0x10];
    float world_z;           // +0x18
    char unknown_1c[0x28 - 0x1c];
    Color4f skirt_color;     // +0x28
};

struct BodList {
    int unknown_00;
    FringeObject* first;    // +0x04
    FringeObject* free_top; // +0x08
};

extern char* g_game_base; // data_4df904

void FringeObject::refresh_fringe_object_draw_list()
{
    Color4f color;
    Color4f* resolved =
        ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&color);

    float current_z = world_z;
    skirt_color = *resolved;

    if (current_z < *(float*)(g_game_base + 0x4326fc)) {
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

        FringeObject* next = list_next;
        if (next != 0)
            next->list_prev = list_prev;

        FringeObject* prev = list_prev;
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
