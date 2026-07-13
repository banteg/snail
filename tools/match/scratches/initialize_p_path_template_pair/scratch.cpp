// initialize_p_path_template_pair @ 0x425a40 (thiscall, ret 0x24)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

void __fastcall finalize_path_template(Path* path);

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
    primary->transform.position.x = center_x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
}

static __forceinline void orient_previous_with_up(
    PathTemplateSample* samples, int current_index, int first_index)
{
    PathTemplateSample* previous = &samples[current_index - 1];
    PathTemplateSample* current = &samples[current_index];

    if (current_index <= first_index) {
        previous->transform.set_matrix_rotation_identity();
        return;
    }

    previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        current->transform.position.x - previous->transform.position.x,
        current->transform.position.y - previous->transform.position.y,
        current->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.normalize_vector();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
}

static __forceinline void compute_terminal_deltas(Path* path)
{
    int i;
    for (i = 0; i < path->segment_count - 1; ++i) {
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

    PathTemplateSample* last_primary = &path->primary_samples[path->segment_count - 1];
    last_primary->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    last_primary->delta_length = 1.0f;

    PathTemplateSample* last_secondary = &path->secondary_samples[path->segment_count - 1];
    last_secondary->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    last_secondary->delta_length = 1.0f;
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

    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            PathTemplateSample* sample = &path->primary_samples[row];
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            if (row == path->segment_count)
                sample = &path->primary_samples[row - 1];
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
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            ObjectFaceQuad* a = &facequads[2 * (column + row * path->width_cells)];
            a->flags = 0;
            a->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
            a->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
            a->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
            a->uv[0].u = u0;
            a->uv[0].v = v0;
            a->uv[1].u = u1;
            a->uv[1].v = v0;
            a->uv[2].u = u1;
            a->uv[2].v = v1;
            a->uv[3].u = u0;
            a->uv[3].v = v1;

            ObjectFaceQuad* b = a + 1;
            b->flags = 0;
            b->vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
            b->vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
            b->vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
            b->vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
            b->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
            b->uv[0].u = u1;
            b->uv[0].v = v0;
            b->uv[1].u = u0;
            b->uv[1].v = v0;
            b->uv[2].u = u0;
            b->uv[2].v = v1;
            b->uv[3].u = u1;
            b->uv[3].v = v1;
        }
    }
}

void Path::initialize_p_path_template_pair(
    int variant,
    float scale_arg,
    int width_cells_,
    float start_x,
    float end_x,
    int curve_segments,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = variant + 0x21;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    int last_index = curve_segments + 1;
    int sample_count = last_index + 1;
    segment_count = sample_count;
    segment_count_f = (float)sample_count;

    double radius_calc = (end_x - start_x) * 0.5f;
    if (radius_calc < 0.0f)
        radius_calc = -radius_calc;
    float radius = (float)radius_calc;

    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    initialize_pair_sample(this, 0, start_x, 0.0f, 0);
    initialize_pair_sample(this, last_index, end_x, 0.0f, last_index);

    int i;
    for (i = 1; i <= curve_segments; ++i) {
        float angle = (float)(i - 1) * 3.1415927f / (float)curve_segments;
        float center;
        if (kind == 0x21) {
            center = sine(angle + 1.5707964f) * radius - radius + 0.5f;
        } else if (kind == 0x22) {
            center = 2.0f - cosine(angle) * radius - radius + 0.5f;
        } else {
            center = (sine(angle + 1.5707964f) + 1.0f) * radius + 0.5f;
        }

        initialize_pair_sample(this, i, center, 0.0f, i);
        PathTemplateSample* primary_previous = &primary_samples[i - 1];
        PathTemplateSample* primary_current = &primary_samples[i];
        PathTemplateSample* secondary_previous = &secondary_samples[i - 1];
        PathTemplateSample* secondary_current = &secondary_samples[i];

        if (i <= 1) {
            primary_previous->transform.set_matrix_rotation_identity();
            secondary_previous->transform.set_matrix_rotation_identity();
        } else {
            primary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            primary_previous->transform.basis_forward = Vector3(
                primary_current->transform.position.x - primary_previous->transform.position.x,
                primary_current->transform.position.y - primary_previous->transform.position.y,
                primary_current->transform.position.z - primary_previous->transform.position.z);
            primary_previous->transform.basis_forward.normalize_vector();
            primary_previous->transform.basis_right.cross_vectors(
                &primary_previous->transform.basis_up,
                &primary_previous->transform.basis_forward);

            secondary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            secondary_previous->transform.basis_forward = Vector3(
                secondary_current->transform.position.x - secondary_previous->transform.position.x,
                secondary_current->transform.position.y - secondary_previous->transform.position.y,
                secondary_current->transform.position.z - secondary_previous->transform.position.z);
            secondary_previous->transform.basis_forward.normalize_vector();
            secondary_previous->transform.basis_right.cross_vectors(
                &secondary_previous->transform.basis_up,
                &secondary_previous->transform.basis_forward);
        }
    }

    compute_terminal_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template(this);
    (void)scale_arg;
    (void)cap_texture;
}
