// spawn_track_jetpack_pickup @ 0x43d890 (thiscall, ret 0x8)

#include "player.h"
#include "position_bits.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "track_jetpack_pickup.h"

typedef unsigned int DWORD;

struct JetpackPickupPoolSlotView {
    char pool_offset[0x355e64];
    TrackJetpackPickup pickup;
};

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
    DWORD* scan = game_words + 874407; // jetpack_pickup.state
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
    JetpackPickupPoolSlotView* slot = (JetpackPickupPoolSlotView*)slot_base;
    slot->pickup.state = 1;
    slot->pickup.owner = player;

    PositionBits staged_position;
    staged_position.z = *(int*)&cell->anchor_position.z;
    staged_position.y = cell->anchor_position.y + 1.5f;
    staged_position.x = *(int*)&cell->anchor_position.x;
    PositionBits* live_position = (PositionBits*)&slot->pickup.world_position;
    *live_position = staged_position;

    int lane = cell->lane_and_flags & 7;
    if (lane == 3 && *((unsigned char*)cell - 24) == 14
        && *((unsigned char*)cell + 228) == 14) {
        ((float*)live_position)[0] = ((float*)live_position)[0] + 0.5f;
    } else if (lane == 4 && *((unsigned char*)cell - 108) == 14
        && *((unsigned char*)cell + 144) == 14) {
        ((float*)live_position)[0] = ((float*)live_position)[0] - 0.5f;
    }

    BodNode* node = (BodNode*)&slot->pickup;
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
        g_sprite_manager.allocate_sprite(player->player_slot, 124, -1, -1);
    slot->pickup.sprite = sprite;
    unsigned int flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    slot->pickup.sprite->gravity_step = 0.0f;
    slot->pickup.sprite->progress = 0.0f;
    slot->pickup.sprite->progress_step = 0.0f;
    slot->pickup.sprite->size_start = 1.5f;
    slot->pickup.sprite->size_end = 1.5f;

    DWORD* out_position = (DWORD*)&slot->pickup.sprite->position;
    out_position[0] = *(DWORD*)live_position;
    out_position[1] = *((DWORD*)live_position + 1);
    out_position[2] = *((DWORD*)live_position + 2);
    slot->pickup.source_cell = cell;
    slot->pickup.bob_phase = 0.0f;

    int z_as_int = (int)slot->pickup.world_position.z;
    if ((z_as_int & 1) == 0)
        slot->pickup.bob_phase = 0.5f;

    slot->pickup.bob_phase_step = 0.012820513f;
    return z_as_int;
}
