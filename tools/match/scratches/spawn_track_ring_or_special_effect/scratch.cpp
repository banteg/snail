// spawn_track_ring_or_special_effect @ 0x43df10 (thiscall, ret 0x10)

#include "bod_ai_dispatch.h"
#include "game_root.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"
#include <stddef.h>

extern GameRoot* g_game; // data_4df904

float random_float_below(float upper_bound, const char* tag);
int report_errorf(const char* format, ...);

void SubgameRuntime::spawn_track_ring_or_special_effect(
    TrackRowCell* cell,
    int requested_kind,
    Player* player,
    float ring_speed)
{
    int slot_index = 0;
    SubRing* scan = (SubRing*)((char*)this
        + offsetof(SubgameRuntime, ring_effects));
    while (1) {
        if (scan->state == SUB_RING_STATE_INACTIVE)
            break;
        slot_index++;
        scan = (SubRing*)((char*)scan + sizeof(SubRing));
        if (slot_index < SUB_RING_POOL_CAPACITY)
            continue;
        return;
    }

    SubRing* slot = &ring_effects.slots[slot_index];
    float owner_scale = (float)player->movement_flag_selector;
    owner_scale *= 0.125f;
    float default_phase_step =
        1.0f / ((2.0f - base_subgame_rate * 0.300000012f) * 60.0f);
    default_phase_step *= owner_scale;
    default_phase_step *= subgame_rate;
    default_phase_step *= 6.28318548f;
    Vector3* slot_position;
    set_matrix_identity(&slot->transform);

    int kind = requested_kind;
    slot->owner_player = player;
    if (kind == SUB_RING_KIND_NORMAL_DEFAULT) {
        if (random_float_below(1.0f, "RT") > 0.930000007f ||
            (random_float_below(1.0f, "RT2") > 0.5f && level_mode == kind)) {
            kind = SUB_RING_KIND_SLOW_DEFAULT;
        }
    }

    slot_position = &slot->transform.position;
    switch (kind) {
    case SUB_RING_KIND_UNKNOWN_0:
    case SUB_RING_KIND_NORMAL_DEFAULT: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z + 6.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR1") * 6.28318548f;
        slot->active_phase_step = default_phase_step;
        break;
    }
    case SUB_RING_KIND_UNKNOWN_1: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z + 6.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR2") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR3") * 6.28318548f;
        break;
    }
    case SUB_RING_KIND_EXPLODE_RAMP: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 3.5f;
        staged_position.z = cell->position.z + 17.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR4") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR5") * 6.28318548f;
        slot->active_phase_step = default_phase_step;
        break;
    }
    case SUB_RING_KIND_SLOW_DEFAULT: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z + 6.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR6") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR7") * 6.28318548f;
        slot->active_phase_step = default_phase_step;
        break;
    }
    case SUB_RING_KIND_NORMAL_AUTHORED: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z;
        *slot_position = staged_position;
        slot->active_phase = random_float_below(1.0f, "RR10") * 6.28318548f;
        slot->active_phase_step =
            1.0f / (ring_speed * 60.0f) * subgame_rate * 6.28318548f;
        break;
    }
    case SUB_RING_KIND_EXPLODE_AUTHORED: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z;
        *slot_position = staged_position;
        slot->active_phase = random_float_below(1.0f, "RR12") * 6.28318548f;
        slot->active_phase_step =
            1.0f / (ring_speed * 60.0f) * subgame_rate * 6.28318548f;
        break;
    }
    case SUB_RING_KIND_SLOW_AUTHORED: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z;
        *slot_position = staged_position;
        slot->active_phase = random_float_below(1.0f, "RR13") * 6.28318548f;
        slot->active_phase_step =
            1.0f / (ring_speed * 60.0f) * subgame_rate * 6.28318548f;
        break;
    }
    case SUB_RING_KIND_POWER_UP_AUTHORED: {
        Vector3 staged_position;
        staged_position.x = cell->position.x;
        staged_position.y = cell->position.y + 2.5f;
        staged_position.z = cell->position.z;
        *slot_position = staged_position;
        slot->active_phase = random_float_below(1.0f, "RR11") * 6.28318548f;
        slot->active_phase_step =
            1.0f / (ring_speed * 60.0f) * subgame_rate * 6.28318548f;
        break;
    }
    }

    if (kind == SUB_RING_KIND_UNKNOWN_1)
        slot->active_phase_step = default_phase_step;

    TrackRowCell* result = get_track_grid_cell_at_world_position(slot_position);
    if (result->tile_id != 14) {
        slot->kind = (SubRingKind)kind;
        slot->owner_lives_snapshot = player->lives;
        slot->state = SUB_RING_STATE_ACTIVE;
        if (random_float_below(1.0f, "RT1") > 0.5f)
            slot->active_phase_step = slot->active_phase_step * -1.0f;

        if ((slot->list_flags & 0x200) != 0) {
            report_errorf("List ADD");
        } else {
            SubRingListAnchor* active_list =
                (SubRingListAnchor*)&g_game->active_bod_list;
            SubRing** active_head = (SubRing**)&active_list->first;
            if (*active_head == 0) {
                *active_head = slot;
                slot->list_prev = 0;
                (*active_head)->list_next = 0;
            } else {
                (*active_head)->list_prev = slot;
                ((SubRing*)(*active_head)->list_prev)->list_next = *active_head;
                *active_head = (SubRing*)(*active_head)->list_prev;
                (*active_head)->list_prev = 0;
            }
            slot->list_flags |= 0x200;
        }

        slot->initialize_ring_or_special_effect_particles(player->lives);
        ((BodAiDispatch*)slot)->update_bod_ai();
    }
}
