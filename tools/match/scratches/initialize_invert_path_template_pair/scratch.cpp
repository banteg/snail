// initialize_invert_path_template_pair @ 0x429250 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;


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

static __forceinline void copy_secondary_transform_from_primary(Path* path, int index)
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
    Path* path, char* texture_b, char* vertical_texture)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;

    int row = 0;
    int column;
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
                        Vector3 lateral_offset = sample->transform.basis_right * lateral;
                        Vector3 generated_position =
                            sample->transform.position + lateral_offset;
                        int vertex_index =
                            column + row * (path->width_cells + 1);
                        vertices[vertex_index] = generated_position;
                    } else {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples + sample_offset);
                        Vector3 lateral_offset = sample[-1].transform.basis_right * lateral;
                        Vector3 endpoint = sample[-1].transform.position
                            + Vector3(0.0f, 0.0f, 1.0f);
                        Vector3 generated_position = endpoint + lateral_offset;
                        int vertex_index =
                            column + row * (path->width_cells + 1);
                        vertices[vertex_index] = generated_position;
                    }
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row) {
        column = 0;
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            do {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;

                int face_index = 0;
                do {
                    int face_offset =
                        face_index
                        + 2 * (row * path->width_cells + column);
                    if (face_index == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_3 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (!((column ^ row) & 1)) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
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
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_1 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        if (!((column ^ row) & 1)) {
                            facequads[face_offset].texture_ref = g_texture_refs.Add(
                                vertical_texture, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref = g_texture_refs.Add(
                                vertical_texture, 0, 0);
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
                    ++face_index;
                } while (face_index < 2);
                ++column;
            } while (column < path->width_cells);
        }
    }
}

void cRPath::initialize_invert_path_template_pair(
    float radius, int width_cells_, bool side_exit,
    char* texture_a, char* texture_b, char* vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_INVERT;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 34;
    segment_count_f = 34.0f;
    GetNodes();

    has_entry_mesh_transition = 1;
    primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[0].transform);
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;
    primary_samples[0].delta_length = 1.0f;
    set_matrix_identity(&secondary_samples[0].transform);
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;
    secondary_samples[0].delta_length = 1.0f;

    primary_samples[33].center_x = 4.0f - (float)width_cells * 0.5f;
    primary_samples[33].rotation_scalar_98 = 3.1415927f;
    primary_samples[33].rotation_scalar_94 = 0.0f;
    primary_samples[33].special_scalar = 0.0f;
    primary_samples[33].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[33].transform);
    primary_samples[33].transform.position.x = primary_samples[33].center_x;
    primary_samples[33].transform.position.y = 0.0f;
    primary_samples[33].transform.position.z = 33.0f;
    primary_samples[33].delta_length = 1.0f;
    set_matrix_identity(&secondary_samples[33].transform);
    secondary_samples[33].transform.position.x = primary_samples[33].center_x;
    secondary_samples[33].transform.position.y = 0.49000001f;
    secondary_samples[33].transform.position.z = 33.0f;
    secondary_samples[33].delta_length = 1.0f;

    int sample_index = 1;
    int local_index = 0;
    do {
        float t = (float)local_index;
        float angle = t * 0.19634955f;

        primary_samples[sample_index].center_x =
            (primary_samples[33].center_x - primary_samples[0].center_x) *
                t * 0.03125f +
            primary_samples[0].center_x;
        primary_samples[sample_index].rotation_scalar_98 = angle * 0.5f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[sample_index].transform);

        float z_position = (float)(local_index + 1);
        primary_samples[sample_index].transform.position.x = 0.0f;
        primary_samples[sample_index].transform.position.z = z_position;
        primary_samples[sample_index].transform.position.y = 0.0f;

        float basis_y = Cos(angle);
        float basis_x = Sin(angle);
        primary_samples[sample_index].transform.basis_up =
            Vector3(basis_x, basis_y, 0.0f);
        primary_samples[sample_index].transform.basis_forward =
            primary_samples[sample_index].transform.position -
            primary_samples[sample_index - 1].transform.position;
        primary_samples[sample_index].transform.basis_forward.Normalize();
        primary_samples[sample_index].transform.basis_right.cross_vectors(
            &primary_samples[sample_index].transform.basis_up,
            &primary_samples[sample_index].transform.basis_forward);

        secondary_samples[sample_index].transform =
            primary_samples[sample_index].transform;
        ++local_index;
        Vector3 secondary_offset =
            primary_samples[sample_index].transform.basis_up * 0.49000001f;
        Vector3* secondary_position =
            &secondary_samples[sample_index].transform.position;
        secondary_position->x += secondary_offset.x;
        secondary_position->y += secondary_offset.y;
        secondary_position->z += secondary_offset.z;
        ++sample_index;
    } while (sample_index < 33);

    compute_path_deltas(this);
    build_strip_mesh(this, texture_b, vertical_texture);
    CalcLengthZ();
    (void)radius;
    (void)side_exit;
    (void)vertical_texture;
}
