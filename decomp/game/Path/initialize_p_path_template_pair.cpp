// initialize_p_path_template_pair @ 0x425a40 (thiscall, ret 0x24)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "path_helpers.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void initialize_endpoint_pair(Path *path, PathTemplateSample *const &primary_bank, int index, float center)
{
    primary_bank[index].center_x = center;
    primary_bank[index].rotation_scalar_98 = 0.0f;
    primary_bank[index].rotation_scalar_94 = 0.0f;
    primary_bank[index].special_scalar = 0.0f;
    primary_bank[index].lateral_scale = 1.0f;
    primary_bank[index].transform.Identity();
    primary_bank[index].transform.position.x = primary_bank[index].center_x;
    float z = (float)index;
    primary_bank[index].transform.position.y = 0.0f;
    primary_bank[index].transform.position.z = z;

    path->secondary_samples[index].transform.Identity();
    path->secondary_samples[index].transform.position.x = primary_bank[index].center_x;
    path->secondary_samples[index].transform.position.y = 0.49000001f;
    path->secondary_samples[index].transform.position.z = z;
}

void cRPath::initialize_p_path_template_pair(int variant, float scale_arg,
                                             int width_cells_, float start_x,
                                             float end_x, int curve_segments,
                                             char *texture_a, char *texture_b,
                                             char *cap_texture)
{
    kind = (PathTemplateKind)(variant + 0x21);
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    int last_index = curve_segments + 1;
    segment_count = last_index + 1;
    segment_count_f = ((float)(last_index + 1));

    float half_distance = ((end_x - start_x) * 0.5f);
    if (half_distance < 0.0f)
        scale_arg = (-half_distance);
    else
        scale_arg = half_distance;

    GetNodes();
    has_entry_mesh_transition = 0;

    primary_samples[0].center_x = start_x;
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

    PathTemplateSample *const &primary_bank = primary_samples;
    initialize_endpoint_pair(this, primary_bank, curve_segments + 1, end_x);

    int curve_index = 0;
    if (curve_segments > 0)
    {
        float curve_segments_f = (float)curve_segments;
        int curve_sample_offset = sizeof(PathTemplateSample);
        do
        {
            float angle = (float)curve_index * 3.1415927f / curve_segments_f;
            switch (kind)
            {
            case 0x21:
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->center_x = Sin(angle + 1.5707964f) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x22:
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->center_x = 2.0f - Cos(angle) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x23:
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->center_x = (Sin(angle + 1.5707964f) + 1.0f) * scale_arg + 0.5f;
                break;
            }

            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->special_scalar = 0.0f;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->lateral_scale = 1.0f;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->transform.Identity();
            float z = (float)(curve_index + 1);
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->transform.position.y = 0.0f;
            ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                ->transform.position.z = z;

            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.Identity();
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.y =
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset))
                    ->transform.position.y +
                0.49000001f;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.z = z;
            if (curve_sample_offset > (int)sizeof(PathTemplateSample))
            {
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathTemplateSample *)((char *)primary_bank +
                                            curve_sample_offset))
                        ->transform.position -
                    ((PathTemplateSample *)((char *)primary_bank +
                                            curve_sample_offset) -
                     1)
                        ->transform.position;
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_right.Cross(
                        ((PathTemplateSample *)((char *)primary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_up,
                        ((PathTemplateSample *)((char *)primary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_forward);

                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathTemplateSample *)((char *)secondary_samples +
                                            curve_sample_offset))
                        ->transform.position -
                    ((PathTemplateSample *)((char *)secondary_samples +
                                            curve_sample_offset) -
                     1)
                        ->transform.position;
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_right.Cross(
                        ((PathTemplateSample *)((char *)secondary_samples +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_up,
                        ((PathTemplateSample *)((char *)secondary_samples +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_forward);
            }
            else
            {
                ((PathTemplateSample *)((char *)primary_bank + curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
            }
            ++curve_index;
            curve_sample_offset += sizeof(PathTemplateSample);
        } while (curve_index < curve_segments);
    }

    {
        int i = 0;
        if (segment_count - 1 > 0)
        {
            int delta_offset = 0;
            do
            {
                ((PathTemplateSample *)((char *)primary_samples + delta_offset))
                    ->delta_dir_to_next =
                    ((PathTemplateSample *)((char *)primary_samples + delta_offset) +
                     1)
                        ->transform.position -
                    ((PathTemplateSample *)((char *)primary_samples + delta_offset))
                        ->transform.position;
                ((PathTemplateSample *)((char *)primary_bank + delta_offset))
                    ->delta_length =
                    ((PathTemplateSample *)((char *)primary_bank + delta_offset))
                        ->delta_dir_to_next.Normalize();

                ((PathTemplateSample *)((char *)secondary_samples + delta_offset))
                    ->delta_dir_to_next =
                    ((PathTemplateSample *)((char *)secondary_samples +
                                            delta_offset) +
                     1)
                        ->transform.position -
                    ((PathTemplateSample *)((char *)secondary_samples + delta_offset))
                        ->transform.position;
                ((PathTemplateSample *)((char *)secondary_samples + delta_offset))
                    ->delta_length =
                    ((PathTemplateSample *)((char *)secondary_samples + delta_offset))
                        ->delta_dir_to_next.Normalize();

                ++i;
                delta_offset += (int)sizeof(PathTemplateSample);
            } while (i < segment_count - 1);
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
    (void)cap_texture;
}
