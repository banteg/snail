// initialize_p_path_template_pair @ 0x425a40 (thiscall, ret 0x24)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


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
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            int face_index;
            for (face_index = 0; face_index < 2; ++face_index) {
                if (face_index == 0) {
                    ObjectFaceQuad* face = &facequads[
                        face_index + 2 * (row * path->width_cells + column)];
                    face->header_word = 0;
                    face->vertex_0 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_1 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_2 =
                        (row + 1) * ((unsigned short)path->width_cells + 1)
                        + column + 1;
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
                    face->vertex_0 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_1 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_2 =
                        column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->vertex_3 =
                        (row + 1) * ((unsigned short)path->width_cells + 1)
                        + column + 1;
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

void cRPath::initialize_p_path_template_pair(
    int variant,
    float scale_arg,
    int width_cells_,
    float start_x,
    float end_x,
    int curve_segments,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = (PathTemplateKind)(variant + 0x21);
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    int last_index = curve_segments + 1;
    int sample_count = last_index + 1;
    segment_count = sample_count;
    segment_count_f = (float)sample_count;

    float half_distance = (end_x - start_x) * 0.5f;
    if (half_distance < 0.0f)
        scale_arg = -half_distance;
    else
        scale_arg = half_distance;

    get_path_nodes();
    has_entry_mesh_transition = 0;

    primary_samples[0].center_x = start_x;
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

    primary_samples[last_index].center_x = end_x;
    primary_samples[last_index].rotation_scalar_98 = 0.0f;
    primary_samples[last_index].rotation_scalar_94 = 0.0f;
    primary_samples[last_index].special_scalar = 0.0f;
    primary_samples[last_index].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[last_index].transform);
    float terminal_z = (float)last_index;
    primary_samples[last_index].transform.position.x = primary_samples[last_index].center_x;
    primary_samples[last_index].transform.position.y = 0.0f;
    primary_samples[last_index].transform.position.z = terminal_z;
    set_matrix_identity(&secondary_samples[last_index].transform);
    secondary_samples[last_index].transform.position.x = primary_samples[last_index].center_x;
    secondary_samples[last_index].transform.position.y = 0.49000001f;
    secondary_samples[last_index].transform.position.z = terminal_z;

    int curve_index = 0;
    if (curve_segments > 0) {
        float curve_segments_f = (float)curve_segments;
        int i = 1;
        do {
            float angle = (float)curve_index * 3.1415927f / curve_segments_f;
            switch (kind) {
            case 0x21:
                primary_samples[i].center_x =
                    sine(angle + 1.5707964f) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x22:
                primary_samples[i].center_x =
                    2.0f - cosine(angle) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x23:
                primary_samples[i].center_x =
                    (sine(angle + 1.5707964f) + 1.0f) * scale_arg + 0.5f;
                break;
            }

            primary_samples[i].rotation_scalar_98 = 0.0f;
            primary_samples[i].rotation_scalar_94 = 0.0f;
            primary_samples[i].special_scalar = 0.0f;
            primary_samples[i].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[i].transform);
            ++curve_index;
            float z = (float)curve_index;
            primary_samples[i].transform.position.x = primary_samples[i].center_x;
            primary_samples[i].transform.position.y = 0.0f;
            primary_samples[i].transform.position.z = z;

            set_matrix_identity(&secondary_samples[i].transform);
            secondary_samples[i].transform.position.x = primary_samples[i].center_x;
            secondary_samples[i].transform.position.y =
                primary_samples[i].transform.position.y + 0.49000001f;
            secondary_samples[i].transform.position.z = z;
            PathTemplateSample* primary_previous = &primary_samples[i - 1];
            PathTemplateSample* primary_current = &primary_samples[i];
            PathTemplateSample* secondary_previous = &secondary_samples[i - 1];
            PathTemplateSample* secondary_current = &secondary_samples[i];
            if (i <= 1) {
                primary_previous->transform.set_matrix_rotation_identity();
                secondary_previous->transform.set_matrix_rotation_identity();
            } else {
                primary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                primary_previous->transform.basis_forward = Vector3(
                    primary_current->transform.position.x - primary_previous->transform.position.x,
                    primary_current->transform.position.y - primary_previous->transform.position.y,
                    primary_current->transform.position.z - primary_previous->transform.position.z);
                primary_previous->transform.basis_forward.normalize_vector();
                primary_previous->transform.basis_right.cross_vectors(
                    &primary_previous->transform.basis_up,
                    &primary_previous->transform.basis_forward);

                secondary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                secondary_previous->transform.basis_forward = Vector3(
                    secondary_current->transform.position.x - secondary_previous->transform.position.x,
                    secondary_current->transform.position.y - secondary_previous->transform.position.y,
                    secondary_current->transform.position.z - secondary_previous->transform.position.z);
                secondary_previous->transform.basis_forward.normalize_vector();
                secondary_previous->transform.basis_right.cross_vectors(
                    &secondary_previous->transform.basis_up,
                    &secondary_previous->transform.basis_forward);
            }
            ++i;
        } while (curve_index < curve_segments);
    }

    int delta_index = 0;
    if (segment_count - 1 > 0) {
        do {
            primary_samples[delta_index].delta_dir_to_next = Vector3(
                primary_samples[delta_index + 1].transform.position.x -
                    primary_samples[delta_index].transform.position.x,
                primary_samples[delta_index + 1].transform.position.y -
                    primary_samples[delta_index].transform.position.y,
                primary_samples[delta_index + 1].transform.position.z -
                    primary_samples[delta_index].transform.position.z);
            primary_samples[delta_index].delta_length =
                primary_samples[delta_index].delta_dir_to_next.normalize_vector();

            secondary_samples[delta_index].delta_dir_to_next = Vector3(
                secondary_samples[delta_index + 1].transform.position.x -
                    secondary_samples[delta_index].transform.position.x,
                secondary_samples[delta_index + 1].transform.position.y -
                    secondary_samples[delta_index].transform.position.y,
                secondary_samples[delta_index + 1].transform.position.z -
                    secondary_samples[delta_index].transform.position.z);
            secondary_samples[delta_index].delta_length =
                secondary_samples[delta_index].delta_dir_to_next.normalize_vector();
            ++delta_index;
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
    (void)cap_texture;
}
