// initialize_sweep_path_template_pair @ 0x422c00 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

void __fastcall finalize_path_template(AttachmentPathTemplate* path);

static __forceinline void orient_previous_with_up(
    PathTemplateSample* samples, int current_index, int first_index, float roll_angle)
{
    PathTemplateSample* previous = &samples[current_index - 1];
    PathTemplateSample* current = &samples[current_index];

    if (current_index <= first_index) {
        previous->transform.set_matrix_rotation_identity();
        return;
    }

    previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        current->transform.position.x - previous->transform.position.x,
        current->transform.position.y - previous->transform.position.y,
        current->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.normalize_vector();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
    if (roll_angle != 0.0f)
        previous->transform.rotate_matrix_world_z(roll_angle);
}

static __forceinline void compute_terminal_deltas(AttachmentPathTemplate* path)
{
    int i;
    for (i = 0; i < path->segment_count - 1; ++i) {
        PathTemplateSample* primary = &path->primary_samples[i];
        PathTemplateSample* primary_next = &path->primary_samples[i + 1];
        primary->delta_dir_to_next = Vector3(
            primary_next->transform.position.x - primary->transform.position.x,
            primary_next->transform.position.y - primary->transform.position.y,
            primary_next->transform.position.z - primary->transform.position.z);
        primary->delta_length = primary->delta_dir_to_next.normalize_vector();

        PathTemplateSample* secondary = &path->secondary_samples[i];
        PathTemplateSample* secondary_next = &path->secondary_samples[i + 1];
        secondary->delta_dir_to_next = Vector3(
            secondary_next->transform.position.x - secondary->transform.position.x,
            secondary_next->transform.position.y - secondary->transform.position.y,
            secondary_next->transform.position.z - secondary->transform.position.z);
        secondary->delta_length = secondary->delta_dir_to_next.normalize_vector();
    }

    PathTemplateSample* last_primary = &path->primary_samples[path->segment_count - 1];
    last_primary->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    last_primary->delta_length = 1.0f;

    PathTemplateSample* last_secondary = &path->secondary_samples[path->segment_count - 1];
    last_secondary->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    last_secondary->delta_length = 1.0f;
}

static __forceinline void build_strip_mesh(AttachmentPathTemplate* path, char* texture_a, char* texture_b)
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
            if (row == path->segment_count)
                sample = &path->primary_samples[row - 1];

            vertex->x = sample->transform.position.x
                + lateral * sample->transform.basis_right.x;
            vertex->y = sample->transform.position.y
                + lateral * sample->transform.basis_right.y;
            vertex->z = sample->transform.position.z
                + lateral * sample->transform.basis_right.z
                + (row == path->segment_count ? 1.0f : 0.0f);
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
            }
        }
    }
}

void AttachmentPathTemplate::initialize_sweep_path_template_pair(
    float scale_arg,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = 0x1c;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 30;
    segment_count_f = 30.0f;
    allocate_path_template_samples();
    special_runtime_flag_9c = 0;

    int i;
    float left = (float)width_cells * 0.5f - 4.0f;

    for (i = 0; i < 3; ++i) {
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = left;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        float z = (float)i;
        primary->transform.position.y = 0.0f;
        primary->transform.position.z = z;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = 0.49000001f;
        secondary->transform.position.z = z;
    }

    float right = 4.0f - (float)width_cells * 0.5f;

    for (i = 27; i < 30; ++i) {
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = right;
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

    for (i = 3; i < 27; ++i) {
        float angle = (float)(i - 3) * 0.1308997f;
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = cosine(angle) * primary_samples[0].center_x;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = sine(angle) * -0.30000001f;
        float z = (float)i;
        primary->transform.position.z = z;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = primary->transform.position.y + 0.49000001f;
        secondary->transform.position.z = z;
        orient_previous_with_up(primary_samples, i, 3, 0.0f);
        orient_previous_with_up(secondary_samples, i, 3, 0.0f);
    }

    compute_terminal_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template(this);
    (void)scale_arg;
    (void)side_exit;
    (void)cap_texture;
}
