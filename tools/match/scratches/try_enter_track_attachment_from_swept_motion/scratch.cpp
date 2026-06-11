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
    const Vector3* anchor = &cell->anchor_position;
    float anchor_x = anchor->x;
    float anchor_y = anchor->y;
    float anchor_z = anchor->z;
    int idx = sample_count - 1;
    if (idx < 0)
        return;
    Vector3 local;
    do {
        AttachmentSample* s = &samples[idx];
        if (s->active > 0.0f) {
            float wy = anchor_y + s->offset.y;
            float wz = anchor_z + s->offset.z;
            float dx = px - (anchor_x + s->offset.x);
            local.x = dx;
            float dy = py - wy;
            local.y = dy;
            float dz = pz - wz;
            local.z = dz;
            local.rotate_by_matrix(s->matrix);
            if ((float)(width_cells / -2) - 0.3f < local.x
                && (float)(width_cells / 2) + 0.3f > local.x
                && local.y >= -0.2
                && local.z > 0.0f) {
                AttachmentSample* hit = &samples[idx];
                if (local.z < hit->entry_depth_limit) {
                    float wy2 = anchor_y + hit->offset.y;
                    float wz2 = anchor_z + hit->offset.z;
                    float sy = py + sweep_y;
                    float sz = pz + sweep_z;
                    Vector3 probe;
                    float dx2 = sweep_x + px - (anchor_x + hit->offset.x);
                    probe.x = dx2;
                    float dy2 = sy - wy2;
                    probe.y = dy2;
                    float dz2 = sz - wz2;
                    probe.z = dz2;
                    probe.rotate_by_matrix(hit->matrix);
                    if (probe.y <= 0.001f)
                        goto seed;
                }
            }
        }
    } while (--idx >= 0);
    return;

seed:
    FOLLOW->live_flag = 0;
    PLAYER->start_squidge_y(FOLLOW->squidge_scratch);
    FOLLOW->active = 1;
    FOLLOW->template_record = this;
    FOLLOW->source_cell = cell;
    FOLLOW->sample_index = idx;
    FOLLOW->progress = local.z;
    FOLLOW->vertical_offset = 0;
    PLAYER->position.y = local.y;
    FOLLOW->squidge_scratch = 0;
    FOLLOW->player = PLAYER;
    FOLLOW->template_record->installed_heading_delta =
        *(float*)(g_row_heading_table + (int)g_game_base + 4 * (61 * cell->get_row_index()));
    FOLLOW->field_1c = 0;
    FOLLOW->field_18 = 0;
    FOLLOW->update_track_attachment_follow_state(
        FOLLOW->update_rate, &FOLLOW->sample_index, &PLAYER->position);
}
