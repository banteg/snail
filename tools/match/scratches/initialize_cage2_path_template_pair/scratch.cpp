// initialize_cage2_path_template_pair @ 0x42e720 (thiscall, ret 0x10)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float cosine(float angle);

struct CageAttachmentSample {
    TransformMatrix transform;             // +0x00
    float inverse_matrix[16];              // +0x40
    Vector3 delta_dir_to_next;             // +0x80
    float delta_length;                    // +0x8c
    float center_x;                        // +0x90
    float rotation_scalar_94;              // +0x94
    float rotation_scalar_98;              // +0x98
    float lateral_scale;                   // +0x9c
    float special_scalar;                  // +0xa0
    float lateral_source;                  // +0xa4
};

typedef char CageAttachmentSample_must_be_0xa8[
    (sizeof(CageAttachmentSample) == 0xa8) ? 1 : -1];

struct CageFaceQuad {
    unsigned short flags;                  // +0x00
    unsigned short vertex_0;               // +0x02
    unsigned short vertex_1;               // +0x04
    unsigned short vertex_2;               // +0x06
    unsigned short vertex_3;               // +0x08
    char unknown_0a[0x0c - 0x0a];
    TextureRef* texture_ref;                // +0x0c
    ObjectUv uv[4];                         // +0x10
};

typedef char CageFaceQuad_must_be_0x30[
    (sizeof(CageFaceQuad) == 0x30) ? 1 : -1];

class AttachmentPathTemplate;
void __fastcall finalize_path_template(AttachmentPathTemplate* path);

class AttachmentPathTemplate {
public:
    void allocate_path_template_samples();
    void initialize_cage2_path_template_pair(
        int width_cells_, char* texture_a, char* texture_b, char* vertical_texture);

    char unknown_00[0x24];
    Object* strip_mesh;                     // +0x24
    char unknown_28[0x38 - 0x28];
    int kind;                               // +0x38
    unsigned char is_mirrored_x;            // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;                     // +0x40
    int segment_count;                      // +0x44
    int row_span_count;                     // +0x48
    float segment_count_f;                  // +0x4c
    float width_or_scale;                   // +0x50
    int width_cells;                        // +0x54
    CageAttachmentSample* primary_samples;  // +0x58
    CageAttachmentSample* secondary_samples;// +0x5c
    char unknown_60[0x9c - 0x60];
    unsigned char special_runtime_flag_9c;  // +0x9c
};

void AttachmentPathTemplate::initialize_cage2_path_template_pair(
    int width_cells_, char* texture_a, char* texture_b, char* vertical_texture)
{
    int mesh_cursor = 0;
    kind = 0x0f;
    is_mirrored_x = 0;
    side_exit_mode = mesh_cursor;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 22;
    segment_count_f = 22.0f;
    allocate_path_template_samples();

    special_runtime_flag_9c = 0;
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

    primary_samples[21].center_x = 4.0f - (float)width_cells * 0.5f;
    primary_samples[21].rotation_scalar_98 = 0.0f;
    primary_samples[21].rotation_scalar_94 = 0.0f;
    primary_samples[21].special_scalar = 0.0f;
    primary_samples[21].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[21].transform);
    primary_samples[21].transform.position.x = primary_samples[21].center_x;
    primary_samples[21].transform.position.y = 0.0f;
    primary_samples[21].transform.position.z = 21.0f;

    set_matrix_identity(&secondary_samples[21].transform);
    secondary_samples[21].transform.position.x = primary_samples[21].center_x;
    width_cells_ = mesh_cursor;
    secondary_samples[21].transform.position.y = 0.49000001f;
    secondary_samples[21].transform.position.z = 21.0f;

    for (int i = 1; i < 21; ++i) {
        float sample_index_f = (float)width_cells_;
        float curve_angle = sample_index_f * 0.31415927f;
        float angle = sample_index_f * 0.47123891f;
        primary_samples[i].center_x = cosine(angle) * primary_samples[0].center_x;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        ++width_cells_;
        primary_samples[i].transform.position.y = 0.0f;
        float sample_z = (float)width_cells_;
        primary_samples[i].transform.position.z = sample_z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y =
            primary_samples[i].transform.position.y + 0.49000001f;
        secondary_samples[i].transform.position.z = sample_z;

        if (i <= 1) {
            primary_samples[i - 1].transform.set_matrix_rotation_identity();
            secondary_samples[i - 1].transform.set_matrix_rotation_identity();
        } else {
            primary_samples[i - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            primary_samples[i - 1].transform.basis_forward = Vector3(
                primary_samples[i].transform.position.x
                    - primary_samples[i - 1].transform.position.x,
                primary_samples[i].transform.position.y
                    - primary_samples[i - 1].transform.position.y,
                primary_samples[i].transform.position.z
                    - primary_samples[i - 1].transform.position.z);
            primary_samples[i - 1].transform.basis_forward.normalize_vector();
            primary_samples[i - 1].transform.basis_right.cross_vectors(
                &primary_samples[i - 1].transform.basis_up,
                &primary_samples[i - 1].transform.basis_forward);
            primary_samples[i - 1].transform.rotate_matrix_world_z(
                (float)((1.0f - cosine(curve_angle)) * 0.5f)
                    * primary_samples[i - 1].center_x * 0.39269909f);

            secondary_samples[i - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            secondary_samples[i - 1].transform.basis_forward = Vector3(
                secondary_samples[i].transform.position.x
                    - secondary_samples[i - 1].transform.position.x,
                secondary_samples[i].transform.position.y
                    - secondary_samples[i - 1].transform.position.y,
                secondary_samples[i].transform.position.z
                    - secondary_samples[i - 1].transform.position.z);
            secondary_samples[i - 1].transform.basis_forward.normalize_vector();
            secondary_samples[i - 1].transform.basis_right.cross_vectors(
                &secondary_samples[i - 1].transform.basis_up,
                &secondary_samples[i - 1].transform.basis_forward);
            secondary_samples[i - 1].transform.rotate_matrix_world_z(
                (float)((1.0f - cosine(curve_angle)) * 0.5f)
                    * primary_samples[i - 1].center_x * 0.39269909f);
        }
    }

    int completed = 0;
    if (segment_count - 1 > 0) {
        int sample_offset = 0;
        do {
            primary_samples[sample_offset].delta_dir_to_next = Vector3(
                primary_samples[sample_offset + 1].transform.position.x
                    - primary_samples[sample_offset].transform.position.x,
                primary_samples[sample_offset + 1].transform.position.y
                    - primary_samples[sample_offset].transform.position.y,
                primary_samples[sample_offset + 1].transform.position.z
                    - primary_samples[sample_offset].transform.position.z);
            primary_samples[sample_offset].delta_length =
                primary_samples[sample_offset].delta_dir_to_next.normalize_vector();

            secondary_samples[sample_offset].delta_dir_to_next = Vector3(
                secondary_samples[sample_offset + 1].transform.position.x
                    - secondary_samples[sample_offset].transform.position.x,
                secondary_samples[sample_offset + 1].transform.position.y
                    - secondary_samples[sample_offset].transform.position.y,
                secondary_samples[sample_offset + 1].transform.position.z
                    - secondary_samples[sample_offset].transform.position.z);
            ++completed;
            secondary_samples[sample_offset].delta_length =
                secondary_samples[sample_offset].delta_dir_to_next.normalize_vector();
            ++sample_offset;
        } while (completed < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->request_object_vertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->request_object_facequads(2 * width_cells * segment_count);

    Vector3* vertices = strip_mesh->vertices;
    CageFaceQuad* facequads = (CageFaceQuad*)strip_mesh->facequads;

    for (int row = 0; row <= segment_count; ++row) {
        int column = 0;
        for (; column <= width_cells; ++column) {
            float lateral = (float)column - (float)width_cells * 0.5f;
            TransformMatrix* transform =
                (TransformMatrix*)((char*)&primary_samples[0].transform + mesh_cursor);
            Vector3* vertex = &vertices[column + row * (width_cells + 1)];
            if (row == segment_count) {
                TransformMatrix* previous =
                    (TransformMatrix*)((char*)transform - sizeof(CageAttachmentSample));
                Vector3 lateral_offset(
                    lateral * previous->basis_right.x,
                    lateral * previous->basis_right.y,
                    lateral * previous->basis_right.z);
                Vector3 generated_position(
                    previous->position.x + lateral_offset.x,
                    previous->position.y + lateral_offset.y,
                    previous->position.z + 1.0f + lateral_offset.z);
                *vertex = generated_position;
            } else {
                Vector3 generated_position(
                    transform->position.x + lateral * transform->basis_right.x,
                    transform->position.y + lateral * transform->basis_right.y,
                    transform->position.z + lateral * transform->basis_right.z);
                *vertex = generated_position;
            }
        }
        mesh_cursor += sizeof(CageAttachmentSample);
    }

    mesh_cursor = 0;
    for (; mesh_cursor < segment_count; ++mesh_cursor) {
        int mesh_column = 0;
        if (width_cells > 0) {
            float v0 = (float)(mesh_cursor % 8) * 0.125f;
            float v1 = (float)(mesh_cursor % 8 + 1) * 0.125f;
            int next_column;
            do {
                next_column = mesh_column + 1;
                float u0 = (float)mesh_column * 0.125f;
                float u1 = (float)(mesh_column + 1) * 0.125f;
                for (int face_index = 0; face_index < 2; ++face_index) {
                    CageFaceQuad* face =
                        &facequads[2 * mesh_column
                            + 2 * mesh_cursor * width_cells + face_index];
                    face->flags = 0;
                    if (face_index == 0) {
                        face->vertex_0 = mesh_column
                            + mesh_cursor * ((unsigned short)width_cells + 1);
                        face->vertex_1 = mesh_cursor
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_2 = (mesh_cursor + 1)
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_3 = mesh_column + (mesh_cursor + 1)
                            * ((unsigned short)width_cells + 1);
                        if ((mesh_column ^ mesh_cursor) & 1)
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
                        face->vertex_0 = mesh_cursor
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        face->vertex_1 = mesh_column
                            + mesh_cursor * ((unsigned short)width_cells + 1);
                        face->vertex_2 = mesh_column + (mesh_cursor + 1)
                            * ((unsigned short)width_cells + 1);
                        face->vertex_3 = (mesh_cursor + 1)
                            * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        if ((mesh_column ^ mesh_cursor) & 1)
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
