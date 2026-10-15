// initialize_hump_path_template_pair @ 0x41d030 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "path_helpers.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

void cRPath::initialize_hump_path_template_pair(float curve_source, float height_scale,
                                                int width_cells_, bool side_exit,
                                                char *texture_a, char *texture_b,
                                                char *cap_texture)
{
    int curve_count;
    int i;

    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    curve_count = (int)(curve_source * 4.0f);
    width_or_scale = 1.0f;
    int departure_index = curve_count + 7;
    segment_count = departure_index;
    segment_count += 7;
    segment_count_f = (float)(departure_index + 7);
    float curve_count_f = (float)curve_count;
    curve_source = curve_count_f * 0.095492966f;
    GetNodes();
    has_entry_mesh_transition = 0;

    i = 0;
    int lead_offset = 0;
    do
    {
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0].center_x =
            ((float)width_cells * 0.5f) - 4.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .rotation_scalar_98 = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .rotation_scalar_94 = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .special_scalar = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .lateral_scale = 1.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .transform.Identity();
        float z;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.x =
            ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
                .center_x;
        z = (float)i;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.y = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.z = z;
        ((PathAttachmentSample *)((char *)secondary_samples + lead_offset))[0]
            .transform.Identity();
        ((PathAttachmentSample *)((char *)secondary_samples + lead_offset))[0]
            .transform.position.x =
            ((PathAttachmentSample *)((char *)primary_samples + lead_offset))[0]
                .center_x;
        ((PathAttachmentSample *)((char *)secondary_samples + lead_offset))[0]
            .transform.position.y = 0.49000001f;
        ((PathAttachmentSample *)((char *)secondary_samples + lead_offset))[0]
            .transform.position.z = z;
        ++i;
        lead_offset += sizeof(PathAttachmentSample);
    } while (lead_offset < 7 * (int)sizeof(PathAttachmentSample));

    i = departure_index;
    int departure_offset = departure_index * sizeof(PathAttachmentSample);
    int departure_origin = -7 - curve_count;
    do
    {
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .center_x = 4.0f - (float)width_cells * 0.5f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .rotation_scalar_98 = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .rotation_scalar_94 = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .special_scalar = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .lateral_scale = 1.0f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .transform.Identity();
        float z = (float)i;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .transform.position.x =
            ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
                .center_x;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .transform.position.y = 0.0f;
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .transform.position.z = z;
        ((PathAttachmentSample *)((char *)secondary_samples + departure_offset))[0]
            .transform.Identity();
        ((PathAttachmentSample *)((char *)secondary_samples + departure_offset))[0]
            .transform.position.x =
            ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
                .center_x;
        ((PathAttachmentSample *)((char *)secondary_samples + departure_offset))[0]
            .transform.position.y = 0.49000001f;
        ((PathAttachmentSample *)((char *)secondary_samples + departure_offset))[0]
            .transform.position.z = z;
        departure_offset += sizeof(PathAttachmentSample);
        ++i;
    } while (i + departure_origin < 7);

    i = 0;
    if (curve_count > 0)
    {
        int sample_offset = 7 * (int)sizeof(PathAttachmentSample);
        do
        {
            int sample_index = i + 7;
            float angle = (float)i * 6.2831855f / curve_count_f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->center_x = Cos(angle * 0.5f) * primary_samples[0].center_x;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->special_scalar = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->lateral_scale = 1.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->transform.Identity();
            float z;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[0]
                .transform.position.x =
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[0]
                    .center_x;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[0]
                .transform.position.y =
                (1.0f - Cos(angle)) * curve_source * height_scale;
            z = (float)sample_index;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[0]
                .transform.position.z = z;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.Identity();
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.position.x =
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                    ->center_x;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.position.y =
                (1.0f - Cos(angle)) * curve_source * (height_scale) + 0.49000001f;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.position.z = z;
            if (sample_offset > 7 * (int)sizeof(PathAttachmentSample))
            {
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset) - 1)
                    ->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset) - 1)
                    ->transform.basis_forward =
                    ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                        ->transform.position -
                    ((PathAttachmentSample *)((char *)primary_samples + sample_offset) -
                     1)
                        ->transform.position;
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset) - 1)
                    ->transform.basis_forward.Normalize();
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset) - 1)
                    ->transform.basis_up.Cross(
                        ((PathAttachmentSample *)((char *)primary_samples +
                                                  sample_offset) -
                         1)
                            ->transform.basis_forward,
                        ((PathAttachmentSample *)((char *)primary_samples +
                                                  sample_offset) -
                         1)
                            ->transform.basis_right);
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset) -
                 1)
                    ->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathAttachmentSample *)((char *)secondary_samples +
                                              sample_offset))
                        ->transform.position -
                    ((PathAttachmentSample *)((char *)secondary_samples +
                                              sample_offset) -
                     1)
                        ->transform.position;
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset) -
                 1)
                    ->transform.basis_up.Cross(
                        ((PathAttachmentSample *)((char *)secondary_samples +
                                                  sample_offset) -
                         1)
                            ->transform.basis_forward,
                        ((PathAttachmentSample *)((char *)secondary_samples +
                                                  sample_offset) -
                         1)
                            ->transform.basis_right);
            }
            else
            {
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset) - 1)
                    ->transform.RotIdentity();
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset) -
                 1)
                    ->transform.RotIdentity();
            }
            ++i;
            sample_offset += (int)sizeof(PathAttachmentSample);
        } while (i < curve_count);
    }

    compute_terminal_deltas(this);

    build_strip_mesh(this, texture_a, texture_b);

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
