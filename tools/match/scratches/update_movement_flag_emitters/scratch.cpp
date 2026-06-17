// update_movement_flag_emitters @ 0x43a300 (thiscall, ret 0x4)

#include "player.h"

typedef unsigned int DWORD;

class GolbEmitterSlot {
public:
    int create_golb(Player* player, int spawn_selector, int emitter_index);

    char unknown_000[0x244];
    int state; // +0x244
    char unknown_248[0x2e8 - 0x248];
};

class PlayerGolbEmitterView {
public:
    void update_movement_flag_emitters(Player* player);

    char unknown_000[0x450];
    GolbEmitterSlot golb_slots[12]; // +0x450, stride 0x2e8
};

void PlayerGolbEmitterView::update_movement_flag_emitters(Player* player)
{
    DWORD flags = player->movement_flags;
    Player* owner = (Player*)this;
    int spawn_count;

    while ((flags & 0x69) == 0) {
        while ((flags & 0x12) == 0) {
            if ((flags & 4) == 0)
                return;
            spawn_count = 3;
            goto spawn;
        }
        spawn_count = 2;
        goto spawn;
    }
    spawn_count = 1;

spawn:
    int index = 0;
    GolbEmitterSlot* slot = golb_slots;
    do {
        if (slot->state == 0) {
            slot->create_golb(owner, spawn_count, index);
            --spawn_count;
            if (spawn_count == 0)
                break;
        }
        ++index;
        ++slot;
    } while (index < 12);
}
