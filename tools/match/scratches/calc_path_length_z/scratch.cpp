// calc_path_length_z @ 0x4217b0 (thiscall, ret 0xc)
// cRPathFollow::CalcPathLengthZ(float, Vec3*, Vec3*): advance the Golb
// projectile path-follow state and return the mode consumed by update_golb_ai.

typedef unsigned int DWORD;

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct TransformMatrix {
    void linear_interpolate_matrix(
        const TransformMatrix* from,
        const TransformMatrix* to,
        float alpha);

    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
};

struct PathTemplateSample {
    TransformMatrix transform; // +0x00
    char unknown_40[0x40];
    Vec3 delta_dir_to_next; // +0x80
    float delta_length; // +0x8c
    float center_x; // +0x90
    float rotation_scalar_94; // +0x94
    float rotation_scalar_98; // +0x98
    float lateral_scale; // +0x9c
    float special_scalar; // +0xa0
    char unknown_a4[0x04];
};

struct PathTemplate {
    char unknown_00[0x38];
    int kind; // +0x38
    char unknown_3c[0x40 - 0x3c];
    int side_exit_mode; // +0x40
    int segment_count; // +0x44
    char unknown_48[0x50 - 0x48];
    float width_or_scale; // +0x50
    int width_cells; // +0x54
    PathTemplateSample* primary_samples; // +0x58
    PathTemplateSample* secondary_samples; // +0x5c
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vec3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    PathTemplate* attachment_template_record; // +0x38
};

struct GolbShot {
    char unknown_000[0x1c4];
    Vec3 basis_right_scratch; // +0x1c4
    char unknown_1d0[0x1d4 - 0x1d0];
    Vec3 basis_up_scratch; // +0x1d4
    char unknown_1e0[0x1e4 - 0x1e0];
    Vec3 basis_forward_scratch; // +0x1e4
    char unknown_1f0[0x1f4 - 0x1f0];
    Vec3 position; // +0x1f4
    char unknown_200[0x24c - 0x200];
    Vec3 velocity; // +0x24c
    Vec3 direction; // +0x258
};

class GolbPathFollowState {
public:
    int calc_path_length_z(float path_factor, Vec3* position, Vec3* velocity);

    unsigned char active; // +0x00
    char unknown_01[0x04 - 0x01];
    PathTemplate* template_record; // +0x04
    TrackRowCell* source_cell; // +0x08
    int sample_index; // +0x0c
    float progress; // +0x10
    float vertical_offset; // +0x14
    Vec3 output_position; // +0x18
    GolbShot* shot; // +0x24
};

void __fastcall set_matrix_identity(TransformMatrix* transform);
int __stdcall compute_kind42_attachment_transform(
    float radius,
    float x,
    float y,
    TransformMatrix* transform,
    float* out_angle);

int GolbPathFollowState::calc_path_length_z(float path_factor, Vec3* position, Vec3* velocity)
{
    PathTemplate* current_template = template_record;
    PathTemplateSample* samples = current_template->secondary_samples;
    int current_index = sample_index;
    float delta = path_factor * samples[current_index].delta_length;

    if (delta + progress > samples[current_index].delta_length) {
        for (;;) {
            current_index = sample_index;
            float remaining = samples[current_index].delta_length - progress;
            progress = 0.0f;
            sample_index = current_index + 1;
            delta = delta - remaining;

            if (current_index + 1 == current_template->segment_count) {
                active = 0;
                velocity->z =
                    path_factor
                    * current_template->secondary_samples[current_template->segment_count - 1]
                          .delta_length;
                shot->position = output_position;

                PathTemplate* terminal_template = template_record;
                if (terminal_template->kind == 31) {
                    velocity->y = velocity->z * 0.69999999f;
                    float old_x = position->x;
                    int count = terminal_template->segment_count;
                    float carry = delta + terminal_template->width_or_scale;
                    PathTemplateSample* terminal =
                        &terminal_template->secondary_samples[count];
                    Vec3* anchor = &source_cell->anchor_position;

                    float forward_x = carry * terminal[-1].transform.basis_forward.x;
                    float forward_y = carry * terminal[-1].transform.basis_forward.y;
                    float forward_z = carry * terminal[-1].transform.basis_forward.z;
                    float base_x = anchor->x + terminal[-1].transform.position.x;
                    float base_y = anchor->y + terminal[-1].transform.position.y;
                    float base_z = anchor->z + terminal[-1].transform.position.z;
                    position->x = base_x + forward_x;
                    position->y = base_y + forward_y;
                    position->z = base_z + forward_z;
                    position->x = old_x;
                    shot->position = *position;
                } else {
                    float z =
                        delta
                        + terminal_template
                              ->secondary_samples[terminal_template->segment_count - 1]
                              .transform.position.z
                        + source_cell->anchor_position.z
                        + terminal_template->width_or_scale;
                    position->z = z;
                    shot->position.z = z;
                }
                return 3;
            }

            samples = current_template->secondary_samples;
            current_index = sample_index;
            if (delta <= samples[current_index].delta_length)
                break;
        }
    }

    current_index = sample_index;
    float advanced = delta + progress;
    progress = advanced;

    current_template = template_record;
    int terminal_index = current_template->segment_count - 1;
    int sample_offset = 0xa8 * current_index;
    PathTemplateSample* primary =
        (PathTemplateSample*)((char*)current_template->primary_samples + sample_offset);

    float center_x;
    if (current_index == terminal_index) {
        center_x = primary->center_x;
    } else {
        center_x =
            advanced / current_template->secondary_samples[current_index].delta_length
                * (primary[1].center_x - primary->center_x)
            + primary->center_x;
    }

    float lateral_scale;
    if (current_index == terminal_index) {
        lateral_scale = primary->lateral_scale;
    } else {
        lateral_scale =
            advanced / current_template->secondary_samples[current_index].delta_length
                * (primary[1].lateral_scale - primary->lateral_scale)
            + primary->lateral_scale;
    }

    float special_scalar;
    if (current_index == terminal_index) {
        special_scalar = primary->special_scalar;
    } else {
        special_scalar =
            advanced / current_template->secondary_samples[current_index].delta_length
                * (primary[1].special_scalar - primary->special_scalar)
            + primary->special_scalar;
    }

    TransformMatrix transform;
    TransformMatrix from;
    TransformMatrix to;
    Vec3* motion = velocity;
    Vec3* input_position = position;
    Vec3* output = &output_position;

    if (current_template->kind == 42) {
        float local_x = input_position->x - center_x;
        compute_kind42_attachment_transform(
            special_scalar,
            local_x,
            0.49000001f,
            &transform,
            &special_scalar);

        PathTemplateSample* active_sample =
            &template_record->secondary_samples[sample_index];
        float z =
            active_sample->delta_dir_to_next.z * progress
            + source_cell->anchor_position.z
            + active_sample->transform.position.z;
        transform.basis_right.x *= lateral_scale;
        transform.basis_right.y *= lateral_scale;
        transform.basis_right.z *= lateral_scale;
        vertical_offset = motion->y + vertical_offset;
        output->x = transform.position.x;
        output->y = transform.position.y;
        output->z = z;
    } else {
        PathTemplateSample* secondary = current_template->secondary_samples;
        PathTemplateSample* sample = &secondary[current_index];
        Vec3* anchor = &source_cell->anchor_position;
        float base_x =
            advanced * sample->delta_dir_to_next.x * lateral_scale
            + sample->transform.position.x
            + anchor->x;
        float base_y =
            advanced * sample->delta_dir_to_next.y * lateral_scale
            + sample->transform.position.y
            + anchor->y;
        float base_z =
            advanced * sample->delta_dir_to_next.z
            + sample->transform.position.z
            + anchor->z;

        if (current_index == terminal_index) {
            set_matrix_identity(&transform);
        } else {
            from = sample->transform;
            to = secondary[current_index + 1].transform;
            from.position.x = 0.0f;
            from.position.y = 0.0f;
            from.position.z = 0.0f;
            to.position.x = 0.0f;
            to.position.y = 0.0f;
            to.position.z = 0.0f;
            float alpha =
                advanced / current_template->secondary_samples[current_index].delta_length;
            transform.linear_interpolate_matrix(&from, &to, alpha);
        }

        transform.basis_right.x *= lateral_scale;
        transform.basis_right.y *= lateral_scale;
        transform.basis_right.z *= lateral_scale;
        vertical_offset = motion->y + vertical_offset;

        float local_x = input_position->x - center_x;
        output->x = local_x * transform.basis_right.x + base_x;
        output->y = transform.basis_right.y * local_x + base_y;
        output->z = local_x * transform.basis_right.z + base_z;
    }

    shot->basis_right_scratch.x = transform.basis_right.x;
    shot->basis_right_scratch.y = transform.basis_right.y;
    shot->basis_right_scratch.z = transform.basis_right.z;
    shot->basis_up_scratch.x = transform.basis_up.x;
    shot->basis_up_scratch.y = transform.basis_up.y;
    shot->basis_up_scratch.z = transform.basis_up.z;
    shot->basis_forward_scratch.x = transform.basis_forward.x;
    shot->basis_forward_scratch.y = transform.basis_forward.y;
    shot->basis_forward_scratch.z = transform.basis_forward.z;

    shot->velocity = shot->direction;

    double abs_lateral = input_position->x - center_x;
    if (abs_lateral < 0.0)
        abs_lateral = -abs_lateral;

    PathTemplate* exit_template = template_record;
    float exit_threshold = (float)exit_template->width_cells * 0.5f + 0.30000001f;
    if (abs_lateral <= exit_threshold) {
        if (exit_template->kind != 42)
            input_position->x = input_position->x + motion->x;
        return 0;
    }

    active = 0;
    shot->position = output_position;
    return template_record->side_exit_mode == 0;
}
