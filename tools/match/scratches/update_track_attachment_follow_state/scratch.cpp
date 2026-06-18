// update_track_attachment_follow_state @ 0x420cb0 (thiscall, ret 0xc)
#include "player.h"
#include "transform_matrix.h"
#include "voice_manager.h"
#include "vector3.h"

typedef Vector3 Vec3;

#include "track_attachment_matrix_path_view.h"
#include "track_row_cell_anchor_view.h"

struct AttachmentFollowRuntimeRow {
    char unknown_00[0x04];
    unsigned int flags;
    char unknown_08[0x24 - 0x08];
    float runtime_value_24;
    char unknown_28[0x34 - 0x28];
    float runtime_value_34;
    void* attachment_runtime_record;
};

struct AttachmentFollowRuntimeRowSlot {
    AttachmentFollowRuntimeRow* row;
    char unknown_04[0xf4 - 0x04];
};

struct AttachmentRuntimeRecord {
    char unknown_00[0xa0];
    float scalar_a0;
    float scalar_a4;
};

class FollowState {
public:
    int update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion);

    unsigned char active;
    char unknown_01[0x04 - 0x01];
    AttachmentPathTemplateMatrixView* template_record;
    TrackRowCellAnchorView* source_cell;
    int sample_index;
    float progress;
    float vertical_offset;
    float orientation_a;
    float orientation_b;
    float orientation_c;
    float orientation_d;
    float orientation_e;
    Vec3 output_position;
    Player* player;
};

extern char* g_game_base; // data_4df904
extern AttachmentFollowRuntimeRowSlot g_track_runtime_rows[]; // 0x641184

void __fastcall set_matrix_identity(TransformMatrix* transform);
struct AttachmentPathTemplate {
    int compute_kind42_attachment_transform(
        float radius,
        float x,
        float y,
        TransformMatrix* transform,
        float* out_angle);
};

int FollowState::update_track_attachment_follow_state(
    float path_factor,
    Vec3* out_position,
    Vec3* motion)
{
    int index = sample_index;
    AttachmentPathTemplateMatrixView* initial_template = this->template_record;
    AttachmentSampleMatrixView* secondary_samples = initial_template->secondary_samples;
    float* p_delta_length = &secondary_samples[index].delta_length;
    float delta = path_factor * *p_delta_length;
    float alpha;
    float out_angle;
    float arg1;
    float arg2;
    float v79;
    float v82;
    float v83;
    float v84;
    float v85;
    TransformMatrix transform;
    float v87;
    float v88;
    float v90;
    float v91;
    float v92;
    float v93;
    TransformMatrix from;
    TransformMatrix v95;
    TransformMatrix v96;
    TransformMatrix to;

    unsigned int current_index;
    AttachmentPathTemplateMatrixView* current_template;
    int terminal_index;
    while (delta + progress > *p_delta_length) {
        delta -= *p_delta_length - progress;
        ++index;
        progress = 0.0f;
        sample_index = index;

        if (index == 2 * this->template_record->segment_count) {
            g_voice_manager.play_voice_manager(4, 1, -1);
        }

        AttachmentPathTemplateMatrixView* runtime_template = this->template_record;
        if (runtime_template->special_runtime_flag_9c) {
            int count = (int)runtime_template->segment_count;
            int current_index = (int)this->sample_index;
            if (current_index == count - 1) {
                AttachmentRuntimeRecord* attached =
                    (AttachmentRuntimeRecord*)((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->attachment_runtime_record;
                ((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->runtime_value_24 = attached->scalar_a4;
                ((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->runtime_value_34 = 1.0f;
            } else if (current_index == (3 * count) / 7) {
                ((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->flags |= 0x80;
                AttachmentRuntimeRecord* attached =
                    (AttachmentRuntimeRecord*)((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->attachment_runtime_record;
                ((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->runtime_value_24 = attached->scalar_a0;
                ((AttachmentFollowRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row->runtime_value_34 = 0.6f;
            }
        }

        AttachmentPathTemplateMatrixView* loop_template = this->template_record;
        index = this->sample_index;
        if (index == loop_template->segment_count)
            goto terminal_path;
        secondary_samples = loop_template->secondary_samples;
        p_delta_length = &secondary_samples[index].delta_length;
    }

    {
        current_index = sample_index;
        out_angle = delta + progress;
        progress = out_angle;
        current_template = this->template_record;
        terminal_index = current_template->segment_count - 1;
        if (current_index == (unsigned int)terminal_index) {
            v85 = current_template->primary_samples[current_index].center_x;
        } else {
            v85 = out_angle / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].center_x
                    - current_template->primary_samples[current_index].center_x)
                + current_template->primary_samples[current_index].center_x;
        }
        if (current_index == (unsigned int)terminal_index) {
            v79 = current_template->primary_samples[current_index].lateral_scale;
        } else {
            v79 = out_angle / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].lateral_scale
                    - current_template->primary_samples[current_index].lateral_scale)
                + current_template->primary_samples[current_index].lateral_scale;
        }
        if (current_index == (unsigned int)terminal_index) {
            arg1 = current_template->primary_samples[current_index].special_scalar;
        } else {
            arg1 = out_angle / current_template->secondary_samples[current_index].delta_length
                * (current_template->primary_samples[current_index + 1].special_scalar
                    - current_template->primary_samples[current_index].special_scalar)
                + current_template->primary_samples[current_index].special_scalar;
        }

        if (current_template->kind == 42) {
            arg2 = out_position->x - v85;
            ((AttachmentPathTemplate*)current_template)->compute_kind42_attachment_transform(
                arg1, arg2, 0.49000001f, &transform, &out_angle);
            unsigned int active_index = sample_index;
            if (active_index == 0 || active_index == (unsigned int)(this->template_record->segment_count - 1)) {
                set_matrix_identity(&from);
                from.position.x = transform.position.x;
                from.position.y = transform.position.y;
                from.position.z = transform.position.z;
                to = transform;
                float blend;
                if (sample_index == 0)
                    blend = progress;
                else
                    blend = 1.0f - progress;
                transform.linear_interpolate_matrix(&from, &to, blend);
            }

            Vec3* output = &output_position;
            float y = transform.position.y;
            float z =
                this->template_record->secondary_samples[sample_index].delta_dir_to_next.z * progress
                + source_cell->anchor_position.z
                + this->template_record->secondary_samples[sample_index].transform.position.z;
            transform.basis_right.x *= v79;
            transform.basis_right.y *= v79;
            transform.basis_right.z *= v79;
            float vertical = motion->y + vertical_offset;
            output->x = transform.position.x;
            output->y = y;
            vertical_offset = vertical;
            output->z = z;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base) = transform.basis_right.x;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base + 4) = transform.basis_right.y;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base + 8) = transform.basis_right.z;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base) = transform.basis_up.x;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base + 4) = transform.basis_up.y;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base + 8) = transform.basis_up.z;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base) = transform.basis_forward.x;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base + 4) = transform.basis_forward.y;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base + 8) = transform.basis_forward.z;
        } else {
            AttachmentSampleMatrixView* secondary = current_template->secondary_samples;
            AttachmentSampleMatrixView* sample = &secondary[current_index];
            Vec3* anchor = &source_cell->anchor_position;
            float path_x = out_angle * sample->delta_dir_to_next.x;
            float path_y = out_angle * sample->delta_dir_to_next.y;
            float path_z = out_angle * sample->delta_dir_to_next.z;
            v82 = path_x * v79 + anchor->x + sample->transform.position.x;
            v83 = path_y * v79 + anchor->y + sample->transform.position.y;
            v84 = path_z + anchor->z + sample->transform.position.z;
            if (current_index == (unsigned int)terminal_index) {
                set_matrix_identity(&transform);
            } else {
                v95 = sample->transform;
                v96 = secondary[current_index + 1].transform;
                v95.position.z = 0.0f;
                v95.position.y = 0.0f;
                v95.position.x = 0.0f;
                v96.position.z = 0.0f;
                v96.position.y = 0.0f;
                v96.position.x = 0.0f;
                alpha = out_angle / current_template->secondary_samples[current_index].delta_length;
                transform.linear_interpolate_matrix(&v95, &v96, alpha);
            }

            Vec3* output = &output_position;
            transform.basis_right.x *= v79;
            transform.basis_right.y *= v79;
            transform.basis_right.z *= v79;
            float vertical = motion->y + vertical_offset;
            vertical_offset = vertical;
            Vec3 up_offset(
                transform.basis_up.x * vertical,
                transform.basis_up.y * vertical,
                transform.basis_up.z * vertical);
            float local_x = out_position->x - v85;
            Vec3 right_offset(
                local_x * transform.basis_right.x,
                transform.basis_right.y * local_x,
                local_x * transform.basis_right.z);
            v90 = right_offset.x + v82;
            v91 = right_offset.y + v83;
            float right_z = right_offset.z + v84;
            v82 = v90 + up_offset.x;
            float out_y = v91 + up_offset.y;
            output->x = v82;
            v83 = out_y;
            output->y = v83;
            v84 = right_z + up_offset.z;
            output->z = v84;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base) = transform.basis_right.x;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base + 4) = transform.basis_right.y;
            *(float*)(g_player_live_matrix_basis_right + (int)g_game_base + 8) = transform.basis_right.z;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base) = transform.basis_up.x;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base + 4) = transform.basis_up.y;
            *(float*)(g_player_live_matrix_basis_up + (int)g_game_base + 8) = transform.basis_up.z;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base) = transform.basis_forward.x;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base + 4) = transform.basis_forward.y;
            *(float*)(g_player_live_matrix_basis_forward + (int)g_game_base + 8) = transform.basis_forward.z;
        }

        orientation_c = transform.basis_up.x;
        orientation_d = transform.basis_up.y;
        orientation_e = transform.basis_up.z;

        AttachmentPathTemplateMatrixView* orient_template = this->template_record;
        unsigned int orient_index = sample_index;
        int offset = 0xa8 * orient_index;
        if (orient_index == (unsigned int)(orient_template->segment_count - 1)) {
            AttachmentSampleMatrixView* last_sample =
                (AttachmentSampleMatrixView*)((char*)orient_template->primary_samples + offset);
            orientation_b = last_sample->rotation_scalar_98;
            orientation_a = last_sample->rotation_scalar_94;
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

        if (player->jetpack_gauge.state != 1) {
            float abs_lateral = out_position->x - v85;
            if (abs_lateral < 0.0f)
                abs_lateral = -abs_lateral;
            if (abs_lateral > (float)(int)orient_template->width_cells * 0.5f + 0.30000001f
                && vertical_offset <= 0.0f) {
                out_position->x = output_position.x;
                out_position->y = output_position.y;
                out_position->z = output_position.z;
                player->heading_roll =
                    this->template_record->installed_heading_delta + player->heading_roll;
                if (out_position->x < -4.0f) {
                    out_position->x = -4.0f;
                    return this->template_record->side_exit_mode == 0;
                }
                if (out_position->x > 4.0f) {
                    out_position->x = 4.0f;
                    return this->template_record->side_exit_mode == 0;
                }
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

        AttachmentPathTemplateMatrixView* exhaust_template = this->template_record;
        float launch_speed =
            path_factor * exhaust_template->secondary_samples[exhaust_template->segment_count - 1].delta_length;
        motion->z = launch_speed;
        if (launch_speed > 1.0f)
            motion->z = 1.0f;

        AttachmentPathTemplateMatrixView* final_template = this->template_record;
        if (final_template->kind == 31) {
            motion->y = motion->z * 0.69999999f;
            AttachmentPathTemplateMatrixView* supertramp_template = this->template_record;
            float old_x = out_position->x;
            unsigned int count = supertramp_template->segment_count;
            float carry = delta + supertramp_template->width_or_scale;
            AttachmentSampleMatrixView* samples = supertramp_template->secondary_samples;
            AttachmentSampleMatrixView* terminal = &samples[count];
            Vec3* anchor = &source_cell->anchor_position;
            Vec3 forward_offset;
            forward_offset.x = carry * terminal[-1].transform.basis_forward.x;
            forward_offset.y = carry * terminal[-1].transform.basis_forward.y;
            forward_offset.z = carry * terminal[-1].transform.basis_forward.z;
            Vec3 base_position;
            base_position.x = anchor->x + terminal[-1].transform.position.x;
            base_position.y = terminal[-1].transform.position.y + anchor->y;
            base_position.z = terminal[-1].transform.position.z + anchor->z;
            Vec3 launch_position;
            launch_position.x = base_position.x + forward_offset.x;
            launch_position.y = base_position.y + forward_offset.y;
            launch_position.z = base_position.z + forward_offset.z;
            *out_position = launch_position;
            out_position->x = old_x;
            player->cutscene_pitch_cycle_step = *(float*)(g_game_base + 0x74650) * 0.013888888f;
            player->cutscene_pitch_cycle = player->cutscene_pitch_cycle_step;
            g_voice_manager.play_voice_manager(15, 0, -1);
        } else {
            out_position->z =
                final_template->secondary_samples[final_template->segment_count - 1].transform.position.z
                + source_cell->anchor_position.z
                + final_template->width_or_scale
                + delta;
        }
        player->heading_roll =
            this->template_record->installed_heading_delta + player->heading_roll;
        return 3;
    }

}
