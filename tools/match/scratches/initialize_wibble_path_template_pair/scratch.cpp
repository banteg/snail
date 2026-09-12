// initialize_wibble_path_template_pair @ 0x4289a0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;



static __forceinline void compute_path_deltas(Path *path)
{
    int i = 0;
    if (path->segment_count - 1 > 0)
    {
        int sample_offset = 0;
        do
        {
            ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->primary_samples + sample_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample *)((char *)path->secondary_samples + sample_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        sample_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        sample_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->secondary_samples + sample_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        sample_offset))
                    ->delta_dir_to_next.Normalize();
            ++i;
            sample_offset += sizeof(PathTemplateSample);
        } while (i < path->segment_count - 1);
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

                int face_index;
                for (face_index = 0; face_index < 2; ++face_index)
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
                }
                ++column;
            } while (column < path->width_cells);
        }
    }
}

static __forceinline void initialize_wibble_primary(PathTemplateSample *&bank,
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

static __forceinline void copy_wibble_frame(PathTemplateSample *&primary,
                                            PathTemplateSample *&secondary, int offset)
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
        float t = (float)local_index;
        float turn_phase = t * 0.20943952f;

        initialize_wibble_primary(primary_samples, sample_offset, t);

        int z_index = local_index + 1;
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.x = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.z = (float)z_index;
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.y = 0.0f;

        float basis_y = Cos(Sin(turn_phase * 3.0f) * 0.30000001f);
        float basis_x = Sin(Sin(turn_phase * 3.0f) * 0.30000001f);
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.basis_up = Vector3(basis_x, basis_y, 0.0f);
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.basis_forward =
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                .transform.position -
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[-1]
                .transform.position;
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.basis_forward.Normalize();
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.basis_right.Cross(
                ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                    .transform.basis_up,
                ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                    .transform.basis_forward);

        copy_wibble_frame(primary_samples, secondary_samples, sample_offset);
        ++local_index;
        sample_offset += sizeof(PathTemplateSample);
    } while (sample_offset < 31 * (int)sizeof(PathTemplateSample));

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)radius;
    (void)side_exit;
    (void)vertical_texture;
}
