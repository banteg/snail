// update_movement_flag_emitters @ 0x43a300 (thiscall, ret 0x4)

#include "player.h"

typedef unsigned int DWORD;

void Player::update_movement_flag_emitters(Player* player)
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
    GolbShot* slot = golb_shots;
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
