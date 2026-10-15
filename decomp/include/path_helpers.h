#ifndef PATH_HELPERS_H
#define PATH_HELPERS_H

// Static helpers that several Path.cpp template builders share. Path compiles
// as one translation unit, so each body exists once; a builder whose code
// differs from a body here writes its own copy inline instead.

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

inline Vector3 operator*(float scale, const Vector3& vector)
{
    return Vector3(scale * vector.x, scale * vector.y, scale * vector.z);
}

static inline void interpolate_path_center(
    AttachmentSample* const& bank, int sample_index, int loop_segment_count,
    float sample_f, float curve_count_f)
{
    bank[sample_index].center_x =
        (bank[loop_segment_count - 1].center_x - bank[0].center_x)
        * sample_f / curve_count_f + bank[0].center_x;
}

static __forceinline void reset_primary_sample(AttachmentSample *&bank,
                                               int sample_offset, float center)
{
    ((AttachmentSample *)((char *)bank + sample_offset))[0].center_x = center;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].rotation_scalar_98 = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].rotation_scalar_94 = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].special_scalar = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].lateral_scale = 1.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].transform.Identity();
}

static __forceinline void compute_terminal_deltas(Path *path)
{
    int i = 0;
    if (path->segment_count - 1 > 0)
    {
        do
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

            ++i;
        } while (i < path->segment_count - 1);
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void initialize_lead_pair(int index, int offset,
                                               AttachmentSample *&secondary,
                                               AttachmentSample *&primary)
{
    ((AttachmentSample *)((char *)primary + offset))->center_x = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->rotation_scalar_98 = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->rotation_scalar_94 = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->special_scalar = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->lateral_scale = 1.0f;
    ((AttachmentSample *)((char *)primary + offset))->transform.Identity();
    ((AttachmentSample *)((char *)primary + offset))->transform.position.x =
        ((AttachmentSample *)((char *)primary + offset))->center_x;
    float z = (float)index;
    ((AttachmentSample *)((char *)primary + offset))->transform.position.y = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->transform.position.z = z;

    ((AttachmentSample *)((char *)secondary + offset))->transform.Identity();
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.x =
        ((AttachmentSample *)((char *)primary + offset))->center_x;
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.y =
        0.49000001f;
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.z = z;
}

static __forceinline void build_extrapolated_strip_mesh(
    Path *path, const int &width_cells, char *texture_a, char *texture_b)
{
    path->strip_mesh->RequestVertices((width_cells + 1) *
                                      (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(2 * width_cells * path->segment_count);

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
            if (width_cells >= 0)
            {
                do
                {
                    if (row != path->segment_count)
                    {
                        float lateral = (float)column - (float)width_cells * 0.5f;
                        Vector3 lateral_offset =
                            ((AttachmentSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.basis_right *
                            lateral;
                        Vector3 generated_position =
                            ((AttachmentSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.position +
                            lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        float lateral = (float)column - (float)width_cells * 0.5f;
                        Vector3 generated_position =
                            (((AttachmentSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((AttachmentSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.basis_right *
                             lateral);
                        Vector3 *vertex =
                            &vertices[column + row * (width_cells + 1)];
                        *vertex = generated_position;
                    }
                    ++column;
                } while (column <= width_cells);
            }
            ++row;
            sample_offset += sizeof(AttachmentSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row)
    {
        for (column = 0; column < width_cells; ++column)
        {

            for (face_index = 0; face_index < 2; ++face_index)
            {
                int face_offset = 2 * column + 2 * row * width_cells + face_index;
                facequads[face_offset].header_word = 0;

                if (face_index == 0)
                {
                    facequads[face_offset].vertex_0 =
                        column + row * ((unsigned short)width_cells + 1);
                    facequads[face_offset].vertex_1 =
                        row * ((unsigned short)width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_2 =
                        (row + 1) * ((unsigned short)width_cells + 1) + column +
                        1;
                    facequads[face_offset].vertex_3 =
                        column + (row + 1) * ((unsigned short)width_cells + 1);
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
                        row * ((unsigned short)width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_1 =
                        column + row * ((unsigned short)width_cells + 1);
                    facequads[face_offset].vertex_2 =
                        column + (row + 1) * ((unsigned short)width_cells + 1);
                    facequads[face_offset].vertex_3 =
                        (row + 1) * ((unsigned short)width_cells + 1) + column +
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
                            ((AttachmentSample *)((char *)path->primary_samples +
                                                      sample_offset))
                                ->transform.basis_right *
                            lateral;
                        Vector3 generated_position =
                            ((AttachmentSample *)((char *)path->primary_samples +
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
                            (((AttachmentSample *)((char *)path->primary_samples +
                                                       sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((AttachmentSample *)((char *)path->primary_samples +
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
            sample_offset += sizeof(AttachmentSample);
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

static __forceinline void compute_path_deltas(
    const int &count, AttachmentSample *const &primary,
    AttachmentSample *const &secondary)
{
    int i = 0;
    if (count - 1 > 0)
    {
        int sample_offset = 0;
        do
        {
            ((AttachmentSample *)((char *)primary + sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)primary + sample_offset) +
                 1)
                    ->transform.position -
                ((AttachmentSample *)((char *)primary + sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)primary + sample_offset))
                ->delta_length =
                ((AttachmentSample *)((char *)primary + sample_offset))
                    ->delta_dir_to_next.Normalize();

            ((AttachmentSample *)((char *)secondary + sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)secondary +
                                        sample_offset) +
                 1)
                    ->transform.position -
                ((AttachmentSample *)((char *)secondary +
                                        sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)secondary + sample_offset))
                ->delta_length =
                ((AttachmentSample *)((char *)secondary +
                                        sample_offset))
                    ->delta_dir_to_next.Normalize();
            ++i;
            sample_offset += sizeof(AttachmentSample);
        } while (i < count - 1);
    }

    primary[count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    primary[count - 1].delta_length = 1.0f;
    secondary[count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    secondary[count - 1].delta_length = 1.0f;
}

static __forceinline void initialize_curve_sample(AttachmentSample *&bank,
                                                  int sample_offset, float center)
{
    ((AttachmentSample *)((char *)bank + sample_offset))[0].center_x = center;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].rotation_scalar_98 = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].rotation_scalar_94 = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].special_scalar = 0.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].lateral_scale = 1.0f;
    ((AttachmentSample *)((char *)bank + sample_offset))[0].transform.Identity();
}

static __forceinline void orient_previous_sample_pair(
    AttachmentSample *const &primary, AttachmentSample *const &secondary,
    int current_offset)
{
    if (current_offset > (int)sizeof(AttachmentSample))
    {
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.basis_forward =
            ((AttachmentSample *)((char *)primary + current_offset))[0]
                .transform.position -
            ((AttachmentSample *)((char *)primary + current_offset))[-1]
                .transform.position;
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.basis_right.Cross(
                ((AttachmentSample *)((char *)primary +
                                        current_offset))[-1]
                    .transform.basis_up,
                ((AttachmentSample *)((char *)primary +
                                        current_offset))[-1]
                    .transform.basis_forward);
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.basis_up.Cross(
                ((AttachmentSample *)((char *)primary +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((AttachmentSample *)((char *)primary +
                                        current_offset))[-1]
                    .transform.basis_right);
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.Orthoganalize();

        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.basis_forward =
            ((AttachmentSample *)((char *)secondary +
                                    current_offset))[0]
                .transform.position -
            ((AttachmentSample *)((char *)secondary +
                                    current_offset))[-1]
                .transform.position;
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.basis_right.Cross(
                ((AttachmentSample *)((char *)secondary +
                                        current_offset))[-1]
                    .transform.basis_up,
                ((AttachmentSample *)((char *)secondary +
                                        current_offset))[-1]
                    .transform.basis_forward);
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.basis_up.Cross(
                ((AttachmentSample *)((char *)secondary +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((AttachmentSample *)((char *)secondary +
                                        current_offset))[-1]
                    .transform.basis_right);
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.Orthoganalize();
    }
    else
    {
        ((AttachmentSample *)((char *)primary + current_offset))[-1]
            .transform.RotIdentity();
        ((AttachmentSample *)((char *)secondary + current_offset))[-1]
            .transform.RotIdentity();
    }
}

static __forceinline int finish_curve_positions(
    AttachmentSample *const &primary, AttachmentSample *const &secondary,
    int sample_offset, int local_index, float angle, float half_angle, float height)
{
    ((AttachmentSample *)((char *)primary + sample_offset))[0]
        .transform.position.x =
        ((AttachmentSample *)((char *)primary + sample_offset))[0]
            .center_x;
    float angle_sine = Sin(angle);
    ((AttachmentSample *)((char *)primary + sample_offset))[0]
        .transform.position.y = Sin(half_angle) * angle_sine * height;
    int sample_z = local_index + 1;
    ((AttachmentSample *)((char *)primary + sample_offset))[0]
        .transform.position.z = (float)sample_z;
    ((AttachmentSample *)((char *)secondary + sample_offset))[0]
        .transform.Identity();
    ((AttachmentSample *)((char *)secondary + sample_offset))[0]
        .transform.position.x =
        ((AttachmentSample *)((char *)primary + sample_offset))[0]
            .center_x;
    ((AttachmentSample *)((char *)secondary + sample_offset))[0]
        .transform.position.y =
        ((AttachmentSample *)((char *)primary + sample_offset))[0]
            .transform.position.y +
        0.49000001f;
    ((AttachmentSample *)((char *)secondary + sample_offset))[0]
        .transform.position.z = (float)sample_z;
    orient_previous_sample_pair(primary, secondary, sample_offset);
    return sample_z;
}

#endif
