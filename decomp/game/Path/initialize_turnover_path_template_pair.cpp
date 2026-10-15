// initialize_turnover_path_template_pair @ 0x426cb0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void build_turnover_curve(
    Path *path, int curve_segments, float curve_segments_f, float length, int endpoint_index)
{
    int curve_index = 0;
    if (curve_segments > 0)
    {
        Vector3 up(0.0f, 0.0f, 0.0f);
        int curve_sample_offset = 6 * sizeof(AttachmentSample);
        do
        {
            float t = (float)curve_index;
            float angle = t * 6.2831855f / curve_segments_f;

            AttachmentSample* const& curve_samples = path->primary_samples;
            ((AttachmentSample *)((char *)curve_samples + curve_sample_offset))
                ->center_x = (curve_samples[endpoint_index].center_x -
                              curve_samples[0].center_x) *
                                 t / curve_segments_f +
                             curve_samples[0].center_x;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->rotation_scalar_98 = -angle;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.Identity();

            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                    ->center_x -
                Sin(angle) * Sin(angle * 0.5f) * 2.0f;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.position.z = (float)(curve_index + 6);
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.position.y = (length - Cos(angle) * length) * 0.40000001f;

            float up_y = Cos(angle);
            float up_x = Sin(angle);
            up.x = up_x;
            up.y = up_y;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.basis_up = up;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.basis_forward =
                ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                    ->transform.position -
                ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset) -
                 1)
                    ->transform.position;
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.basis_forward.Normalize();
            ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                ->transform.basis_right.Cross(
                    ((AttachmentSample *)((char *)path->primary_samples +
                                          curve_sample_offset))
                        ->transform.basis_up,
                    ((AttachmentSample *)((char *)path->primary_samples +
                                          curve_sample_offset))
                        ->transform.basis_forward);

            ((AttachmentSample *)((char *)path->secondary_samples + curve_sample_offset))
                ->transform =
                ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                    ->transform;
            Vector3 secondary_offset =
                ((AttachmentSample *)((char *)path->primary_samples + curve_sample_offset))
                    ->transform.basis_up *
                0.49000001f;
            Vector3 *secondary_position =
                &((AttachmentSample *)((char *)path->secondary_samples + curve_sample_offset))
                     ->transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;

            ++curve_index;
            curve_sample_offset += sizeof(AttachmentSample);
        } while (curve_index < curve_segments);
    }
}

void cRPath::initialize_turnover_path_template_pair(float length, int width_cells_,
                                                    bool side_exit, char *texture_a,
                                                    char *texture_b, char *cap_texture)
{
    kind = PATH_TEMPLATE_KIND_TURNOVER;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 6.2831855f);
    width_or_scale = 1.0f;
    segment_count = curve_segments + 8;
    segment_count_f = (float)(curve_segments + 8);
    float curve_segments_f = (float)curve_segments;
    length = curve_segments_f * 0.15915494f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int lead_z_index = 0;
    int lead_sample_offset = 0;
    do
    {
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->center_x = (float)width_cells * 0.5f - 4.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->special_scalar = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->lateral_scale = 1.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.Identity();
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
                ->center_x;
        float z = (float)lead_z_index;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.z = z;
        ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
            ->delta_length = 1.0f;

        ((PathTemplateSample *)((char *)secondary_samples + lead_sample_offset))
            ->transform.Identity();
        ((PathTemplateSample *)((char *)secondary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample *)((char *)primary_samples + lead_sample_offset))
                ->center_x;
        ((PathTemplateSample *)((char *)secondary_samples + lead_sample_offset))
            ->transform.position.y = 0.49000001f;
        ++lead_z_index;
        ((PathTemplateSample *)((char *)secondary_samples + lead_sample_offset))
            ->transform.position.z = z;
        ((PathTemplateSample *)((char *)secondary_samples + lead_sample_offset))
            ->delta_length = 1.0f;
        lead_sample_offset += (int)sizeof(PathTemplateSample);
    } while (lead_sample_offset < 6 * (int)sizeof(PathTemplateSample));

    int endpoint_index = curve_segments + 6;
    int tail_index = endpoint_index;
    int tail_sample_offset = tail_index * sizeof(AttachmentSample);
    int tail_control_base = -6 - curve_segments;
    do
    {
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->center_x =
            4.0f - (float)width_cells * 0.5f;
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
        tail_sample_offset += sizeof(AttachmentSample);
        ++tail_index;
    } while (tail_index + tail_control_base < 2);

    build_turnover_curve(this, curve_segments, curve_segments_f, length, endpoint_index);

    {

    int i = 0;
    if (segment_count - 1 > 0)
    {
        do
        {
            primary_samples[i].delta_dir_to_next =
                primary_samples[i + 1].transform.position -
                primary_samples[i].transform.position;
            primary_samples[i].delta_length =
                primary_samples[i].delta_dir_to_next.Normalize();

            secondary_samples[i].delta_dir_to_next =
                secondary_samples[i + 1].transform.position -
                secondary_samples[i].transform.position;
            secondary_samples[i].delta_length =
                secondary_samples[i].delta_dir_to_next.Normalize();

            ++i;
        } while (i < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;
    }
    {

    strip_mesh->RequestVertices((width_cells + 1) *
                                      (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    Vector3 *vertices = strip_mesh->vertices;
    cRFaceQuad *facequads = strip_mesh->facequads;
    int row = 0;
    int column;
    int face_index;
    if (segment_count >= 0)
    {
        int sample_offset = 0;
        do
        {
            column = 0;
            if (width_cells >= 0)
            {
                do
                {
                    if (row != segment_count)
                    {
                        float lateral = (float)column - (float)width_cells * 0.5f;
                        Vector3 lateral_offset =
                            ((PathTemplateSample *)((char *)primary_samples +
                                                    sample_offset))
                                ->transform.basis_right *
                            lateral;
                        Vector3 generated_position =
                            ((PathTemplateSample *)((char *)primary_samples +
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
                            (((PathTemplateSample *)((char *)primary_samples +
                                                     sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((PathTemplateSample *)((char *)primary_samples +
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
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= segment_count);
    }

    for (row = 0; row < segment_count; ++row)
    {
        column = 0;
        if (width_cells > 0)
        {
            int row_mod = row % 8;
            float row_mod_f = (float)row_mod;
            float v0 = row_mod_f * 0.125f;
            int next_row_mod = row % 8 + 1;
            float next_row_mod_f = (float)next_row_mod;
            float v1 = next_row_mod_f * 0.125f;
            do
            {
                float col_f = (float)column;
                float u0 = col_f * 0.125f;
                int next_column = column + 1;
                float next_col_f = (float)next_column;
                float u1 = next_col_f * 0.125f;

                for (face_index = 0; face_index < 2; ++face_index)
                {
                    int col_offset = 2 * column;
                    int row_offset = 2 * row * width_cells;
                    int face_offset =
                        col_offset + row_offset + face_index;

                    if (face_index == 0)
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            column + row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            row * ((unsigned short)width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1) * ((unsigned short)width_cells + 1) +
                            column + 1;
                        facequads[face_offset].vertex_3 =
                            column +
                            (row + 1) * ((unsigned short)width_cells + 1);
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
                            row * ((unsigned short)width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_1 =
                            column + row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column +
                            (row + 1) * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1) * ((unsigned short)width_cells + 1) +
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
            } while (column < width_cells);
        }
    }
    }
    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
