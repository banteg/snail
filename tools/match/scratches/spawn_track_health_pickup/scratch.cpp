// spawn_track_health_pickup @ 0x43d6c0 (thiscall, ret 0x8)

#include "player.h"
#include "position_bits.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "track_health_pickup.h"

typedef unsigned int DWORD;

class Game {
public:
    DWORD* spawn_track_health_pickup(TrackRowCell* cell, Player* player);
};

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

DWORD* Game::spawn_track_health_pickup(TrackRowCell* cell, Player* player)
{
    int slot_index = 0;
    DWORD* game_words = (DWORD*)this;
    DWORD* scan = game_words + 874510; // game + 0x356038
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += 29;
        if (slot_index < 8)
            continue;
        return scan;
    }

    DWORD* slot_base = game_words + 29 * slot_index;
    DWORD* slot = slot_base + 874496; // game + 0x356000 + slot_index * 0x74
    slot_base[874510] = 1;            // TrackHealthPickup::state
    slot_base[874511] = (DWORD)player; // TrackHealthPickup::owner

    PositionBits staged_position;
    staged_position.z = *(int*)&cell->anchor_position.z;
    staged_position.y = cell->anchor_position.y + 0.60000002f;
    staged_position.x = *(int*)&cell->anchor_position.x;
    PositionBits* live_position = (PositionBits*)(slot_base + 874500);
    *live_position = staged_position;

    if ((slot_base[874497] & 0x200) != 0) {
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
            slot_base[874498] = 0;
            *(DWORD*)(*first_ref + 12) = 0;
        }
        slot_base[874497] |= 0x200;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(player->player_slot, 57, -1, -1);
    slot_base[874521] = (DWORD)sprite;
    unsigned int flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    ((Sprite*)slot_base[874521])->gravity_step = 0.0f;
    ((Sprite*)slot_base[874521])->progress = 0.0f;
    ((Sprite*)slot_base[874521])->progress_step = 0.0f;
    ((Sprite*)slot_base[874521])->size_start = 0.60000002f;
    ((Sprite*)slot_base[874521])->size_end = 0.60000002f;

    DWORD* out_position = (DWORD*)&((Sprite*)slot_base[874521])->position;
    out_position[0] = *(DWORD*)live_position;
    out_position[1] = *((DWORD*)live_position + 1);
    out_position[2] = *((DWORD*)live_position + 2);
    slot_base[874522] = (DWORD)cell; // TrackHealthPickup::source_cell
    slot_base[874523] = 0;
    if (((int)*(float*)&slot_base[874502] & 1) == 0)
        slot_base[874523] = 0x3f000000;

    int step_index = slot_index + 30156;
    game_words[29 * step_index] = 0x3c520d21;
    return (DWORD*)(7 * step_index);
}
