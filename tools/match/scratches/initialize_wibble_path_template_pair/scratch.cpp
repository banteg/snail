// initialize_wibble_path_template_pair @ 0x4289a0 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

void __fastcall finalize_path_template(Path* path);

static __forceinline void initialize_sample(
    PathTemplateSample* sample, float center_x, float x, float y, float z)
{
    sample->center_x = center_x;
    sample->rotation_scalar_98 = 0.0f;
    sample->rotation_scalar_94 = 0.0f;
    sample->special_scalar = 0.0f;
    sample->lateral_scale = 1.0f;
    set_matrix_identity(&sample->transform);
    sample->transform.position.x = x;
    sample->transform.position.y = y;
    sample->transform.position.z = z;
}

static __forceinline void copy_secondary_from_primary(Path* path, int index)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    secondary->center_x = primary->center_x;
    secondary->rotation_scalar_98 = primary->rotation_scalar_98;
    secondary->rotation_scalar_94 = primary->rotation_scalar_94;
    secondary->special_scalar = primary->special_scalar;
    secondary->lateral_scale = primary->lateral_scale;
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

    PathTemplateSample* primary_last = &path->primary_samples[path->segment_count - 1];
    primary_last->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_last->delta_length = 1.0f;

    PathTemplateSample* secondary_last = &path->secondary_samples[path->segment_count - 1];
    secondary_last->delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_last->delta_length = 1.0f;
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

            int face_index;
            for (face_index = 0; face_index < 2; ++face_index) {
                ObjectFaceQuad* face =
                    &facequads[2 * column + 2 * row * path->width_cells + face_index];
                face->flags = 0;
                if (face_index == 0) {
                    face->vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    face->vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    face->vertex_2 =
                        (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
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
                    face->vertex_3 =
                        (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
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

void Path::initialize_wibble_path_template_pair(
    float radius, int width_cells_, int side_exit,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = 0x28;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 32;
    segment_count_f = 32.0f;
    allocate_path_template_samples();

    has_entry_mesh_transition = 0;
    initialize_sample(
        &primary_samples[0], (float)width_cells * 0.5f - 4.0f,
        (float)width_cells * 0.5f - 4.0f, 0.0f, 0.0f);
    copy_secondary_from_primary(this, 0);
    initialize_sample(
        &primary_samples[31], 4.0f - (float)width_cells * 0.5f,
        4.0f - (float)width_cells * 0.5f, 0.0f, 31.0f);
    copy_secondary_from_primary(this, 31);

    for (int i = 1; i < 31; ++i) {
        float local_index = (float)(i - 1);
        float center = primary_samples[0].center_x
            + (primary_samples[31].center_x - primary_samples[0].center_x)
                * local_index * 0.033333335f;
        float turn_phase = local_index * 0.20943952f;
        float roll_phase = turn_phase * 3.0f;
        initialize_sample(&primary_samples[i], center, 0.0f, 0.0f, (float)i);
        float basis_y = cosine(sine(roll_phase) * 0.30000001f);
        float basis_x = sine(sine(roll_phase) * 0.30000001f);
        primary_samples[i].transform.basis_up.x = basis_x;
        primary_samples[i].transform.basis_up.y = basis_y;
        primary_samples[i].transform.basis_up.z = 0.0f;
        copy_secondary_from_primary(this, i);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    finalize_path_template(this);
}
