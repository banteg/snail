// spawn_track_garbage_hazard @ 0x43da80 (thiscall, ret 0x8)
// cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*): allocate one garbage slot,
// seed its live body position from the runtime cell, project attachment rows,
// link it into both active lists, and allocate the sprite presentation.

#include "sprite.h"
#include "player.h"
#include "position_bits.h"
#include "transform_matrix.h"

typedef unsigned int DWORD;

class Game {
public:
    DWORD* spawn_track_garbage_hazard(int cell, Player* player);
    char* project_position_onto_track_attachment(float* position, float* out_angle);
};

extern char* g_game_base; // data_4df904

float random_float_below(float upper_bound, const char* tag);
int next_math_random_value();
int report_warningf(char* format, ...);
int report_errorf(char* format, ...);

DWORD* Game::spawn_track_garbage_hazard(int cell, Player* player)
{
    int slot_index = 0;
    DWORD* self_words = (DWORD*)this;
    DWORD* scan;
    scan = self_words + 877682;
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += 49;
        if (slot_index < 50)
            continue;
        return (DWORD*)report_warningf("Run Out of Garbage Slots");
    }

    float* slot_base_words = (float*)(self_words + 49 * slot_index);
    slot_base_words[877681] = *((float*)this + 877648);
    DWORD* slot = (DWORD*)(slot_base_words + 877649);
    self_words[877648] = (DWORD)slot;

    ((DWORD*)slot_base_words)[877697] = (DWORD)player;
    float* scale = (float*)(self_words + 49 * slot_index + 877688);
    *scale = (random_float_below(0.40000001f, "Gadd") + 1.0f) * 0.60000002f;
    ((DWORD*)slot_base_words)[877682] = 1;
    set_matrix_identity((TransformMatrix*)((DWORD*)slot_base_words + 877663));

    float staged_y = *scale;
    staged_y += *(float*)(cell + 20);
    PositionBits staged_position;
    staged_position.x = *(int*)(cell + 16);
    staged_position.z = *(int*)(cell + 24);
    staged_position.y = staged_y;
    PositionBits* live_position = (PositionBits*)(slot_base_words + 877675);
    *live_position = staged_position;
    project_position_onto_track_attachment((float*)live_position, slot_base_words + 877689);

    float* tail = (float*)(self_words + 978393);
    char* anchor = g_game_base + 1448;
    if ((slot[1] & 0x200) != 0) {
        report_errorf("List ADDbefore");
    } else {
        slot[3] = (DWORD)tail;
        if (*((float**)anchor + 1) == tail) {
            ((DWORD*)tail)[2] = (DWORD)slot;
            *((DWORD*)anchor + 1) = (DWORD)slot;
            slot[2] = 0;
        } else {
            slot[2] = ((DWORD*)tail)[2];
            ((DWORD*)tail)[2] = (DWORD)slot;
            *(DWORD*)(slot[2] + 12) = (DWORD)slot;
        }
        slot[1] |= 0x200u;
    }

    Sprite* sprite = g_sprite_manager.allocate_sprite(
        ((Player*)((DWORD*)slot_base_words)[877697])->player_slot,
        114 - (int)((float)next_math_random_value() * -0.00012207031f),
        -1,
        -1);
    ((DWORD*)slot_base_words)[877694] = (DWORD)sprite;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->flags |= 0x800u;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->gravity_step = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->progress = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->progress_step = 0.0f;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->size_start = *scale;
    ((Sprite*)((DWORD*)slot_base_words)[877694])->size_end = *scale;

    DWORD* result = (DWORD*)&((Sprite*)((DWORD*)slot_base_words)[877694])->position;
    result[0] = *(DWORD*)live_position;
    result[1] = *((DWORD*)live_position + 1);
    result[2] = *((DWORD*)live_position + 2);
    ((DWORD*)slot_base_words)[877695] = cell;
    *((char*)slot_base_words + 3510784) = 0;
    return result;
}
