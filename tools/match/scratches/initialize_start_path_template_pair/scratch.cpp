// initialize_start_path_template_pair @ 0x426400 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

void __fastcall finalize_path_template(AttachmentPathTemplate* path);

static __forceinline void orient_previous_with_right(
    PathTemplateSample* samples, int current_index, int first_index)
{
    PathTemplateSample* previous = &samples[current_index - 1];
    PathTemplateSample* current = &samples[current_index];

    if (current_index <= first_index) {
        previous->transform.set_matrix_rotation_identity();
        return;
    }

    previous->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        current->transform.position.x - previous->transform.position.x,
        current->transform.position.y - previous->transform.position.y,
        current->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.normalize_vector();
    previous->transform.basis_up.cross_vectors(
        &previous->transform.basis_forward,
        &previous->transform.basis_right);
}

static __forceinline void compute_direct_deltas(AttachmentPathTemplate* path)
{
    int i;
    for (i = 0; i < path->segment_count; ++i) {
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
}

static __forceinline void build_direct_strip_mesh(AttachmentPathTemplate* path, char* texture)
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
            PathTemplateSample* sample = &path->primary_samples[row];
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            vertex->x = sample->transform.position.x
                + lateral * sample->transform.basis_right.x;
            vertex->y = sample->transform.position.y
                + lateral * sample->transform.basis_right.y;
            vertex->z = sample->transform.position.z
                + lateral * sample->transform.basis_right.z;
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;
            ObjectFaceQuad* a = &facequads[2 * (column + row * path->width_cells)];
            ObjectFaceQuad* b = a + 1;

            a->flags = 0;
            a->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
            a->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
            a->texture_ref = g_texture_refs.get_or_create_texture_ref(texture, 0, 0);
            a->uv[0].u = u0;
            a->uv[0].v = v0;
            a->uv[1].u = u1;
            a->uv[1].v = v0;
            a->uv[2].u = u1;
            a->uv[2].v = v1;
            a->uv[3].u = u0;
            a->uv[3].v = v1;

            b->flags = 4;
            b->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
            b->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
            b->vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
            b->vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
            b->texture_ref = g_texture_refs.get_or_create_texture_ref(texture, 0, 0);
            b->uv[0].u = u1;
            b->uv[0].v = v0;
            b->uv[1].u = u0;
            b->uv[1].v = v0;
            b->uv[2].u = u0;
            b->uv[2].v = v1;
            b->uv[3].u = u1;
            b->uv[3].v = v1;
        }
    }
}

void AttachmentPathTemplate::initialize_start_path_template_pair(
    float length,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = 0x24;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 3.1415927f);
    int last_segment_index = curve_segments + 15;
    width_or_scale = 1.0f;
    segment_count = last_segment_index + 1;
    segment_count_f = (float)last_segment_index;
    float radius = (float)curve_segments * 0.31830987f;
    allocate_path_template_samples();
    special_runtime_flag_9c = 0;
    segment_count = segment_count - 1;

    int i;
    for (i = 0; i < 5; ++i) {
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = 0.0f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = radius + radius;
        float z = (float)i;
        primary->transform.position.z = z;
        primary->delta_length = 1.0f;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = radius + radius + 0.49000001f;
        secondary->transform.position.z = z;
        secondary->delta_length = 1.0f;
    }

    for (i = curve_segments + 5; i <= curve_segments + 15; ++i) {
        PathTemplateSample* primary = &primary_samples[i];
        PathTemplateSample* secondary = &secondary_samples[i];

        primary->center_x = 0.0f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        primary->transform.position.y = 0.0f;
        primary->transform.position.z = (float)i;
        primary->delta_length = 1.0f;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.y = 0.49000001f;
        secondary->transform.position.z = primary->transform.position.z;
        secondary->delta_length = 1.0f;
    }

    for (i = 0; i < curve_segments; ++i) {
        int sample_index = i + 5;
        PathTemplateSample* primary = &primary_samples[sample_index];
        PathTemplateSample* secondary = &secondary_samples[sample_index];

        primary->center_x = 0.0f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = primary->center_x;
        float z = (float)sample_index;
        primary->transform.position.z = z;
        float angle = (float)i * 3.1415927f / (float)curve_segments;
        primary->transform.position.y = (cosine(angle) + 1.0f) * radius;

        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.z = z;
        secondary->transform.position.y = primary->transform.position.y + 0.49000001f;
        orient_previous_with_right(primary_samples, sample_index, 5);
        orient_previous_with_right(secondary_samples, sample_index, 5);
    }

    compute_direct_deltas(this);
    build_direct_strip_mesh(this, texture_a);
    finalize_path_template(this);
    (void)side_exit;
    (void)texture_b;
    (void)cap_texture;
}
