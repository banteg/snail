// initialize_twister_path_template_pair @ 0x42a540 (thiscall, ret 0x18)

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
        path->primary_samples[current_index - 1].transform.basis_forward = Vector3(
            path->primary_samples[current_index].transform.position.x -
                path->primary_samples[current_index - 1].transform.position.x,
            path->primary_samples[current_index].transform.position.y -
                path->primary_samples[current_index - 1].transform.position.y,
            path->primary_samples[current_index].transform.position.z -
                path->primary_samples[current_index - 1].transform.position.z);
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
        path->secondary_samples[current_index - 1].transform.basis_forward = Vector3(
            path->secondary_samples[current_index].transform.position.x -
                path->secondary_samples[current_index - 1].transform.position.x,
            path->secondary_samples[current_index].transform.position.y -
                path->secondary_samples[current_index - 1].transform.position.y,
            path->secondary_samples[current_index].transform.position.z -
                path->secondary_samples[current_index - 1].transform.position.z);
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
        PathTemplateSample* primary = &path->primary_samples[i];
        PathTemplateSample* primary_next = &path->primary_samples[i + 1];
        primary->delta_dir_to_next = Vector3(
            primary_next->transform.position.x - primary->transform.position.x,
            primary_next->transform.position.y - primary->transform.position.y,
            primary_next->transform.position.z - primary->transform.position.z);
        primary->delta_length = primary->delta_dir_to_next.Normalize();

        PathTemplateSample* secondary = &path->secondary_samples[i];
        PathTemplateSample* secondary_next = &path->secondary_samples[i + 1];
        secondary->delta_dir_to_next = Vector3(
            secondary_next->transform.position.x - secondary->transform.position.x,
            secondary_next->transform.position.y - secondary->transform.position.y,
            secondary_next->transform.position.z - secondary->transform.position.z);
        secondary->delta_length = secondary->delta_dir_to_next.Normalize();
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
    path->strip_mesh->request_object_vertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->request_object_facequads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    ObjectFaceQuad* facequads = path->strip_mesh->facequads;

    int row;
    int column;
    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            PathTemplateSample* sample = &path->primary_samples[row];
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            if (row != path->segment_count) {
                Vector3 lateral_offset(
                    lateral * sample->transform.basis_right.x,
                    lateral * sample->transform.basis_right.y,
                    lateral * sample->transform.basis_right.z);
                Vector3 generated_position(
                    sample->transform.position.x + lateral_offset.x,
                    sample->transform.position.y + lateral_offset.y,
                    sample->transform.position.z + lateral_offset.z);
                *vertex = generated_position;
            } else {
                PathTemplateSample* previous = sample - 1;
                Vector3 lateral_offset(
                    lateral * previous->transform.basis_right.x,
                    lateral * previous->transform.basis_right.y,
                    lateral * previous->transform.basis_right.z);
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
                Vector3 generated_position(
                    endpoint.x + lateral_offset.x,
                    endpoint.y + lateral_offset.y,
                    endpoint.z + lateral_offset.z);
                *vertex = generated_position;
            }
        }
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
                    if (face_index == 0) {
                        ObjectFaceQuad* face = &facequads[
                            face_index + 2 * (row * path->width_cells + column)];
                        face->header_word = 0;
                        face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_3 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (!((column ^ row) & 1)) {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
                        } else {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
                        }
                        face->uv[0].u = u0;
                        face->uv[0].v = v0;
                        face->uv[1].u = u1;
                        face->uv[1].v = v0;
                        face->uv[2].u = u1;
                        face->uv[2].v = v1;
                        face->uv[3].u = u0;
                        face->uv[3].v = v1;
                    } else {
                        ObjectFaceQuad* face = &facequads[
                            face_index + 2 * (row * path->width_cells + column)];
                        face->header_word = 0;
                        face->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_2 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        face->vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        if (!((column ^ row) & 1)) {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
                        } else {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
                        }
                        face->uv[0].u = u1;
                        face->uv[0].v = v0;
                        face->uv[1].u = u0;
                        face->uv[1].v = v0;
                        face->uv[2].u = u0;
                        face->uv[2].v = v1;
                        face->uv[3].u = u1;
                        face->uv[3].v = v1;
                    }
                }
            }
        }
    }
}

void cRPath::initialize_twister_path_template_pair(
    float height, int width_cells_, bool handedness,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_TWISTER;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 34;
    segment_count_f = 34.0f;
    get_path_nodes();

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

    primary_samples[33].center_x = (float)width_cells * 0.5f - 4.0f;
    if (!handedness)
        primary_samples[33].center_x = primary_samples[33].center_x * -1.0f;
    primary_samples[33].rotation_scalar_98 = 0.0f;
    primary_samples[33].rotation_scalar_94 = 0.0f;
    primary_samples[33].special_scalar = 0.0f;
    primary_samples[33].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[33].transform);
    primary_samples[33].transform.position.x = primary_samples[33].center_x;
    primary_samples[33].transform.position.y = 0.0f;
    primary_samples[33].transform.position.z = 33.0f;
    set_matrix_identity(&secondary_samples[33].transform);
    secondary_samples[33].transform.position.x = primary_samples[33].center_x;
    secondary_samples[33].transform.position.y = 0.49000001f;
    secondary_samples[33].transform.position.z = 33.0f;

    int local_index = 0;
    for (int i = 1; i < 33; ++i) {
        float angle = (float)local_index * 0.19634955f;
        float half_angle = angle * 0.5f;
        if (!handedness)
            angle += 3.1415927f;

        float center_scale = cosine(angle) + 1.0f;
        center_scale = center_scale * 0.5f;
        center_scale = center_scale * 5.0f;
        float center = 2.5f - center_scale;

        PathTemplateSample* primary = &primary_samples[i];
        primary->center_x = center;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        float angle_sine = sine(angle);
        ++local_index;
        primary->transform.position.y = sine(half_angle) * angle_sine * height;
        primary->transform.position.z = (float)local_index;
        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y =
            primary_samples[i].transform.position.y + 0.49000001f;
        secondary_samples[i].transform.position.z = (float)local_index;
        orient_previous_sample_pair(this, i);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
}
