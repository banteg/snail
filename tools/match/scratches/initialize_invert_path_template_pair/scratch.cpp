// initialize_invert_path_template_pair @ 0x429250 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void compute_path_deltas(Path *path)
{
    for (int i = 0; i < path->segment_count - 1; ++i)
    {
        path->primary_samples[i].delta_dir_to_next =
            path->primary_samples[i + 1].transform.position -
            path->primary_samples[i].transform.position;
        path->primary_samples[i].delta_length =
            path->primary_samples[i].delta_dir_to_next.Normalize();

        path->secondary_samples[i].delta_dir_to_next =
            path->secondary_samples[i + 1].transform.position -
            path->secondary_samples[i].transform.position;
        path->secondary_samples[i].delta_length =
            path->secondary_samples[i].delta_dir_to_next.Normalize();
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void build_strip_mesh(Path *path, char *texture_a, char *texture_b)
{
    path->strip_mesh->RequestVertices((path->width_cells + 1) *
                                      (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(2 * path->width_cells * path->segment_count);

    Vector3 *vertices = path->strip_mesh->vertices;
    cRFaceQuad *facequads = path->strip_mesh->facequads;
    int row = 0;
    int column;
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

                int face_index = 0;
                do
                {
                    int face_offset =
                        face_index + 2 * (row * path->width_cells + column);
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
                    ++face_index;
                } while (face_index < 2);
                ++column;
            } while (column < path->width_cells);
        }
    }
}

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
        Vector3 secondary_offset =
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                .transform.basis_up *
            0.49000001f;
        Vector3 *secondary_position =
            &((PathTemplateSample *)((char *)secondary_samples + sample_offset))[0]
                 .transform.position;
        secondary_position->x += secondary_offset.x;
        secondary_position->y += secondary_offset.y;
        secondary_position->z += secondary_offset.z;
        sample_offset += (int)sizeof(PathTemplateSample);
    } while (sample_offset < 33 * (int)sizeof(PathTemplateSample));

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)radius;
    (void)side_exit;
    (void)cap_texture;
}
