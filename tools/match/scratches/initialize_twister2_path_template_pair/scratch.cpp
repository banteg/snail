// initialize_twister2_path_template_pair @ 0x42af30 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void orient_previous_sample_pair(Path *path, int current_offset)
{
    if (current_offset > (int)sizeof(PathTemplateSample))
    {
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_forward =
            ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[0]
                .transform.position -
            ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
                .transform.position;
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_right.Cross(
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_up,
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward);
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_up.Cross(
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_right);
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.Orthoganalize();

        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_forward =
            ((PathTemplateSample *)((char *)path->secondary_samples +
                                    current_offset))[0]
                .transform.position -
            ((PathTemplateSample *)((char *)path->secondary_samples +
                                    current_offset))[-1]
                .transform.position;
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_right.Cross(
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_up,
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward);
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_up.Cross(
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_right);
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.Orthoganalize();
    }
    else
    {
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.RotIdentity();
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.RotIdentity();
    }
}

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
                    double lateral = (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count)
                    {
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

static __forceinline void initialize_curve_sample(PathTemplateSample *&bank,
                                                  int sample_offset, float center)
{
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].center_x = center;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].rotation_scalar_98 = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].rotation_scalar_94 = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].special_scalar = 0.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].lateral_scale = 1.0f;
    ((PathTemplateSample *)((char *)bank + sample_offset))[0].transform.Identity();
}

void cRPath::initialize_twister2_path_template_pair(float height, int width_cells_,
                                                    bool handedness, char *texture_a,
                                                    char *texture_b,
                                                    char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_TWISTER2;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 52;
    segment_count_f = 52.0f;
    GetNodes();

    has_entry_mesh_transition = 0;
    primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    if (!handedness)
        primary_samples[0].center_x = primary_samples[0].center_x * -1.0f;
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

    primary_samples[51].center_x = (float)width_cells * 0.5f - 4.0f;
    if (!handedness)
        primary_samples[51].center_x = primary_samples[51].center_x * -1.0f;
    primary_samples[51].rotation_scalar_98 = 0.0f;
    primary_samples[51].rotation_scalar_94 = 0.0f;
    primary_samples[51].special_scalar = 0.0f;
    primary_samples[51].lateral_scale = 1.0f;
    primary_samples[51].transform.Identity();
    primary_samples[51].transform.position.x = primary_samples[51].center_x;
    primary_samples[51].transform.position.y = 0.0f;
    primary_samples[51].transform.position.z = 51.0f;
    secondary_samples[51].transform.Identity();
    secondary_samples[51].transform.position.x = primary_samples[51].center_x;
    secondary_samples[51].transform.position.y = 0.49000001f;
    secondary_samples[51].transform.position.z = 51.0f;

    int local_index = 0;
    for (int sample_offset = sizeof(PathTemplateSample);
         sample_offset < 51 * (int)sizeof(PathTemplateSample);
         sample_offset += sizeof(PathTemplateSample))
    {
        float angle = (float)local_index * 0.25132743f;
        float half_angle = angle * 0.5f;
        if (!handedness)
            angle += 3.1415927f;

        float center_scale = Cos(angle) + 1.0f;
        center_scale = center_scale * 0.5f;
        center_scale = center_scale * 5.0f;
        float center = 2.5f - center_scale;

        initialize_curve_sample(primary_samples, sample_offset, center);
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                .center_x;
        float angle_sine = Sin(angle);
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.y = Sin(half_angle) * angle_sine * height;
        int sample_z = local_index + 1;
        ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
            .transform.position.z = (float)sample_z;
        ((PathTemplateSample *)((char *)secondary_samples + sample_offset))[0]
            .transform.Identity();
        ((PathTemplateSample *)((char *)secondary_samples + sample_offset))[0]
            .transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                .center_x;
        ((PathTemplateSample *)((char *)secondary_samples + sample_offset))[0]
            .transform.position.y =
            ((PathTemplateSample *)((char *)primary_samples + sample_offset))[0]
                .transform.position.y +
            0.49000001f;
        ((PathTemplateSample *)((char *)secondary_samples + sample_offset))[0]
            .transform.position.z = (float)sample_z;
        orient_previous_sample_pair(this, sample_offset);
        local_index = sample_z;
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
