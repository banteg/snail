// spawn_slug_hazard @ 0x43dc80 (thiscall, ret 0x8)
// cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*): allocate a slug runtime slot,
// seed its renderable body state, link it into the shared BOD list, and attach
// the live sprite presentation.

#include "player.h"
#include "slug_hazard_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

typedef unsigned int DWORD;

class Game {
public:
    int spawn_slug_hazard(TrackRowCell* cell, Player* player);
    char* project_position_onto_track_attachment(
        Vector3* position,
        float* out_angle);
};

extern char* g_game_base; // data_4df904

int next_math_random_value();
int report_errorf(char* format, ...);

int Game::spawn_slug_hazard(TrackRowCell* cell, Player* player)
{
    int slot_index = 0;
    DWORD* game_words = (DWORD*)this;
    DWORD* scan = game_words + 874760;
    while (1) {
        if (*scan == 0)
            break;
        ++slot_index;
        scan += 59;
        if (slot_index < 8)
            continue;
        return slot_index;
    }

    char* slot_base = (char*)(game_words + 59 * slot_index);
    *(DWORD*)(slot_base + 0x356420) = 1;
    *(DWORD*)(slot_base + 0x356460) = (DWORD)player;
    set_matrix_identity((TransformMatrix*)(slot_base + 0x3563d8));

    Vector3 staged_position;
    staged_position.y = cell->anchor_position.y + 1.7f;
    staged_position.x = cell->anchor_position.x;
    staged_position.z = cell->anchor_position.z;
    Vector3* live_position = (Vector3*)(slot_base + 0x356408);
    *live_position = staged_position;
    project_position_onto_track_attachment(
        live_position,
        (float*)(slot_base + 0x356438));

    float velocity_z = *((float*)this + 14) * -0.2f;
    Vector3 velocity;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = velocity_z;
    *(Vector3*)(slot_base + 0x35642c) = velocity;

    DWORD* node = (DWORD*)(slot_base + 0x3563a0);
    char* anchor = g_game_base + 0x5a8;
    DWORD tail = (DWORD)((char*)this + 0x3bb764);
    if ((node[1] & 0x200) != 0) {
        report_errorf("List ADDbefore");
    } else {
        node[3] = tail;
        if (*((DWORD*)anchor + 1) == tail) {
            *(DWORD*)(tail + 8) = (DWORD)node;
            *((DWORD*)anchor + 1) = (DWORD)node;
            node[2] = 0;
        } else {
            node[2] = *(DWORD*)(tail + 8);
            *(DWORD*)(tail + 8) = (DWORD)node;
            *(DWORD*)(node[2] + 12) = (DWORD)node;
        }
        node[1] |= 0x200u;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(player->player_slot, 118, -1, -1);
    *(DWORD*)(slot_base + 0x35644c) = (DWORD)sprite;
    DWORD flags = sprite->flags;
    flags |= 0x800;
    sprite->flags = flags;
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->color.set_color_white();
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->gravity_step = 0.0f;
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->progress = 0.0f;
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->progress_step = 0.0f;
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->size_start = 2.0f;
    ((Sprite*)*(DWORD*)(slot_base + 0x35644c))->size_end = 2.0f;

    DWORD* sprite_position =
        (DWORD*)&((Sprite*)*(DWORD*)(slot_base + 0x35644c))->position;
    sprite_position[0] = *(DWORD*)&live_position->x;
    sprite_position[1] = *(DWORD*)&live_position->y;
    sprite_position[2] = *(DWORD*)&live_position->z;
    *(DWORD*)(slot_base + 0x356450) = (DWORD)cell;
    *(unsigned char*)(slot_base + 0x356454) = 0;
    *(unsigned char*)(slot_base + 0x35646c) = 0;
    *(DWORD*)(slot_base + 0x356470) = 0;
    *(float*)(slot_base + 0x356474) =
        *(float*)(g_game_base + 0x74650) * 0.16666667f;
    *(DWORD*)(slot_base + 0x356468) = 7;

    DWORD node_flags = *(DWORD*)(slot_base + 0x3563a4);
    node_flags &= ~0x1000u;
    *(DWORD*)(slot_base + 0x3563a4) = node_flags;
    *(unsigned char*)(slot_base + 0x356478) = 0;
    *(unsigned char*)(slot_base + 0x356479) = 0;
    *(DWORD*)(slot_base + 0x35647c) = 0;
    *(DWORD*)(slot_base + 0x356480) = 0x3d088889;

    if (cell->anchor_position.z > *(float*)((char*)this + 0x1270fcc)) {
        *(DWORD*)(slot_base + 0x356464) = 1;
        *(float*)((char*)this + 0x1270fcc) =
            *(float*)((char*)this + 0x1270fd0)
            + *(float*)((char*)this + 0x1270fcc);
    }

    *(DWORD*)(slot_base + 0x356484) = 0;
    int result = next_math_random_value();
    *(float*)(slot_base + 0x356488) =
        1.0f / (((float)result * 0.000030517578f + 1.0f) * 60.0f);
    return result;
}
