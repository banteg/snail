// initialize_toad_path_template_pair @ 0x42cbf0 (thiscall, ret 0x10)

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
        int delta_sample_offset = 0;
        do
        {
            ((AttachmentSample *)((char *)path->primary_samples + delta_sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)path->primary_samples +
                                      delta_sample_offset))[1]
                    .transform.position -
                ((AttachmentSample *)((char *)path->primary_samples +
                                      delta_sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)path->primary_samples + delta_sample_offset))
                ->delta_length = ((AttachmentSample *)((char *)path->primary_samples +
                                                       delta_sample_offset))
                                     ->delta_dir_to_next.Normalize();

            ((AttachmentSample *)((char *)path->secondary_samples +
                                  delta_sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)path->secondary_samples +
                                      delta_sample_offset))[1]
                    .transform.position -
                ((AttachmentSample *)((char *)path->secondary_samples +
                                      delta_sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)path->secondary_samples +
                                  delta_sample_offset))
                ->delta_length = ((AttachmentSample *)((char *)path->secondary_samples +
                                                       delta_sample_offset))
                                     ->delta_dir_to_next.Normalize();
            ++i;
            delta_sample_offset += sizeof(AttachmentSample);
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
                            path->primary_samples[row].transform.basis_right * lateral;
                        Vector3 generated_position =
                            path->primary_samples[row].transform.position +
                            lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        Vector3 lateral_offset =
                            path->primary_samples[row - 1].transform.basis_right *
                            lateral;
                        Vector3 endpoint =
                            path->primary_samples[row - 1].transform.position +
                            Vector3(0.0f, 0.0f, 1.0f);
                        Vector3 generated_position = endpoint + lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
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
                        if ((column ^ row) & 1)
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
                        if ((column ^ row) & 1)
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

void cRPath::initialize_toad_path_template_pair(bool turn_left, char *texture_a,
                                                char *texture_b, char *vertical_texture)
{
    int lead_count;
    int tail_count;
    float start_x;
    float turn_sign;
    int i;

    kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = 4;

    if (turn_left)
    {
        start_x = -2.0f;
        turn_sign = -1.0f;
        lead_count = 1;
        tail_count = 3;
    }
    else
    {
        start_x = 2.0f;
        turn_sign = 1.0f;
        lead_count = 2;
        tail_count = 1;
    }

    width_or_scale = 1.0f;
    segment_count = lead_count + tail_count + 26;
    segment_count_f = (float)segment_count;
    GetNodes();

    has_entry_mesh_transition = 0;
    i = 0;
    if (lead_count > 0)
    {
        int lead_sample_offset = 0;
        do
        {
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->center_x = start_x;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                    ->center_x;
            float z = (float)i;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.y = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->delta_length = 1.0f;

            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.y = 0.49000001f;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.z = z;
            ++i;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->delta_length = 1.0f;
            lead_sample_offset += sizeof(AttachmentSample);
        } while (i < lead_count);
    }

    if (tail_count > 0)
    {
        int tail_start = lead_count + 26;
        int tail_index = tail_start;
        int tail_sample_offset = tail_index * (int)sizeof(AttachmentSample);
        int tail_control_base = -tail_start;
        do
        {
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->center_x = start_x;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.Identity();
            float z = (float)tail_index;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.y = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->delta_length = 1.0f;

            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.y = 0.49000001f;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->delta_length = 1.0f;
            tail_sample_offset += (int)sizeof(AttachmentSample);
            ++tail_index;
        } while (tail_index + tail_control_base < tail_count);
    }

    int curve_sample_offset = lead_count * sizeof(AttachmentSample);
    for (i = 0; i < 26; ++i)
    {
        float phase = (float)i * 6.2831855f / 26.0f;
        float angle = (1.0f - Cos(phase)) * 0.5f;
        angle = angle * turn_sign * 3.1415927f * 0.5f;

        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->center_x = start_x;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->special_scalar = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.Identity();
        float turn_x = Sin(angle);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.x = turn_x + turn_x + start_x;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.z = (float)(lead_count + i);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.y = 0.0f;

        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_forward =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position -
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))[-1]
                .transform.position;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_forward.Normalize();
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_right.Cross(
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.basis_up,
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.basis_forward);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.RotLocalZ(angle);

        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform;
        Vector3 lane_offset =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_up *
            0.49000001f;
        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.position += lane_offset;
        curve_sample_offset += sizeof(AttachmentSample);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
