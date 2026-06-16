// spawn_track_health_pickup @ 0x43d6c0 (thiscall, ret 0x8)

#include "player.h"
#include "position_bits.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "track_health_pickup.h"

typedef unsigned int DWORD;

struct HealthPickupPoolSlotView {
    char pool_offset[0x356000];
    TrackHealthPickup pickup;
};

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
    HealthPickupPoolSlotView* slot = (HealthPickupPoolSlotView*)slot_base;
    slot->pickup.state = 1;
    slot->pickup.owner = player;

    PositionBits staged_position;
    staged_position.z = *(int*)&cell->anchor_position.z;
    staged_position.y = cell->anchor_position.y + 0.60000002f;
    staged_position.x = *(int*)&cell->anchor_position.x;
    PositionBits* live_position = (PositionBits*)&slot->pickup.world_position;
    *live_position = staged_position;

    BodNode* node = (BodNode*)&slot->pickup;
    if ((node->list_flags & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first != 0) {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        } else {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        }
        node->list_flags |= 0x200;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(player->player_slot, 57, -1, -1);
    slot->pickup.sprite = sprite;
    unsigned int flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    slot->pickup.sprite->gravity_step = 0.0f;
    slot->pickup.sprite->progress = 0.0f;
    slot->pickup.sprite->progress_step = 0.0f;
    slot->pickup.sprite->size_start = 0.60000002f;
    slot->pickup.sprite->size_end = 0.60000002f;

    DWORD* out_position = (DWORD*)&slot->pickup.sprite->position;
    out_position[0] = *(DWORD*)live_position;
    out_position[1] = *((DWORD*)live_position + 1);
    out_position[2] = *((DWORD*)live_position + 2);
    slot->pickup.source_cell = cell;
    slot->pickup.bob_phase = 0.0f;
    if (((int)slot->pickup.world_position.z & 1) == 0)
        slot->pickup.bob_phase = 0.5f;

    int step_index = slot_index + 30156;
    game_words[29 * step_index] = 0x3c520d21;
    return (DWORD*)(7 * step_index);
}
