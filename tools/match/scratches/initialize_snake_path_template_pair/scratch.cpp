// initialize_snake_path_template_pair @ 0x423580 (thiscall, ret 0x18)

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
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            if (row == path->segment_count) {
                PathTemplateSample* previous = &path->primary_samples[row - 1];
                vertex->x = previous->transform.position.x
                    + lateral * previous->transform.basis_right.x;
                vertex->y = previous->transform.position.y
                    + lateral * previous->transform.basis_right.y;
                vertex->z = previous->transform.position.z + 1.0f
                    + lateral * previous->transform.basis_right.z;
            } else {
                PathTemplateSample* sample = &path->primary_samples[row];
                vertex->x = sample->transform.position.x
                    + lateral * sample->transform.basis_right.x;
                vertex->y = sample->transform.position.y
                    + lateral * sample->transform.basis_right.y;
                vertex->z = sample->transform.position.z
                    + lateral * sample->transform.basis_right.z;
            }
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            column = 0;
            int next_column;
            do {
                next_column = column + 1;
                float u0 = (float)column * 0.125f;
                float u1 = (float)next_column * 0.125f;
                int face_index;
                for (face_index = 0; face_index < 2; ++face_index) {
                    ObjectFaceQuad* face =
                        &facequads[2 * column + 2 * row * path->width_cells + face_index];
                    face->header_word = 0;
                    if (face_index == 0) {
                        face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_3 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        face->texture_ref =
                            g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
                        face->uv[0].u = u0;
                        face->uv[0].v = v0;
                        face->uv[1].u = u1;
                        face->uv[1].v = v0;
                        face->uv[2].u = u1;
                        face->uv[2].v = v1;
                        face->uv[3].u = u0;
                    } else {
                        face->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_2 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        face->vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->texture_ref =
                            g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
                        face->uv[0].u = u1;
                        face->uv[0].v = v0;
                        face->uv[1].u = u0;
                        face->uv[1].v = v0;
                        face->uv[2].u = u0;
                        face->uv[2].v = v1;
                        face->uv[3].u = u1;
                    }
                    face->uv[3].v = v1;
                }
                column = next_column;
            } while (next_column < path->width_cells);
        }
    }
}

void Path::initialize_snake_path_template_pair(
    float scale_arg,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = 0x1d;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 27;
    segment_count_f = 27.0f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    int i;

    for (i = 0; i < 6; ++i) {
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = 0.0f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        float z = (float)i;
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = 0.0f;
        primary->transform.position.z = z;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = 0.49000001f;
        secondary->transform.position.z = z;
    }

    int departure_index = 24;
    do {
        PathTemplateSample* primary = &primary_samples[departure_index];
        PathTemplateSample* secondary = &secondary_samples[departure_index];

        primary->center_x = 4.0f - (float)width_cells * 0.5f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        float z = (float)departure_index;
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = 0.0f;
        primary->transform.position.z = z;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = 0.49000001f;
        secondary->transform.position.z = z;
        ++departure_index;
    } while (departure_index - 24 < 3);

    int curve_index = 0;
    for (i = 6; i < 24; ++i) {
        float angle = (float)curve_index * 0.34906587f;
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];
        primary->center_x = (0.5f - cosine(angle * 0.5f) * 0.5f)
            * primary_samples[24].center_x;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = -(1.0f - cosine(angle));
        float z = (float)(curve_index + 6);
        primary->transform.position.z = z;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = 0.49000001f - (1.0f - cosine(angle));
        secondary->transform.position.z = z;
        PathTemplateSample* primary_previous = &primary_samples[i - 1];
        PathTemplateSample* primary_current = &primary_samples[i];
        PathTemplateSample* secondary_previous = &secondary_samples[i - 1];
        PathTemplateSample* secondary_current = &secondary_samples[i];

        if (i <= 6) {
            primary_previous->transform.set_matrix_rotation_identity();
            secondary_previous->transform.set_matrix_rotation_identity();
        } else {
            primary_previous->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
            primary_previous->transform.basis_forward = Vector3(
                primary_current->transform.position.x - primary_previous->transform.position.x,
                primary_current->transform.position.y - primary_previous->transform.position.y,
                primary_current->transform.position.z - primary_previous->transform.position.z);
            primary_previous->transform.basis_forward.normalize_vector();
            primary_previous->transform.basis_up.cross_vectors(
                &primary_previous->transform.basis_forward,
                &primary_previous->transform.basis_right);

            secondary_previous->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
            secondary_previous->transform.basis_forward = Vector3(
                secondary_current->transform.position.x - secondary_previous->transform.position.x,
                secondary_current->transform.position.y - secondary_previous->transform.position.y,
                secondary_current->transform.position.z - secondary_previous->transform.position.z);
            secondary_previous->transform.basis_forward.normalize_vector();
            secondary_previous->transform.basis_up.cross_vectors(
                &secondary_previous->transform.basis_forward,
                &secondary_previous->transform.basis_right);
        }
        ++curve_index;
    }

    int delta_index = 0;
    if (segment_count > 1) {
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
    finalize_path_template();
    (void)scale_arg;
    (void)side_exit;
    (void)cap_texture;
}
