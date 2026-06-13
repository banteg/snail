// project_position_onto_track_attachment @ 0x4444b0 (thiscall, ret 0x8)
#include "vector_types.h"

struct Vector3 {
    float x;
    float y;
    float z;
};

struct TransformMatrix {
    Vector4 basis_right;
    Vector4 basis_up;
    Vector4 basis_forward;
    Vector4 position;
};

struct PathTemplateSample {
    TransformMatrix transform;
    char unknown_40[0x40];
    Vector3 delta_dir_to_next;
    float delta_length;
    float center_x;
    float rotation_scalar_94;
    float rotation_scalar_98;
    float lateral_scale;
    float special_scalar;
    char unknown_a4[0x4];
};

struct PathTemplate {
    int compute_kind42_attachment_transform(
        float radius, float x, float y, TransformMatrix* transform, float* out_angle);

    char unknown_00[0x38];
    int kind;
    char unknown_3c[0x1c];
    PathTemplateSample* primary_samples;
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position;
    char unknown_1c[0x38 - 0x1c];
    PathTemplate* attachment_template_record;

    int get_row_index();
};

struct TrackRuntimeRow {
    int flags;
    char unknown_04[0xa4 - 0x04];
    TrackRowCell* attachment_cell;
};

struct Game {
    char* project_position_onto_track_attachment(float* position, float* out_angle);
};

char* Game::project_position_onto_track_attachment(float* position, float* out_angle)
{
    TrackRuntimeRow* row =
        (TrackRuntimeRow*)((char*)this + 0x5ccac8 + 0xf4 * (int)position[2]);
    *out_angle = 0.0f;
    if ((row->flags & 0x40) != 0) {
        TrackRowCell* cell = row->attachment_cell;
        PathTemplate* template_record = cell->attachment_template_record;
        int sample_index = (int)position[2] - cell->get_row_index();
        PathTemplateSample* sample = &template_record->primary_samples[sample_index];
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
