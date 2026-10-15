// initialize_wibble_path_template_pair @ 0x4289a0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "path_helpers.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;



static __forceinline void initialize_wibble_primary(PathTemplateSample *const &bank,
                                                    int offset, float t)
{
    ((PathTemplateSample *)((char *)bank + offset))[0].center_x =
        (bank[31].center_x - bank[0].center_x) * t * 0.033333335f + bank[0].center_x;
    ((PathTemplateSample *)((char *)bank + offset))[0].rotation_scalar_98 = 0.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].rotation_scalar_94 = 0.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].special_scalar = 0.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].lateral_scale = 1.0f;
    ((PathTemplateSample *)((char *)bank + offset))[0].transform.Identity();
}

static __forceinline void copy_wibble_frame(PathTemplateSample *const &primary,
                                            PathTemplateSample *const &secondary, int offset)
{
    ((PathTemplateSample *)((char *)secondary + offset))[0].transform =
        ((PathTemplateSample *)((char *)primary + offset))[0].transform;
    Vector3 secondary_offset =
        ((PathTemplateSample *)((char *)primary + offset))[0].transform.basis_up *
        0.49000001f;
    Vector3 *secondary_position =
        &((PathTemplateSample *)((char *)secondary + offset))[0].transform.position;
    secondary_position->x += secondary_offset.x;
    secondary_position->y += secondary_offset.y;
    secondary_position->z += secondary_offset.z;
}

static __forceinline void finish_wibble_sample(
    PathTemplateSample *const &primary, PathTemplateSample *const &secondary,
    int sample_offset, int local_index)
{
    float t = (float)local_index;
    float turn_phase = t * 0.20943952f;

    initialize_wibble_primary(primary, sample_offset, t);

    int z_index = local_index + 1;
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.position.x = 0.0f;
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.position.z = (float)z_index;
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.position.y = 0.0f;

    float basis_y = Cos(Sin(turn_phase * 3.0f) * 0.30000001f);
    float basis_x = Sin(Sin(turn_phase * 3.0f) * 0.30000001f);
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.basis_up = Vector3(basis_x, basis_y, 0.0f);
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.basis_forward =
        ((PathTemplateSample *)((char *)primary + sample_offset))[0]
            .transform.position -
        ((PathTemplateSample *)((char *)primary + sample_offset))[-1]
            .transform.position;
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.basis_forward.Normalize();
    ((PathTemplateSample *)((char *)primary + sample_offset))[0]
        .transform.basis_right.Cross(
            ((PathTemplateSample *)((char *)primary + sample_offset))[0]
                .transform.basis_up,
            ((PathTemplateSample *)((char *)primary + sample_offset))[0]
                .transform.basis_forward);

    copy_wibble_frame(primary, secondary, sample_offset);
}

void cRPath::initialize_wibble_path_template_pair(float radius, int width_cells_,
                                                  bool side_exit, char *texture_a,
                                                  char *texture_b,
                                                  char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_WIBBLE;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 32;
    segment_count_f = 32.0f;
    GetNodes();

    has_entry_mesh_transition = 0;
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

    primary_samples[31].center_x = 4.0f - (float)width_cells * 0.5f;
    primary_samples[31].rotation_scalar_98 = 0.0f;
    primary_samples[31].rotation_scalar_94 = 0.0f;
    primary_samples[31].special_scalar = 0.0f;
    primary_samples[31].lateral_scale = 1.0f;
    primary_samples[31].transform.Identity();
    primary_samples[31].transform.position.x = primary_samples[31].center_x;
    primary_samples[31].transform.position.y = 0.0f;
    primary_samples[31].transform.position.z = 31.0f;
    primary_samples[31].delta_length = 1.0f;
    secondary_samples[31].transform.Identity();
    secondary_samples[31].transform.position.x = primary_samples[31].center_x;
    secondary_samples[31].transform.position.y = 0.49000001f;
    secondary_samples[31].transform.position.z = 31.0f;
    secondary_samples[31].delta_length = 1.0f;

    int sample_offset = sizeof(PathTemplateSample);
    int local_index = 0;
    do
    {
        finish_wibble_sample(primary_samples, secondary_samples, sample_offset,
                             local_index);
        ++local_index;
        sample_offset += sizeof(PathTemplateSample);
    } while (sample_offset < 31 * (int)sizeof(PathTemplateSample));

    compute_path_deltas(segment_count, primary_samples, secondary_samples);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)radius;
    (void)side_exit;
    (void)vertical_texture;
}
