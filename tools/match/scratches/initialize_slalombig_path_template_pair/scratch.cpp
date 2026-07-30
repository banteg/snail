// initialize_slalombig_path_template_pair @ 0x4221f0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_pair_sample(
    Path* path, int index, float center_x, float y, float z)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    primary->center_x = center_x;
    primary->rotation_scalar_98 = 0.0f;
    primary->rotation_scalar_94 = 0.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_scale = 1.0f;
    set_matrix_identity(&primary->transform);
    primary->transform.position.x = center_x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
}

static __forceinline void orient_previous_with_up(
    PathTemplateSample* samples,
    int current_index,
    int curve_index,
    PathTemplateSample* roll_source)
{
    PathTemplateSample* previous = &samples[current_index - 1];
    PathTemplateSample* current = &samples[current_index];

    if (curve_index == 0) {
        previous->transform.RotIdentity();
        return;
    }

    previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        current->transform.position.x - previous->transform.position.x,
        current->transform.position.y - previous->transform.position.y,
        current->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.Normalize();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
    float roll_angle = roll_source->center_x * 0.2617994f;
    previous->transform.RotLocalZ(roll_angle);
}

static __forceinline void compute_terminal_deltas(Path* path)
{
    for (int i = 0; i < path->segment_count - 1; ++i) {
        path->primary_samples[i].delta_dir_to_next =
            path->primary_samples[i + 1].transform.position -
            path->primary_samples[i].transform.position;
        path->primary_samples[i].delta_length =
            path->primary_samples[i].delta_dir_to_next.Normalize();

        path->secondary_samples[i].delta_dir_to_next =
            path->secondary_samples[i + 1].transform.position -
            path->secondary_samples[i].transform.position;
        path->secondary_samples[i].delta_length =
            path->secondary_samples[i].delta_dir_to_next.Normalize();
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void build_extrapolated_strip_mesh(
    Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    cRFaceQuad* facequads = path->strip_mesh->facequads;
    Vector3* vertices = path->strip_mesh->vertices;

    int row;
    int column;
    int face_index;
    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            double lateral = (float)column - (float)path->width_cells * 0.5f;
            if (row != path->segment_count) {
                PathTemplateSample* sample = &path->primary_samples[row];
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position(
                    sample->transform.position.x + lateral_offset.x,
                    sample->transform.position.y + lateral_offset.y,
                    sample->transform.position.z + lateral_offset.z);
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
            } else {
                PathTemplateSample* previous = &path->primary_samples[row - 1];
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
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
                cRFaceQuad* face =
                    &facequads[2 * column + 2 * row * path->width_cells + face_index];
                face->header_word = 0;

                if (face_index == 0) {
                    face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    if ((column ^ row) & 1) {
                        face->texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        face->texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    }
                    face->uv[0].u = u0;
                    face->uv[0].v = v0;
                    face->uv[1].u = u1;
                    face->uv[1].v = v0;
                    face->uv[2].u = u1;
                    face->uv[2].v = v1;
                    face->uv[3].u = u0;
                    face->uv[3].v = v1;
                } else {
                    face->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    if ((column ^ row) & 1) {
                        face->texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    } else {
                        face->texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    }
                    face->uv[0].u = u1;
                    face->uv[0].v = v0;
                    face->uv[1].u = u0;
                    face->uv[1].v = v0;
                    face->uv[2].u = u0;
                    face->uv[2].v = v1;
                    face->uv[3].u = u1;
                    face->uv[3].v = v1;
                }
            }
        }
    }
}

void cRPath::initialize_slalombig_path_template_pair(
    int curve_segments,
    int width_cells_,
    bool side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    width_cells = width_cells_;
    kind = PATH_TEMPLATE_KIND_SLALOMBIG;
    int lead_out_start = curve_segments + 4;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    int total_segments = lead_out_start + 4;
    width_or_scale = 1.0f;
    segment_count = total_segments;
    segment_count_f = (float)total_segments;
    get_path_nodes();
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
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
    }

    int departure_index = lead_out_start;
    do {
        primary_samples[departure_index].center_x = 0.0f;
        primary_samples[departure_index].rotation_scalar_98 = 0.0f;
        primary_samples[departure_index].rotation_scalar_94 = 0.0f;
        primary_samples[departure_index].special_scalar = 0.0f;
        primary_samples[departure_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[departure_index].transform);
        primary_samples[departure_index].transform.position.x =
            primary_samples[departure_index].center_x;
        float z = (float)departure_index;
        primary_samples[departure_index].transform.position.y = 0.0f;
        primary_samples[departure_index].transform.position.z = z;
        set_matrix_identity(&secondary_samples[departure_index].transform);
        secondary_samples[departure_index].transform.position.x =
            primary_samples[departure_index].center_x;
        secondary_samples[departure_index].transform.position.y = 0.49000001f;
        secondary_samples[departure_index].transform.position.z = z;
        ++departure_index;
    } while (departure_index - 4 - curve_segments < 4);

    for (i = 0; i < curve_segments; ++i) {
        float t = (float)i / (float)curve_segments;
        float folded = t - 0.5f;
        float folded_copy;
        if (folded >= 0.0f)
            folded_copy = folded;
        else
            folded_copy = -folded;
        if (folded < 0.0f)
            folded = -folded;

        float angle = t * 6.2831855f;
        float center = sine(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
        int sample_index = i + 4;
        primary_samples[sample_index].center_x = center;
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[sample_index].transform);
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        float z = (float)(i + 4);
        primary_samples[sample_index].transform.position.y = 0.0f;
        primary_samples[sample_index].transform.position.z = z;

        set_matrix_identity(&secondary_samples[sample_index].transform);
        secondary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        secondary_samples[sample_index].transform.position.y = 0.49000001f;
        secondary_samples[sample_index].transform.position.z = z;

        if (i == 0) {
            primary_samples[sample_index - 1].transform.RotIdentity();
            secondary_samples[sample_index - 1].transform.RotIdentity();
        } else {
            primary_samples[sample_index - 1].transform.basis_up =
                Vector3(0.0f, 1.0f, 0.0f);
            primary_samples[sample_index - 1].transform.basis_forward =
                Vector3(
                    primary_samples[sample_index].transform.position.x
                        - primary_samples[sample_index - 1].transform.position.x,
                    primary_samples[sample_index].transform.position.y
                        - primary_samples[sample_index - 1].transform.position.y,
                    primary_samples[sample_index].transform.position.z
                        - primary_samples[sample_index - 1].transform.position.z);
            primary_samples[sample_index - 1]
                .transform.basis_forward.Normalize();
            primary_samples[sample_index - 1]
                .transform.basis_right.cross_vectors(
                    &primary_samples[sample_index - 1].transform.basis_up,
                    &primary_samples[sample_index - 1].transform.basis_forward);
            float primary_roll =
                primary_samples[sample_index - 1].center_x * 0.2617994f;
            primary_samples[sample_index - 1]
                .transform.RotLocalZ(primary_roll);

            secondary_samples[sample_index - 1].transform.basis_up =
                Vector3(0.0f, 1.0f, 0.0f);
            secondary_samples[sample_index - 1].transform.basis_forward =
                Vector3(
                    secondary_samples[sample_index].transform.position.x
                        - secondary_samples[sample_index - 1].transform.position.x,
                    secondary_samples[sample_index].transform.position.y
                        - secondary_samples[sample_index - 1].transform.position.y,
                    secondary_samples[sample_index].transform.position.z
                        - secondary_samples[sample_index - 1].transform.position.z);
            secondary_samples[sample_index - 1]
                .transform.basis_forward.Normalize();
            secondary_samples[sample_index - 1]
                .transform.basis_right.cross_vectors(
                    &secondary_samples[sample_index - 1].transform.basis_up,
                    &secondary_samples[sample_index - 1].transform.basis_forward);

            float secondary_roll =
                primary_samples[sample_index - 1].center_x * 0.2617994f;
            secondary_samples[sample_index - 1]
                .transform.RotLocalZ(secondary_roll);
        }
    }

    compute_terminal_deltas(this);
    build_extrapolated_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
    (void)side_exit;
    (void)cap_texture;
}
