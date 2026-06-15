// update_track_attachment_follow_state @ 0x420cb0 (thiscall, ret 0xc)
#include "vector_types.h"

struct Vec3 {
    float x;
    float y;
    float z;
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
    TransformMatrix transform;
    char unknown_40[0x40];
    Vec3 delta_dir_to_next;
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
    unsigned char is_mirrored_x;
    char unknown_3d[0x40 - 0x3d];
    unsigned int side_exit_mode;
    unsigned int segment_count;
    unsigned int unknown_48;
    float segment_count_f;
    float width_or_scale;
    unsigned int width_cells;
    PathTemplateSample* primary_samples;
    PathTemplateSample* secondary_samples;
    char unknown_60[0x98 - 0x60];
    float installed_heading_delta;
    unsigned char special_runtime_flag_9c;
    char unknown_9d[0xa8 - 0x9d];
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vec3 anchor_position;
    char unknown_1c[0x38 - 0x1c];
    PathTemplate* attachment_template_record;

    int get_track_cell_row_index();
};

struct TrackRuntimeRow {
    char unknown_00[0x04];
    unsigned int flags;
    char unknown_08[0x24 - 0x08];
    float runtime_value_24;
    char unknown_28[0x34 - 0x28];
    float runtime_value_34;
    void* attachment_runtime_record;
};

struct TrackRuntimeRowSlot {
    TrackRuntimeRow* row;
    char unknown_04[0xf4 - 0x04];
};

struct AttachmentRuntimeRecord {
    char unknown_00[0xa0];
    float scalar_a0;
    float scalar_a4;
};

struct JetpackGaugeController {
    char unknown_00[0x0c];
    unsigned int state;
};

class Player {
public:
    char unknown_00[0x2dc];
    float cutscene_pitch_cycle;
    float cutscene_pitch_cycle_step;
    char unknown_2e4[0x370 - 0x2e4];
    float heading_roll;
    char unknown_374[0x2750 - 0x374];
    JetpackGaugeController jetpack_gauge;
};

class FollowState {
public:
    int update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion);

    unsigned char active;
    char unknown_01[0x04 - 0x01];
    PathTemplate* template_record;
    TrackRowCell* source_cell;
    unsigned int sample_index;
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
extern TrackRuntimeRowSlot g_track_runtime_rows[]; // 0x641184
extern char g_camera_basis_right[]; // 0x42fdb4
extern char g_camera_basis_up[]; // 0x42fdc4
extern char g_camera_basis_forward[]; // 0x42fdd4

void __fastcall set_matrix_identity(TransformMatrix* transform);
int __stdcall compute_kind42_attachment_transform(
    float radius,
    float x,
    float y,
    TransformMatrix* transform,
    float* out_angle);

class VoiceManager {
public:
    bool play_voice_manager(int set_id, unsigned int mode, int sample_override);
};

extern VoiceManager g_voice_manager; // 0x751498

int FollowState::update_track_attachment_follow_state(
    float path_factor,
    Vec3* out_position,
    Vec3* motion)
{
    unsigned int index = sample_index;
    PathTemplate* template_record = this->template_record;
    PathTemplateSample* secondary_samples = template_record->secondary_samples;
    float delta = path_factor * secondary_samples[index].delta_length;
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
    PathTemplate* current_template;
    int terminal_index;
    PathTemplateSample* primary;
    if (delta + progress > secondary_samples[index].delta_length) {
        for (;;) {
            delta -= secondary_samples[index].delta_length - progress;
            ++index;
            progress = 0.0f;
            sample_index = index;

            if (index == 2 * template_record->segment_count) {
                g_voice_manager.play_voice_manager(4, 1, -1);
            }

            PathTemplate* current_template = this->template_record;
            if (current_template->special_runtime_flag_9c) {
                int count = (int)current_template->segment_count;
                int current_index = (int)this->sample_index;
                if (current_index == count - 1) {
                    TrackRuntimeRow* row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    AttachmentRuntimeRecord* attached = (AttachmentRuntimeRecord*)row->attachment_runtime_record;
                    row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    row->runtime_value_24 = attached->scalar_a4;
                    row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    row->runtime_value_34 = 1.0f;
                } else if (current_index == (3 * count) / 7) {
                    TrackRuntimeRow* row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    row->flags |= 0x80;
                    row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    AttachmentRuntimeRecord* attached = (AttachmentRuntimeRecord*)row->attachment_runtime_record;
                    row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    row->runtime_value_24 = attached->scalar_a0;
                    row = ((TrackRuntimeRowSlot*)((char*)g_track_runtime_rows + (int)g_game_base))[source_cell->get_track_cell_row_index()].row;
                    row->runtime_value_34 = 0.6f;
                }
            }

            template_record = this->template_record;
            index = this->sample_index;
            if (index == template_record->segment_count) {
                active = 0;
                if (delta >= 1.0f)
                    delta = 0.99900001f;

                float launch_speed =
                    path_factor * template_record->secondary_samples[template_record->segment_count - 1].delta_length;
                motion->z = launch_speed;
                if (launch_speed > 1.0f)
                    motion->z = 1.0f;

                PathTemplate* final_template = this->template_record;
                if (final_template->kind == 31) {
                    motion->y = motion->z * 0.69999999f;
                    PathTemplate* supertramp_template = this->template_record;
                    float old_x = out_position->x;
                    unsigned int count = supertramp_template->segment_count;
                    float carry = delta + supertramp_template->width_or_scale;
                    PathTemplateSample* samples = supertramp_template->secondary_samples;
                    PathTemplateSample* terminal = &samples[count];
                    Vec3* anchor = &source_cell->anchor_position;
                    float forward_x = carry * terminal[-1].transform.basis_forward.x;
                    float forward_y = carry * terminal[-1].transform.basis_forward.y;
                    float forward_z = carry * terminal[-1].transform.basis_forward.z;
                    float base_x = anchor->x + terminal[-1].transform.position.x;
                    float base_y = anchor->y + terminal[-1].transform.position.y;
                    float base_z = anchor->z + terminal[-1].transform.position.z;
                    out_position->x = base_x + forward_x;
                    out_position->y = base_y + forward_y;
                    out_position->z = base_z + forward_z;
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
                player->heading_roll = template_record->installed_heading_delta + player->heading_roll;
                return 3;
            }
            secondary_samples = template_record->secondary_samples;
            if (delta + progress <= secondary_samples[index].delta_length) {
                current_index = sample_index;
                float advanced = delta + progress;
                progress = advanced;
                current_template = template_record;
                terminal_index = current_template->segment_count - 1;
                primary = &current_template->primary_samples[current_index];
                if (current_index == (unsigned int)terminal_index) {
                    v85 = primary->center_x;
                } else {
                    v85 = advanced / current_template->secondary_samples[current_index].delta_length
                        * (primary[1].center_x - primary->center_x)
                        + primary->center_x;
                }
                out_angle = advanced;
                goto after_v85;
            }
        }
    }

    current_index = sample_index;
    out_angle = delta + progress;
    progress = out_angle;
    current_template = template_record;
    terminal_index = current_template->segment_count - 1;
    primary = &current_template->primary_samples[current_index];
    if (current_index == (unsigned int)terminal_index) {
        v85 = primary->center_x;
    } else {
        v85 = out_angle / current_template->secondary_samples[current_index].delta_length
            * (primary[1].center_x - primary->center_x)
            + primary->center_x;
    }
after_v85:
    if (current_index == (unsigned int)terminal_index) {
        v79 = primary->lateral_scale;
    } else {
        v79 = out_angle / current_template->secondary_samples[current_index].delta_length
            * (primary[1].lateral_scale - primary->lateral_scale)
            + primary->lateral_scale;
    }
    if (current_index == (unsigned int)terminal_index) {
        arg1 = primary->special_scalar;
    } else {
        arg1 = out_angle / current_template->secondary_samples[current_index].delta_length
            * (primary[1].special_scalar - primary->special_scalar)
            + primary->special_scalar;
    }

    if (current_template->kind == 42) {
        arg2 = out_position->x - v85;
        compute_kind42_attachment_transform(arg1, arg2, 0.49000001f, &transform, &out_angle);
        unsigned int active_index = sample_index;
        if (active_index == 0 || active_index == template_record->segment_count - 1) {
            set_matrix_identity(&from);
            from.position.x = transform.position.x;
            from.position.y = transform.position.y;
            from.position.z = transform.position.z;
            to = transform;
            float blend;
            if (sample_index != 0)
                blend = 1.0f - progress;
            else
                blend = progress;
            transform.linear_interpolate_matrix(&from, &to, blend);
        }

        Vec3* output = &output_position;
        float y = transform.position.y;
        float z =
            template_record->secondary_samples[sample_index].delta_dir_to_next.z * progress
            + source_cell->anchor_position.z
            + template_record->secondary_samples[sample_index].transform.position.z;
        transform.basis_right.x *= v79;
        transform.basis_right.y *= v79;
        transform.basis_right.z *= v79;
        float vertical = motion->y + vertical_offset;
        output->x = transform.position.x;
        output->y = y;
        vertical_offset = vertical;
        output->z = z;
        *(float*)(g_camera_basis_right + (int)g_game_base) = transform.basis_right.x;
        *(float*)(g_camera_basis_right + (int)g_game_base + 4) = transform.basis_right.y;
        *(float*)(g_camera_basis_right + (int)g_game_base + 8) = transform.basis_right.z;
        *(float*)(g_camera_basis_up + (int)g_game_base) = transform.basis_up.x;
        *(float*)(g_camera_basis_up + (int)g_game_base + 4) = transform.basis_up.y;
        *(float*)(g_camera_basis_up + (int)g_game_base + 8) = transform.basis_up.z;
        *(float*)(g_camera_basis_forward + (int)g_game_base) = transform.basis_forward.x;
        *(float*)(g_camera_basis_forward + (int)g_game_base + 4) = transform.basis_forward.y;
        *(float*)(g_camera_basis_forward + (int)g_game_base + 8) = transform.basis_forward.z;
    } else {
        PathTemplateSample* secondary = current_template->secondary_samples;
        PathTemplateSample* sample = &secondary[current_index];
        Vec3* anchor = &source_cell->anchor_position;
        v82 = out_angle * sample->delta_dir_to_next.x * v79
            + anchor->x
            + sample->transform.position.x;
        v83 = out_angle * sample->delta_dir_to_next.y * v79
            + anchor->y
            + sample->transform.position.y;
        v84 = out_angle * sample->delta_dir_to_next.z
            + anchor->z
            + sample->transform.position.z;
        if (current_index == (unsigned int)terminal_index) {
            set_matrix_identity(&transform);
        } else {
            v95 = sample->transform;
            v96 = secondary[current_index + 1].transform;
            v95.position.x = 0.0f;
            v95.position.y = 0.0f;
            v95.position.z = 0.0f;
            v96.position.x = 0.0f;
            v96.position.y = 0.0f;
            v96.position.z = 0.0f;
            alpha = out_angle / current_template->secondary_samples[current_index].delta_length;
            transform.linear_interpolate_matrix(&v95, &v96, alpha);
        }

        Vec3* output = &output_position;
        transform.basis_right.x *= v79;
        transform.basis_right.y *= v79;
        transform.basis_right.z *= v79;
        float vertical = motion->y + vertical_offset;
        vertical_offset = vertical;
        v92 = transform.basis_up.x * vertical;
        v93 = transform.basis_up.y * vertical;
        float up_z = transform.basis_up.z * vertical;
        float local_x = out_position->x - v85;
        v87 = local_x * transform.basis_right.x;
        v88 = transform.basis_right.y * local_x;
        v90 = v87 + v82;
        v91 = v88 + v83;
        float right_z = local_x * transform.basis_right.z + v84;
        v82 = v90 + v92;
        float out_y = v91 + v93;
        output->x = v82;
        v83 = out_y;
        output->y = v83;
        v84 = right_z + up_z;
        output->z = v84;
        *(float*)(g_camera_basis_right + (int)g_game_base) = transform.basis_right.x;
        *(float*)(g_camera_basis_right + (int)g_game_base + 4) = transform.basis_right.y;
        *(float*)(g_camera_basis_right + (int)g_game_base + 8) = transform.basis_right.z;
        *(float*)(g_camera_basis_up + (int)g_game_base) = transform.basis_up.x;
        *(float*)(g_camera_basis_up + (int)g_game_base + 4) = transform.basis_up.y;
        *(float*)(g_camera_basis_up + (int)g_game_base + 8) = transform.basis_up.z;
        *(float*)(g_camera_basis_forward + (int)g_game_base) = transform.basis_forward.x;
        *(float*)(g_camera_basis_forward + (int)g_game_base + 4) = transform.basis_forward.y;
        *(float*)(g_camera_basis_forward + (int)g_game_base + 8) = transform.basis_forward.z;
    }

    orientation_c = transform.basis_up.x;
    orientation_d = transform.basis_up.y;
    orientation_e = transform.basis_up.z;

    PathTemplate* orient_template = template_record;
    unsigned int orient_index = sample_index;
    int offset = 0xa8 * orient_index;
    if (orient_index == orient_template->segment_count - 1) {
        orientation_b = *(float*)((char*)orient_template->primary_samples + offset + 0x98);
        orientation_a = *(float*)((char*)orient_template->primary_samples + offset + 0x94);
    } else {
        PathTemplateSample* orient_sample = &orient_template->primary_samples[orient_index];
        float delta_b = orient_sample[1].rotation_scalar_98 - orient_sample->rotation_scalar_98;
        if (delta_b > 3.1415927f) {
            delta_b = delta_b - 6.2831855f;
        } else if (delta_b < -3.1415927f) {
            delta_b = delta_b + 6.2831855f;
        }
        orientation_b =
            progress / orient_template->secondary_samples[orient_index].delta_length
            * delta_b
            + orient_sample->rotation_scalar_98;
        float delta_a = orient_sample[1].rotation_scalar_94 - orient_sample->rotation_scalar_94;
        if (delta_a > 3.1415927f) {
            delta_a = delta_a - 6.2831855f;
        } else if (delta_a < -3.1415927f) {
            delta_a = delta_a + 6.2831855f;
        }
        orientation_a =
            progress / orient_template->secondary_samples[orient_index].delta_length
            * delta_a
            + orient_sample->rotation_scalar_94;
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
            player->heading_roll = template_record->installed_heading_delta + player->heading_roll;
            if (out_position->x < -4.0f) {
                out_position->x = -4.0f;
            } else if (out_position->x > 4.0f) {
                out_position->x = 4.0f;
            }
            return template_record->side_exit_mode == 0;
        }
    }

    if (vertical_offset < 0.0f) {
        vertical_offset = 0.0f;
        motion->y = 0.0f;
    }
    return 0;
}
