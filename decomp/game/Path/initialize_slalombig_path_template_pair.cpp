// initialize_slalombig_path_template_pair @ 0x4221f0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "path_helpers.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

void cRPath::initialize_slalombig_path_template_pair(int curve_segments,
                                                     int width_cells_, bool side_exit,
                                                     char *texture_a, char *texture_b,
                                                     char *cap_texture)
{
    width_cells = width_cells_;
    kind = PATH_TEMPLATE_KIND_SLALOMBIG;
    int lead_out_start = curve_segments + 4;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    int total_segments = lead_out_start + 4;
    width_or_scale = 1.0f;
    segment_count = total_segments;
    segment_count_f = (float)total_segments;
    GetNodes();
    has_entry_mesh_transition = 0;

    int i;
    int lead_sample_index = 0;
    int lead_sample_offset = 0;
    do
    {
        initialize_lead_pair(lead_sample_index, lead_sample_offset, secondary_samples,
                             primary_samples);
        ++lead_sample_index;
        lead_sample_offset += (int)sizeof(PathTemplateSample);
    } while (lead_sample_offset < 4 * (int)sizeof(PathTemplateSample));

    int departure_index = lead_out_start;
    int departure_sample_offset = departure_index * (int)sizeof(PathTemplateSample);
    int departure_origin = -4 - curve_segments;
    do
    {
        reset_primary_sample(primary_samples, departure_sample_offset, 0.0f);
        ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))
                ->center_x;
        float z = (float)departure_index;
        ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))
            ->transform.position.z = z;
        ((PathTemplateSample *)((char *)secondary_samples + departure_sample_offset))
            ->transform.Identity();
        ((PathTemplateSample *)((char *)secondary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))
                ->center_x;
        ((PathTemplateSample *)((char *)secondary_samples + departure_sample_offset))
            ->transform.position.y = 0.49000001f;
        ((PathTemplateSample *)((char *)secondary_samples + departure_sample_offset))
            ->transform.position.z = z;
        departure_sample_offset += (int)sizeof(PathTemplateSample);
        ++departure_index;
    } while (departure_index + departure_origin < 4);

    int curve_sample_index = 0;
    i = 0;
    if (curve_segments > 0)
    {
        int curve_sample_offset = 4 * (int)sizeof(PathTemplateSample);
        do
        {
            float t = (float)i / (float)curve_segments;
            float angle = t * 6.2831855f;
            float folded = (t - 0.5f) < 0.0f ? -(t - 0.5f) : (t - 0.5f);
            float folded_copy = (t - 0.5f) < 0.0f ? -(t - 0.5f) : (t - 0.5f);

            float center =
                Sin(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
            reset_primary_sample(primary_samples, curve_sample_offset, center);
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.y = 0.0f;
            float z = (float)(curve_sample_index + 4);
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.z = z;

            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.Identity();
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.y = 0.49000001f;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.z = z;

            if (curve_sample_offset > 4 * (int)sizeof(PathTemplateSample))
            {
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathTemplateSample *)((char *)primary_samples +
                                            curve_sample_offset))
                        ->transform.position -
                    ((PathTemplateSample *)((char *)primary_samples +
                                            curve_sample_offset) -
                     1)
                        ->transform.position;
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.basis_right.Cross(
                        ((PathTemplateSample *)((char *)primary_samples +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_up,
                        ((PathTemplateSample *)((char *)primary_samples +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_forward);
                float primary_roll = ((PathTemplateSample *)((char *)primary_samples +
                                                             curve_sample_offset) -
                                      1)
                                         ->center_x *
                                     0.2617994f;
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.RotLocalZ(primary_roll);

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

                float secondary_roll = ((PathTemplateSample *)((char *)primary_samples +
                                                               curve_sample_offset) -
                                        1)
                                           ->center_x *
                                       0.2617994f;
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.RotLocalZ(secondary_roll);
            }
            else
            {
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
                ((PathTemplateSample *)((char *)secondary_samples +
                                        curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
            }
            ++i;
            ++curve_sample_index;
            curve_sample_offset += sizeof(PathTemplateSample);
        } while (i < curve_segments);
    }

    compute_terminal_deltas(this);
    build_extrapolated_strip_mesh(this, width_cells, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
