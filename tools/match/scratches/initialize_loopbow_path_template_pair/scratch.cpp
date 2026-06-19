// initialize_loopbow_path_template_pair @ 0x42ba80 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"

float sine(float angle);
float cosine(float angle);

static __inline Vector3 vector_subtract(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

struct LoopbowFaceQuad {
    unsigned short flags;             // +0x00
    unsigned short vertex_0;          // +0x02
    unsigned short vertex_1;          // +0x04
    unsigned short vertex_2;          // +0x06
    unsigned short vertex_3;          // +0x08
    unsigned short unknown_0a;        // +0x0a
    TextureRef* texture_ref;          // +0x0c
    float u0;                         // +0x10
    float v0;                         // +0x14
    float u1;                         // +0x18
    float v1;                         // +0x1c
    float u2;                         // +0x20
    float v2;                         // +0x24
    float u3;                         // +0x28
    float v3;                         // +0x2c
};

typedef char LoopbowFaceQuad_must_be_0x30[
    (sizeof(LoopbowFaceQuad) == 0x30) ? 1 : -1];

class AttachmentPathTemplate {
public:
    void allocate_path_template_samples();
    int initialize_loopbow_path_template_pair(
        float curve_scale,
        unsigned int width_cells_arg,
        char unused_mode,
        char* texture_a,
        char* texture_b,
        char* unused_texture);

    char unknown_00[0x24];
    Object* strip_mesh;                // +0x24
    char unknown_28[0x38 - 0x28];
    int kind;                          // +0x38
    unsigned char is_mirrored_x;       // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;                // +0x40
    int segment_count;                 // +0x44
    int row_span_count;                // +0x48
    float segment_count_f;             // +0x4c
    float width_or_scale;              // +0x50
    int width_cells;                   // +0x54
    AttachmentSample* primary_samples; // +0x58
    AttachmentSample* secondary_samples; // +0x5c
    char unknown_60[0x9c - 0x60];
    unsigned char special_runtime_flag_9c; // +0x9c
};

int __fastcall finalize_path_template(AttachmentPathTemplate* path);

int AttachmentPathTemplate::initialize_loopbow_path_template_pair(
    float curve_scale,
    unsigned int width_cells_arg,
    char unused_mode,
    char* texture_a,
    char* texture_b,
    char* unused_texture)
{
    int cell_index = 0;
    Vector3 endpoint;
    kind = cell_index;
    float center_offset = 0.0f;
    if (width_cells_arg == 4) {
        kind = cell_index;
        center_offset = 0.5f;
    }

    is_mirrored_x = 0;
    side_exit_mode = cell_index;
    width_cells = width_cells_arg;

    int curve_segment_count = (int)(curve_scale * 6.2831855f);
    int total_segment_count = curve_segment_count + 14;
    width_or_scale = 1.0f;
    segment_count = total_segment_count;
    segment_count_f = (float)total_segment_count;

    float curve_segment_count_f = (float)curve_segment_count;
    curve_scale = curve_segment_count_f * 0.15915494f;

    allocate_path_template_samples();
    special_runtime_flag_9c = 1;

    int i = 0;
    do {
        float fi = (float)i;
        float center_progress = fi * 0.14285715f;
        primary_samples[i].center_x =
            (float)width_cells * 0.5f - 4.0f
            - center_progress * center_offset;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = fi;
        primary_samples[i].delta_length = 1.0f;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = fi;
        secondary_samples[i].delta_length = 1.0f;
        ++i;
    } while (i < 7);

    i = 0;
    int sample_index = curve_segment_count + 7;
    do {
        primary_samples[sample_index].center_x =
            (1.0f - (float)i * 0.16666667f) * center_offset
            + (4.0f - (float)width_cells * 0.5f);
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[sample_index].transform);
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        primary_samples[sample_index].transform.position.y = 0.0f;
        float z = (float)(i + 7);
        primary_samples[sample_index].transform.position.z = z;
        primary_samples[sample_index].delta_length = 1.0f;

        set_matrix_identity(&secondary_samples[sample_index].transform);
        ++i;
        secondary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        secondary_samples[sample_index].transform.position.y = 0.49000001f;
        secondary_samples[sample_index].transform.position.z = z;
        secondary_samples[sample_index].delta_length = 1.0f;
        ++sample_index;
    } while (i < 7);

    i = 0;
    if (curve_segment_count > 0) {
        float secondary_radius = curve_scale - 0.49000001f;
        Vector3 primary_right(1.0f, 0.0f, 0.0f);
        Vector3 secondary_right(1.0f, 0.0f, 0.0f);

        do {
            float fi = (float)i;
            float angle = fi * 6.2831855f / curve_segment_count_f;
            int sample_index = i + 7;

            primary_samples[sample_index].center_x =
                (primary_samples[total_segment_count - 1].center_x
                    - primary_samples[0].center_x)
                    * fi / curve_segment_count_f
                + primary_samples[0].center_x;

            float half_angle = angle * 0.5f;
            primary_samples[sample_index].center_x =
                sine(half_angle + 4.712389f) * center_offset
                + primary_samples[sample_index].center_x;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;

            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                sine(angle) * curve_scale + 7.0f;
            primary_samples[sample_index].transform.position.y =
                curve_scale - cosine(angle) * curve_scale;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                sine(angle) * secondary_radius + 7.0f;
            secondary_samples[sample_index].transform.position.y =
                curve_scale - cosine(angle) * secondary_radius;

            primary_samples[sample_index].transform.basis_right = primary_right;
            primary_samples[sample_index].transform.basis_up.x = 0.0f;
            primary_samples[sample_index].transform.basis_up.y =
                curve_scale
                - primary_samples[sample_index].transform.position.y;
            primary_samples[sample_index].transform.basis_up.z =
                7.0f - primary_samples[sample_index].transform.position.z;
            primary_samples[sample_index].transform.basis_up.normalize_vector();
            primary_samples[sample_index].transform.basis_forward.cross_vectors(
                &primary_samples[sample_index].transform.basis_right,
                &primary_samples[sample_index].transform.basis_up);

            secondary_samples[sample_index].transform.basis_right = secondary_right;
            secondary_samples[sample_index].transform.basis_up.x = 0.0f;
            secondary_samples[sample_index].transform.basis_up.y =
                curve_scale
                - secondary_samples[sample_index].transform.position.y;
            secondary_samples[sample_index].transform.basis_up.z =
                7.0f - secondary_samples[sample_index].transform.position.z;
            secondary_samples[sample_index].transform.basis_up.normalize_vector();
            secondary_samples[sample_index].transform.basis_forward.cross_vectors(
                &secondary_samples[sample_index].transform.basis_right,
                &secondary_samples[sample_index].transform.basis_up);

            TransformMatrix rotation;
            set_matrix_identity(&rotation);
            float half_sine = sine(half_angle);
            rotation.rotate_matrix_world_y(
                sine(half_angle) * half_sine * 0.52359879f);

            primary_samples[sample_index].transform.position.z -= 7.0f;
            secondary_samples[sample_index].transform.position.z -= 7.0f;
            primary_samples[sample_index].transform.multiply_matrix_in_place(
                (const TransformMatrix*)&rotation);
            secondary_samples[sample_index].transform.multiply_matrix_in_place(
                (const TransformMatrix*)&rotation);
            primary_samples[sample_index].transform.position.z += 7.0f;
            secondary_samples[sample_index].transform.position.z += 7.0f;

            secondary_samples[sample_index].transform =
                primary_samples[sample_index].transform;

            float offset_x =
                primary_samples[sample_index].transform.basis_up.x * 0.49000001f;
            float offset_y =
                primary_samples[sample_index].transform.basis_up.y * 0.49000001f;
            float offset_z =
                primary_samples[sample_index].transform.basis_up.z * 0.49000001f;
            secondary_samples[sample_index].transform.position.x += offset_x;
            secondary_samples[sample_index].transform.position.y += offset_y;
            secondary_samples[sample_index].transform.position.z += offset_z;

            ++i;
        } while (i < curve_segment_count);
    }

    i = 0;
    if (segment_count - 1 > 0) {
        do {
            primary_samples[i].delta_dir_to_next = vector_subtract(
                primary_samples[i + 1].transform.position,
                primary_samples[i].transform.position);
            primary_samples[i].delta_length =
                primary_samples[i].delta_dir_to_next.normalize_vector();

            secondary_samples[i].delta_dir_to_next = vector_subtract(
                secondary_samples[i + 1].transform.position,
                secondary_samples[i].transform.position);
            ++i;
            secondary_samples[i - 1].delta_length =
                secondary_samples[i - 1].delta_dir_to_next.normalize_vector();
        } while (i < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->request_object_vertices(
        (segment_count + 1) * (width_cells + 1));
    strip_mesh->request_object_facequads(
        2 * segment_count * width_cells);

    LoopbowFaceQuad* facequads = (LoopbowFaceQuad*)strip_mesh->facequads;
    Vector3* vertices = strip_mesh->vertices;

    int row = 0;
    if (segment_count >= 0) {
        int sample_offset = 0;
        do {
            int column = 0;
            if (width_cells >= 0) {
                do {
                    float lateral =
                        (float)column - (float)width_cells * 0.5f;
                    if (row == segment_count) {
                        AttachmentSample* sample =
                            (AttachmentSample*)((char*)primary_samples + sample_offset);
                        Vector3 lateral_offset(
                            lateral * sample[-1].transform.basis_right.x,
                            lateral * sample[-1].transform.basis_right.y,
                            lateral * sample[-1].transform.basis_right.z);
                        endpoint.x = sample[-1].transform.position.x;
                        endpoint.y = sample[-1].transform.position.y;
                        endpoint.z = sample[-1].transform.position.z + 1.0f;
                        Vector3 point(
                            lateral_offset.x + endpoint.x,
                            lateral_offset.y + endpoint.y,
                            lateral_offset.z + endpoint.z);
                        int vertex_index =
                            column + row * (width_cells + 1);
                        vertices[vertex_index] = point;
                    } else {
                        AttachmentSample* sample =
                            (AttachmentSample*)((char*)primary_samples + sample_offset);
                        Vector3 lateral_offset(
                            lateral * sample->transform.basis_right.x,
                            lateral * sample->transform.basis_right.y,
                            lateral * sample->transform.basis_right.z);
                        Vector3 point(
                            lateral_offset.x + sample->transform.position.x,
                            lateral_offset.y + sample->transform.position.y,
                            lateral_offset.z + sample->transform.position.z);
                    int vertex_index =
                        column + row * (width_cells + 1);
                        vertices[vertex_index] = point;
                    }
                    ++column;
                } while (column <= width_cells);
            }
            ++row;
            sample_offset += sizeof(AttachmentSample);
        } while (row <= segment_count);
    }

    int segment = 0;
    if (segment_count > 0) {
        do {
            cell_index = 0;
            if (width_cells > 0) {
                float v0 = (float)(segment % 8) * 0.125f;
                float v1 = (float)(segment % 8 + 1) * 0.125f;
                do {
                    int side = 0;
                    int next_cell = cell_index + 1;
                    float u0 = (float)cell_index * 0.125f;
                    float u1 = (float)(cell_index + 1) * 0.125f;
                    do {
                        if (side != 0) {
                            LoopbowFaceQuad* face =
                                &facequads[side + 2 *
                                    (cell_index + segment * width_cells)];
                            face->flags = 0;
                            face->vertex_0 =
                                segment * (width_cells + 1) + cell_index + 1;
                            face->vertex_1 =
                                cell_index + segment * (width_cells + 1);
                            face->vertex_2 =
                                cell_index + (segment + 1) * (width_cells + 1);
                            face->vertex_3 =
                                (segment + 1) * (width_cells + 1)
                                + cell_index + 1;

                            if (((cell_index ^ segment) & 1) == 0) {
                                face->texture_ref =
                                    g_texture_refs.get_or_create_texture_ref(
                                        texture_b, 0, 0);
                            } else {
                                face->texture_ref =
                                    g_texture_refs.get_or_create_texture_ref(
                                        texture_b, 0, 0);
                            }

                            face->u0 = u1;
                            face->v0 = v0;
                            face->u1 = u0;
                            face->v1 = v0;
                            face->u2 = u0;
                            face->v2 = v1;
                            face->u3 = u1;
                            face->v3 = v1;
                        } else {
                            LoopbowFaceQuad* face =
                                &facequads[side + 2 *
                                    (cell_index + segment * width_cells)];
                            face->flags = 0;
                            face->vertex_0 =
                                cell_index + segment * (width_cells + 1);
                            face->vertex_1 =
                                segment * (width_cells + 1) + cell_index + 1;
                            face->vertex_2 =
                                (segment + 1) * (width_cells + 1)
                                + cell_index + 1;
                            face->vertex_3 =
                                cell_index + (segment + 1) * (width_cells + 1);

                            if (((cell_index ^ segment) & 1) == 0) {
                                face->texture_ref =
                                    g_texture_refs.get_or_create_texture_ref(
                                        texture_a, 0, 0);
                            } else {
                                face->texture_ref =
                                    g_texture_refs.get_or_create_texture_ref(
                                        texture_a, 0, 0);
                            }

                            face->u0 = u0;
                            face->v0 = v0;
                            face->u1 = u1;
                            face->v1 = v0;
                            face->u2 = u1;
                            face->v2 = v1;
                            face->u3 = u0;
                            face->v3 = v1;
                        }
                        ++side;
                    } while (side < 2);
                    cell_index = next_cell;
                } while (cell_index < width_cells);
            }
            ++segment;
        } while (segment < segment_count);
    }

    return finalize_path_template(this);
}
