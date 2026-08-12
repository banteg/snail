// Controlled same-TU probe in native address order:
//   cRPath::CalcLengthZ                    @ 0x42c600 (exact)
//   cRPath::Search split                   @ 0x42c770 (WIP)
//   cRPath::SearchPos                      @ 0x42ca90 (exact)
// Each body is copied verbatim from its independently recovered scratch.

#include <stddef.h>

#include "track_attachment.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"
#include "game_root.h"

void __fastcall cRPath::CalcLengthZ()
{
    int segment_count = this->segment_count;
    this->row_span_count = 0;

    if (segment_count > 0) {
        float* sample_z = &this->secondary_samples->transform.position.z;
        int remaining = segment_count;
        do {
            int row_span = (int)(*sample_z + 1.0f);
            if (row_span > this->row_span_count)
                this->row_span_count = row_span;
            sample_z = (float*)((char*)sample_z + sizeof(AttachmentSample));
            --remaining;
        } while (remaining != 0);
    }

    int i = 0;
    if (segment_count > 0) {
        do {
            this->primary_samples[i].inverse_matrix.Invert(
                this->primary_samples[i].transform);
            this->secondary_samples[i].inverse_matrix.Invert(
                this->secondary_samples[i].transform);

            ++i;
        } while (i < this->segment_count);
    }

    int segment_index = 0;
    if (this->segment_count - 1 > 0) {
        int sample_offset = 0;
        do {
            Vector3 cross;
            cross.cross_vectors(
                &((AttachmentSample*)((char*)this->primary_samples
                    + sample_offset))->transform.basis_forward,
                &((AttachmentSample*)((char*)this->primary_samples
                    + sample_offset + sizeof(AttachmentSample)))->transform.basis_forward);

            *(float*)((char*)this->primary_samples + sample_offset
                + offsetof(AttachmentSample, lateral_source)) =
                (float)cross.Dot(
                    *(Vector3*)((char*)this->primary_samples + sample_offset));

            if (this->is_mirrored_x)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) *= -1.0f;

            if (*(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) > 0.0f)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) = 0.0f;

            if (*(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) < -0.1f)
                *(float*)((char*)this->primary_samples + sample_offset
                    + offsetof(AttachmentSample, lateral_source)) = -0.1f;

            ++segment_index;
            sample_offset += sizeof(AttachmentSample);
        } while (segment_index < this->segment_count - 1);
    }

    (this->primary_samples + this->segment_count - 1)->lateral_source = 0.0f;
    this->strip_mesh->flags |= OBJECT_FLAG_TEXTURE_TRANSFORM;
    this->strip_mesh->flags &= ~OBJECT_FLAG_DISABLE_CULLING;
}

#define PLAYER (&g_game->subgame.player)

void cRPath::try_enter_track_attachment_from_swept_motion(
    float px, float py, float pz,
    float sweep_x, float sweep_y, float sweep_z,
    cRSubLoc* cell)
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
            local.Rotate(sample->inverse_matrix);
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
                    probe.Rotate(hit->inverse_matrix);
                    if (probe.y <= 0.001f)
                        goto seed;
                }
            }
        }
    } while (--idx >= 0);
    return;

seed:
    PLAYER->attachment_exit_pending = 0;
    PLAYER->squidge.StartY(PLAYER->velocity.y);
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
        g_game->subgame.runtime_rows[cell->Yi()]
            .installed_heading_delta;
    PLAYER->follow_state.orientation_b = 0;
    PLAYER->follow_state.orientation_a = 0;
    PLAYER->follow_state.update_track_attachment_follow_state(
        PLAYER->velocity.z,
        &PLAYER->transform.position,
        &PLAYER->velocity);
}

#undef PLAYER

bool cRPath::SearchPos(
    tVector probe, tVector swept_motion, cRSubLoc* cell)
{
    Vector3 local;
    Vector3 sample_origin;
    Vector3 anchor = cell->position;
    float anchor_x = anchor.x;
    float anchor_y = anchor.y;
    float anchor_z = anchor.z;

    int idx = segment_count - 1;
    while (idx >= 0) {
        sample_origin.x = anchor_x + secondary_samples[idx].transform.position.x;
        sample_origin.y = anchor_y + secondary_samples[idx].transform.position.y;
        TransformMatrix* inverse_matrix = &secondary_samples[idx].inverse_matrix;
        sample_origin.z = anchor_z + secondary_samples[idx].transform.position.z;
        local = probe - sample_origin;
        local.Rotate(*inverse_matrix);

        if ((float)(width_cells / -2) - 0.300000012f < local.x
            && (float)(width_cells / 2) + 0.300000012f > local.x
            && local.y >= -0.300000012f
            && local.y < 0.300000012f
            && local.z > 0.0f
            && local.z < secondary_samples[idx].delta_length)
        {
            return true;
        }
        idx--;
    }

    return false;
}
