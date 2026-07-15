// initialize_supertramp_path_template_pair @ 0x423f10 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void build_direct_strip_mesh(
    Path* path,
    char* top_texture,
    char* bottom_texture,
    char* cap_texture)
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
        column = 0;
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            int next_column;
            do {
                next_column = column + 1;
                float u0 = (float)column * 0.125f;
                float u1 = (float)next_column * 0.125f;
                int side = 0;
                do {
                    ObjectFaceQuad* face =
                        &facequads[side + 2 * (column + row * path->width_cells)];
                    face->header_word = 0;
                    if (side == 0) {
                        face->vertex_0 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_1 = row *
                                ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        face->vertex_2 = (row + 1) *
                                ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        face->vertex_3 = column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (row == path->segment_count - 1) {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(
                                    cap_texture, 0, 0);
                        } else if ((column ^ row) & 1) {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(
                                    top_texture, 0, 0);
                        } else {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(
                                    top_texture, 0, 0);
                        }
                        face->uv[0].u = u0;
                        face->uv[0].v = v0;
                        face->uv[1].u = u1;
                        face->uv[1].v = v0;
                        face->uv[2].u = u1;
                        face->uv[2].v = v1;
                        face->uv[3].u = u0;
                    } else {
                        face->vertex_0 = row *
                                ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        face->vertex_1 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_2 = column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        face->vertex_3 = (row + 1) *
                                ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        if ((column ^ row) & 1) {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(
                                    bottom_texture, 0, 0);
                        } else {
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(
                                    bottom_texture, 0, 0);
                        }
                        face->uv[0].u = u1;
                        face->uv[0].v = v0;
                        face->uv[1].u = u0;
                        face->uv[1].v = v0;
                        face->uv[2].u = u0;
                        face->uv[2].v = v1;
                        face->uv[3].u = u1;
                    }
                    face->uv[3].v = v1;
                    ++side;
                } while (side < 2);
                column = next_column;
            } while (next_column < path->width_cells);
        }
    }
}

void Path::initialize_supertramp_path_template_pair(
    float length,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* unused_texture,
    char* cap_texture)
{
    kind = 0x1f;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 1.0461504f);
    int last_segment_index = curve_segments + 7;
    width_or_scale = 1.0f;
    segment_count = last_segment_index + 1;
    segment_count_f = (float)last_segment_index;
    float curve_segments_f = (float)curve_segments;
    float radius = curve_segments_f * 0.95588547f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;
    segment_count = segment_count - 1;

    int i;
    for (i = 0; i < 7; ++i) {
        primary_samples[i].center_x = 0.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        float z = (float)i;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;
        primary_samples[i].delta_length = 1.0f;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
        secondary_samples[i].delta_length = 1.0f;
    }

    if (curve_segments >= 0) {
        float secondary_radius = radius - 0.49000001f;
        i = 0;
        do {
            int sample_index = i + 7;
            float angle = (float)i * 1.0461504f / curve_segments_f;

            primary_samples[sample_index].center_x = 0.0f;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                sine(angle) * radius + 7.0f;
            primary_samples[sample_index].transform.position.y =
                radius - cosine(angle) * radius;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                sine(angle) * secondary_radius + 7.0f;
            secondary_samples[sample_index].transform.position.y =
                radius - cosine(angle) * secondary_radius;

            primary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            primary_samples[sample_index].transform.basis_up.x = 0.0f;
            primary_samples[sample_index].transform.basis_up.y =
                radius - primary_samples[sample_index].transform.position.y;
            primary_samples[sample_index].transform.basis_up.z =
                7.0f - primary_samples[sample_index].transform.position.z;
            primary_samples[sample_index].transform.basis_up.normalize_vector();
            primary_samples[sample_index].transform.basis_forward.cross_vectors(
                &primary_samples[sample_index].transform.basis_right,
                &primary_samples[sample_index].transform.basis_up);

            secondary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            secondary_samples[sample_index].transform.basis_up.x = 0.0f;
            secondary_samples[sample_index].transform.basis_up.y =
                radius - secondary_samples[sample_index].transform.position.y;
            secondary_samples[sample_index].transform.basis_up.z =
                7.0f - secondary_samples[sample_index].transform.position.z;
            secondary_samples[sample_index].transform.basis_up.normalize_vector();
            secondary_samples[sample_index].transform.basis_forward.cross_vectors(
                &secondary_samples[sample_index].transform.basis_right,
                &secondary_samples[sample_index].transform.basis_up);
            ++i;
        } while (i <= curve_segments);
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
    build_direct_strip_mesh(this, texture_a, texture_b, cap_texture);
    finalize_path_template();
    (void)side_exit;
    (void)unused_texture;
}
