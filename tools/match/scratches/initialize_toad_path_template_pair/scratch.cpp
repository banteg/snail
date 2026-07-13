// initialize_toad_path_template_pair @ 0x42cbf0 (thiscall, ret 0x10)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_sample(
    PathTemplateSample* sample, float center_x, float x, float y, float z)
{
    sample->center_x = center_x;
    sample->rotation_scalar_94 = 0.0f;
    sample->rotation_scalar_98 = 0.0f;
    sample->lateral_scale = 1.0f;
    sample->special_scalar = 0.0f;
    set_matrix_identity(&sample->transform);
    sample->transform.position.x = x;
    sample->transform.position.y = y;
    sample->transform.position.z = z;
}

static __forceinline void initialize_secondary_flat(Path* path, int index)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    secondary->center_x = primary->center_x;
    secondary->rotation_scalar_94 = primary->rotation_scalar_94;
    secondary->rotation_scalar_98 = primary->rotation_scalar_98;
    secondary->lateral_scale = primary->lateral_scale;
    secondary->special_scalar = primary->special_scalar;
    secondary->lateral_source = primary->lateral_source;
    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = primary->transform.position.x;
    secondary->transform.position.y = primary->transform.position.y + 0.49000001f;
    secondary->transform.position.z = primary->transform.position.z;
}

static __forceinline void copy_secondary_from_primary(Path* path, int index)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    secondary->center_x = primary->center_x;
    secondary->rotation_scalar_94 = primary->rotation_scalar_94;
    secondary->rotation_scalar_98 = primary->rotation_scalar_98;
    secondary->lateral_scale = primary->lateral_scale;
    secondary->special_scalar = primary->special_scalar;
    secondary->transform = primary->transform;
    secondary->transform.position.x += primary->transform.basis_up.x * 0.49000001f;
    secondary->transform.position.y += primary->transform.basis_up.y * 0.49000001f;
    secondary->transform.position.z += primary->transform.basis_up.z * 0.49000001f;
}

static __forceinline void orient_current_with_previous(Path* path, int index, float angle)
{
    PathTemplateSample* sample = &path->primary_samples[index];
    PathTemplateSample* previous = &path->primary_samples[index - 1];

    sample->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
    sample->transform.basis_forward = Vector3(
        sample->transform.position.x - previous->transform.position.x,
        sample->transform.position.y - previous->transform.position.y,
        sample->transform.position.z - previous->transform.position.z);
    sample->transform.basis_forward.normalize_vector();
    sample->transform.basis_right.cross_vectors(
        &sample->transform.basis_up, &sample->transform.basis_forward);
    sample->transform.rotate_matrix_world_z(angle);
}

static __forceinline void compute_path_deltas(Path* path)
{
    for (int i = 0; i < path->segment_count - 1; ++i) {
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

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void build_strip_mesh(Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->request_object_vertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->request_object_facequads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    ObjectFaceQuad* facequads = path->strip_mesh->facequads;

    int row;
    int column;
    int face_index;
    for (row = 0; row <= path->segment_count; ++row) {
        PathTemplateSample* sample = &path->primary_samples[row];
        if (row == path->segment_count)
            sample = &path->primary_samples[row - 1];

        for (column = 0; column <= path->width_cells; ++column) {
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            vertex->x = sample->transform.position.x
                + lateral * sample->transform.basis_right.x;
            vertex->y = sample->transform.position.y
                + lateral * sample->transform.basis_right.y;
            vertex->z = sample->transform.position.z
                + lateral * sample->transform.basis_right.z
                + (row == path->segment_count ? 1.0f : 0.0f);
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        float v0 = (float)(row % 8) * 0.125f;
        float v1 = (float)(row % 8 + 1) * 0.125f;
        for (column = 0; column < path->width_cells; ++column) {
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            for (face_index = 0; face_index < 2; ++face_index) {
                ObjectFaceQuad* face =
                    &facequads[2 * column + 2 * row * path->width_cells + face_index];
                face->flags = 0;
                if (face_index == 0) {
                    face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    face->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
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
                    face->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
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

void Path::initialize_toad_path_template_pair(
    char turn_left, char* texture_a, char* texture_b, char* vertical_texture)
{
    int lead_count;
    int tail_count;
    float start_x;
    float turn_sign;

    kind = 0x27;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = 4;

    if (turn_left) {
        lead_count = 1;
        tail_count = 3;
        start_x = -2.0f;
        turn_sign = -1.0f;
    } else {
        lead_count = 2;
        tail_count = 1;
        start_x = 2.0f;
        turn_sign = 1.0f;
    }

    width_or_scale = 1.0f;
    segment_count = lead_count + tail_count + 26;
    segment_count_f = (float)segment_count;
    allocate_path_template_samples();

    has_entry_mesh_transition = 0;
    for (int i = 0; i < lead_count; ++i) {
        initialize_sample(&primary_samples[i], start_x, start_x, 0.0f, (float)i);
        primary_samples[i].delta_length = 1.0f;
        initialize_secondary_flat(this, i);
        secondary_samples[i].delta_length = 1.0f;
    }

    for (int tail = 0; tail < tail_count; ++tail) {
        int index = lead_count + 26 + tail;
        initialize_sample(&primary_samples[index], start_x, start_x, 0.0f, (float)index);
        primary_samples[index].delta_length = 1.0f;
        initialize_secondary_flat(this, index);
        secondary_samples[index].delta_length = 1.0f;
    }

    for (int k = 0; k < 26; ++k) {
        int index = lead_count + k;
        float phase = (float)k * 0.24166098f;
        float angle = (1.0f - cosine(phase)) * 0.5f;
        angle = angle * turn_sign * 1.5707964f;
        float x = start_x + 2.0f * sine(angle);

        initialize_sample(
            &primary_samples[index], start_x, x, 0.0f, (float)(lead_count + k));
        orient_current_with_previous(this, index, angle);
        copy_secondary_from_primary(this, index);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template();
}
