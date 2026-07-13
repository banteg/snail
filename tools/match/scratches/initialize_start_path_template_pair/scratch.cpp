// initialize_start_path_template_pair @ 0x426400 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void build_direct_strip_mesh(Path* path, char* texture)
{
    path->strip_mesh->request_object_vertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->request_object_facequads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    ObjectFaceQuad* facequads = path->strip_mesh->facequads;
    int row;
    int column;

    row = 0;
    int sample_offset = 0;
    if (path->segment_count >= 0) {
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    PathTemplateSample* sample = (PathTemplateSample*)(
                        (char*)path->primary_samples + sample_offset);
                    float lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    Vector3* vertex =
                        &vertices[column + row * (path->width_cells + 1)];
                    Vector3 lateral_offset(
                        lateral * sample->transform.basis_right.x,
                        lateral * sample->transform.basis_right.y,
                        lateral * sample->transform.basis_right.z);
                    Vector3 generated_position(
                        sample->transform.position.x + lateral_offset.x,
                        sample->transform.position.y + lateral_offset.y,
                        sample->transform.position.z + lateral_offset.z);
                    *vertex = generated_position;
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            for (int face_index = 0; face_index < 2; ++face_index) {
                ObjectFaceQuad* face =
                    &facequads[2 * column + 2 * row * path->width_cells + face_index];
                if (face_index == 0) {
                    face->flags = 0;
                    face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->texture_ref = g_texture_refs.get_or_create_texture_ref(texture, 0, 0);
                    face->uv[0].u = u0;
                    face->uv[0].v = v0;
                    face->uv[1].u = u1;
                    face->uv[1].v = v0;
                    face->uv[2].u = u1;
                    face->uv[2].v = v1;
                    face->uv[3].u = u0;
                } else {
                    face->flags = 4;
                    face->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->texture_ref = g_texture_refs.get_or_create_texture_ref(texture, 0, 0);
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

void Path::initialize_start_path_template_pair(
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
    has_entry_mesh_transition = 0;
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

    int tail_count = 11;
    i = curve_segments + 5;
    do {
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
        ++i;
        --tail_count;
    } while (tail_count != 0);

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
        PathTemplateSample* primary_previous = &primary_samples[sample_index - 1];
        PathTemplateSample* primary_current = &primary_samples[sample_index];
        PathTemplateSample* secondary_previous = &secondary_samples[sample_index - 1];
        PathTemplateSample* secondary_current = &secondary_samples[sample_index];

        if (sample_index <= 5) {
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
    }

    int delta_index = 0;
    if (segment_count > 0) {
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
        } while (delta_index < segment_count);
    }
    build_direct_strip_mesh(this, texture_a);
    finalize_path_template();
    (void)side_exit;
    (void)texture_b;
    (void)cap_texture;
}
