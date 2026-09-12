// initialize_dump_path_template_pair @ 0x41da30 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

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
                    double lateral = (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count)
                    {
                        PathAttachmentSample *sample =
                            (PathAttachmentSample *)((char *)path->primary_samples +
                                                     sample_offset);
                        Vector3 lateral_offset =
                            sample->transform.basis_right * lateral;
                        Vector3 generated_position =
                            sample->transform.position + lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        Vector3 generated_position =
                            (((PathAttachmentSample *)((char *)path->primary_samples +
                                                       sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((PathAttachmentSample *)((char *)path->primary_samples +
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
            sample_offset += sizeof(PathAttachmentSample);
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
            ((PathAttachmentSample *)((char *)path->primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample *)((char *)path->primary_samples +
                                          delta_offset) +
                 1)
                    ->transform.position -
                ((PathAttachmentSample *)((char *)path->primary_samples + delta_offset))
                    ->transform.position;
            ((PathAttachmentSample *)((char *)path->primary_samples + delta_offset))
                ->delta_length =
                ((PathAttachmentSample *)((char *)path->primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathAttachmentSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample *)((char *)path->secondary_samples +
                                          delta_offset) +
                 1)
                    ->transform.position -
                ((PathAttachmentSample *)((char *)path->secondary_samples +
                                          delta_offset))
                    ->transform.position;
            ((PathAttachmentSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_length =
                ((PathAttachmentSample *)((char *)path->secondary_samples +
                                          delta_offset))
                    ->delta_dir_to_next.Normalize();

            ++i;
            delta_offset += (int)sizeof(PathAttachmentSample);
        } while (i < path->segment_count - 1);
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

void cRPath::initialize_dump_path_template_pair(float curve_source, float height_scale,
                                                int width_cells_, bool side_exit,
                                                char *texture_a, char *texture_b,
                                                char *cap_texture)
{
    int curve_count;
    int i;

    kind = PATH_TEMPLATE_KIND_FAMILY_11;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    curve_count = (int)(curve_source * 4.0f);
    width_or_scale = 1.0f;
    int departure_index = curve_count + 7;
    segment_count = departure_index + 7;
    segment_count_f = (float)(departure_index + 7);
    float curve_count_f = (float)curve_count;
    curve_source = curve_count_f * 0.095492966f;
    GetNodes();
    has_entry_mesh_transition = 0;

    for (i = 0; i < 7; ++i)
    {
        primary_samples[i].center_x = -((float)width_cells * 0.5f - 4.0f);
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        primary_samples[i].transform.Identity();
        float z = (float)i;
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;
        secondary_samples[i].transform.Identity();
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
    }

    i = departure_index;
    int departure_offset = departure_index * sizeof(PathAttachmentSample);
    int departure_origin = -7 - curve_count;
    do
    {
        ((PathAttachmentSample *)((char *)primary_samples + departure_offset))[0]
            .center_x = -(4.0f - (float)width_cells * 0.5f);
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
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->transform.position.x =
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                    ->center_x;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->transform.position.y =
                -((1.0f - Cos(angle)) * curve_source * (height_scale));
            float z = (float)sample_index;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->transform.position.z = z;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.Identity();
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.position.x =
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                    ->center_x;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.position.y =
                0.49000001f - (1.0f - Cos(angle)) * curve_source * (height_scale);
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
