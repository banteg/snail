// initialize_slalomdouble_path_template_pair @ 0x425050 (thiscall, ret 0x18)

#include "path_helpers.h"

typedef AttachmentSample PathTemplateSample;

static __forceinline void initialize_secondary_departure(Path *path,
                                               PathTemplateSample *&secondary,
                                               int offset, float z)
{
    ((PathTemplateSample *)((char *)secondary + offset))->transform.Identity();
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.x =
        ((PathTemplateSample *)((char *)path->primary_samples + offset))->center_x;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.y =
        0.49000001f;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.z = z;
}

void cRPath::initialize_slalomdouble_path_template_pair(int curve_segments,
                                                        int width_cells_,
                                                        bool side_exit, char *texture_a,
                                                        char *texture_b,
                                                        char *cap_texture)
{
    kind = PATH_TEMPLATE_KIND_SLALOMDOUBLE;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 70;
    segment_count_f = 70.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    PathTemplateSample *&secondary_bank = secondary_samples;
    const int active_curve_segments = 62;
    const int lead_out_start = 66;
    int i;
    int lead_sample_index = 0;
    int lead_sample_offset = 0;
    do
    {
        initialize_lead_pair(lead_sample_index, lead_sample_offset, secondary_bank,
                             primary_samples);
        ++lead_sample_index;
        lead_sample_offset += (int)sizeof(PathTemplateSample);
    } while (lead_sample_offset < 4 * (int)sizeof(PathTemplateSample));

    int departure_index = lead_out_start;
    int departure_sample_offset = departure_index * (int)sizeof(PathTemplateSample);
    int departure_origin = -4 - active_curve_segments;
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
        initialize_secondary_departure(this, secondary_bank,
                             departure_sample_offset, z);
        departure_sample_offset += (int)sizeof(PathTemplateSample);
        ++departure_index;
    } while (departure_index + departure_origin < 4);

    int curve_sample_index = 0;
    i = 0;
    if (active_curve_segments > 0)
    {
        int curve_sample_offset = 4 * (int)sizeof(PathTemplateSample);
        do
        {
            float t = (float)i * 0.016129032f;
            float angle = t * 12.566371f;
            float folded = (t - 0.5f) < 0.0f ? -(t - 0.5f) : (t - 0.5f);
            float folded_copy = (t - 0.5f) < 0.0f ? -(t - 0.5f) : (t - 0.5f);

            PathTemplateSample *&curve_primary_bank = primary_samples;
            float center =
                Sin(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .center_x = center;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .rotation_scalar_98 = 0.0f;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .rotation_scalar_94 = 0.0f;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .special_scalar = 0.0f;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .lateral_scale = 1.0f;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))[0]
                .transform.Identity();
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))
                ->transform.position.y = 1.0f - Cos(angle * 0.5f);
            float z = (float)(curve_sample_index + 4);
            ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset))
                ->transform.position.z = z;

            {
                PathTemplateSample *&primary = curve_primary_bank;
                PathTemplateSample *&secondary = secondary_bank;
                ((PathTemplateSample *)((char *)secondary + curve_sample_offset))->transform.Identity();
                ((PathTemplateSample *)((char *)secondary + curve_sample_offset))->transform.position.x =
                    ((PathTemplateSample *)((char *)primary + curve_sample_offset))->center_x;
                ((PathTemplateSample *)((char *)secondary + curve_sample_offset))->transform.position.y =
                        ((PathTemplateSample *)((char *)primary + curve_sample_offset))->transform.position.y +
                        0.49000001f;
                ((PathTemplateSample *)((char *)secondary + curve_sample_offset))->transform.position.z = z;
            }

            if (curve_sample_offset > 4 * (int)sizeof(PathTemplateSample))
            {
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathTemplateSample *)((char *)curve_primary_bank +
                                            curve_sample_offset))
                        ->transform.position -
                    ((PathTemplateSample *)((char *)curve_primary_bank +
                                            curve_sample_offset) -
                     1)
                        ->transform.position;
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.basis_right.Cross(
                        ((PathTemplateSample *)((char *)curve_primary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_up,
                        ((PathTemplateSample *)((char *)curve_primary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_forward);
                float primary_roll = ((PathTemplateSample *)((char *)curve_primary_bank +
                                                             curve_sample_offset) -
                                      1)
                                         ->center_x *
                                     0.2617994f;
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.RotLocalZ(primary_roll);

                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_forward =
                    ((PathTemplateSample *)((char *)secondary_bank +
                                            curve_sample_offset))
                        ->transform.position -
                    ((PathTemplateSample *)((char *)secondary_bank +
                                            curve_sample_offset) -
                     1)
                        ->transform.position;
                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_forward.Normalize();
                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.basis_right.Cross(
                        ((PathTemplateSample *)((char *)secondary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_up,
                        ((PathTemplateSample *)((char *)secondary_bank +
                                                curve_sample_offset) -
                         1)
                            ->transform.basis_forward);

                float secondary_roll = ((PathTemplateSample *)((char *)curve_primary_bank +
                                                               curve_sample_offset) -
                                        1)
                                           ->center_x *
                                       0.2617994f;
                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.RotLocalZ(secondary_roll);
            }
            else
            {
                ((PathTemplateSample *)((char *)curve_primary_bank + curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
                ((PathTemplateSample *)((char *)secondary_bank +
                                        curve_sample_offset) -
                 1)
                    ->transform.RotIdentity();
            }
            ++i;
            ++curve_sample_index;
            curve_sample_offset += sizeof(PathTemplateSample);
        } while (curve_sample_offset < 66 * (int)sizeof(PathTemplateSample));
    }

    compute_terminal_deltas(this);
    build_extrapolated_strip_mesh(this, width_cells, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
