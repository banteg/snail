// calc_path_length_z @ 0x4217b0 (thiscall, ret 0xc)
// cRPathFollow::CalcPathLengthZ(float, Vec3*, Vec3*): advance the Golb
// projectile path-follow state and return the mode consumed by update_golb_ai.
#include "transform_matrix.h"
#include "golb.h"
#include "track_attachment_types.h"

typedef unsigned int DWORD;

typedef Vector3 Vec3;

#include "track_attachment_matrix_path_view.h"
#include "track_row_cell_anchor_view.h"

void __fastcall set_matrix_identity(TransformMatrix* transform);

int GolbPathFollowState::calc_path_length_z(float path_factor, Vec3* position, Vec3* velocity)
{
    GolbPathTemplate* current_template = template_record;
    AttachmentSampleMatrixView* samples = current_template->secondary_samples;
    int current_index = sample_index;
    float delta = path_factor * samples[current_index].delta_length;

    while (delta + progress > samples[sample_index].delta_length) {
        current_index = sample_index;
        delta -= samples[current_index].delta_length - progress;
        int next_index = current_index + 1;
        progress = 0.0f;
        sample_index = next_index;

        if (next_index == current_template->segment_count) {
            active = 0;
            velocity->z =
                path_factor
                * ((AttachmentSampleMatrixView*)current_template->secondary_samples)[current_template->segment_count - 1]
                      .delta_length;
            shot->position = output_position;

            GolbPathTemplate* terminal_template = template_record;
            if (terminal_template->kind == 31) {
                velocity->y = velocity->z * 0.69999999f;
                float old_x = position->x;
                int count = terminal_template->segment_count;
                float carry = delta + terminal_template->width_or_scale;
                AttachmentSampleMatrixView* terminal =
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
                shot->position.x = position->x;
                shot->position.y = position->y;
                shot->position.z = position->z;
            } else {
                float z =
                    delta
                    + terminal_template->secondary_samples[terminal_template->segment_count - 1]
                          .transform.position.z
                    + source_cell->anchor_position.z
                    + terminal_template->width_or_scale;
                position->z = z;
                shot->position.z = z;
            }
            return 3;
        }

        samples = current_template->secondary_samples;
    }

    float advanced = delta + progress;
    progress = advanced;

    current_template = template_record;
    int terminal_index = current_template->segment_count - 1;

    float center_x;
    if (sample_index == terminal_index) {
        center_x = current_template->primary_samples[sample_index].center_x;
    } else {
        center_x =
            advanced / current_template->secondary_samples[sample_index].delta_length
                * (current_template->primary_samples[sample_index + 1].center_x
                   - current_template->primary_samples[sample_index].center_x)
            + current_template->primary_samples[sample_index].center_x;
    }

    float lateral_scale;
    if (sample_index == terminal_index) {
        lateral_scale = current_template->primary_samples[sample_index].lateral_scale;
    } else {
        lateral_scale =
            advanced / current_template->secondary_samples[sample_index].delta_length
                * (current_template->primary_samples[sample_index + 1].lateral_scale
                   - current_template->primary_samples[sample_index].lateral_scale)
            + current_template->primary_samples[sample_index].lateral_scale;
    }

    float special_scalar;
    if (sample_index == terminal_index) {
        special_scalar = current_template->primary_samples[sample_index].special_scalar;
    } else {
        special_scalar =
            advanced / current_template->secondary_samples[sample_index].delta_length
                * (current_template->primary_samples[sample_index + 1].special_scalar
                   - current_template->primary_samples[sample_index].special_scalar)
            + current_template->primary_samples[sample_index].special_scalar;
    }

    TransformMatrix transform;
    TransformMatrix from;
    TransformMatrix to;
    Vec3* motion = velocity;
    Vec3* input_position = position;
    Vec3* output = &output_position;

    if (current_template->kind == 42) {
        float local_x = input_position->x - center_x;
        ((AttachmentPathTemplate*)current_template)->compute_kind42_attachment_transform(
            special_scalar,
            local_x,
            0.49000001f,
            &transform,
            &special_scalar);

        AttachmentSampleMatrixView* active_sample =
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
        AttachmentSampleMatrixView* secondary = current_template->secondary_samples;
        AttachmentSampleMatrixView* sample = &secondary[sample_index];
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

        if (sample_index == terminal_index) {
            set_matrix_identity(&transform);
        } else {
            from = sample->transform;
            to = secondary[sample_index + 1].transform;
            from.position.z = 0.0f;
            from.position.y = 0.0f;
            from.position.x = 0.0f;
            to.position.z = 0.0f;
            to.position.y = 0.0f;
            to.position.x = 0.0f;
            float alpha =
                advanced / ((AttachmentSampleMatrixView*)current_template->secondary_samples)[sample_index].delta_length;
            transform.linear_interpolate_matrix(&from, &to, alpha);
        }

        transform.basis_right.x *= lateral_scale;
        transform.basis_right.y *= lateral_scale;
        transform.basis_right.z *= lateral_scale;
        vertical_offset = motion->y + vertical_offset;

        float local_x = input_position->x - center_x;
        Vec3 result(
            local_x * transform.basis_right.x + base_x,
            transform.basis_right.y * local_x + base_y,
            local_x * transform.basis_right.z + base_z);
        output->x = result.x;
        output->y = result.y;
        output->z = result.z;
    }

    Vec3* basis_right = &shot->basis_right_scratch;
    basis_right->x = transform.basis_right.x;
    basis_right->y = transform.basis_right.y;
    basis_right->z = transform.basis_right.z;
    Vec3* basis_up = &shot->basis_up_scratch;
    basis_up->x = transform.basis_up.x;
    basis_up->y = transform.basis_up.y;
    basis_up->z = transform.basis_up.z;
    Vec3* basis_forward = &shot->basis_forward_scratch;
    basis_forward->x = transform.basis_forward.x;
    basis_forward->y = transform.basis_forward.y;
    basis_forward->z = transform.basis_forward.z;

    Vec3* shot_velocity = &shot->velocity;
    Vec3* shot_direction = &shot->direction;
    shot_velocity->x = shot_direction->x;
    shot_velocity->y = shot_direction->y;
    shot_velocity->z = shot_direction->z;

    float abs_lateral = input_position->x - center_x;
    if (abs_lateral < 0.0f)
        abs_lateral = -abs_lateral;

    GolbPathTemplate* exit_template = template_record;
    float exit_threshold = (float)exit_template->width_cells * 0.5f + 0.30000001f;
    if (abs_lateral > exit_threshold) {
        active = 0;
        shot->position.x = output_position.x;
        shot->position.y = output_position.y;
        shot->position.z = output_position.z;
        return template_record->side_exit_mode == 0;
    }

    if (exit_template->kind != 42)
        input_position->x = input_position->x + motion->x;
    return 0;
}
