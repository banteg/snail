// spawn_track_jetpack_pickup @ 0x43d890 (thiscall, ret 0x8)

#include "player.h"
#include "position_bits.h"
#include "sprite.h"
#include "track_attachment_types.h"

typedef unsigned int DWORD;

class Game {
public:
    int spawn_track_jetpack_pickup(TrackRowCell* cell, Player* player);
};

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

int Game::spawn_track_jetpack_pickup(TrackRowCell* cell, Player* player)
{
    int slot_index = 0;
    DWORD* game_words = (DWORD*)this;
    DWORD* scan = game_words + 874407; // game + 0x355e9c
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += 103;
        if (slot_index < 1)
            continue;
        return (int)scan;
    }

    DWORD* slot_base = game_words + 103 * slot_index;
    DWORD* slot = slot_base + 874393; // game + 0x355e64 + slot_index * 0x19c
    slot_base[874407] = 1;            // parent state
    slot_base[874408] = (DWORD)player;

    PositionBits staged_position;
    staged_position.z = *(int*)&cell->anchor_position.z;
    staged_position.y = cell->anchor_position.y + 1.5f;
    staged_position.x = *(int*)&cell->anchor_position.x;
    PositionBits* live_position = (PositionBits*)(slot_base + 874397);
    *live_position = staged_position;

    int lane = cell->lane_and_flags & 7;
    if (lane == 3 && *((unsigned char*)cell - 24) == 14
        && *((unsigned char*)cell + 228) == 14) {
        ((float*)live_position)[0] = ((float*)live_position)[0] + 0.5f;
    } else if (lane == 4 && *((unsigned char*)cell - 108) == 14
        && *((unsigned char*)cell + 144) == 14) {
        ((float*)live_position)[0] = ((float*)live_position)[0] - 0.5f;
    }

    if ((slot_base[874394] & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        DWORD* first_ref = (DWORD*)(g_game_base + 0x5ac);
        DWORD first = *first_ref;
        if (first != 0) {
            *(DWORD*)(first + 8) = (DWORD)slot;
            *(DWORD*)(*(DWORD*)(*first_ref + 8) + 12) = *first_ref;
            DWORD new_first = *(DWORD*)(*first_ref + 8);
            *first_ref = new_first;
            *(DWORD*)(new_first + 8) = 0;
        } else {
            *first_ref = (DWORD)slot;
            slot_base[874395] = 0;
            *(DWORD*)(*first_ref + 12) = 0;
        }
        slot_base[874394] |= 0x200;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(player->player_slot, 124, -1, -1);
    slot_base[874418] = (DWORD)sprite;
    unsigned int flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    ((Sprite*)slot_base[874418])->gravity_step = 0.0f;
    ((Sprite*)slot_base[874418])->progress = 0.0f;
    ((Sprite*)slot_base[874418])->progress_step = 0.0f;
    ((Sprite*)slot_base[874418])->size_start = 1.5f;
    ((Sprite*)slot_base[874418])->size_end = 1.5f;

    DWORD* out_position = (DWORD*)&((Sprite*)slot_base[874418])->position;
    out_position[0] = *(DWORD*)live_position;
    out_position[1] = *((DWORD*)live_position + 1);
    out_position[2] = *((DWORD*)live_position + 2);
    slot_base[874419] = (DWORD)cell;
    slot_base[874420] = 0;

    int z_as_int = (int)*(float*)&slot_base[874399];
    if ((z_as_int & 1) == 0)
        slot_base[874420] = 0x3f000000;

    slot_base[874421] = 0x3c520d21;
    return z_as_int;
}
