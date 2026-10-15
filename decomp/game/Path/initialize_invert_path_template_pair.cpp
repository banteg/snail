// initialize_invert_path_template_pair @ 0x429250 (thiscall, ret 0x18)

#include "path_helpers.h"

typedef AttachmentSample PathTemplateSample;

static __forceinline void initialize_invert_curve_primary(PathTemplateSample *&bank,
                                                          int offset, float t,
                                                          float angle)
{
    ((PathTemplateSample *)((char *)bank + offset))[0].center_x =
        (bank[33].center_x - bank[0].center_x) * t * 0.03125f + bank[0].center_x;
    ((PathTemplateSample *)((char *)bank + offset))[0].rotation_scalar_98 =
        angle * 0.5f;
    ((PathTemplateSample *)((char *)bank + offset))[0].rotation_scalar_94 = 0.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].special_scalar = 0.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].lateral_scale = 1.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].transform.Identity();
}

static __forceinline void finish_invert_frame(PathTemplateSample *&primary,
                                              PathTemplateSample *&secondary,
                                              const int &offset, float angle,
                                              float z_position)
{
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.position.x = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.position.z =
        z_position;
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.position.y = 0.0f;

    float basis_y = Cos(angle);
    float basis_x = Sin(angle);
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_up =
        Vector3(basis_x, basis_y, 0.0f);
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_forward =
        ((PathTemplateSample *)((char *)primary + offset))[0].transform.position -
        ((PathTemplateSample *)((char *)primary + offset))[-1].transform.position;
    ((PathTemplateSample *)((char *)primary + offset))[0]
        .transform.basis_forward.Normalize();
    ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_right.Cross(
        ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_up,
        ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_forward);

    ((PathTemplateSample *)((char *)secondary + offset))[0].transform =
        ((PathTemplateSample *)((char *)primary + offset))[0].transform;
    Vector3 secondary_offset =
        ((PathTemplateSample *)((char *)primary + offset))[0]
            .transform.basis_up *
        0.49000001f;
    Vector3 *secondary_position =
        &((PathTemplateSample *)((char *)secondary + offset))[0]
             .transform.position;
    secondary_position->x += secondary_offset.x;
    secondary_position->y += secondary_offset.y;
    secondary_position->z += secondary_offset.z;
}

void cRPath::initialize_invert_path_template_pair(float radius, int width_cells_,
                                                  bool side_exit, char *texture_a,
                                                  char *texture_b, char *cap_texture)
{
    kind = PATH_TEMPLATE_KIND_INVERT;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 34;
    segment_count_f = 34.0f;
    GetNodes();

    has_entry_mesh_transition = 1;
    primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    primary_samples[0].transform.Identity();
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;
    primary_samples[0].delta_length = 1.0f;
    secondary_samples[0].transform.Identity();
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;
    secondary_samples[0].delta_length = 1.0f;

    primary_samples[33].center_x = 4.0f - (float)width_cells * 0.5f;
    primary_samples[33].rotation_scalar_98 = 3.1415927f;
    primary_samples[33].rotation_scalar_94 = 0.0f;
    primary_samples[33].special_scalar = 0.0f;
    primary_samples[33].lateral_scale = 1.0f;
    primary_samples[33].transform.Identity();
    primary_samples[33].transform.position.x = primary_samples[33].center_x;
    primary_samples[33].transform.position.y = 0.0f;
    primary_samples[33].transform.position.z = 33.0f;
    primary_samples[33].delta_length = 1.0f;
    secondary_samples[33].transform.Identity();
    secondary_samples[33].transform.position.x = primary_samples[33].center_x;
    secondary_samples[33].transform.position.y = 0.49000001f;
    secondary_samples[33].transform.position.z = 33.0f;
    secondary_samples[33].delta_length = 1.0f;

    int sample_offset = (int)sizeof(PathTemplateSample);
    int local_index = 0;
    do
    {
        float t = (float)local_index;
        float angle = t * 0.19634955f;

        initialize_invert_curve_primary(primary_samples, sample_offset, t, angle);
        finish_invert_frame(primary_samples, secondary_samples, sample_offset, angle,
                            (float)(local_index + 1));
        ++local_index;
        sample_offset += (int)sizeof(PathTemplateSample);
    } while (sample_offset < 33 * (int)sizeof(PathTemplateSample));

    compute_path_deltas(segment_count, primary_samples, secondary_samples);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)radius;
    (void)side_exit;
    (void)cap_texture;
}
