// project_position_onto_track_attachment @ 0x4444b0 (thiscall, ret 0x8)
#include "subgame_runtime.h"
#include "track_attachment.h"
#include "transform_matrix.h"

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

void SubgameRuntime::project_position_onto_track_attachment(Vector3* position, float* out_angle)
{
    TrackAttachmentRuntimeRow* row = &runtime_rows[(int)position->z];
    *out_angle = 0.0f;
    if ((row->flags & 0x40) != 0) {
        TrackRowCell* cell = row->primary_attachment_cell;
        Path* template_record = cell->attachment_template_record;
        int sample_index = (int)position->z - cell->get_track_cell_row_index();
        AttachmentSample* sample = &template_record->primary_samples[sample_index];
        if (template_record->kind == 42) {
            TransformMatrix transform;
            template_record->compute_kind42_attachment_transform(
                sample->special_scalar,
                position->x,
                position->y,
                &transform,
                out_angle);
            int y = *(int*)&transform.position.y;
            *(int*)&position->x = *(int*)&transform.position.x;
            *(int*)&position->y = y;
            return;
        } else {
            Vector3 vertical_contribution =
                sample->transform.basis_up * position->y;
            Vector3 lateral_contribution =
                sample->transform.basis_right
                * (position->x - sample->center_x);
            Vector3 anchored_base(
                sample->transform.position.x + cell->anchor_position.x,
                sample->transform.position.y + cell->anchor_position.y,
                sample->transform.position.z + cell->anchor_position.z);
            Vector3 projected = anchored_base + lateral_contribution;
            *position = projected + vertical_contribution;
            return;
        }
    }
}
