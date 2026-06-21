// spawn_track_health_pickup @ 0x43d6c0 (thiscall, ret 0x8)

#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_health_pickup.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

DWORD* SubgameRuntime::spawn_track_health_pickup(TrackRowCell* cell, Player* player)
{
    int slot_index = 0;
    DWORD* game_words = (DWORD*)this;
    DWORD* scan = game_words + 874510; // health_pickups[0].state
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += 29;
        if (slot_index < 8)
            continue;
        return (DWORD*)scan;
    }

    DWORD* slot_base = game_words + 29 * slot_index;
    SubgameRuntime* slot = (SubgameRuntime*)slot_base;
    slot->health_pickups[0].state = 1;
    slot->health_pickups[0].owner = player;

    Vector3 staged_position;
    staged_position.x = cell->anchor_position.x;
    staged_position.z = cell->anchor_position.z;
    staged_position.y = cell->anchor_position.y + 0.60000002f;
    Vector3* live_position = &slot->health_pickups[0].world_position;
    *live_position = staged_position;

    BodNode* node = (BodNode*)&slot->health_pickups[0];
    if ((node->list_flags & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(player->player_slot, 57, -1, -1);
    slot->health_pickups[0].sprite = sprite;
    unsigned int flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    slot->health_pickups[0].sprite->gravity_step = 0.0f;
    slot->health_pickups[0].sprite->progress = 0.0f;
    slot->health_pickups[0].sprite->progress_step = 0.0f;
    slot->health_pickups[0].sprite->size_start = 0.60000002f;
    slot->health_pickups[0].sprite->size_end = 0.60000002f;

    slot->health_pickups[0].sprite->position = *live_position;
    slot->health_pickups[0].source_cell = cell;
    slot->health_pickups[0].bob_phase = 0.0f;
    if (((int)slot->health_pickups[0].world_position.z & 1) != 0)
        slot->health_pickups[0].bob_phase = 0.0f;
    else
        slot->health_pickups[0].bob_phase = 0.5f;

    int step_index = slot_index + 30156;
    int result = 7 * step_index;
    game_words[step_index + (result << 2)] = 0x3c520d21;
    return (DWORD*)result;
}
