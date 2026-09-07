// cRPathFollowGoldy::Traverse @ 0x420cb0 (thiscall, ret 0xc)
#include "game_root.h"
#include "player.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"
#include "voice_manager.h"
#include "vector3.h"

typedef Vector3 Vec3;

int cRPathFollowGoldy::Traverse(
    float path_factor,
    Vec3& out_position,
    Vec3* motion)
{
    int index = sample_index;
    Path* initial_template = this->template_record;
    AttachmentSample* secondary_samples = initial_template->secondary_samples;
    float* p_delta_length = &secondary_samples[index].delta_length;
    float delta = path_factor * *p_delta_length;
    float ordinary_alpha;
    float sample_progress;
    float special_scalar;
    float nonlinear_x;
    float lateral_scale;
    Vec3 base_position;
    float center_x;
    TransformMatrix transform;
    TransformMatrix nonlinear_from;
    TransformMatrix ordinary_from;
    TransformMatrix ordinary_to;
    TransformMatrix nonlinear_to;

    unsigned int current_index;
    Path* current_template;
    int sample_count;
    while (delta + progress > *p_delta_length) {
        delta -= *p_delta_length - progress;
        ++index;
        progress = 0.0f;
        sample_index = index;

        if (index == 2 * this->template_record->segment_count) {
            g_voice_manager.Play(
                VOICE_SET_MISC, VOICE_PLAY_AFTER_GLOBAL_COOLDOWN, -1);
        }

        Path* runtime_template = this->template_record;
        if (runtime_template->has_entry_mesh_transition) {
            int count = (int)runtime_template->segment_count;
            int current_index = (int)this->sample_index;
            if (current_index == count - 1) {
                Path* attached =
                    g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->attachment_template_record;
                g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->object = attached->entry_base_strip_mesh;
                g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->color.a = 1.0f;
            } else if (current_index == (3 * count) / 7) {
                g_game->subgame.runtime_rows[source_cell->Yi()]
                    .primary_attachment_cell->list_flags |=
                    BOD_FLAG_AFTER_SPRITES;
                Path* attached =
                    g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->attachment_template_record;
                g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->object = attached->entry_transition_strip_mesh;
                g_game->subgame.runtime_rows[source_cell->Yi()].primary_attachment_cell->color.a = 0.6f;
            }
        }

        Path* loop_template = this->template_record;
        index = this->sample_index;
        if (index == loop_template->segment_count)
            goto terminal_path;
        secondary_samples = loop_template->secondary_samples;
        p_delta_length = &secondary_samples[index].delta_length;
    }

    {
        current_index = sample_index;
        sample_progress = delta + progress;
        progress = sample_progress;
        current_template = this->template_record;
        sample_count = current_template->segment_count;
        if (current_index == (unsigned int)(sample_count - 1)) {
            center_x = current_template->primary_samples[current_index].center_x;
        } else {
            center_x = sample_progress / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].center_x
                    - current_template->primary_samples[current_index].center_x)
                + current_template->primary_samples[current_index].center_x;
        }
        if (current_index == (unsigned int)(sample_count - 1)) {
            lateral_scale = current_template->primary_samples[current_index].lateral_scale;
        } else {
            lateral_scale = sample_progress / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].lateral_scale
                    - current_template->primary_samples[current_index].lateral_scale)
                + current_template->primary_samples[current_index].lateral_scale;
        }
        if (current_index == (unsigned int)(sample_count - 1)) {
            special_scalar = current_template->primary_samples[current_index].special_scalar;
        } else {
            special_scalar = sample_progress / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].special_scalar
                    - current_template->primary_samples[current_index].special_scalar)
                + current_template->primary_samples[current_index].special_scalar;
        }

        float& input_x = out_position.x;
        Vec3* output = &output_position;
        if (current_template->kind == PATH_TEMPLATE_KIND_NONLINEAR_42) {
            float nonlinear_output;
            nonlinear_x = input_x - center_x;
            current_template->compute_kind42_attachment_transform(
                special_scalar, nonlinear_x, 0.49000001f, &transform, &nonlinear_output);
            unsigned int active_index = sample_index;
            if (active_index == 0 || active_index == (unsigned int)(this->template_record->segment_count - 1)) {
                nonlinear_from.Identity();
                nonlinear_from.position.x = transform.position.x;
                nonlinear_from.position.y = transform.position.y;
                nonlinear_from.position.z = transform.position.z;
                nonlinear_to = transform;
                float blend;
                if (sample_index == 0)
                    blend = progress;
                else
                    blend = 1.0f - progress;
                transform.LinearInterpolate(nonlinear_from, nonlinear_to, blend);
            }

            float y = transform.position.y;
            float z =
                this->template_record->secondary_samples[sample_index].delta_dir_to_next.z * progress
                + source_cell->position.z
                + this->template_record->secondary_samples[sample_index].transform.position.z;
            transform.basis_right.x *= lateral_scale;
            transform.basis_right.y *= lateral_scale;
            transform.basis_right.z *= lateral_scale;
            float vertical = motion->y + vertical_offset;
            output->x = transform.position.x;
            output->y = y;
            vertical_offset = vertical;
            output->z = z;
            g_game->subgame.player.transform.basis_right = transform.basis_right;
            g_game->subgame.player.transform.basis_up = transform.basis_up;
            g_game->subgame.player.transform.basis_forward = transform.basis_forward;
        } else {
            AttachmentSample* secondary = current_template->secondary_samples;
            AttachmentSample* sample = &secondary[current_index];
            base_position.x = lateral_scale * (sample_progress * secondary[current_index].delta_dir_to_next.x)
                + secondary[current_index].transform.position.x + source_cell->position.x;
            base_position.y = lateral_scale * (sample_progress * secondary[current_index].delta_dir_to_next.y)
                + secondary[current_index].transform.position.y + source_cell->position.y;
            base_position.z = sample_progress * secondary[current_index].delta_dir_to_next.z
                + secondary[current_index].transform.position.z + source_cell->position.z;
            if (current_index == (unsigned int)(sample_count - 1)) {
                transform.Identity();
            } else {
                ordinary_from = sample->transform;
                ordinary_to = current_template->secondary_samples[current_index + 1].transform;
                ordinary_from.position.z = 0.0f;
                ordinary_from.position.y = 0.0f;
                ordinary_from.position.x = 0.0f;
                ordinary_to.position.z = 0.0f;
                ordinary_to.position.y = 0.0f;
                ordinary_to.position.x = 0.0f;
                ordinary_alpha = sample_progress / current_template->secondary_samples[current_index].delta_length;
                transform.LinearInterpolate(ordinary_from, ordinary_to, ordinary_alpha);
            }

            transform.basis_right.x *= lateral_scale;
            transform.basis_right.y *= lateral_scale;
            transform.basis_right.z *= lateral_scale;
            float vertical = motion->y + vertical_offset;
            vertical_offset = vertical;
            Vec3 up_offset = transform.basis_up * vertical;
            float local_x = input_x - center_x;
            Vec3 right_offset = transform.basis_right * local_x;
            Vec3 result = (right_offset + base_position) + up_offset;
            *output = result;
            g_game->subgame.player.transform.basis_right = transform.basis_right;
            g_game->subgame.player.transform.basis_up = transform.basis_up;
            g_game->subgame.player.transform.basis_forward = transform.basis_forward;
        }

        orientation_up = transform.basis_up;

        Path* orient_template = this->template_record;
        unsigned int orient_index = sample_index;
        if (orient_index == (unsigned int)(orient_template->segment_count - 1)) {
            orientation_b = orient_template->primary_samples[orient_index].rotation_scalar_98;
            orientation_a = orient_template->primary_samples[orient_index].rotation_scalar_94;
        } else {
            float delta_b =
                orient_template->primary_samples[orient_index + 1].rotation_scalar_98
                - orient_template->primary_samples[orient_index].rotation_scalar_98;
            if (delta_b > 3.1415927f) {
                delta_b = delta_b - 6.2831855f;
            } else if (delta_b < -3.1415927f) {
                delta_b = delta_b + 6.2831855f;
            }
            orientation_b =
                progress / orient_template->secondary_samples[orient_index].delta_length
                * delta_b
                + orient_template->primary_samples[orient_index].rotation_scalar_98;
            float delta_a =
                orient_template->primary_samples[orient_index + 1].rotation_scalar_94
                - orient_template->primary_samples[orient_index].rotation_scalar_94;
            if (delta_a > 3.1415927f) {
                delta_a = delta_a - 6.2831855f;
            } else if (delta_a < -3.1415927f) {
                delta_a = delta_a + 6.2831855f;
            }
            orientation_a =
                progress / orient_template->secondary_samples[orient_index].delta_length
                * delta_a
                + orient_template->primary_samples[orient_index].rotation_scalar_94;
        }

        float segment_alpha = progress / orient_template->secondary_samples[orient_index].delta_length;
        orientation_b =
            (segment_alpha + (float)(int)orient_index)
            * orient_template->installed_heading_delta
            / (float)(int)orient_template->segment_count;

        if (player->sub_hover.state != SUB_HOVER_STATE_ACTIVE) {
            float abs_lateral = input_x - center_x;
            if (abs_lateral < 0.0f)
                abs_lateral = -abs_lateral;
            if (abs_lateral > (float)(int)orient_template->width_cells * 0.5f + 0.30000001f
                && vertical_offset <= 0.0f) {
                out_position = *output;
                player->heading_roll =
                    this->template_record->installed_heading_delta + player->heading_roll;
                float clamped_x = input_x < -4.0f
                    ? -4.0f
                    : (input_x > 4.0f ? 4.0f : input_x);
                input_x = clamped_x;
                return this->template_record->side_exit_mode == 0;
            }
        }

        if (vertical_offset < 0.0f) {
            vertical_offset = 0.0f;
            motion->y = 0.0f;
        }
        return 0;
    }

terminal_path:
    {
        active = 0;
        if (delta >= 1.0f)
            delta = 0.99900001f;

        Path* exhaust_template = this->template_record;
        float launch_speed =
            path_factor * exhaust_template->secondary_samples[exhaust_template->segment_count - 1].delta_length;
        motion->z = launch_speed;
        if (launch_speed > 1.0f)
            motion->z = 1.0f;

        Path* final_template = this->template_record;
        if (final_template->kind == PATH_TEMPLATE_KIND_SUPERTRAMP) {
            motion->y = motion->z * 0.69999999f;
            Path* supertramp_template = this->template_record;
            float old_x = out_position.x;
            unsigned int count = supertramp_template->segment_count;
            float carry = delta + supertramp_template->width_or_scale;
            AttachmentSample* samples = supertramp_template->secondary_samples;
            AttachmentSample* terminal = &samples[count];
            Vec3* anchor = &source_cell->position;
            Vec3 forward_offset;
            forward_offset.x = carry * terminal[-1].transform.basis_forward.x;
            forward_offset.y = carry * terminal[-1].transform.basis_forward.y;
            forward_offset.z = carry * terminal[-1].transform.basis_forward.z;
            Vec3 launch_position =
                (*anchor + terminal[-1].transform.position) + forward_offset;
            out_position = launch_position;
            out_position.x = old_x;
            player->cutscene_pitch_cycle_step =
                g_game->subgame.subgame_rate * 0.013888888f;
            player->cutscene_pitch_cycle = player->cutscene_pitch_cycle_step;
            g_voice_manager.Play(
                VOICE_SET_SUPERTRAMP, VOICE_PLAY_IF_IDLE, -1);
        } else {
            out_position.z =
                final_template->secondary_samples[final_template->segment_count - 1].transform.position.z
                + source_cell->position.z
                + final_template->width_or_scale
                + delta;
        }
        player->heading_roll =
            this->template_record->installed_heading_delta + player->heading_roll;
        return 3;
    }
}
