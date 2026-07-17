// initialize_hill_valley_path_template_pair @ 0x42d570 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_secondary_hill(
    Path* path, int index, float phase, float height)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = primary->center_x;
    float y = (1.0f - cosine(phase)) * 0.5f * height;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = primary->transform.position.z;
}

static __forceinline void orient_previous_hill_pair(Path* path, int current_index)
{
    PathTemplateSample* primary = &path->primary_samples[current_index - 1];
    PathTemplateSample* primary_next = &path->primary_samples[current_index];
    PathTemplateSample* secondary = &path->secondary_samples[current_index - 1];
    PathTemplateSample* secondary_next = &path->secondary_samples[current_index];

    if (current_index <= 1) {
        primary->transform.set_matrix_rotation_identity();
        secondary->transform.set_matrix_rotation_identity();
        return;
    }

    primary->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    primary->transform.basis_forward = Vector3(
        primary_next->transform.position.x - primary->transform.position.x,
        primary_next->transform.position.y - primary->transform.position.y,
        primary_next->transform.position.z - primary->transform.position.z);
    primary->transform.basis_forward.normalize_vector();
    primary->transform.basis_up.cross_vectors(
        &primary->transform.basis_forward, &primary->transform.basis_right);

    secondary->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    secondary->transform.basis_forward = Vector3(
        secondary_next->transform.position.x - secondary->transform.position.x,
        secondary_next->transform.position.y - secondary->transform.position.y,
        secondary_next->transform.position.z - secondary->transform.position.z);
    secondary->transform.basis_forward.normalize_vector();
    secondary->transform.basis_up.cross_vectors(
        &secondary->transform.basis_forward, &secondary->transform.basis_right);
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

void Path::initialize_hill_valley_path_template_pair(
    int width_cells_, float height, float length, char centered,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = 0x10;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int steps = (int)length;
    int last = steps + 1;
    width_or_scale = 1.0f;
    segment_count = last + 1;
    segment_count_f = (float)(last + 1);
    allocate_path_template_samples();

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

    if (centered)
        primary_samples[last].center_x = 0.0f;
    else
        primary_samples[last].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[last].rotation_scalar_98 = 0.0f;
    primary_samples[last].rotation_scalar_94 = 0.0f;
    primary_samples[last].special_scalar = 0.0f;
    primary_samples[last].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[last].transform);
    primary_samples[last].transform.position.x = primary_samples[last].center_x;
    float last_z = (float)last;
    primary_samples[last].transform.position.y = 0.0f;
    primary_samples[last].transform.position.z = last_z;
    set_matrix_identity(&secondary_samples[last].transform);
    secondary_samples[last].transform.position.x = primary_samples[last].center_x;
    secondary_samples[last].transform.position.y = 0.49000001f;
    secondary_samples[last].transform.position.z = last_z;

    int phase_index = 0;
    for (int i = 1; phase_index < steps; ++i) {
        primary_samples[i].center_x = primary_samples[0].center_x;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        float phase = (float)phase_index * 6.2831855f / (float)steps;
        set_matrix_identity(&primary_samples[i].transform);
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        ++phase_index;
        float y = (1.0f - cosine(phase)) * 0.5f * height;
        primary_samples[i].transform.position.y = y;
        primary_samples[i].transform.position.z = (float)phase_index;
        initialize_secondary_hill(this, i, phase, height);
        orient_previous_hill_pair(this, i);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template();
}
