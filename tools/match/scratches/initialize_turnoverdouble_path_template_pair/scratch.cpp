// initialize_turnoverdouble_path_template_pair @ 0x427640 (thiscall, ret 0x18)

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
    primary->delta_length = 1.0f;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
    secondary->delta_length = 1.0f;
}

static __forceinline void orient_turnover_sample(
    PathTemplateSample* sample, PathTemplateSample* previous, float angle)
{
    sample->transform.basis_up = Vector3(sine(angle), cosine(angle), 0.0f);
    sample->transform.basis_forward = Vector3(
        sample->transform.position.x - previous->transform.position.x,
        sample->transform.position.y - previous->transform.position.y,
        sample->transform.position.z - previous->transform.position.z);
    sample->transform.basis_forward.normalize_vector();
    sample->transform.basis_right.cross_vectors(
        &sample->transform.basis_up,
        &sample->transform.basis_forward);
}

static __forceinline void copy_secondary_from_primary(PathTemplateSample* secondary, PathTemplateSample* primary)
{
    secondary->transform = primary->transform;
    secondary->transform.position.x += primary->transform.basis_up.x * 0.49000001f;
    secondary->transform.position.y += primary->transform.basis_up.y * 0.49000001f;
    secondary->transform.position.z += primary->transform.basis_up.z * 0.49000001f;
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
    int face_index;

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

void Path::initialize_turnoverdouble_path_template_pair(
    float length,
    int width_cells_,
    int side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = 0x26;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 9.424778f);
    width_or_scale = 1.0f;
    segment_count = curve_segments + 8;
    segment_count_f = (float)(curve_segments + 8);
    float radius = (float)curve_segments * 0.079577468f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    float left = (float)width_cells * 0.5f - 4.0f;

    int i;
    for (i = 0; i < 6; ++i)
        initialize_pair_sample(this, i, left, 0.0f, (float)i);

    for (i = curve_segments + 6; i < curve_segments + 8; ++i)
        initialize_pair_sample(this, i, left, 0.0f, (float)i);

    for (i = 0; i < curve_segments; ++i) {
        float t = (float)i;
        float slalom_angle = t * 6.2831855f / (float)curve_segments;
        float roll_angle = t * 12.566371f / (float)curve_segments;
        if (roll_angle > 6.2831855f)
            roll_angle = 12.566371f - roll_angle;

        int sample_index = i + 6;
        PathTemplateSample* sample = &primary_samples[sample_index];
        float half = roll_angle * 0.5f;

        sample->center_x = sine(slalom_angle + 1.5707964f) * left;
        sample->rotation_scalar_98 = -roll_angle;
        sample->rotation_scalar_94 = 0.0f;
        sample->special_scalar = 0.0f;
        sample->lateral_scale = 1.0f;
        set_matrix_identity(&sample->transform);
        sample->transform.position.x = sample->center_x - (sine(roll_angle) * sine(half) + sine(roll_angle) * sine(half));
        sample->transform.position.y = (radius - cosine(roll_angle) * radius) * 0.40000001f;
        sample->transform.position.z = (float)sample_index;
        orient_turnover_sample(sample, &primary_samples[sample_index - 1], roll_angle);
        copy_secondary_from_primary(&secondary_samples[sample_index], sample);
    }

    compute_terminal_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template(this);
    (void)side_exit;
    (void)cap_texture;
}
