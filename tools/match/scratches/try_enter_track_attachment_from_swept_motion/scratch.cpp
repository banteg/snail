// try_enter_track_attachment_from_swept_motion @ 0x42c770 (thiscall, ret 0x1c)
// WIP: real vector expressions and owner fields recovered; see NOTES.md for
// the remaining standard-flags compiler deltas.
#include "track_attachment.h"
#include "game_root.h"

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// The follow state is embedded in the fixed player owned by SubgameRuntime.
extern GameRoot* g_game;
#define PLAYER (&g_game->subgame.player)

void Path::try_enter_track_attachment_from_swept_motion(
    float px, float py, float pz,
    float sweep_x, float sweep_y, float sweep_z,
    TrackRowCell* cell)
{
    Vector3 local;
    Vector3 probe;
    Vector3 sample_origin;
    Vector3 hit_origin;
    Vector3 swept_position;
    Vector3 anchor = cell->position;
    float v19 = anchor.x;
    float v20 = anchor.y;
    float v21 = anchor.z;
    int idx = segment_count - 1;
    if (idx < 0)
        return;
    do {
        if (secondary_samples[idx].transform.basis_up.y > 0.0f) {
            AttachmentSample* sample = &secondary_samples[idx];
            sample_origin = Vector3(
                v19 + sample->transform.position.x,
                v20 + sample->transform.position.y,
                v21 + sample->transform.position.z);
            local = Vector3(px, py, pz) - sample_origin;
            local.rotate_vector_by_matrix(sample->inverse_matrix);
            if ((float)(width_cells / -2) - 0.3f < local.x
                && (float)(width_cells / 2) + 0.3f > local.x
                && local.y >= -0.2
                && local.z > 0.0f) {
                if (local.z < secondary_samples[idx].delta_length) {
                    AttachmentSample* hit = &secondary_samples[idx];
                    hit_origin = Vector3(
                        v19 + hit->transform.position.x,
                        v20 + hit->transform.position.y,
                        v21 + hit->transform.position.z);
                    swept_position =
                        Vector3(px, py, pz) + Vector3(sweep_x, sweep_y, sweep_z);
                    probe = swept_position - hit_origin;
                    probe.rotate_vector_by_matrix(hit->inverse_matrix);
                    if (probe.y <= 0.001f)
                        goto seed;
                }
            }
        }
    } while (--idx >= 0);
    return;

seed:
    // The follow child is embedded at player+0x384; velocity and exit state
    // are adjacent Player fields, not FollowState tail fields.
    PLAYER->attachment_exit_pending = 0;
    PLAYER->squidge.start_squidge_y(PLAYER->velocity.y);
    PLAYER->follow_state.active = 1;
    PLAYER->follow_state.template_record = this;
    PLAYER->follow_state.source_cell = cell;
    PLAYER->follow_state.sample_index = idx;
    PLAYER->follow_state.progress = local.z;
    PLAYER->follow_state.vertical_offset = 0;
    PLAYER->transform.position.y = local.y;
    PLAYER->velocity.y = 0;
    PLAYER->follow_state.player = PLAYER;
    PLAYER->follow_state.template_record->installed_heading_delta =
        g_game->subgame.runtime_rows[cell->get_track_cell_row_index()]
            .installed_heading_delta;
    PLAYER->follow_state.orientation_b = 0;
    PLAYER->follow_state.orientation_a = 0;
    PLAYER->follow_state.update_track_attachment_follow_state(
        PLAYER->velocity.z,
        &PLAYER->transform.position,
        &PLAYER->velocity);
}
