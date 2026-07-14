// spawn_track_garbage_hazard @ 0x43da80 (thiscall, ret 0x8)
// cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*): allocate one garbage slot,
// seed its live body position from the runtime cell, project attachment rows,
// link it into both active lists, and allocate the sprite presentation.

#include "sprite.h"
#include "game_root.h"
#include "player.h"
#include "garbage_hazard_slot.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

typedef unsigned int DWORD;

enum {
    GARBAGE_SLOT_COUNT = 50,
    GARBAGE_SLOT_WORD_STRIDE = 49,
    GARBAGE_POOL_ACTIVE_HEAD_WORD = 877648,
    GARBAGE_SLOT_BASE_WORD = 877649,
    GARBAGE_SLOT_NEXT_ACTIVE_WORD = 877681,
};

extern char* g_game_base; // data_4df904

float random_float_below(float upper_bound, const char* tag);
int next_math_random_value();
int report_warningf(char* format, ...);
int report_errorf(char* format, ...);

DWORD* SubgameRuntime::spawn_track_garbage_hazard(TrackRowCell* cell, Player* player)
{
    int slot_index = 0;
    DWORD* self_words = (DWORD*)this;
    SubGarbage* scan = garbage_hazards.slots;
    while (1) {
        if (scan->state == 0)
            break;
        ++slot_index;
        ++scan;
        if (slot_index < GARBAGE_SLOT_COUNT)
            continue;
        return (DWORD*)report_warningf("Run Out of Garbage Slots");
    }

    float* slot_base_words =
        (float*)(self_words + GARBAGE_SLOT_WORD_STRIDE * slot_index);
    ((DWORD*)slot_base_words)[GARBAGE_SLOT_NEXT_ACTIVE_WORD] = self_words[GARBAGE_POOL_ACTIVE_HEAD_WORD];
    DWORD* slot = (DWORD*)(slot_base_words + GARBAGE_SLOT_BASE_WORD);
    self_words[GARBAGE_POOL_ACTIVE_HEAD_WORD] = (DWORD)slot;

    garbage_hazards.slots[slot_index].player = player;
    float* radius = &garbage_hazards.slots[slot_index].radius;
    *radius = (random_float_below(0.40000001f, "Gadd") + 1.0f) * 0.60000002f;
    garbage_hazards.slots[slot_index].state = 1;
    garbage_hazards.slots[slot_index].transform.set_matrix_identity();

    Vector3 staged_position;
    float& staged_y = staged_position.y;
    staged_y = *radius;
    staged_y += cell->position.y;
    staged_position.x = cell->position.x;
    staged_position.z = cell->position.z;
    Vector3* live_position =
        &garbage_hazards.slots[slot_index].transform.position;
    *live_position = staged_position;
    project_position_onto_track_attachment(
        live_position,
        &garbage_hazards.slots[slot_index].attachment_facing_angle);

    BodNode* node = (BodNode*)slot;
    BodNode* tail = &this->player;
    BodList* active_list = &((GameRoot*)g_game_base)->active_bod_list;
    if ((node->list_flags & 0x200) != 0) {
        report_errorf("List ADDbefore");
    } else {
        node->list_next = tail;
        if (active_list->first == tail) {
            tail->list_prev = node;
            active_list->first = node;
            node->list_prev = 0;
        } else {
            node->list_prev = tail->list_prev;
            tail->list_prev = node;
            node->list_prev->list_next = node;
        }
        node->list_flags |= 0x200u;
    }

    Sprite* sprite = g_sprite_manager.allocate_sprite(
        garbage_hazards.slots[slot_index].player->player_slot,
        114 - (int)((float)next_math_random_value() * -0.00012207031f),
        -1,
        -1);
    garbage_hazards.slots[slot_index].sprite = sprite;
    garbage_hazards.slots[slot_index].sprite->flags |= 0x800u;
    garbage_hazards.slots[slot_index].sprite->gravity_step = 0.0f;
    garbage_hazards.slots[slot_index].sprite->progress = 0.0f;
    garbage_hazards.slots[slot_index].sprite->progress_step = 0.0f;
    garbage_hazards.slots[slot_index].sprite->size_start = *radius;
    garbage_hazards.slots[slot_index].sprite->size_end = *radius;

    DWORD* result =
        (DWORD*)&garbage_hazards.slots[slot_index].sprite->position;
    result[0] = *(DWORD*)&live_position->x;
    result[1] = *(DWORD*)&live_position->y;
    result[2] = *(DWORD*)&live_position->z;
    SubGarbage* slot_view = &garbage_hazards.slots[slot_index];
    slot_view->source_cell = cell;
    slot_view->hidden = 0;
    return result;
}
