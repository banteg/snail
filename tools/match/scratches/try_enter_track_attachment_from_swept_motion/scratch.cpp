// try_enter_track_attachment_from_swept_motion @ 0x42c770 (thiscall, ret 0x1c)
// WIP: structure aligned (205/204 insns with /Op), registers still shifted —
// see NOTES.md for the recovered semantics and remaining deltas.
#include "track_attachment.h"

// The shared scratch follow state and the player both live at fixed offsets
// from the relocatable game base; g_game_base is volatile so every statement
// re-derives it like the original.
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
    int idx = sample_count - 1;
    if (idx < 0)
        return;
    do {
        AttachmentSample* s = &samples[idx];
        if (s->active > 0.0f) {
            sample_origin = Vector3(v19 + s->offset.x, v20 + s->offset.y, v21 + s->offset.z);
            v31 = sample_origin.y;
            v32 = sample_origin.z;
            v22 = px - sample_origin.x;
            v23 = py;
            v23 -= v31;
            v24 = pz;
            v24 -= v32;
            local = Vector3(v22, v23, v24);
            local.rotate_by_matrix(s->matrix);
            if ((float)(width_cells / -2) - 0.3f < local.x
                && (float)(width_cells / 2) + 0.3f > local.x
                && local.y >= -0.2
                && local.z > 0.0f) {
                AttachmentSample* hit = &samples[idx];
                if (local.z < hit->delta_length) {
                    hit_origin = Vector3(v19 + hit->offset.x, v20 + hit->offset.y, v21 + hit->offset.z);
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
                    probe.rotate_by_matrix(hit->matrix);
                    if (probe.y <= 0.001f)
                        goto seed;
                }
            }
        }
    } while (--idx >= 0);
    return;

seed:
    // unified layout: these "FollowState" fields are adjacent Player fields
    // (exit_pending +0x41d, velocity.y +0x414, velocity.z +0x418) — the
    // follow struct is embedded at player+0x384. The entry squidges with the
    // incoming fall speed and zeroes it, the exit-lane idiom in reverse.
    FOLLOW->attachment_exit_pending = 0;
    char* call_base = g_game_base;
    ((Player*)(g_player_block + (int)call_base))->start_squidge_y(
        ((FollowState*)(g_follow_state_block + (int)call_base))->player_velocity_y);
    FOLLOW->active = 1;
    FOLLOW->template_record = this;
    FOLLOW->source_cell = cell;
    FOLLOW->sample_index = idx;
    FOLLOW->progress = local.z;
    FOLLOW->vertical_offset = 0;
    PLAYER->position.y = local.y;
    FOLLOW->player_velocity_y = 0;
    char* player_base = g_game_base;
    ((FollowState*)(g_follow_state_block + (int)player_base))->player =
        (Player*)(g_player_block + (int)player_base);
    FOLLOW->template_record->installed_heading_delta =
        *(float*)(g_row_heading_table + (int)g_game_base + 4 * (61 * cell->get_row_index()));
    FOLLOW->orientation_b = 0;
    FOLLOW->orientation_a = 0;
    char* update_base = g_game_base;
    ((FollowState*)(g_follow_state_block + (int)update_base))->update_track_attachment_follow_state(
        ((FollowState*)(g_follow_state_block + (int)update_base))->player_velocity_z,
        &((FollowState*)(g_follow_state_block + (int)update_base))->sample_index,
        &((Player*)(g_player_block + (int)update_base))->position);
}
