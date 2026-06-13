// spawn_track_garbage_hazard @ 0x43da80 (thiscall, ret 0x8)
// cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*): allocate one garbage slot,
// seed its live body position from the runtime cell, project attachment rows,
// link it into both active lists, and allocate the sprite presentation.

typedef unsigned int uint32_t;
typedef unsigned int DWORD;

struct TransformMatrix {
    float rows[16];
};

struct SpriteManager {
    void* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

class Game {
public:
    DWORD* spawn_track_garbage_hazard(int cell, int player);
    char* project_position_onto_track_attachment(float* position, float* out_angle);
};

extern char* g_game_base; // data_4df904
extern SpriteManager g_sprite_manager; // data_790f30

void __fastcall set_matrix_identity(TransformMatrix* transform);
float random_float_below(float upper_bound, const char* tag);
int next_math_random_value();
int report_warningf(char* format, ...);
int report_errorf(char* format, ...);

DWORD* Game::spawn_track_garbage_hazard(int cell, int player)
{
    int slot_index = 0;
    DWORD* self_words = (DWORD*)this;
    DWORD* scan;
    scan = self_words + 877682;
    while (*scan) {
        ++slot_index;
        scan += 49;
        if (slot_index >= 50)
            return (DWORD*)report_warningf("Run Out of Garbage Slots");
    }

    float* slot_base_words = (float*)(self_words + 49 * slot_index);
    slot_base_words[877681] = *((float*)this + 877648);
    DWORD* slot = (DWORD*)(slot_base_words + 877649);
    self_words[877648] = (DWORD)slot;

    float* scale = (float*)(self_words + 49 * slot_index + 877688);
    ((DWORD*)slot_base_words)[877697] = player;
    *scale = (random_float_below(0.40000001f, "Gadd") + 1.0f) * 0.60000002f;
    ((DWORD*)slot_base_words)[877682] = 1;
    set_matrix_identity((TransformMatrix*)((DWORD*)slot_base_words + 877663));

    int x_bits = *(int*)(cell + 16);
    float y = *scale + *(float*)(cell + 20);
    int z_bits = *(int*)(cell + 24);
    ((DWORD*)slot_base_words)[877675] = x_bits;
    slot_base_words[877676] = y;
    ((DWORD*)slot_base_words)[877677] = z_bits;
    float* live_position = slot_base_words + 877675;
    project_position_onto_track_attachment(live_position, slot_base_words + 877689);

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

    DWORD* sprite = (DWORD*)g_sprite_manager.allocate_sprite(
        *(DWORD*)(((DWORD*)slot_base_words)[877697] + 896),
        114 - (int)((float)next_math_random_value() * -0.00012207031f),
        -1,
        -1);
    ((DWORD*)slot_base_words)[877694] = (DWORD)sprite;
    sprite[1] |= 0x800u;
    *(DWORD*)(((DWORD*)slot_base_words)[877694] + 120) = 0;
    *(DWORD*)(((DWORD*)slot_base_words)[877694] + 104) = 0;
    *(DWORD*)(((DWORD*)slot_base_words)[877694] + 108) = 0;
    *(DWORD*)(((DWORD*)slot_base_words)[877694] + 96) = *(DWORD*)scale;
    *(DWORD*)(((DWORD*)slot_base_words)[877694] + 100) = *(DWORD*)scale;

    DWORD* result = (DWORD*)(((DWORD*)slot_base_words)[877694] + 72);
    result[0] = *(DWORD*)live_position;
    result[1] = *((DWORD*)live_position + 1);
    result[2] = *((DWORD*)live_position + 2);
    ((DWORD*)slot_base_words)[877695] = cell;
    *((char*)slot_base_words + 3510784) = 0;
    return result;
}
