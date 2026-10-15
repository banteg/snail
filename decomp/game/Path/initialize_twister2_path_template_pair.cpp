// initialize_twister2_path_template_pair @ 0x42af30 (thiscall, ret 0x18)

#include "path_helpers.h"

typedef AttachmentSample PathTemplateSample;

void cRPath::initialize_twister2_path_template_pair(float height, int width_cells_,
                                                    bool handedness, char *texture_a,
                                                    char *texture_b,
                                                    char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_TWISTER2;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 52;
    segment_count_f = 52.0f;
    GetNodes();

    has_entry_mesh_transition = 0;
    primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    if (!handedness)
        primary_samples[0].center_x = primary_samples[0].center_x * -1.0f;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    primary_samples[0].transform.Identity();
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;
    secondary_samples[0].transform.Identity();
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;

    primary_samples[51].center_x = (float)width_cells * 0.5f - 4.0f;
    if (!handedness)
        primary_samples[51].center_x = primary_samples[51].center_x * -1.0f;
    primary_samples[51].rotation_scalar_98 = 0.0f;
    primary_samples[51].rotation_scalar_94 = 0.0f;
    primary_samples[51].special_scalar = 0.0f;
    primary_samples[51].lateral_scale = 1.0f;
    primary_samples[51].transform.Identity();
    primary_samples[51].transform.position.x = primary_samples[51].center_x;
    primary_samples[51].transform.position.y = 0.0f;
    primary_samples[51].transform.position.z = 51.0f;
    secondary_samples[51].transform.Identity();
    secondary_samples[51].transform.position.x = primary_samples[51].center_x;
    secondary_samples[51].transform.position.y = 0.49000001f;
    secondary_samples[51].transform.position.z = 51.0f;

    int local_index = 0;
    for (int sample_offset = sizeof(PathTemplateSample);
         sample_offset < 51 * (int)sizeof(PathTemplateSample);
         sample_offset += sizeof(PathTemplateSample))
    {
        float angle = (float)local_index * 0.25132743f;
        float half_angle = angle * 0.5f;
        if (!handedness)
            angle += 3.1415927f;

        float center_scale = Cos(angle) + 1.0f;
        center_scale = center_scale * 0.5f;
        center_scale = center_scale * 5.0f;
        float center = 2.5f - center_scale;

        initialize_curve_sample(primary_samples, sample_offset, center);
        int sample_z = finish_curve_positions(primary_samples, secondary_samples,
                                              sample_offset, local_index, angle,
                                              half_angle, height);
        local_index = sample_z;
    }

    {
        for (int i = 0; i < segment_count - 1; ++i)
        {
            primary_samples[i].delta_dir_to_next =
                primary_samples[i + 1].transform.position -
                primary_samples[i].transform.position;
            primary_samples[i].delta_length =
                primary_samples[i].delta_dir_to_next.Normalize();

            secondary_samples[i].delta_dir_to_next =
                secondary_samples[i + 1].transform.position -
                secondary_samples[i].transform.position;
            secondary_samples[i].delta_length =
                secondary_samples[i].delta_dir_to_next.Normalize();
        }

        primary_samples[segment_count - 1].delta_dir_to_next =
            Vector3(0.0f, 0.0f, 1.0f);
        primary_samples[segment_count - 1].delta_length = 1.0f;
        secondary_samples[segment_count - 1].delta_dir_to_next =
            Vector3(0.0f, 0.0f, 1.0f);
        secondary_samples[segment_count - 1].delta_length = 1.0f;
    }
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
