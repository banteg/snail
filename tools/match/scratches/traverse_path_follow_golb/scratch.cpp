// traverse_path_follow_golb @ 0x4217b0 (thiscall, ret 0xc)
// cRPathFollowGolb::Traverse(float, Vec3&, Vec3*): advance the Golb
// projectile path-follow state and return the mode consumed by update_golb_ai.
#include "transform_matrix.h"
#include "golb.h"
#include "track_attachment_types.h"

typedef Vector3 Vec3;

int cRPathFollowGolb::traverse_path_follow_golb(float path_factor, Vec3* position, Vec3* velocity)
{
    Path* current_template = template_record;
    AttachmentSample* samples = current_template->secondary_samples;
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
                * current_template->secondary_samples[current_template->segment_count - 1]
                      .delta_length;
            shot->flight_transform.position = output_position;

            Path* terminal_template = template_record;
            if (terminal_template->kind == PATH_TEMPLATE_KIND_SUPERTRAMP) {
                velocity->y = velocity->z * 0.69999999f;
                float old_x = position->x;
                Path* launch_template = template_record;
                int count = launch_template->segment_count;
                float carry = delta + launch_template->width_or_scale;
                AttachmentSample* terminal =
                    &launch_template->secondary_samples[count];
                Vec3* anchor = &source_cell->position;

                Vec3 forward = terminal[-1].transform.basis_forward * carry;
                Vec3 terminal_position;
                terminal_position.x =
                    anchor->x + terminal[-1].transform.position.x + forward.x;
                terminal_position.y =
                    anchor->y + terminal[-1].transform.position.y + forward.y;
                terminal_position.z =
                    anchor->z + terminal[-1].transform.position.z + forward.z;
                *position = terminal_position;
                position->x = old_x;
                shot->flight_transform.position = *position;
            } else {
                float z =
                    delta
                    + terminal_template->secondary_samples[terminal_template->segment_count - 1]
                          .transform.position.z
                    + source_cell->position.z
                    + terminal_template->width_or_scale;
                position->z = z;
                shot->flight_transform.position.z = z;
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

    if (current_template->kind == PATH_TEMPLATE_KIND_NONLINEAR_42) {
        float local_x = input_position->x - center_x;
        current_template->compute_kind42_attachment_transform(
            special_scalar,
            local_x,
            0.49000001f,
            &transform,
            &special_scalar);

        AttachmentSample* active_sample =
            &template_record->secondary_samples[sample_index];
        float z =
            active_sample->delta_dir_to_next.z * progress
            + source_cell->position.z
            + active_sample->transform.position.z;
        transform.basis_right.x *= lateral_scale;
        transform.basis_right.y *= lateral_scale;
        transform.basis_right.z *= lateral_scale;
        vertical_offset = motion->y + vertical_offset;
        output_position.x = transform.position.x;
        output_position.y = transform.position.y;
        output_position.z = z;
    } else {
        AttachmentSample* ordinary_samples =
            current_template->secondary_samples;
        float base_x =
            lateral_scale
                * (advanced
                   * ordinary_samples[sample_index].delta_dir_to_next.x)
            + ordinary_samples[sample_index].transform.position.x
            + source_cell->position.x;
        float base_y =
            lateral_scale
                * (advanced
                   * ordinary_samples[sample_index].delta_dir_to_next.y)
            + ordinary_samples[sample_index].transform.position.y
            + source_cell->position.y;
        float base_z =
            advanced * ordinary_samples[sample_index].delta_dir_to_next.z
            + ordinary_samples[sample_index].transform.position.z
            + source_cell->position.z;
        AttachmentSample* sample = &ordinary_samples[sample_index];

        if (sample_index == terminal_index) {
            transform.Identity();
        } else {
            from = sample->transform;
            to = current_template->secondary_samples[sample_index + 1].transform;
            from.position.z = 0.0f;
            from.position.y = 0.0f;
            from.position.x = 0.0f;
            to.position.z = 0.0f;
            to.position.y = 0.0f;
            to.position.x = 0.0f;
            float alpha =
                advanced / current_template->secondary_samples[sample_index].delta_length;
            transform.LinearInterpolate(from, to, alpha);
        }

        transform.basis_right.x *= lateral_scale;
        transform.basis_right.y *= lateral_scale;
        transform.basis_right.z *= lateral_scale;
        vertical_offset = motion->y + vertical_offset;

        Vec3* output = &output_position;
        float local_x = input_position->x - center_x;
        Vec3 right_offset = transform.basis_right * local_x;
        Vec3 base(base_x, base_y, base_z);
        Vec3 result = right_offset + base;
        *output = result;
    }

    Vec3* basis_right = &shot->flight_transform.basis_right;
    basis_right->x = transform.basis_right.x;
    basis_right->y = transform.basis_right.y;
    basis_right->z = transform.basis_right.z;
    Vec3* basis_up = &shot->flight_transform.basis_up;
    basis_up->x = transform.basis_up.x;
    basis_up->y = transform.basis_up.y;
    basis_up->z = transform.basis_up.z;
    Vec3* basis_forward = &shot->flight_transform.basis_forward;
    basis_forward->x = transform.basis_forward.x;
    basis_forward->y = transform.basis_forward.y;
    basis_forward->z = transform.basis_forward.z;

    shot->velocity = shot->direction;

    float abs_lateral = input_position->x - center_x;
    if (abs_lateral < 0.0f)
        abs_lateral = -abs_lateral;

    Path* exit_template = template_record;
    float exit_threshold = (float)exit_template->width_cells * 0.5f + 0.30000001f;
    if (abs_lateral > exit_threshold) {
        active = 0;
        shot->flight_transform.position = output_position;
        return template_record->side_exit_mode == 0;
    }

    if (exit_template->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
        input_position->x = input_position->x + motion->x;
    return 0;
}
