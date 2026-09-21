// initialize_dip_path_template_pair @ 0x41e440 (thiscall, ret 0x18)

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
                    if (row != path->segment_count)
                    {
                        double lateral = (float)column - (float)path->width_cells * 0.5f;
                        Vector3 lateral_offset =
                            ((PathAttachmentSample *)((char *)path->primary_samples +
                                                      sample_offset))
                                ->transform.basis_right * lateral;
                        Vector3 generated_position =
                            ((PathAttachmentSample *)((char *)path->primary_samples +
                                                      sample_offset))
                                ->transform.position + lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        double lateral = (float)column - (float)path->width_cells * 0.5f;
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
                face_index = 0;
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;

                for (; face_index < 2; ++face_index)
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

static __forceinline void initialize_primary_curve(
    PathAttachmentSample *&bank, int offset, int index,
    float angle, float radius, float &z)
{
    ((PathAttachmentSample *)((char *)bank + offset))
        ->transform.Identity();
    ((PathAttachmentSample *)((char *)bank + offset))[0].transform.position.x =
        ((PathAttachmentSample *)((char *)bank + offset))[0].center_x;
    ((PathAttachmentSample *)((char *)bank + offset))[0].transform.position.y =
        -((1.0f - Cos(angle)) * radius);
    z = (float)index;
    ((PathAttachmentSample *)((char *)bank + offset))[0].transform.position.z = z;
}

static __forceinline void initialize_secondary_curve_position(
    PathAttachmentSample *&primary, PathAttachmentSample *&secondary,
    int offset, float angle, float radius, const float &z)
{
    ((PathAttachmentSample *)((char *)secondary + offset))
        ->transform.position.x =
        ((PathAttachmentSample *)((char *)primary + offset))
            ->center_x;
    ((PathAttachmentSample *)((char *)secondary + offset))
        ->transform.position.y =
        0.49000001f - (1.0f - Cos(angle)) * radius;
    ((PathAttachmentSample *)((char *)secondary + offset))
        ->transform.position.z = z;
}

void cRPath::initialize_dip_path_template_pair(
    float curve_source, int width_cells_, bool side_exit,
    char *texture_a, char *texture_b, char *cap_texture)
{
    float curve_count_source = curve_source * 5.0f;
    int curve_count;

    kind = PATH_TEMPLATE_KIND_DIP;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    curve_count = (int)curve_count_source;
    width_cells_ = curve_count;
    width_or_scale = 1.0f;
    int endpoint_index = curve_count + 1;
    segment_count = endpoint_index + 1;
    segment_count_f = (float)segment_count;
    float curve_count_f = (float)curve_count;
    curve_source = curve_count_f * 0.047746483f;
    GetNodes();
    has_entry_mesh_transition = 0;

    primary_samples[0].center_x = 0.0f;
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

    int endpoint_sample_offset = endpoint_index * (int)sizeof(PathAttachmentSample);
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->center_x = 0.0f;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->rotation_scalar_98 = 0.0f;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->rotation_scalar_94 = 0.0f;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->special_scalar = 0.0f;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->lateral_scale = 1.0f;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->transform.Identity();
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->transform.position.x =
        ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
            ->center_x;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->transform.position.y = 0.0f;
    float endpoint_z = (float)endpoint_index;
    ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
        ->transform.position.z = endpoint_z;
    ((PathAttachmentSample *)((char *)secondary_samples + endpoint_sample_offset))
        ->transform.Identity();
    ((PathAttachmentSample *)((char *)secondary_samples + endpoint_sample_offset))
        ->transform.position.x =
        ((PathAttachmentSample *)((char *)primary_samples + endpoint_sample_offset))
            ->center_x;
    ((PathAttachmentSample *)((char *)secondary_samples + endpoint_sample_offset))
        ->transform.position.y = 0.49000001f;
    ((PathAttachmentSample *)((char *)secondary_samples + endpoint_sample_offset))
        ->transform.position.z = endpoint_z;

    int i = 0;
    int curve_phase_index = 0;
    if (width_cells_ > 0)
    {
        int sample_offset = (int)sizeof(PathAttachmentSample);
        do
        {
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->center_x = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->special_scalar = 0.0f;
            ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                ->lateral_scale = 1.0f;
            float angle = (float)curve_phase_index * 6.2831855f / curve_count_f;
            float z;
            initialize_primary_curve(primary_samples, sample_offset, i + 1,
                                              angle, curve_source, z);
            ++i;
            ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                ->transform.Identity();
            initialize_secondary_curve_position(primary_samples, secondary_samples,
                                       sample_offset, angle, curve_source, z);
            if (sample_offset > (int)sizeof(PathAttachmentSample))
            {
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                    .transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                    .transform.basis_forward =
                    ((PathAttachmentSample *)((char *)primary_samples + sample_offset))
                        ->transform.position -
                    ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                        .transform.position;
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                    .transform.basis_forward.Normalize();
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                    .transform.basis_up.Cross(
                        ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                            .transform.basis_forward,
                        ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                            .transform.basis_right);
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                    .transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                    .transform.basis_forward =
                    ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))
                        ->transform.position -
                    ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                        .transform.position;
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                    .transform.basis_forward.Normalize();
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                    .transform.basis_up.Cross(
                        ((PathAttachmentSample *)((char *)secondary_samples +
                                                  sample_offset))[-1]
                            .transform.basis_forward,
                        ((PathAttachmentSample *)((char *)secondary_samples +
                                                  sample_offset))[-1]
                            .transform.basis_right);
            }
            else
            {
                ((PathAttachmentSample *)((char *)primary_samples + sample_offset))[-1]
                    .transform.RotIdentity();
                ((PathAttachmentSample *)((char *)secondary_samples + sample_offset))[-1]
                    .transform.RotIdentity();
            }
            sample_offset += (int)sizeof(PathAttachmentSample);
            curve_phase_index = i;
        } while (i < width_cells_);
    }

    int delta_index = 0;
    if (delta_index < segment_count - 1)
    {
        int delta_sample_offset = 0;
        do
        {
            ((PathAttachmentSample *)((char *)primary_samples + delta_sample_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample *)((char *)primary_samples +
                                          delta_sample_offset) +
                 1)
                    ->transform.position -
                ((PathAttachmentSample *)((char *)primary_samples +
                                          delta_sample_offset))
                    ->transform.position;
            ((PathAttachmentSample *)((char *)primary_samples + delta_sample_offset))
                ->delta_length = ((PathAttachmentSample *)((char *)primary_samples +
                                                           delta_sample_offset))
                                     ->delta_dir_to_next.Normalize();

            ((PathAttachmentSample *)((char *)secondary_samples + delta_sample_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample *)((char *)secondary_samples +
                                          delta_sample_offset) +
                 1)
                    ->transform.position -
                ((PathAttachmentSample *)((char *)secondary_samples +
                                          delta_sample_offset))
                    ->transform.position;
            ((PathAttachmentSample *)((char *)secondary_samples + delta_sample_offset))
                ->delta_length = ((PathAttachmentSample *)((char *)secondary_samples +
                                                           delta_sample_offset))
                                     ->delta_dir_to_next.Normalize();

            ++delta_index;
            delta_sample_offset += (int)sizeof(PathAttachmentSample);
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
