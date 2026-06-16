// spawn_track_ring_or_special_effect @ 0x43df10 (thiscall, ret 0x10)

#include "player.h"
#include "ring_special_effect_types.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

extern char* g_game_base; // data_4df904

float random_float_below(float upper_bound, const char* tag);
int report_errorf(const char* format, ...);

class Game {
public:
    TrackRowCell* spawn_track_ring_or_special_effect(
        TrackRowCell* cell,
        int requested_kind,
        Player* player,
        float ring_speed);
    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);

    char unknown_00[0x38];
    float subgame_rate; // +0x38
    char unknown_3c[0x40 - 0x3c];
    int level_mode; // +0x40
    char unknown_44[0x48 - 0x44];
    float base_subgame_rate; // +0x48
};

class RingOrSpecialEffectVirtual {
public:
    virtual TrackRowCell* update_subgoldy_bullet(); // vtable slot 0
};

TrackRowCell* Game::spawn_track_ring_or_special_effect(
    TrackRowCell* cell,
    int requested_kind,
    Player* player,
    float ring_speed)
{
    int slot_index = 0;
    RingOrSpecialEffectParent* scan =
        (RingOrSpecialEffectParent*)((char*)this + 0x35b78c);
    while (1) {
        if (scan->state == 0)
            break;
        slot_index++;
        scan = (RingOrSpecialEffectParent*)((char*)scan + 0x1f8);
        if (slot_index < 2)
            continue;
        return (TrackRowCell*)slot_index;
    }

    float owner_scale = (float)player->movement_flag_selector;
    owner_scale *= 0.125f;
    float default_phase_step =
        1.0f / ((2.0f - base_subgame_rate * 0.300000012f) * 60.0f);
    default_phase_step *= owner_scale;
    default_phase_step *= subgame_rate;
    default_phase_step *= 6.28318548f;
    char* slot_base = (char*)this + slot_index * 0x1f8;
    RingOrSpecialEffectParent* slot =
        (RingOrSpecialEffectParent*)(slot_base + 0x35b78c);
    Vector3* slot_position = (Vector3*)(slot_base + 0x35b7f4);
    set_matrix_identity((TransformMatrix*)((char*)slot + 0x38));

    int kind = requested_kind;
    slot->owner_player = player;
    if (kind == 4) {
        if (random_float_below(1.0f, "RT") > 0.930000007f ||
            (random_float_below(1.0f, "RT2") > 0.5f && level_mode == kind)) {
            kind = 3;
        }
    }

    switch (kind) {
    case 0:
    case 1:
    case 3:
    case 4: {
        Vector3 staged_position;
        staged_position.x = cell->anchor_position.x;
        staged_position.y = cell->anchor_position.y + 2.5f;
        staged_position.z = cell->anchor_position.z + 6.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR1") * 6.28318548f;
        slot->active_phase_step = default_phase_step;
        break;
    }
    case 2: {
        Vector3 staged_position;
        staged_position.x = cell->anchor_position.x;
        staged_position.y = cell->anchor_position.y + 3.5f;
        staged_position.z = cell->anchor_position.z + 17.0f;
        *slot_position = staged_position;
        double random_x = random_float_below(1.0f, "RR4") - 0.5f;
        slot_position->x = (float)((random_x + random_x) * 3.0);
        slot->active_phase = random_float_below(1.0f, "RR5") * 6.28318548f;
        slot->active_phase_step = default_phase_step;
        break;
    }
    case 5:
    case 6:
    case 7:
    case 8: {
        Vector3 staged_position;
        staged_position.x = cell->anchor_position.x;
        staged_position.y = cell->anchor_position.y + 2.5f;
        staged_position.z = cell->anchor_position.z;
        *slot_position = staged_position;
        slot->active_phase = random_float_below(1.0f, "RR10") * 6.28318548f;
        slot->active_phase_step =
            1.0f / (ring_speed * 60.0f) * subgame_rate * 6.28318548f;
        break;
    }
    }

    TrackRowCell* result = get_track_grid_cell_at_world_position(slot_position);
    if (result->tile_id != 14) {
        slot->kind = kind;
        slot->owner_lives_snapshot = player->lives;
        slot->state = 1;
        if (random_float_below(1.0f, "RT1") > 0.5f)
            slot->active_phase_step = slot->active_phase_step * -1.0f;

        if ((slot->list_flags & 0x200) != 0) {
            report_errorf("List ADD");
        } else {
            RingOrSpecialEffectListAnchor* active_list =
                (RingOrSpecialEffectListAnchor*)(g_game_base + 0x5a8);
            RingOrSpecialEffectParent** active_head =
                (RingOrSpecialEffectParent**)&active_list->first;
            if (*active_head != 0) {
                (*active_head)->list_prev = slot;
                ((RingOrSpecialEffectParent*)(*active_head)->list_prev)->list_next = *active_head;
                *active_head = (RingOrSpecialEffectParent*)(*active_head)->list_prev;
                (*active_head)->list_prev = 0;
            } else {
                *active_head = slot;
                slot->list_prev = 0;
                (*active_head)->list_next = 0;
            }
            slot->list_flags |= 0x200;
        }

        slot->initialize_ring_or_special_effect_particles(player->lives);
        return ((RingOrSpecialEffectVirtual*)slot)->update_subgoldy_bullet();
    }

    return result;
}
