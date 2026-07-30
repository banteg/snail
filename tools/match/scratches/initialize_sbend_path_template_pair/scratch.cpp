// initialize_sbend_path_template_pair @ 0x42df00 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void compute_path_deltas(Path* path)
{
    int i = 0;
    if (path->segment_count - 1 > 0) {
        int sample_offset = 0;
        do {
            ((PathTemplateSample*)((char*)path->primary_samples + sample_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)path->primary_samples + sample_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)path->primary_samples + sample_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)path->primary_samples + sample_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)path->primary_samples + sample_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample*)((char*)path->secondary_samples + sample_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)path->secondary_samples + sample_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)path->secondary_samples + sample_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)path->secondary_samples + sample_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)path->secondary_samples + sample_offset))
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

static __forceinline void build_strip_mesh(
    Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;

    int row = 0;
    int column;
    int face_index;
    if (path->segment_count >= 0) {
        int sample_offset = 0;
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    double lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count) {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        Vector3 lateral_offset =
                            sample->transform.basis_right * lateral;
                        Vector3 generated_position =
                            sample->transform.position + lateral_offset;
                        Vector3* vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    } else {
                        Vector3 lateral_offset =
                            ((PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset))[-1].transform.basis_right * lateral;
                        Vector3 endpoint;
                        endpoint.x =
                            ((PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset))[-1].transform.position.x;
                        endpoint.y =
                            ((PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset))[-1].transform.position.y;
                        endpoint.z =
                            ((PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset))[-1].transform.position.z + 1.0f;
                        Vector3 generated_position(
                            endpoint.x + lateral_offset.x,
                            endpoint.y + lateral_offset.y,
                            endpoint.z + lateral_offset.z);
                        Vector3* vertex =
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

    for (row = 0; row < path->segment_count; ++row) {
        column = 0;
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            do {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;

                for (face_index = 0; face_index < 2; ++face_index) {
                    int face_offset =
                        2 * column + 2 * row * path->width_cells + face_index;
                    if (face_index == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            column
                            + row
                                * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            row * ((unsigned short)path->width_cells + 1)
                            + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1)
                                * ((unsigned short)path->width_cells + 1)
                            + column + 1;
                        facequads[face_offset].vertex_3 =
                            column
                            + (row + 1)
                                * ((unsigned short)path->width_cells + 1);
                        if ((column ^ row) & 1)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        facequads[face_offset].uv[0].u = u0;
                        facequads[face_offset].uv[0].v = v0;
                        facequads[face_offset].uv[1].u = u1;
                        facequads[face_offset].uv[1].v = v0;
                        facequads[face_offset].uv[2].u = u1;
                        facequads[face_offset].uv[2].v = v1;
                        facequads[face_offset].uv[3].u = u0;
                        facequads[face_offset].uv[3].v = v1;
                    } else {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            row * ((unsigned short)path->width_cells + 1)
                            + column + 1;
                        facequads[face_offset].vertex_1 =
                            column
                            + row
                                * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column
                            + (row + 1)
                                * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1)
                                * ((unsigned short)path->width_cells + 1)
                            + column + 1;
                        if ((column ^ row) & 1)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
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

void cRPath::initialize_sbend_path_template_pair(
    int width_cells_, float height, float z_amplitude, bool centered,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int steps = (int)(height * 3.1415927f);
    width_or_scale = 1.0f;
    segment_count = steps + 1;
    segment_count_f = (float)(steps + 1);
    get_path_nodes();

    has_entry_mesh_transition = 0;
    if (centered)
        primary_samples[0].center_x = 0.0f;
    else
        primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[0].transform);
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;

    set_matrix_identity(&secondary_samples[0].transform);
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;

    int sample_index = 0;
    if (steps > 0) {
        Vector3 fixed_up(1.0f, 0.0f, 0.0f);
        int sample_offset = sizeof(PathTemplateSample);
        do {
            float phase =
                (float)sample_index * 6.2831855f / (float)steps;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->center_x = primary_samples[0].center_x;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->special_scalar = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->lateral_scale = 1.0f;
            set_matrix_identity(
                &((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform);
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.position.x =
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->center_x;
            float y = (1.0f - cosine(phase * 0.5f)) * 0.5f;
            y *= height;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.position.y = y;
            float z = (1.0f - cosine(phase * 1.5f)) * 0.5f;
            z = z * z_amplitude * 0.33333334f + 1.0f;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.position.z = z;

            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.basis_up = fixed_up;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.basis_forward =
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform.position -
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))[-1]
                    .transform.position;
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.basis_forward.Normalize();
            ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                ->transform.basis_up.Cross(
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform.basis_forward,
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform.basis_right);

            ((PathTemplateSample*)((char*)secondary_samples + sample_offset))
                ->transform =
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform;
            Vector3 secondary_offset =
                ((PathTemplateSample*)((char*)primary_samples + sample_offset))
                    ->transform.basis_up * 0.49000001f;
            Vector3* secondary_position =
                &((PathTemplateSample*)((char*)secondary_samples + sample_offset))
                    ->transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;
            sample_offset += sizeof(PathTemplateSample);
            ++sample_index;
        } while (sample_index < steps);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
}
