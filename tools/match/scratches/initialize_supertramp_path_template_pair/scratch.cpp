// initialize_supertramp_path_template_pair @ 0x423f10 (thiscall, ret 0x1c)

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
    primary->delta_length = 1.0f;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
    secondary->delta_length = 1.0f;
}

static __forceinline void orient_arc_sample(PathTemplateSample* sample, float radius)
{
    sample->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    sample->transform.basis_up = Vector3(
        0.0f,
        radius - sample->transform.position.y,
        7.0f - sample->transform.position.z);
    sample->transform.basis_up.normalize_vector();
    sample->transform.basis_forward.cross_vectors(
        &sample->transform.basis_right,
        &sample->transform.basis_up);
}

static __forceinline void compute_direct_deltas(Path* path)
{
    int i;
    for (i = 0; i < path->segment_count; ++i) {
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
}

static __forceinline void build_direct_strip_mesh(
    Path* path,
    char* top_texture,
    char* bottom_texture,
    char* cap_texture)
{
    path->strip_mesh->request_object_facequads(
        2 * path->width_cells * path->segment_count);
    path->strip_mesh->request_object_vertices(
        (path->width_cells + 1) * (path->segment_count + 1));

    Vector3* vertices = path->strip_mesh->vertices;
    ObjectFaceQuad* facequads = path->strip_mesh->facequads;
    int row;
    int column;

    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            PathTemplateSample* sample = &path->primary_samples[row];
            float lateral = (float)column - (float)path->width_cells * 0.5f;
            Vector3* vertex = &vertices[column + row * (path->width_cells + 1)];
            Vector3 generated_position(
                sample->transform.position.x + lateral * sample->transform.basis_right.x,
                sample->transform.position.y + lateral * sample->transform.basis_right.y,
                sample->transform.position.z + lateral * sample->transform.basis_right.z);
            *vertex = generated_position;
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;
            char* top = row == path->segment_count - 1 ? cap_texture : top_texture;

            ObjectFaceQuad* a = &facequads[2 * (column + row * path->width_cells)];
            a->flags = 0;
            a->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
            a->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
            a->vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
            a->texture_ref = g_texture_refs.get_or_create_texture_ref(top, 0, 0);
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
            b->texture_ref = g_texture_refs.get_or_create_texture_ref(bottom_texture, 0, 0);
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

void Path::initialize_supertramp_path_template_pair(
    float length,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture,
    char* underside_texture)
{
    kind = 0x1f;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 1.0461504f);
    int last_segment_index = curve_segments + 7;
    width_or_scale = 1.0f;
    segment_count = last_segment_index + 1;
    segment_count_f = (float)last_segment_index;
    float radius = (float)curve_segments * 0.95588547f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;
    segment_count = segment_count - 1;

    int i;
    for (i = 0; i < 7; ++i)
        initialize_pair_sample(this, i, 0.0f, 0.0f, i);

    float secondary_radius = radius - 0.49000001f;
    for (i = 0; i <= curve_segments; ++i) {
        int sample_index = i + 7;
        float angle = (float)i * 1.0461504f / (float)curve_segments;
        PathTemplateSample* primary = &primary_samples[sample_index];
        PathTemplateSample* secondary = &secondary_samples[sample_index];

        primary->center_x = 0.0f;
        primary->rotation_scalar_98 = 0.0f;
        primary->rotation_scalar_94 = 0.0f;
        primary->special_scalar = 0.0f;
        primary->lateral_scale = 1.0f;
        set_matrix_identity(&primary->transform);
        primary->transform.position.x = 0.0f;
        primary->transform.position.z = sine(angle) * radius + 7.0f;
        primary->transform.position.y = radius - cosine(angle) * radius;

        secondary->center_x = 0.0f;
        secondary->rotation_scalar_98 = 0.0f;
        secondary->rotation_scalar_94 = 0.0f;
        secondary->special_scalar = 0.0f;
        secondary->lateral_scale = 1.0f;
        set_matrix_identity(&secondary->transform);
        secondary->transform.position.x = primary->center_x;
        secondary->transform.position.z = sine(angle) * secondary_radius + 7.0f;
        secondary->transform.position.y = radius - cosine(angle) * secondary_radius;
        orient_arc_sample(primary, radius);
        orient_arc_sample(secondary, radius);
    }

    compute_direct_deltas(this);
    build_direct_strip_mesh(this, texture_b, underside_texture, cap_texture);
    finalize_path_template(this);
    (void)side_exit;
    (void)texture_a;
}
