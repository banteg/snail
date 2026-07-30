// initialize_sbend_path_template_pair @ 0x42df00 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void compute_path_deltas(Path* path)
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

static __forceinline void build_strip_mesh(
    Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;

    int row = 0;
    int column;
    int face_index;
    if (path->segment_count >= 0) {
        int sample_offset = 0;
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    double lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count) {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        Vector3 lateral_offset =
                            sample->transform.basis_right * lateral;
                        Vector3 generated_position =
                            sample->transform.position + lateral_offset;
                        Vector3* vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    } else {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        PathTemplateSample* previous = sample - 1;
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
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row) {
        float v0 = (float)(row % 8) * 0.125f;
        float v1 = (float)(row % 8 + 1) * 0.125f;
        for (column = 0; column < path->width_cells; ++column) {
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
                    if ((column ^ row) & 1)
                        face->texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                    else
                        face->texture_ref = g_texture_refs.Add(texture_a, 0, 0);
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
                    face->vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    if ((column ^ row) & 1)
                        face->texture_ref = g_texture_refs.Add(texture_b, 0, 0);
                    else
                        face->texture_ref = g_texture_refs.Add(texture_b, 0, 0);
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

void cRPath::initialize_sbend_path_template_pair(
    int width_cells_, float height, float z_amplitude, bool centered,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int steps = (int)(height * 3.1415927f);
    width_or_scale = 1.0f;
    segment_count = steps + 1;
    segment_count_f = (float)(steps + 1);
    get_path_nodes();

    has_entry_mesh_transition = 0;
    if (centered)
        primary_samples[0].center_x = 0.0f;
    else
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

    for (int sample_index = 0; sample_index < steps; ++sample_index) {
        int i = sample_index + 1;
        float phase = (float)sample_index * 6.2831855f / (float)steps;
        primary_samples[i].center_x = primary_samples[0].center_x;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        float y = (1.0f - cosine(phase * 0.5f)) * 0.5f;
        y *= height;
        primary_samples[i].transform.position.y = y;
        float z = (1.0f - cosine(phase * 1.5f)) * 0.5f;
        z = z * z_amplitude * 0.33333334f + 1.0f;
        primary_samples[i].transform.position.z = z;

        primary_samples[i].transform.basis_up = Vector3(1.0f, 0.0f, 0.0f);
        primary_samples[i].transform.basis_forward =
            primary_samples[i].transform.position -
            primary_samples[i - 1].transform.position;
        primary_samples[i].transform.basis_forward.Normalize();
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
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
}
