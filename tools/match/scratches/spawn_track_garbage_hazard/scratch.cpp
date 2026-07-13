// spawn_track_garbage_hazard @ 0x43da80 (thiscall, ret 0x8)
// cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*): allocate one garbage slot,
// seed its live body position from the runtime cell, project attachment rows,
// link it into both active lists, and allocate the sprite presentation.

#include "sprite.h"
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
    GARBAGE_SLOT_STATE_WORD = 877682,
    GARBAGE_SLOT_MATRIX_WORD = 877663,
    GARBAGE_SLOT_WORLD_POSITION_FLOAT = 877675,
    GARBAGE_SLOT_RADIUS_WORD = 877688,
    GARBAGE_SLOT_ATTACHMENT_FACING_ANGLE_WORD = 877689,
    GARBAGE_SLOT_SPRITE_WORD = 877694,
    GARBAGE_SLOT_PLAYER_WORD = 877697,
    GAME_ACTIVE_BOD_TAIL_WORD = 978393,
};

struct GarbageHazardPoolSlotView {
    char pool_offset[0x359144];
    SubGarbage slot;
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
    DWORD* scan;
    scan = self_words + GARBAGE_SLOT_STATE_WORD;
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += GARBAGE_SLOT_WORD_STRIDE;
        if (slot_index < GARBAGE_SLOT_COUNT)
            continue;
        return (DWORD*)report_warningf("Run Out of Garbage Slots");
    }

    float* slot_base_words = (float*)(self_words + GARBAGE_SLOT_WORD_STRIDE * slot_index);
    ((DWORD*)slot_base_words)[GARBAGE_SLOT_NEXT_ACTIVE_WORD] = self_words[GARBAGE_POOL_ACTIVE_HEAD_WORD];
    DWORD* slot = (DWORD*)(slot_base_words + GARBAGE_SLOT_BASE_WORD);
    self_words[GARBAGE_POOL_ACTIVE_HEAD_WORD] = (DWORD)slot;

    ((DWORD*)slot_base_words)[GARBAGE_SLOT_PLAYER_WORD] = (DWORD)player;
    float* radius = (float*)(self_words + GARBAGE_SLOT_WORD_STRIDE * slot_index + GARBAGE_SLOT_RADIUS_WORD);
    *radius = (random_float_below(0.40000001f, "Gadd") + 1.0f) * 0.60000002f;
    ((DWORD*)slot_base_words)[GARBAGE_SLOT_STATE_WORD] = 1;
    set_matrix_identity((TransformMatrix*)((DWORD*)slot_base_words + GARBAGE_SLOT_MATRIX_WORD));

    Vector3 staged_position;
    float& staged_y = staged_position.y;
    staged_y = *radius;
    staged_y += cell->anchor_position.y;
    staged_position.x = cell->anchor_position.x;
    staged_position.z = cell->anchor_position.z;
    Vector3* live_position = (Vector3*)(slot_base_words + GARBAGE_SLOT_WORLD_POSITION_FLOAT);
    *live_position = staged_position;
    project_position_onto_track_attachment(
        live_position,
        slot_base_words + GARBAGE_SLOT_ATTACHMENT_FACING_ANGLE_WORD);

    BodNode* node = (BodNode*)slot;
    BodNode* tail = (BodNode*)(self_words + GAME_ACTIVE_BOD_TAIL_WORD);
    BodList* active_list = (BodList*)(g_game_base + 1448);
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
        ((Player*)((DWORD*)slot_base_words)[GARBAGE_SLOT_PLAYER_WORD])->player_slot,
        114 - (int)((float)next_math_random_value() * -0.00012207031f),
        -1,
        -1);
    ((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD] = (DWORD)sprite;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->flags |= 0x800u;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->gravity_step = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->progress = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->progress_step = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->size_start = *radius;
    ((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->size_end = *radius;

    DWORD* result = (DWORD*)&((Sprite*)((DWORD*)slot_base_words)[GARBAGE_SLOT_SPRITE_WORD])->position;
    result[0] = *(DWORD*)&live_position->x;
    result[1] = *(DWORD*)&live_position->y;
    result[2] = *(DWORD*)&live_position->z;
    GarbageHazardPoolSlotView* slot_view = (GarbageHazardPoolSlotView*)slot_base_words;
    slot_view->slot.source_cell = cell;
    slot_view->slot.hidden = 0;
    return result;
}
