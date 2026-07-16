// spawn_slug_hazard @ 0x43dc80 (thiscall, ret 0x8)
// cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*): allocate a slug runtime slot,
// seed its renderable body state, link it into the shared BOD list, and attach
// the live sprite presentation.

#include "game_root.h"
#include "bod_flags.h"
#include "player.h"
#include "slug_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"


int next_math_random_value();
int report_errorf(char* format, ...);

int SubgameRuntime::spawn_slug_hazard(TrackRowCell* cell, Player* owner_player)
{
    int slot_index = 0;
    Slug* scan = slug_hazards.slots;
    while (1) {
        if (scan->state == SUB_SLUG_STATE_INACTIVE)
            break;
        ++slot_index;
        ++scan;
        if (slot_index < SUB_SLUG_SLOT_CAPACITY)
            continue;
        return slot_index;
    }

    int* state_ref = &slug_hazards.slots[slot_index].state;
    Player** player_ref = &slug_hazards.slots[slot_index].owner_player;
    *state_ref = SUB_SLUG_STATE_ACTIVE;
    *player_ref = owner_player;
    slug_hazards.slots[slot_index].transform.set_matrix_identity();

    Vector3 staged_position;
    staged_position.y = cell->position.y + 1.7f;
    staged_position.x = cell->position.x;
    staged_position.z = cell->position.z;
    Vector3* live_position =
        &slug_hazards.slots[slot_index].transform.position;
    *live_position = staged_position;
    project_position_onto_track_attachment(
        live_position,
        &slug_hazards.slots[slot_index].attachment_facing_angle);

    Vector3 velocity = Vector3(0.0f, 0.0f, -0.2f) * subgame_rate;
    slug_hazards.slots[slot_index].velocity = velocity;

    BodNode* node = &slug_hazards.slots[slot_index];
    BodNode* tail = &this->player;
    BodList* anchor = &g_game->active_bod_list;
    if ((node->list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf("List ADDbefore");
    } else {
        node->list_next = tail;
        if (anchor->first == tail) {
            tail->list_prev = node;
            anchor->first = node;
            node->list_prev = 0;
        } else {
            node->list_prev = tail->list_prev;
            tail->list_prev = node;
            node->list_prev->list_next = node;
        }
        node->list_flags |= BOD_FLAG_LINKED;
    }

    Sprite* sprite =
        g_sprite_manager.allocate_sprite(owner_player->player_slot, 118, -1, -1);
    slug_hazards.slots[slot_index].sprite = sprite;
    unsigned int flags = sprite->flags;
    flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    sprite->flags = flags;
    slug_hazards.slots[slot_index].sprite->color.set_color_white();
    slug_hazards.slots[slot_index].sprite->gravity_step = 0.0f;
    slug_hazards.slots[slot_index].sprite->progress = 0.0f;
    slug_hazards.slots[slot_index].sprite->progress_step = 0.0f;
    slug_hazards.slots[slot_index].sprite->size_start = 2.0f;
    slug_hazards.slots[slot_index].sprite->size_end = 2.0f;

    slug_hazards.slots[slot_index].sprite->position = *live_position;
    slug_hazards.slots[slot_index].source_cell = cell;
    slug_hazards.slots[slot_index].passed_player = 0;
    slug_hazards.slots[slot_index].hit_flash_pending = 0;
    slug_hazards.slots[slot_index].hit_flash_progress = 0.0f;
    float* hit_flash_step_ref =
        &slug_hazards.slots[slot_index].hit_flash_progress_step;
    *hit_flash_step_ref =
        g_game->subgame.subgame_rate * 0.16666667f;
    int* hit_points_ref = &slug_hazards.slots[slot_index].hit_points;
    *hit_points_ref = 7;

    int* node_flags_ref = &slug_hazards.slots[slot_index].list_flags;
    unsigned int node_flags = (unsigned int)*node_flags_ref;
    node_flags &= ~BOD_FLAG_SUPPRESS_CONTACT;
    *node_flags_ref = node_flags;
    slug_hazards.slots[slot_index].voice_active = 0;
    slug_hazards.slots[slot_index].player_encounter_latched = 0;
    slug_hazards.slots[slot_index].voice_progress = 0.0f;
    slug_hazards.slots[slot_index].voice_progress_step = 0.0333333351f;

    if (cell->position.z > next_slug_voice_trigger_z) {
        slug_hazards.slots[slot_index].engagement_voice_gate = 1;
        next_slug_voice_trigger_z =
            slug_voice_trigger_spacing_z + next_slug_voice_trigger_z;
    }

    slug_hazards.slots[slot_index].blink_progress = 0.0f;
    int result = next_math_random_value();
    slug_hazards.slots[slot_index].blink_step =
        1.0f / (((float)result * 0.000030517578f + 1.0f) * 60.0f);
    return result;
}
