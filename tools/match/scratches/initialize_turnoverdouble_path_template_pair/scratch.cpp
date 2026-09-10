// initialize_turnoverdouble_path_template_pair @ 0x427640 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void initialize_pair_sample(Path *path, int index, float center_x,
                                                 float y, float z)
{
    PathTemplateSample *primary = &path->primary_samples[index];
    PathTemplateSample *secondary = &path->secondary_samples[index];

    primary->center_x = center_x;
    primary->rotation_scalar_98 = 0.0f;
    primary->rotation_scalar_94 = 0.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_scale = 1.0f;
    primary->transform.Identity();
    primary->transform.position.x = center_x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;
    primary->delta_length = 1.0f;

    secondary->transform.Identity();
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
    secondary->delta_length = 1.0f;
}

static __forceinline void orient_turnover_sample(PathTemplateSample *sample,
                                                 PathTemplateSample *previous,
                                                 float angle)
{
    sample->transform.basis_up = Vector3(Sin(angle), Cos(angle), 0.0f);
    sample->transform.basis_forward =
        Vector3(sample->transform.position.x - previous->transform.position.x,
                sample->transform.position.y - previous->transform.position.y,
                sample->transform.position.z - previous->transform.position.z);
    sample->transform.basis_forward.Normalize();
    sample->transform.basis_right.Cross(sample->transform.basis_up,
                                        sample->transform.basis_forward);
}

static __forceinline void copy_secondary_from_primary(PathTemplateSample *secondary,
                                                      PathTemplateSample *primary)
{
    secondary->transform = primary->transform;
    secondary->transform.position.x += primary->transform.basis_up.x * 0.49000001f;
    secondary->transform.position.y += primary->transform.basis_up.y * 0.49000001f;
    secondary->transform.position.z += primary->transform.basis_up.z * 0.49000001f;
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

void cRPath::initialize_turnoverdouble_path_template_pair(
    float length, int width_cells_, bool side_exit, char *texture_a, char *texture_b,
    char *cap_texture)
{
    kind = PATH_TEMPLATE_KIND_TURNOVERDOUBLE;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 9.424778f);
    width_or_scale = 1.0f;
    segment_count = curve_segments + 8;
    segment_count_f = (float)(curve_segments + 8);
    float curve_segments_f = (float)curve_segments;
    length = curve_segments_f * 0.079577468f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int i = 0;
    int lead_sample_offset = 0;
    do
    {
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))->center_x =
            (float)width_cells * 0.5f - 4.0f;
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
    } while (lead_sample_offset < 6 * (int)sizeof(AttachmentSample));

    i = curve_segments + 6;
    int tail_control_base = -6 - curve_segments;
    int tail_sample_offset = (curve_segments + 6) * sizeof(AttachmentSample);
    do
    {
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->center_x =
            (float)width_cells * 0.5f - 4.0f;
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
        float z = (float)i;
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
        ++i;
    } while (i + tail_control_base < 2);

    i = 0;
    if (curve_segments > 0)
    {
        int curve_sample_offset = 6 * sizeof(AttachmentSample);
        do
        {
            float t = (float)i;
            float slalom_angle = t * 6.2831855f / curve_segments_f;
            float roll_angle = t * 12.566371f / curve_segments_f;
            if (roll_angle > 6.2831855f)
                roll_angle = 12.566371f - roll_angle;

            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->center_x =
                Sin(slalom_angle + 1.5707964f) * primary_samples[0].center_x;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->rotation_scalar_98 = -roll_angle;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.Identity();

            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->center_x -
                Sin(roll_angle) * Sin(roll_angle * 0.5f) * 2.0f;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.z = (float)(i + 6);
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position.y =
                (length - Cos(roll_angle) * length) * 0.40000001f;

            float up_y = Cos(roll_angle);
            float up_x = Sin(roll_angle);
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_up = Vector3(up_x, up_y, 0.0f);
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_forward =
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.position -
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset) -
                 1)
                    ->transform.position;
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_forward.Normalize();
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_right.Cross(
                    ((AttachmentSample *)((char *)primary_samples +
                                          curve_sample_offset))
                        ->transform.basis_up,
                    ((AttachmentSample *)((char *)primary_samples +
                                          curve_sample_offset))
                        ->transform.basis_forward);

            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
                ->transform =
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform;
            Vector3 secondary_offset =
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.basis_up *
                0.49000001f;
            Vector3 *secondary_position =
                &((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
                     ->transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;

            ++i;
            curve_sample_offset += sizeof(AttachmentSample);
        } while (i < curve_segments);
    }

    compute_terminal_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
