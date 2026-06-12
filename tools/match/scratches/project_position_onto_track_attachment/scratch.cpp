// project_position_onto_track_attachment @ 0x4444b0 (thiscall, ret 0x8)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
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

int __stdcall compute_kind42_attachment_transform(
    float radius, float x, float y, TransformMatrix* transform, float* out_angle);

char* Game::project_position_onto_track_attachment(float* position, float* out_angle)
{
    float v12;
    float v13;
    float v14;
    float v15;
    float v16;
    float v17;
    float v18;
    float v19;
    float v20;
    float v21;
    float v22;
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
            int result = compute_kind42_attachment_transform(
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
            float v8 = position[1];
            v21 = v8 * sample->transform.basis_up.x;
            v22 = v8 * sample->transform.basis_up.y;
            float v9 = v8 * sample->transform.basis_up.z;
            float v10 = position[0] - sample->center_x;
            v12 = v10 * sample->transform.basis_right.x;
            v14 = v10 * sample->transform.basis_right.y;
            v17 = sample->transform.position.y + cell->anchor_position.y;
            v18 = sample->transform.position.z + cell->anchor_position.z;
            v19 = sample->transform.position.x + cell->anchor_position.x + v12;
            v20 = v17 + v14;
            float v11 = v10 * sample->transform.basis_right.z + v18;
            v13 = v19 + v21;
            position[0] = v13;
            v15 = v20 + v22;
            position[1] = v15;
            v16 = v11 + v9;
            position[2] = v16;
            return (char*)*(int*)&v13;
        }
    }
    return (char*)row;
}
