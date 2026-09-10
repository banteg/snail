// initialize_p_path_template_pair @ 0x425a40 (thiscall, ret 0x24)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void build_strip_mesh(Path *path, char *texture_a, char *texture_b)
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
        column = 0;
        if (path->width_cells > 0)
        {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            do
            {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;

                for (face_index = 0; face_index < 2; ++face_index)
                {
                    int face_offset =
                        2 * column + 2 * row * path->width_cells + face_index;
                    if (face_index == 0)
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        facequads[face_offset].vertex_3 =
                            column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (((column ^ row) & 1) == 0)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                    }
                    else
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_1 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        if (((column ^ row) & 1) == 0)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                    }
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
                ++column;
            } while (column < path->width_cells);
        }
    }
}

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

static __forceinline void initialize_endpoint_pair(int index,
                                                   PathTemplateSample *&primary,
                                                   PathTemplateSample *&secondary,
                                                   float center)
{
    int offset = index * (int)sizeof(PathTemplateSample);
    ((PathTemplateSample *)((char *)primary + offset))->center_x = center;
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
    int sample_count = last_index + 1;
    segment_count = sample_count;
    segment_count_f = (float)sample_count;

    float half_distance = (end_x - start_x) * 0.5f;
    if (half_distance < 0.0f)
        scale_arg = -half_distance;
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

    initialize_endpoint_pair(last_index, primary_samples, secondary_samples, end_x);

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
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x = Sin(angle + 1.5707964f) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x22:
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x = 2.0f - Cos(angle) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x23:
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x = (Sin(angle + 1.5707964f) + 1.0f) * scale_arg + 0.5f;
                break;
            }

            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->special_scalar = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->lateral_scale = 1.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.Identity();
            float z = (float)(curve_index + 1);
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.y = 0.0f;
            ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.z = z;

            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.Identity();
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.y =
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.position.y +
                0.49000001f;
            ((PathTemplateSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform.position.z = z;
            if (curve_sample_offset > (int)sizeof(PathTemplateSample))
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
                ((PathTemplateSample *)((char *)primary_samples + curve_sample_offset) -
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

    compute_terminal_deltas(this);

    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)cap_texture;
}
