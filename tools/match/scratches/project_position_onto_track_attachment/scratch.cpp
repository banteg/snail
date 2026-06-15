// project_position_onto_track_attachment @ 0x4444b0 (thiscall, ret 0x8)
#include "track_attachment.h"

struct TransformMatrix {
    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

struct Game {
    char* project_position_onto_track_attachment(float* position, float* out_angle);
};

char* Game::project_position_onto_track_attachment(float* position, float* out_angle)
{
    TrackAttachmentRuntimeRow* row =
        (TrackAttachmentRuntimeRow*)((char*)this + 0x5ccac8 + 0xf4 * (int)position[2]);
    *out_angle = 0.0f;
    if ((row->flags & 0x40) != 0) {
        TrackRowCell* cell = row->primary_attachment_cell;
        AttachmentPathTemplate* template_record = cell->attachment_template_record;
        int sample_index = (int)position[2] - cell->get_track_cell_row_index();
        AttachmentSample* sample = &template_record->primary_samples[sample_index];
        if (template_record->kind == 42) {
            TransformMatrix transform;
            int result = template_record->compute_kind42_attachment_transform(
                sample->special_scalar,
                position[0],
                position[1],
                &transform,
                out_angle);
            int y = *(int*)&transform.position.y;
            *(int*)position = *(int*)&transform.position.x;
            *((int*)position + 1) = y;
            return (char*)result;
        } else {
            float vertical = position[1];
            Vector3 vertical_contribution;
            vertical_contribution.x = vertical * sample->transform.basis_up.x;
            vertical_contribution.y = vertical * sample->transform.basis_up.y;
            vertical_contribution.z = vertical * sample->transform.basis_up.z;

            float lateral = position[0] - sample->center_x;
            Vector3 lateral_contribution;
            lateral_contribution.x = lateral * sample->transform.basis_right.x;
            lateral_contribution.y = lateral * sample->transform.basis_right.y;
            lateral_contribution.z = lateral * sample->transform.basis_right.z;

            Vector3 anchored_base;
            anchored_base.x = sample->transform.position.x + cell->anchor_position.x;
            anchored_base.y = sample->transform.position.y + cell->anchor_position.y;
            anchored_base.z = sample->transform.position.z + cell->anchor_position.z;

            Vector3 projected;
            projected.x = anchored_base.x + lateral_contribution.x;
            projected.y = anchored_base.y + lateral_contribution.y;
            projected.z = anchored_base.z + lateral_contribution.z;

            projected.x += vertical_contribution.x;
            position[0] = projected.x;
            projected.y += vertical_contribution.y;
            position[1] = projected.y;
            projected.z += vertical_contribution.z;
            position[2] = projected.z;
            return (char*)*(int*)&projected.x;
        }
    }
    return (char*)row;
}
