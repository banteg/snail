// try_enter_track_attachment_from_swept_motion @ 0x42c770 (thiscall, ret 0x1c)
// WIP: real vector expressions and owner fields recovered; see NOTES.md for
// the remaining standard-flags compiler deltas.
#include "track_attachment.h"
#include "player.h"

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// The follow state is embedded in the fixed player owned by SubgameRuntime.
extern char* g_game_base;
#define FOLLOW ((FollowState*)(g_follow_state_block + (int)g_game_base))
#define PLAYER ((Player*)(g_player_block + (int)g_game_base))

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
    Vector3 anchor = cell->anchor_position;
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
            local.rotate_vector_by_matrix(&sample->inverse_matrix);
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
                    probe.rotate_vector_by_matrix(&hit->inverse_matrix);
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
    *(unsigned char*)(g_player_attachment_exit_pending_offset + (int)g_game_base) = 0;
    ((Squidge*)(g_player_squidge_offset + (int)g_game_base))->start_squidge_y(
        ((Vector3*)(g_player_velocity_offset + (int)g_game_base))->y);
    FOLLOW->active = 1;
    FOLLOW->template_record = this;
    FOLLOW->source_cell = cell;
    FOLLOW->sample_index = idx;
    FOLLOW->progress = local.z;
    FOLLOW->vertical_offset = 0;
    PLAYER->position.y = local.y;
    ((Vector3*)(g_player_velocity_offset + (int)g_game_base))->y = 0;
    FOLLOW->player = PLAYER;
    FOLLOW->template_record->installed_heading_delta =
        *(float*)(g_runtime_row_installed_heading_fields + (int)g_game_base
                  + 4 * (61 * cell->get_track_cell_row_index()));
    FOLLOW->orientation_b = 0;
    FOLLOW->orientation_a = 0;
    FOLLOW->update_track_attachment_follow_state(
        ((Vector3*)(g_player_velocity_offset + (int)g_game_base))->z,
        (Vector3*)(g_player_position_offset + (int)g_game_base),
        (Vector3*)(g_player_velocity_offset + (int)g_game_base));
}
