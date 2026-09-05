// initialize_slalomdouble_path_template_pair @ 0x425050 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_pair_sample(
    Path* path, int index, float center_x, float y, int z_index)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    primary->center_x = center_x;
    primary->rotation_scalar_98 = 0.0f;
    primary->rotation_scalar_94 = 0.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_scale = 1.0f;
    set_matrix_identity(&primary->transform);
    float z = (float)z_index;
    primary->transform.position.x = primary->center_x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = primary->center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
}

static __forceinline void build_strip_mesh(Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;
    int row;
    int column;
    int face_index;

    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            double lateral = (float)column - (float)path->width_cells * 0.5f;
            int vertex_index = column + row * (path->width_cells + 1);
            if (row != path->segment_count) {
                PathTemplateSample* sample = &path->primary_samples[row];
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position =
                    sample->transform.position + lateral_offset;

                vertices[vertex_index] = generated_position;
            } else {
                PathTemplateSample* previous = &path->primary_samples[row - 1];
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
                Vector3 endpoint = previous->transform.position
                    + Vector3(0.0f, 0.0f, 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;

                vertices[vertex_index] = generated_position;
            }
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            for (face_index = 0; face_index < 2; ++face_index) {
                int face_offset = 2 * column + 2 * row * path->width_cells + face_index;
                facequads[face_offset].header_word = 0;

                if (face_index == 0) {
                    facequads[face_offset].vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    if ((column ^ row) & 1) {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    }
                    facequads[face_offset].uv[0].u = u0;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u1;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u1;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u0;
                    facequads[face_offset].uv[3].v = v1;
                } else {
                    facequads[face_offset].vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    if ((column ^ row) & 1) {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    } else {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    }
                    facequads[face_offset].uv[0].u = u1;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u0;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u0;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u1;
                    facequads[face_offset].uv[3].v = v1;
                }
            }
        }
    }
}

void cRPath::initialize_slalomdouble_path_template_pair(
    int curve_segments,
    int width_cells_,
    bool side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = PATH_TEMPLATE_KIND_SLALOMDOUBLE;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 70;
    segment_count_f = 70.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int i;
    for (i = 0; i < 4; ++i) {
        primary_samples[i].center_x = 0.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        float z = (float)i;
        primary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
    }

    for (i = 66; i < 70; ++i) {
        primary_samples[i].center_x = 0.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        float z = (float)i;
        primary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
    }

    int curve_index = 0;
    for (i = 4; i < 66; ++i) {
        float t = (float)curve_index * 0.016129032f;
        float angle = t * 12.566371f;
        float folded = t - 0.5f;
        float folded_copy;
        if (folded >= 0.0f)
            folded_copy = folded;
        else
            folded_copy = -folded;
        if (folded < 0.0f)
            folded = -folded;

        float center = Sin(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
        primary_samples[i].center_x = center;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        primary_samples[i].transform.position.y =
            1.0f - Cos(angle * 0.5f);
        float z = (float)(curve_index + 4);
        primary_samples[i].transform.position.z = z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x =
            primary_samples[i].center_x;
        secondary_samples[i].transform.position.y =
            primary_samples[i].transform.position.y + 0.49000001f;
        secondary_samples[i].transform.position.z = z;
        PathTemplateSample* primary_previous = &primary_samples[i - 1];
        PathTemplateSample* primary_current = &primary_samples[i];
        if (curve_index == 0) {
            primary_previous->transform.RotIdentity();
        } else {
            primary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            primary_previous->transform.basis_forward = Vector3(
                primary_current->transform.position.x
                    - primary_previous->transform.position.x,
                primary_current->transform.position.y
                    - primary_previous->transform.position.y,
                primary_current->transform.position.z
                    - primary_previous->transform.position.z);
            primary_previous->transform.basis_forward.Normalize();
            primary_previous->transform.basis_right.cross_vectors(
                &primary_previous->transform.basis_up,
                &primary_previous->transform.basis_forward);
            float primary_roll = primary_previous->center_x * 0.2617994f;
            primary_previous->transform.RotLocalZ(primary_roll);
        }

        PathTemplateSample* secondary_previous = &secondary_samples[i - 1];
        PathTemplateSample* secondary_current = &secondary_samples[i];
        if (curve_index == 0) {
            secondary_previous->transform.RotIdentity();
        } else {
            secondary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            secondary_previous->transform.basis_forward = Vector3(
                secondary_current->transform.position.x
                    - secondary_previous->transform.position.x,
                secondary_current->transform.position.y
                    - secondary_previous->transform.position.y,
                secondary_current->transform.position.z
                    - secondary_previous->transform.position.z);
            secondary_previous->transform.basis_forward.Normalize();
            secondary_previous->transform.basis_right.cross_vectors(
                &secondary_previous->transform.basis_up,
                &secondary_previous->transform.basis_forward);
            float secondary_roll = primary_previous->center_x * 0.2617994f;
            secondary_previous->transform.RotLocalZ(secondary_roll);
        }
        ++curve_index;
    }

    int delta_index = 0;
    if (segment_count - 1 > 0) {
        do {
            primary_samples[delta_index].delta_dir_to_next =
                primary_samples[delta_index + 1].transform.position -
                primary_samples[delta_index].transform.position;
            primary_samples[delta_index].delta_length =
                primary_samples[delta_index].delta_dir_to_next.Normalize();

            secondary_samples[delta_index].delta_dir_to_next =
                secondary_samples[delta_index + 1].transform.position -
                secondary_samples[delta_index].transform.position;
            secondary_samples[delta_index].delta_length =
                secondary_samples[delta_index].delta_dir_to_next.Normalize();

            ++delta_index;
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)curve_segments;
    (void)side_exit;
    (void)cap_texture;
}
