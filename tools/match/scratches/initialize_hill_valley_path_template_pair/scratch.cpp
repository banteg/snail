// initialize_hill_valley_path_template_pair @ 0x42d570 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void initialize_secondary_hill(PathTemplateSample *const &secondary,
                                                    Path *path, int offset, float phase,
                                                    float height, float z)
{
    ((PathTemplateSample *)((char *)secondary + offset))->transform.Identity();
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.x = ((PathTemplateSample *)((char *)path->primary_samples + offset))->center_x;
    float y = (1.0f - Cos(phase)) * 0.5f;
    y *= height;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.y = y + 0.49000001f;
    ((PathTemplateSample *)((char *)secondary + offset))->transform.position.z = z;
}

static __forceinline void orient_previous_hill_pair(Path *path, int current_offset)
{
    if (current_offset > (int)sizeof(PathTemplateSample))
    {
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_forward =
            (*(PathTemplateSample *)((char *)path->primary_samples + current_offset))
                .transform.position -
            ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
                .transform.position;
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((PathTemplateSample *)((char *)path->primary_samples + current_offset))[-1]
            .transform.basis_up.Cross(
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((PathTemplateSample *)((char *)path->primary_samples +
                                        current_offset))[-1]
                    .transform.basis_right);

        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_forward =
            (*(PathTemplateSample *)((char *)path->secondary_samples + current_offset))
                .transform.position -
            ((PathTemplateSample *)((char *)path->secondary_samples +
                                    current_offset))[-1]
                .transform.position;
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_forward.Normalize();
        ((PathTemplateSample *)((char *)path->secondary_samples + current_offset))[-1]
            .transform.basis_up.Cross(
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_forward,
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        current_offset))[-1]
                    .transform.basis_right);
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
                        Vector3 generated_position(((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                                ->transform.position.x + lateral_offset.x,
                            ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                                ->transform.position.y + lateral_offset.y, 0.0f);
                        generated_position.z = ((PathTemplateSample *)((char *)path->primary_samples + sample_offset))
                                ->transform.position.z + lateral_offset.z;
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
                        if ((column & 1) == (row & 1))
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
                        if ((column & 1) == (row & 1))
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

void cRPath::initialize_hill_valley_path_template_pair(int width_cells_, float height,
                                                       float length, bool centered,
                                                       char *texture_a, char *texture_b,
                                                       char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int steps = (int)length;
    width_or_scale = 1.0f;
    int last = steps + 1;
    segment_count = last;
    ++segment_count;
    segment_count_f = (float)(last + 1);
    segment_count_f = (float)segment_count;
    GetNodes();

    has_entry_mesh_transition = 0;

    if (centered)
        primary_samples[0].center_x = 0.0f;
    else
        primary_samples[0].center_x = ((float)width_cells * 0.5f) - 4.0f;
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

    int terminal_index;
    if (centered)
    {
        terminal_index = steps + 1;
        primary_samples[terminal_index].center_x = 0.0f;
    }
    else
    {
        terminal_index = steps + 1;
        primary_samples[terminal_index].center_x = (float)width_cells * 0.5f - 4.0f;
    }
    primary_samples[terminal_index].rotation_scalar_98 = 0.0f;
    primary_samples[terminal_index].rotation_scalar_94 = 0.0f;
    primary_samples[terminal_index].special_scalar = 0.0f;
    primary_samples[terminal_index].lateral_scale = 1.0f;
    primary_samples[terminal_index].transform.Identity();
    primary_samples[terminal_index].transform.position.x =
        primary_samples[terminal_index].center_x;
    float terminal_z = (float)terminal_index;
    primary_samples[terminal_index].transform.position.y = 0.0f;
    primary_samples[terminal_index].transform.position.z = terminal_z;
    secondary_samples[terminal_index].transform.Identity();
    secondary_samples[terminal_index].transform.position.x =
        primary_samples[terminal_index].center_x;
    secondary_samples[terminal_index].transform.position.y = 0.49000001f;
    secondary_samples[terminal_index].transform.position.z = terminal_z;

    PathTemplateSample *const &secondary_bank = secondary_samples;
    int i = 0;
    if (steps > 0)
    {
      int curve_offset = sizeof(PathTemplateSample);
      do
      {
        PathTemplateSample *const &primary_bank = primary_samples;
        int sample_index = i + 1;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->center_x = primary_bank[0].center_x;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->special_scalar = 0.0f;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->lateral_scale = 1.0f;
        float phase = (float)i * 6.2831855f / (float)steps;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->transform.Identity();
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->transform.position.x =
            ((PathTemplateSample *)((char *)primary_bank + curve_offset))->center_x;
        float y = (1.0f - Cos(phase)) * 0.5f;
        y *= height;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->transform.position.y = y;
        float z = (float)sample_index;
        ((PathTemplateSample *)((char *)primary_bank + curve_offset))->transform.position.z = z;
        initialize_secondary_hill(secondary_bank, this, curve_offset, phase, height, z);
        orient_previous_hill_pair(this, curve_offset);
        curve_offset += sizeof(PathTemplateSample);
        ++i;
      } while (i < steps);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
