// initialize_kind42_path_template_pair @ 0x429b20 (thiscall, ret 0x18)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

float sine(float angle);

void __fastcall finalize_path_template(AttachmentPathTemplate* path);

void AttachmentPathTemplate::initialize_kind42_path_template_pair(
    int unused_scale_bits,
    int width_cells_,
    int unused_kind_arg,
    char* texture_a,
    char* texture_b,
    char* unused_path_version)
{
    unused_scale_bits = unused_scale_bits;
    unused_kind_arg = unused_kind_arg;
    unused_path_version = unused_path_version;

    kind = 0x2a;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 66;
    segment_count_f = 66.0f;
    allocate_path_template_samples();
    special_runtime_flag_9c = 0;

    int i = 0;
    do {
        float index = (float)i;
        float angle_base = index * 0.0625f;
        float angle = angle_base * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - sine(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        primary_samples[i].center_x = (float)width_cells * 0.5f - 4.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = (depth * depth + 16.0f) / (depth + depth);
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = index;
        primary_samples[i].delta_length = 1.0f;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = index;
        secondary_samples[i].delta_length = 1.0f;
        ++i;
    } while (i < 16);

    int exit_index = 0;
    for (i = 50; i < 66; ++i) {
        float angle_base = 1.0f - (float)exit_index * 0.0625f;
        float angle = angle_base * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - sine(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        primary_samples[i].center_x = 4.0f - (float)width_cells * 0.5f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = (depth * depth + 16.0f) / (depth + depth);
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = (float)(exit_index + 50);
        primary_samples[i].delta_length = 1.0f;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = (float)(exit_index + 50);
        secondary_samples[i].delta_length = 1.0f;
        ++exit_index;
    }

    int middle = 0;
    for (i = 16; i < 50; ++i) {
        float middle_f = (float)middle;
        float out_angle[2];
        out_angle[0] = middle_f * 0.18479957f;
        primary_samples[i].center_x =
            (primary_samples[50].center_x - primary_samples[0].center_x)
                * middle_f * 0.029411765f
            + primary_samples[0].center_x;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 4.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = 0.0f;
        primary_samples[i].transform.position.z = (float)(middle + 16);
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        primary_samples[i].transform.basis_forward = Vector3(
            primary_samples[i].transform.position.x
                - primary_samples[i - 1].transform.position.x,
            primary_samples[i].transform.position.y
                - primary_samples[i - 1].transform.position.y,
            primary_samples[i].transform.position.z
                - primary_samples[i - 1].transform.position.z);
        primary_samples[i].transform.basis_forward.normalize_vector();
        primary_samples[i].transform.basis_right.cross_vectors(
            &primary_samples[i].transform.basis_up,
            &primary_samples[i].transform.basis_forward);

        secondary_samples[i].transform = primary_samples[i].transform;
        secondary_samples[i].transform.position.x +=
            primary_samples[i].transform.basis_up.x * 0.49000001f;
        secondary_samples[i].transform.position.y +=
            primary_samples[i].transform.basis_up.y * 0.49000001f;
        secondary_samples[i].transform.position.z +=
            primary_samples[i].transform.basis_up.z * 0.49000001f;
        ++middle;
    }

    int sample_index = 0;
    if (segment_count - 1 > 0) {
        do {
            primary_samples[sample_index].delta_dir_to_next = Vector3(
                primary_samples[sample_index + 1].transform.position.x
                    - primary_samples[sample_index].transform.position.x,
                primary_samples[sample_index + 1].transform.position.y
                    - primary_samples[sample_index].transform.position.y,
                primary_samples[sample_index + 1].transform.position.z
                    - primary_samples[sample_index].transform.position.z);
            primary_samples[sample_index].delta_length =
                primary_samples[sample_index].delta_dir_to_next.normalize_vector();

            secondary_samples[sample_index].delta_dir_to_next = Vector3(
                secondary_samples[sample_index + 1].transform.position.x
                    - secondary_samples[sample_index].transform.position.x,
                secondary_samples[sample_index + 1].transform.position.y
                    - secondary_samples[sample_index].transform.position.y,
                secondary_samples[sample_index + 1].transform.position.z
                    - secondary_samples[sample_index].transform.position.z);
            secondary_samples[sample_index].delta_length =
                secondary_samples[sample_index].delta_dir_to_next.normalize_vector();
            ++sample_index;
        } while (sample_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->request_object_vertices((segment_count + 1) * (width_cells + 1));
    strip_mesh->request_object_facequads(2 * segment_count * width_cells);

    Vector3* vertices = strip_mesh->vertices;
    ObjectFaceQuad* facequads = strip_mesh->facequads;
    TransformMatrix kind42_transform;
    float out_angle[2];
    set_matrix_identity(&kind42_transform);

    int sample_offset = 0;
    for (int row = 0; row <= segment_count; ++row) {
        int column = 0;
        for (; column <= width_cells; ++column) {
            float lateral = (float)column - (float)width_cells * 0.5f;
            TransformMatrix* transform =
                (TransformMatrix*)((char*)&primary_samples[0].transform + sample_offset);
            Vector3* vertex = &vertices[column + row * (width_cells + 1)];
            if (row == segment_count) {
                TransformMatrix* previous =
                    (TransformMatrix*)((char*)transform - sizeof(AttachmentSample));
                Vector3 generated_position(
                    previous->position.x + lateral * previous->basis_right.x,
                    previous->position.y + lateral * previous->basis_right.y,
                    previous->position.z + 1.0f + lateral * previous->basis_right.z);
                *vertex = generated_position;
            } else {
                Vector3 generated_position(
                    transform->position.x + lateral * transform->basis_right.x,
                    transform->position.y + lateral * transform->basis_right.y,
                    transform->position.z + lateral * transform->basis_right.z);
                *vertex = generated_position;
            }

            int radius_sample = row - 1;
            if (row != segment_count)
                radius_sample = row;
            compute_kind42_attachment_transform(
                primary_samples[radius_sample].special_scalar,
                vertex->x,
                0.0f,
                &kind42_transform,
                out_angle);
            if (sample_offset > sizeof(AttachmentSample) && row != segment_count) {
                vertex->x = kind42_transform.position.x;
                vertex->y = kind42_transform.position.y;
            }
        }
        sample_offset += sizeof(AttachmentSample);
    }

    for (int mesh_row = 0; mesh_row < segment_count; ++mesh_row) {
        int mesh_column = 0;
        if (width_cells > 0) {
            float v0 = (float)(mesh_row % 8) * 0.125f;
            float v1 = (float)(mesh_row % 8 + 1) * 0.125f;
            int next_column;
            do {
                next_column = mesh_column + 1;
                float u0 = (float)mesh_column * 0.125f;
                float u1 = (float)(mesh_column + 1) * 0.125f;
                for (int face_index = 0; face_index < 2; ++face_index) {
                    ObjectFaceQuad* face =
                        &facequads[2 * mesh_column
                            + 2 * mesh_row * width_cells + face_index];
                    face->header_word = 0;
                    if (face_index == 0) {
                        face->vertex_0 = mesh_column
                            + mesh_row * ((unsigned short)width_cells + 1);
                        face->vertex_1 = mesh_row
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_2 = (mesh_row + 1)
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_3 = mesh_column + (mesh_row + 1)
                            * ((unsigned short)width_cells + 1);
                        if ((mesh_column ^ mesh_row) & 1)
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
                        else
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
                        face->vertex_0 = mesh_row
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_1 = mesh_column
                            + mesh_row * ((unsigned short)width_cells + 1);
                        face->vertex_2 = mesh_column + (mesh_row + 1)
                            * ((unsigned short)width_cells + 1);
                        face->vertex_3 = (mesh_row + 1)
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        if ((mesh_column ^ mesh_row) & 1)
                            face->texture_ref =
                                g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
                        else
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
                mesh_column = next_column;
            } while (next_column < width_cells);
        }
    }

    finalize_path_template(this);
}
