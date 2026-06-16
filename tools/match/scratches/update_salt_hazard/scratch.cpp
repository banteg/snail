// update_salt_hazard @ 0x441c10 (thiscall, ret)

#include "salt_hazard_types.h"
#include "sprite.h"

class Game {
public:
    char unknown_00[0x09];
    unsigned char paused; // +0x09
    char unknown_0a[0x5a8 - 0x0a];
    SaltListAnchor salt_free_anchor; // +0x5a8
    char unknown_5b4[0x3bb7d4 - 0x5b4];
    float salt_fade_start_z; // +0x3bb7d4
    char unknown_3bb7d8[0x3be0e4 - 0x3bb7d8];
    float salt_kill_plane_z; // +0x3be0e4
};

extern Game* volatile g_game; // data_4df904
int report_errorf(char* format, ...);

void SaltHazardSlot::update_salt_hazard()
{
    if (owner_game->paused)
        return;

    switch (state) {
    case 2: {
        SaltListAnchor* anchor = &g_game->salt_free_anchor;
        int flags = list_flags;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            state = 0;
            return;
        } else {
            if ((flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
                state = 0;
                return;
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
            }
        }
        return;
    }
    case 1: {
        float alpha =
            1.0f - (position.z - owner_game->salt_fade_start_z) * 0.021739131f;
        *(float*)((char*)this + 0x8c) = alpha;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        } else if (alpha > 1.0f) {
            alpha = 1.0f;
        }
        *(float*)((char*)this + 0x8c) = alpha;
        color.set_color_alpha(0x3f666666);
        if (position.z < owner_game->salt_kill_plane_z)
            state = 2;
        return;
    }
    }
}
