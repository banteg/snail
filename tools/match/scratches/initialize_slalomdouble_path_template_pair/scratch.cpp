// initialize_slalomdouble_path_template_pair @ 0x425050 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void compute_terminal_deltas(Path *path)
{
    int i = 0;
    if (path->segment_count - 1 > 0)
    {
        int delta_offset = 0;
        do
        {
            ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        delta_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ++i;
            delta_offset += (int)sizeof(PathTemplateSample);
        } while (i < path->segment_count - 1);
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void build_extrapolated_strip_mesh(Path *path, char *texture_a,
                                                        char *texture_b)
{
    path->strip_mesh->RequestVertices((path->width_cells + 1) *
                                      (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(2 * path->width_cells * path->segment_count);

    Vector3 *vertices = path->strip_mesh->vertices;
    cRFaceQuad *facequads = path->strip_mesh->facequads;

    int row = 0;
    int column;
    int face_index;
    if (path->segment_count >= 0)
    {
        int sample_offset = 0;
        do
        {
            column = 0;
            if (path->width_cells >= 0)
            {
                do
                {
                    if (row != path->segment_count)
                    {
                        float lateral = (float)column - (float)path->width_cells * 0.5f;
                        Vector3 lateral_offset =
                            ((PathTemplateSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.basis_right *
                            lateral;
                        Vector3 generated_position =
                            ((PathTemplateSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.position +
                            lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        float lateral = (float)column - (float)path->width_cells * 0.5f;
                        Vector3 generated_position =
                            (((PathTemplateSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((PathTemplateSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.basis_right *
                             lateral);
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row)
    {
        for (column = 0; column < path->width_cells; ++column)
        {

            for (face_index = 0; face_index < 2; ++face_index)
            {
                int face_offset = 2 * column + 2 * row * path->width_cells + face_index;
                facequads[face_offset].header_word = 0;

                if (face_index == 0)
                {
                    facequads[face_offset].vertex_0 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_1 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_2 =
                        (row + 1) * ((unsigned short)path->width_cells + 1) + column +
                        1;
                    facequads[face_offset].vertex_3 =
                        column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    if (((column ^ row) & 1) == 0)
                    {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    }
                    else
                    {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    }
                }
                else
                {
                    facequads[face_offset].vertex_0 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_1 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_2 =
                        column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_3 =
                        (row + 1) * ((unsigned short)path->width_cells + 1) + column +
                        1;
                    if (((column ^ row) & 1) == 0)
                    {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    }
                    else
                    {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    }
                }
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;
                float v0 = (float)(row % 8) * 0.125f;
                float v1 = (float)(row % 8 + 1) * 0.125f;
                if (face_index == 0)
                {
                    facequads[face_offset].uv[0].u = u0;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u1;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u1;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u0;
                    facequads[face_offset].uv[3].v = v1;
                }
                else
                {
                    facequads[face_offset].uv[0].u = u1;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u0;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u0;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u1;
                    facequads[face_offset].uv[3].v = v1;
                }
            }
        }
    }
}

static __forceinline void initialize_lead_pair(int index, int offset,
                                               PathTemplateSample *&secondary,
                                               PathTemplateSample *&primary)
{
    ((PathTemplateSample *)((char *)primary + offset))->center_x = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))->rotation_scalar_98 = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))->rotation_scalar_94 = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))->special_scalar = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))->lateral_scale = 1.0f;
    ((PathTemplateSample *)((char *)primary + offset))->transform.Identity();
    ((PathTemplateSample *)((char *)primary + offset))->transform.position.x =
        ((PathTemplateSample *)((char *)primary + offset))->center_x;
    float z = (float)index;
    ((PathTemplateSample *)((char *)primary + offset))->transform.position.y = 0.0f;
    ((PathTemplateSample *)((char *)primary + offset))->transform.position.z = z;

    ((PathTemplateSample *)((char *)secondary + offset))->transform.Identity();
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.x =
        ((PathTemplateSample *)((char *)primary + offset))->center_x;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.y =
        0.49000001f;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.z = z;
}

static __forceinline void reset_primary_sample(PathTemplateSample *&bank,
                                               int sample_offset, float center)
{
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].center_x = center;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].rotation_scalar_98 = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].rotation_scalar_94 = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].special_scalar = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].lateral_scale = 1.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].transform.Identity();
}

static __forceinline void initialize_secondary(PathTemplateSample *&primary,
                                               PathTemplateSample *&secondary,
                                               int offset, float z, bool copy_primary_y)
{
    ((PathTemplateSample *)((char *)secondary + offset))->transform.Identity();
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.x =
        ((PathTemplateSample *)((char *)primary + offset))->center_x;
    if (copy_primary_y)
        ((PathTemplateSample *)((char *)secondary + offset))->transform.position.y =
            ((PathTemplateSample *)((char *)primary + offset))->transform.position.y +
            0.49000001f;
    else
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

    const int active_curve_segments = 62;
    const int lead_out_start = 66;
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
        initialize_secondary(primary_samples, secondary_samples,
                             departure_sample_offset, z, false);
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

            float center =
                Sin(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .center_x = center;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .rotation_scalar_98 = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .rotation_scalar_94 = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .special_scalar = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .lateral_scale = 1.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))[0]
                .transform.Identity();
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.y = 1.0f - Cos(angle * 0.5f);
            float z = (float)(curve_sample_index + 4);
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.z = z;

            initialize_secondary(primary_samples, secondary_samples,
                                 curve_sample_offset, z, true);

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
        } while (curve_sample_offset < 66 * (int)sizeof(PathTemplateSample));
    }

    compute_terminal_deltas(this);
    build_extrapolated_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
