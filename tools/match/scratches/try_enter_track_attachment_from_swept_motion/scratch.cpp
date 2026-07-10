// try_enter_track_attachment_from_swept_motion @ 0x42c770 (thiscall, ret 0x1c)
// WIP: structure aligned (205/204 insns with /Op), registers still shifted —
// see NOTES.md for the recovered semantics and remaining deltas.
#include "track_attachment.h"
#include "player.h"

// The shared scratch follow state and the player both live at fixed offsets
// from the relocatable game base; g_game_base is volatile so every statement
// re-derives it like the original.
extern char* volatile g_game_base;
#define FOLLOW ((FollowState*)(g_follow_state_block + (int)g_game_base))
#define PLAYER ((Player*)(g_player_block + (int)g_game_base))

void AttachmentPathTemplate::try_enter_track_attachment_from_swept_motion(
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
    float v22;
    float v23;
    float v24;
    float v25;
    float v26;
    float v27;
    float v31;
    float v32;
    float v33;
    float v34;
    float v35;
    float v36;
    int idx = segment_count - 1;
    if (idx < 0)
        return;
    do {
        AttachmentSample* s = &secondary_samples[idx];
        if (s->transform.basis_up.y > 0.0f) {
            sample_origin = Vector3(
                v19 + s->transform.position.x,
                v20 + s->transform.position.y,
                v21 + s->transform.position.z);
            v31 = sample_origin.y;
            v32 = sample_origin.z;
            v22 = px - sample_origin.x;
            v23 = py;
            v23 -= v31;
            v24 = pz;
            v24 -= v32;
            local = Vector3(v22, v23, v24);
            local.rotate_vector_by_matrix(&s->inverse_matrix);
            if ((float)(width_cells / -2) - 0.3f < local.x
                && (float)(width_cells / 2) + 0.3f > local.x
                && local.y >= -0.2
                && local.z > 0.0f) {
                AttachmentSample* hit = &secondary_samples[idx];
                if (local.z < hit->delta_length) {
                    hit_origin = Vector3(
                        v19 + hit->transform.position.x,
                        v20 + hit->transform.position.y,
                        v21 + hit->transform.position.z);
                    v35 = hit_origin.y;
                    v36 = hit_origin.z;
                    swept_position = Vector3(sweep_x + px, py + sweep_y, pz + sweep_z);
                    v33 = swept_position.y;
                    v34 = swept_position.z;
                    v25 = swept_position.x - hit_origin.x;
                    v26 = v33;
                    v26 -= v35;
                    v27 = v34;
                    v27 -= v36;
                    probe = Vector3(v25, v26, v27);
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
    char* call_base = g_game_base;
    ((SquidgeState*)(g_player_squidge_offset + (int)call_base))->start_squidge_y(
        ((Vector3*)(g_player_velocity_offset + (int)call_base))->y);
    FOLLOW->active = 1;
    FOLLOW->template_record = this;
    FOLLOW->source_cell = cell;
    FOLLOW->sample_index = idx;
    FOLLOW->progress = local.z;
    FOLLOW->vertical_offset = 0;
    PLAYER->position.y = local.y;
    ((Vector3*)(g_player_velocity_offset + (int)g_game_base))->y = 0;
    char* player_base = g_game_base;
    ((FollowState*)(g_follow_state_block + (int)player_base))->player =
        (Player*)(g_player_block + (int)player_base);
    FOLLOW->template_record->installed_heading_delta =
        *(float*)(g_runtime_row_installed_heading_fields + (int)g_game_base
                  + 4 * (61 * cell->get_track_cell_row_index()));
    FOLLOW->orientation_b = 0;
    FOLLOW->orientation_a = 0;
    char* update_base = g_game_base;
    ((FollowState*)(g_follow_state_block + (int)update_base))->update_track_attachment_follow_state(
        ((Vector3*)(g_player_velocity_offset + (int)update_base))->z,
        (Vector3*)(g_player_position_offset + (int)update_base),
        (Vector3*)(g_player_velocity_offset + (int)update_base));
}
