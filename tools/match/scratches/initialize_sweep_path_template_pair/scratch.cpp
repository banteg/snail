// initialize_sweep_path_template_pair @ 0x422c00 (thiscall, ret 0x18)

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
            int next_column;
            do
            {
                next_column = column + 1;
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
                        if (!((column ^ row) & 1))
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
                        if (!((column ^ row) & 1))
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
                column = next_column;
            } while (next_column < path->width_cells);
        }
    }
}

static __forceinline void initialize_secondary(PathTemplateSample *&secondary,
                                               PathTemplateSample *&primary, int offset,
                                               float z, bool copy_primary_y)
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

void cRPath::initialize_sweep_path_template_pair(float scale_arg, int width_cells_,
                                                 bool side_exit, char *texture_a,
                                                 char *texture_b, char *cap_texture)
{
    kind = PATH_TEMPLATE_KIND_SWEEP;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 30;
    segment_count_f = 30.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int i;
    i = 0;
    int lead_offset = 0;
    for (; lead_offset < 3 * (int)sizeof(PathTemplateSample);
         ++i, lead_offset += sizeof(PathTemplateSample))
    {
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0].center_x =
            (float)width_cells * 0.5f - 4.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .rotation_scalar_98 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .rotation_scalar_94 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .special_scalar = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .lateral_scale = 1.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .transform.Identity();
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0].center_x;
        float z = (float)i;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.y = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_offset))[0]
            .transform.position.z = z;

        initialize_secondary(secondary_samples, primary_samples, lead_offset, z, false);
    }

    int departure_index = 27;
    int departure_offset = 27 * (int)sizeof(PathTemplateSample);
    do
    {
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))->center_x =
            4.0f - (float)width_cells * 0.5f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->special_scalar = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->lateral_scale = 1.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->transform.Identity();
        float z = (float)departure_index;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + departure_offset))
                ->center_x;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + departure_offset))
            ->transform.position.z = z;

        initialize_secondary(secondary_samples, primary_samples, departure_offset, z,
                             false);
        departure_offset += (int)sizeof(PathTemplateSample);
        ++departure_index;
    } while (departure_index - 27 < 3);

    int curve_index = 0;
    for (i = 3 * (int)sizeof(PathTemplateSample);
         i < 27 * (int)sizeof(PathTemplateSample); i += (int)sizeof(PathTemplateSample))
    {
        float angle = (float)curve_index * 0.1308997f;
        ((PathTemplateSample *)((char *)primary_samples + i))->center_x =
            Cos(angle) * primary_samples[0].center_x;
        ((PathTemplateSample *)((char *)primary_samples + i))->rotation_scalar_98 =
            0.0f;
        ((PathTemplateSample *)((char *)primary_samples + i))->rotation_scalar_94 =
            0.0f;
        ((PathTemplateSample *)((char *)primary_samples + i))->special_scalar = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + i))->lateral_scale = 1.0f;
        ((PathTemplateSample *)((char *)primary_samples + i))->transform.Identity();
        ((PathTemplateSample *)((char *)primary_samples + i))->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + i))->center_x;
        ((PathTemplateSample *)((char *)primary_samples + i))->transform.position.y =
            Sin(angle) * -0.30000001f;
        float z = (float)(curve_index + 3);
        ((PathTemplateSample *)((char *)primary_samples + i))->transform.position.z = z;

        initialize_secondary(secondary_samples, primary_samples, i, z, true);
        if (i > 3 * (int)sizeof(PathTemplateSample))
        {
            ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                ->transform.basis_forward =
                ((PathTemplateSample *)((char *)primary_samples + i))
                    ->transform.position -
                ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                    ->transform.position;
            ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                ->transform.basis_forward.Normalize();
            ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                ->transform.basis_right.Cross(
                    ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                        ->transform.basis_up,
                    ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                        ->transform.basis_forward);

            ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                ->transform.basis_forward =
                ((PathTemplateSample *)((char *)secondary_samples + i))
                    ->transform.position -
                ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                    ->transform.position;
            ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                ->transform.basis_forward.Normalize();
            ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                ->transform.basis_right.Cross(
                    ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                        ->transform.basis_up,
                    ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                        ->transform.basis_forward);
        }
        else
        {
            ((PathTemplateSample *)((char *)primary_samples + i) - 1)
                ->transform.RotIdentity();
            ((PathTemplateSample *)((char *)secondary_samples + i) - 1)
                ->transform.RotIdentity();
        }
        ++curve_index;
    }

    int delta_index = 0;
    if (segment_count - 1 > 0)
    {
        do
        {
            primary_samples[delta_index].delta_dir_to_next =
                primary_samples[delta_index + 1].transform.position -
                primary_samples[delta_index].transform.position;
            primary_samples[delta_index].delta_length =
                primary_samples[delta_index].delta_dir_to_next.Normalize();

            secondary_samples[delta_index].delta_dir_to_next =
                secondary_samples[delta_index + 1].transform.position -
                secondary_samples[delta_index].transform.position;
            secondary_samples[delta_index].delta_length =
                secondary_samples[delta_index].delta_dir_to_next.Normalize();

            ++delta_index;
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)scale_arg;
    (void)side_exit;
    (void)cap_texture;
}
