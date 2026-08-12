// initialize_twister2_path_template_pair @ 0x42af30 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void orient_previous_sample_pair(Path* path, int current_index)
{
    if (current_index > 1) {
        path->primary_samples[current_index - 1].transform.basis_up =
            Vector3(0.0f, 1.0f, 0.0f);
        path->primary_samples[current_index - 1].transform.basis_forward =
            path->primary_samples[current_index].transform.position -
            path->primary_samples[current_index - 1].transform.position;
        path->primary_samples[current_index - 1]
            .transform.basis_forward.Normalize();
        path->primary_samples[current_index - 1].transform.basis_right.cross_vectors(
            &path->primary_samples[current_index - 1].transform.basis_up,
            &path->primary_samples[current_index - 1].transform.basis_forward);
        path->primary_samples[current_index - 1].transform.basis_up.cross_vectors(
            &path->primary_samples[current_index - 1].transform.basis_forward,
            &path->primary_samples[current_index - 1].transform.basis_right);
        path->primary_samples[current_index - 1].transform.Orthoganalize();

        path->secondary_samples[current_index - 1].transform.basis_up =
            Vector3(0.0f, 1.0f, 0.0f);
        path->secondary_samples[current_index - 1].transform.basis_forward =
            path->secondary_samples[current_index].transform.position -
            path->secondary_samples[current_index - 1].transform.position;
        path->secondary_samples[current_index - 1]
            .transform.basis_forward.Normalize();
        path->secondary_samples[current_index - 1]
            .transform.basis_right.cross_vectors(
                &path->secondary_samples[current_index - 1].transform.basis_up,
                &path->secondary_samples[current_index - 1]
                     .transform.basis_forward);
        path->secondary_samples[current_index - 1].transform.basis_up.cross_vectors(
            &path->secondary_samples[current_index - 1]
                 .transform.basis_forward,
            &path->secondary_samples[current_index - 1].transform.basis_right);
        path->secondary_samples[current_index - 1]
            .transform.Orthoganalize();
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

static __forceinline void build_strip_mesh(Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;

    int row = 0;
    int column;
    if (path->segment_count >= 0) {
        int sample_offset = 0;
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    float lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count) {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        Vector3 lateral_offset(
                            lateral * sample->transform.basis_right.x,
                            lateral * sample->transform.basis_right.y,
                            lateral * sample->transform.basis_right.z);
                        Vector3 generated_position =
                            sample->transform.position + lateral_offset;
                        int vertex_index =
                            column + row * (path->width_cells + 1);
                        vertices[vertex_index] = generated_position;
                    } else {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        Vector3 lateral_offset(
                            lateral * sample[-1].transform.basis_right.x,
                            lateral * sample[-1].transform.basis_right.y,
                            lateral * sample[-1].transform.basis_right.z);
                        Vector3 endpoint(
                            sample[-1].transform.position.x,
                            sample[-1].transform.position.y,
                            sample[-1].transform.position.z + 1.0f);
                        Vector3 generated_position(
                            endpoint.x + lateral_offset.x,
                            endpoint.y + lateral_offset.y,
                            endpoint.z + lateral_offset.z);
                        int vertex_index =
                            column + row * (path->width_cells + 1);
                        vertices[vertex_index] = generated_position;
                    }
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row) {
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            for (column = 0; column < path->width_cells; ++column) {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;
                int face_index;
                for (face_index = 0; face_index < 2; ++face_index) {
                    int face_offset = face_index + 2 * (row * path->width_cells + column);
                    if (face_index == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_3 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (!((column ^ row) & 1)) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        }
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
                        facequads[face_offset].vertex_2 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        if (!((column ^ row) & 1)) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        }
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
}

void cRPath::initialize_twister2_path_template_pair(
    float height, int width_cells_, bool handedness,
    char* texture_a, char* texture_b, char* vertical_texture)
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
    set_matrix_identity(&primary_samples[0].transform);
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;
    set_matrix_identity(&secondary_samples[0].transform);
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
    set_matrix_identity(&primary_samples[51].transform);
    primary_samples[51].transform.position.x = primary_samples[51].center_x;
    primary_samples[51].transform.position.y = 0.0f;
    primary_samples[51].transform.position.z = 51.0f;
    set_matrix_identity(&secondary_samples[51].transform);
    secondary_samples[51].transform.position.x = primary_samples[51].center_x;
    secondary_samples[51].transform.position.y = 0.49000001f;
    secondary_samples[51].transform.position.z = 51.0f;

    int local_index = 0;
    for (int i = 1; i < 51; ++i) {
        float angle = (float)local_index * 0.25132743f;
        float half_angle = angle * 0.5f;
        if (!handedness)
            angle += 3.1415927f;

        float center_scale = cosine(angle) + 1.0f;
        center_scale = center_scale * 0.5f;
        center_scale = center_scale * 5.0f;
        float center = 2.5f - center_scale;

        primary_samples[i].center_x = center;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        float angle_sine = sine(angle);
        int sample_z = local_index + 1;
        primary_samples[i].transform.position.y =
            sine(half_angle) * angle_sine * height;
        primary_samples[i].transform.position.z = (float)sample_z;
        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y =
            primary_samples[i].transform.position.y + 0.49000001f;
        secondary_samples[i].transform.position.z = (float)sample_z;
        orient_previous_sample_pair(this, i);
        local_index = sample_z;
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
