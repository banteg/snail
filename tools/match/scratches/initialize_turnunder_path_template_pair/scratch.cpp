// initialize_turnunder_path_template_pair @ 0x427fe0 (thiscall, ret 0x18)

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
    sample->lateral_source = 0.0f;
    set_matrix_identity(&sample->transform);
    sample->transform.position.x = x;
    sample->transform.position.y = y;
    sample->transform.position.z = z;
}

static __forceinline void initialize_pair_sample(
    Path* path, int index, float center_x, float x, float y, float z)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    primary->center_x = center_x;
    primary->rotation_scalar_94 = 0.0f;
    primary->rotation_scalar_98 = 0.0f;
    primary->lateral_scale = 1.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_source = 0.0f;
    set_matrix_identity(&primary->transform);
    primary->transform.position.x = x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;
    primary->delta_length = 1.0f;

    secondary->center_x = center_x;
    secondary->rotation_scalar_94 = 0.0f;
    secondary->rotation_scalar_98 = 0.0f;
    secondary->lateral_scale = 1.0f;
    secondary->special_scalar = 0.0f;
    secondary->lateral_source = 0.0f;
    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
    secondary->delta_length = 1.0f;
}

static __forceinline void copy_secondary_from_primary(Path* path, int index)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    secondary->transform = primary->transform;
    secondary->transform.position.x += primary->transform.basis_up.x * 0.49000001f;
    secondary->transform.position.y += primary->transform.basis_up.y * 0.49000001f;
    secondary->transform.position.z += primary->transform.basis_up.z * 0.49000001f;
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

void Path::initialize_turnunder_path_template_pair(
    float turns, int width_cells_, int side_exit,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    float scaled_turns = turns * 6.2831855f;

    kind = 0x27;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    int interior_count = (int)scaled_turns;
    width_or_scale = 1.0f;
    segment_count = interior_count + 8;
    segment_count_f = (float)segment_count;
    allocate_path_template_samples();

    has_entry_mesh_transition = 0;
    for (int i = 0; i < 6; ++i) {
        float center = (float)width_cells * 0.5f - 4.0f;
        initialize_pair_sample(this, i, center, center, 0.0f, (float)i);
    }

    for (int j = 0; j < 2; ++j) {
        int index = interior_count + 6 + j;
        float center = 4.0f - (float)width_cells * 0.5f;
        initialize_pair_sample(this, index, center, center, 0.0f, (float)index);
    }

    float start_center = primary_samples[0].center_x;
    float end_center = primary_samples[interior_count + 6].center_x;
    float interior_count_f = (float)interior_count;
    float radius = interior_count_f * 0.15915494f;

    for (int k = 0; k < interior_count; ++k) {
        int index = k + 6;
        float phase = (float)k / interior_count_f;
        float angle = phase * -6.2831855f;
        float center = start_center + (end_center - start_center) * phase;
        float half_angle = angle * 0.5f;
        float half_side = sine(half_angle);
        float side = sine(angle);
        float offset = side * half_side + side * half_side;
        float y = (radius - cosine(angle) * radius) * -0.2f;
        float roll_cos = cosine(sine(angle) * 1.0471976f);
        float roll_sin = sine(sine(angle) * 1.0471976f);

        initialize_sample(&primary_samples[index], center, center - offset, y, (float)index);
        primary_samples[index].transform.basis_up.x = -roll_sin;
        primary_samples[index].transform.basis_up.y = roll_cos;
        primary_samples[index].transform.basis_up.z = 0.0f;
        PathTemplateSample* previous = &primary_samples[index - 1];
        primary_samples[index].transform.basis_forward = Vector3(
            primary_samples[index].transform.position.x - previous->transform.position.x,
            primary_samples[index].transform.position.y - previous->transform.position.y,
            primary_samples[index].transform.position.z - previous->transform.position.z);
        primary_samples[index].transform.basis_forward.normalize_vector();
        primary_samples[index].transform.basis_right.cross_vectors(
            &primary_samples[index].transform.basis_up,
            &primary_samples[index].transform.basis_forward);
        copy_secondary_from_primary(this, index);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template();
}
