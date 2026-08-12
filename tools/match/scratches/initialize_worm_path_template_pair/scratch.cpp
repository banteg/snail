// initialize_worm_path_template_pair @ 0x420170 (thiscall, ret 0x4)

#include "font_system.h"
#include "object_render_types.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

const float WORM_TAU = 6.2831855f;
const float WORM_RADIUS = 4.0f;
const float WORM_UNDERSIDE_SCALE = 0.30000001f;
const float WORM_UV_ROW_STEP = 0.125f;

inline Vector3 operator*(float scalar, const Vector3& value)
{
    return Vector3(scalar * value.x, scalar * value.y, scalar * value.z);
}

void cRPath::initialize_worm_path_template_pair(char* texture_path)
{
    kind = PATH_TEMPLATE_KIND_WORM;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = 16;
    width_or_scale = 4.0f;
    segment_count = 24;
    segment_count_f = 96.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int entrance_index = 0;
    do {
        primary_samples[entrance_index].center_x = 0.0f;
        primary_samples[entrance_index].rotation_scalar_98 = 0.0f;
        primary_samples[entrance_index].rotation_scalar_94 = 0.0f;
        primary_samples[entrance_index].special_scalar = 0.0f;
        primary_samples[entrance_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[entrance_index].transform);

        primary_samples[entrance_index].transform.position.x =
            primary_samples[entrance_index].center_x;
        primary_samples[entrance_index].transform.position.y = 0.49000001f;
        primary_samples[entrance_index].transform.position.z =
            (float)entrance_index * width_or_scale;

        set_matrix_identity(&secondary_samples[entrance_index].transform);
        secondary_samples[entrance_index].transform.position.x =
            primary_samples[entrance_index].center_x;
        secondary_samples[entrance_index].transform.position.y = 0.49000001f;
        secondary_samples[entrance_index].transform.position.z =
            (float)entrance_index * width_or_scale;
        ++entrance_index;
    } while (entrance_index < 4);

    int exit_index = 20;
    do {
        primary_samples[exit_index].center_x = 0.0f;
        primary_samples[exit_index].rotation_scalar_98 = 0.0f;
        primary_samples[exit_index].rotation_scalar_94 = 0.0f;
        primary_samples[exit_index].special_scalar = 0.0f;
        primary_samples[exit_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[exit_index].transform);

        primary_samples[exit_index].transform.position.x =
            primary_samples[exit_index].center_x;
        primary_samples[exit_index].transform.position.y = 0.49000001f;
        primary_samples[exit_index].transform.position.z =
            (float)exit_index * width_or_scale;

        set_matrix_identity(&secondary_samples[exit_index].transform);
        secondary_samples[exit_index].transform.position.x =
            primary_samples[exit_index].center_x;
        secondary_samples[exit_index].transform.position.y = 0.49000001f;
        secondary_samples[exit_index].transform.position.z =
            (float)exit_index * width_or_scale;
        ++exit_index;
    } while (exit_index - 20 < 4);

    int middle_index = 0;
    for (int i = 4; i < 20; ++i) {
        primary_samples[i].center_x = 0.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;

        int absolute_index = middle_index + 4;
        primary_samples[i].transform.position.y = 0.49000001f;
        primary_samples[i].transform.position.z =
            (float)absolute_index * width_or_scale;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z =
            (float)absolute_index * width_or_scale;

        if (middle_index != 0) {
            primary_samples[i - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);

            Vector3 primary_forward;
            primary_forward.x = primary_samples[i].transform.position.x -
                primary_samples[i - 1].transform.position.x;
            primary_forward.y = primary_samples[i].transform.position.y -
                primary_samples[i - 1].transform.position.y;
            primary_forward.z = primary_samples[i].transform.position.z -
                primary_samples[i - 1].transform.position.z;
            primary_samples[i - 1].transform.basis_forward = primary_forward;
            primary_samples[i - 1].transform.basis_forward.Normalize();
            primary_samples[i - 1].transform.basis_right.cross_vectors(
                &primary_samples[i - 1].transform.basis_up,
                &primary_samples[i - 1].transform.basis_forward);
            primary_samples[i - 1].transform.basis_up.cross_vectors(
                &primary_samples[i - 1].transform.basis_forward,
                &primary_samples[i - 1].transform.basis_right);

            secondary_samples[i - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);

            Vector3 secondary_forward;
            secondary_forward.x = secondary_samples[i].transform.position.x -
                secondary_samples[i - 1].transform.position.x;
            secondary_forward.y = secondary_samples[i].transform.position.y -
                secondary_samples[i - 1].transform.position.y;
            secondary_forward.z = secondary_samples[i].transform.position.z -
                secondary_samples[i - 1].transform.position.z;
            secondary_samples[i - 1].transform.basis_forward = secondary_forward;
            secondary_samples[i - 1].transform.basis_forward.Normalize();
            secondary_samples[i - 1].transform.basis_right.cross_vectors(
                &secondary_samples[i - 1].transform.basis_up,
                &secondary_samples[i - 1].transform.basis_forward);
            secondary_samples[i - 1].transform.basis_up.cross_vectors(
                &secondary_samples[i - 1].transform.basis_forward,
                &secondary_samples[i - 1].transform.basis_right);
        } else {
            primary_samples[i - 1].transform.RotIdentity();
            secondary_samples[i - 1].transform.RotIdentity();
        }

        ++middle_index;
    }

    int delta_index = 0;
    if (segment_count - 1 > 0) {
        do {
            Vector3 primary_delta;
            primary_delta.x = primary_samples[delta_index + 1].transform.position.x -
                primary_samples[delta_index].transform.position.x;
            primary_delta.y = primary_samples[delta_index + 1].transform.position.y -
                primary_samples[delta_index].transform.position.y;
            primary_delta.z = primary_samples[delta_index + 1].transform.position.z -
                primary_samples[delta_index].transform.position.z;
            primary_samples[delta_index].delta_dir_to_next = primary_delta;
            primary_samples[delta_index].delta_length =
                primary_samples[delta_index].delta_dir_to_next.Normalize();

            Vector3 secondary_delta;
            secondary_delta.x = secondary_samples[delta_index + 1].transform.position.x -
                secondary_samples[delta_index].transform.position.x;
            secondary_delta.y = secondary_samples[delta_index + 1].transform.position.y -
                secondary_samples[delta_index].transform.position.y;
            secondary_delta.z = secondary_samples[delta_index + 1].transform.position.z -
                secondary_samples[delta_index].transform.position.z;
            secondary_samples[delta_index].delta_dir_to_next = secondary_delta;
            secondary_samples[delta_index].delta_length =
                secondary_samples[delta_index].delta_dir_to_next.Normalize();

            ++delta_index;
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = width_or_scale;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = width_or_scale;

    strip_mesh->flags |= OBJECT_FLAG_TEXTURE_TRANSFORM;
    strip_mesh->RequestVertices((segment_count + 1) * width_cells);
    strip_mesh->RequestFaceQuads(2 * segment_count * width_cells);
    strip_mesh->RequestColours();
    int row = 0;
    int mesh_column;
    strip_mesh->flags |= OBJECT_FLAG_USE_VERTEX_COLOURS;

    Vector3* vertices = strip_mesh->vertices;
    cRFaceQuad* facequads = strip_mesh->facequads;
    tColour* vertex_colours = strip_mesh->vertex_colours;

    if (segment_count >= 0) {
        do {
            float row_angle = (float)row * WORM_TAU / segment_count;
            mesh_column = 0;
            if (width_cells > 0) {
                do {
                    if (row < segment_count) {
                        float radius = primary_samples[row].lateral_scale;
                        radius *= WORM_RADIUS;

                        Vector3 up_radius =
                            radius * primary_samples[row].transform.basis_up;
                        float column_as_float = (float)mesh_column;
                        Vector3 up_component =
                            cosine(column_as_float / (float)width_cells * WORM_TAU) *
                                up_radius;
                        Vector3 base_plus_right =
                            primary_samples[row].transform.position +
                            sine(column_as_float / (float)width_cells * WORM_TAU) *
                                (radius * primary_samples[row].transform.basis_right);
                        Vector3 vertex = base_plus_right + up_component;
                        vertices[mesh_column + row * width_cells] = vertex;

                        float double_row_angle = row_angle + row_angle;
                        float row_wave = cosine(double_row_angle);
                        float alpha = 0.5f - row_wave * 0.5f;
                        vertex_colours[mesh_column + row * width_cells].store_color4f(
                            1.0f, 1.0f, 1.0f, alpha);
                    } else {
                        vertices[mesh_column + row * width_cells] =
                            vertices[mesh_column + (row - 1) * width_cells];
                        vertices[mesh_column + row * width_cells].z += width_or_scale;
                        vertex_colours[mesh_column + row * width_cells].store_color4f(
                            0.0f, 0.0f, 0.0f, 0.0f);
                    }

                    if (vertices[mesh_column + row * width_cells].y < 0.0f) {
                        float lowered_y = vertices[mesh_column + row * width_cells].y;
                        lowered_y *= WORM_UNDERSIDE_SCALE;
                        vertices[mesh_column + row * width_cells].y = lowered_y;
                    }

                    ++mesh_column;
                } while (mesh_column < width_cells);
            }

            ++row;
        } while (row <= segment_count);
    }

    mesh_column = 0;
    if (segment_count > 0) {
        do {
            int column = 0;
            if (width_cells > 0) {
                float row_v = (float)mesh_column * WORM_UV_ROW_STEP;
                float next_row_v = (float)(mesh_column + 1) * WORM_UV_ROW_STEP;
                do {
                    int next_column = column + 1;
                    float column_f = (float)column;
                    float next_column_f = (float)next_column;
                    int side = 0;
                    do {
                        cRFaceQuad* face =
                            &facequads[side + 2 * (mesh_column * width_cells + column)];
                        face->header_word = 0;
                        if (side == 0) {
                            face->vertex_0 =
                                (unsigned short)(mesh_column * width_cells + column);
                            face->vertex_1 =
                                (unsigned short)(mesh_column * width_cells + next_column % width_cells);
                            face->vertex_2 =
                                (unsigned short)((mesh_column + 1) * width_cells + next_column % width_cells);
                            face->vertex_3 =
                                (unsigned short)((mesh_column + 1) * width_cells + column);
                        } else {
                            face->vertex_0 =
                                (unsigned short)(mesh_column * width_cells + next_column % width_cells);
                            face->vertex_1 =
                                (unsigned short)(mesh_column * width_cells + column);
                            face->vertex_2 =
                                (unsigned short)((mesh_column + 1) * width_cells + column);
                            face->vertex_3 =
                                (unsigned short)((mesh_column + 1) * width_cells + next_column % width_cells);
                        }

                        face->texture_ref =
                            g_texture_refs.Add(texture_path, 0, 0);

                        float width_f = (float)width_cells;
                        float u0 = column_f / width_f;
                        float u1 = next_column_f / width_f;
                        if (side == 0) {
                            face->u0 = u0;
                            face->v0 = row_v;
                            face->u1 = u1;
                            face->v1 = row_v;
                            face->u2 = u1;
                            face->v2 = next_row_v;
                            face->u3 = u0;
                            face->v3 = next_row_v;
                        } else {
                            face->u0 = u1;
                            face->v0 = row_v;
                            face->u1 = u0;
                            face->v1 = row_v;
                            face->u2 = u0;
                            face->v2 = next_row_v;
                            face->u3 = u1;
                            face->v3 = next_row_v;
                        }

                        ++side;
                    } while (side < 2);

                    ++column;
                } while (column < width_cells);
            }

            ++mesh_column;
        } while (mesh_column < segment_count);
    }

    CalcLengthZ();
}
