// initialize_hill_valley_path_template_pair @ 0x42d570 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Cos(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_secondary_hill(
    Path* path, int index, float phase, float height, float z)
{
    set_matrix_identity(&path->secondary_samples[index].transform);
    path->secondary_samples[index].transform.position.x =
        path->primary_samples[index].center_x;
    float y = (1.0f - Cos(phase)) * 0.5f;
    y *= height;
    path->secondary_samples[index].transform.position.y = y + 0.49000001f;
    path->secondary_samples[index].transform.position.z = z;
}

static __forceinline void orient_previous_hill_pair(Path* path, int current_index)
{
    if (current_index > 1) {
        path->primary_samples[current_index - 1].transform.basis_right =
            Vector3(1.0f, 0.0f, 0.0f);
        path->primary_samples[current_index - 1].transform.basis_forward =
            path->primary_samples[current_index].transform.position -
            path->primary_samples[current_index - 1].transform.position;
        path->primary_samples[current_index - 1]
            .transform.basis_forward.Normalize();
        path->primary_samples[current_index - 1].transform.basis_up.cross_vectors(
            &path->primary_samples[current_index - 1].transform.basis_forward,
            &path->primary_samples[current_index - 1].transform.basis_right);

        path->secondary_samples[current_index - 1].transform.basis_right =
            Vector3(1.0f, 0.0f, 0.0f);
        path->secondary_samples[current_index - 1].transform.basis_forward =
            path->secondary_samples[current_index].transform.position -
            path->secondary_samples[current_index - 1].transform.position;
        path->secondary_samples[current_index - 1]
            .transform.basis_forward.Normalize();
        path->secondary_samples[current_index - 1].transform.basis_up.cross_vectors(
            &path->secondary_samples[current_index - 1]
                 .transform.basis_forward,
            &path->secondary_samples[current_index - 1].transform.basis_right);
    } else {
        path->primary_samples[current_index - 1]
            .transform.RotIdentity();
        path->secondary_samples[current_index - 1]
            .transform.RotIdentity();
    }
}

static __forceinline void compute_path_deltas(Path* path)
{
    for (int i = 0; i < path->segment_count - 1; ++i) {
        path->primary_samples[i].delta_dir_to_next = Vector3(
            path->primary_samples[i + 1].transform.position.x -
                path->primary_samples[i].transform.position.x,
            path->primary_samples[i + 1].transform.position.y -
                path->primary_samples[i].transform.position.y,
            path->primary_samples[i + 1].transform.position.z -
                path->primary_samples[i].transform.position.z);
        path->primary_samples[i].delta_length =
            path->primary_samples[i].delta_dir_to_next.Normalize();

        path->secondary_samples[i].delta_dir_to_next = Vector3(
            path->secondary_samples[i + 1].transform.position.x -
                path->secondary_samples[i].transform.position.x,
            path->secondary_samples[i + 1].transform.position.y -
                path->secondary_samples[i].transform.position.y,
            path->secondary_samples[i + 1].transform.position.z -
                path->secondary_samples[i].transform.position.z);
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

static __forceinline void build_strip_mesh(Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;

    int row;
    int column;
    int face_index;
    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            double lateral = (float)column - (float)path->width_cells * 0.5f;
            if (row != path->segment_count) {
                PathTemplateSample* sample = &path->primary_samples[row];
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position =
                    sample->transform.position + lateral_offset;
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
            } else {
                PathTemplateSample* sample = &path->primary_samples[row];
                Vector3 lateral_offset =
                    sample[-1].transform.basis_right * lateral;
                Vector3 endpoint = sample[-1].transform.position
                    + Vector3(0.0f, 0.0f, 1.0f);
                Vector3 generated_position(
                    endpoint.x + lateral_offset.x,
                    endpoint.y + lateral_offset.y,
                    endpoint.z + lateral_offset.z);
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
            }
        }
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
                        face_index
                        + 2 * (row * path->width_cells + column);
                    if (face_index == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
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
                        facequads[face_offset].vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
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

void cRPath::initialize_hill_valley_path_template_pair(
    int width_cells_, float height, float length, bool centered,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int steps = (int)length;
    width_or_scale = 1.0f;
    int last = steps + 1;
    segment_count = last + 1;
    segment_count_f = (float)(last + 1);
    GetNodes();

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

    if (centered)
        primary_samples[last].center_x = 0.0f;
    else
        primary_samples[last].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[last].rotation_scalar_98 = 0.0f;
    primary_samples[last].rotation_scalar_94 = 0.0f;
    primary_samples[last].special_scalar = 0.0f;
    primary_samples[last].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[last].transform);
    primary_samples[last].transform.position.x = primary_samples[last].center_x;
    float last_z = (float)last;
    primary_samples[last].transform.position.y = 0.0f;
    primary_samples[last].transform.position.z = last_z;
    set_matrix_identity(&secondary_samples[last].transform);
    secondary_samples[last].transform.position.x = primary_samples[last].center_x;
    secondary_samples[last].transform.position.y = 0.49000001f;
    secondary_samples[last].transform.position.z = last_z;

    for (int i = 0; i < steps; ++i) {
        int sample_index = i + 1;
        primary_samples[sample_index].center_x = primary_samples[0].center_x;
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        float phase = (float)i * 6.2831855f / (float)steps;
        set_matrix_identity(&primary_samples[sample_index].transform);
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        float y = (1.0f - Cos(phase)) * 0.5f;
        y *= height;
        primary_samples[sample_index].transform.position.y = y;
        float z = (float)sample_index;
        primary_samples[sample_index].transform.position.z = z;
        initialize_secondary_hill(this, sample_index, phase, height, z);
        orient_previous_hill_pair(this, sample_index);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
