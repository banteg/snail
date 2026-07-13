// initialize_looptheloopw_path_template_pair @ 0x41bb40 (thiscall, ret 0x18)

#define PATH_FUNCTION initialize_looptheloopw_path_template_pair
#define PATH_SIGNATURE float curve_source, int width_cells_, int side_exit, char* texture_a, char* texture_b, char* cap_texture
#define PATH_CURVE_COUNT ((int)(curve_source * 6.2831855f))
#define PATH_HEIGHT_SCALE 1.0f
#define PATH_VARIANT 1

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathAttachmentSample;

typedef ObjectFaceQuad PathTemplateFaceQuad;


static inline void initialize_sample_pair(
    PathAttachmentSample* primary,
    PathAttachmentSample* secondary,
    float center_x,
    float primary_y,
    float secondary_y,
    float z,
    int seed_delta_length)
{
    primary->center_x = center_x;
    primary->rotation_scalar_98 = 0.0f;
    primary->rotation_scalar_94 = 0.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_scale = 1.0f;
    set_matrix_identity(&primary->transform);
    primary->transform.position.x = primary->center_x;
    primary->transform.position.y = primary_y;
    primary->transform.position.z = z;
    if (seed_delta_length)
        primary->delta_length = 1.0f;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = primary->center_x;
    secondary->transform.position.y = secondary_y;
    secondary->transform.position.z = z;
    if (seed_delta_length)
        secondary->delta_length = 1.0f;
}

static inline void orient_loop_sample(
    PathAttachmentSample* sample,
    float up_y,
    float up_z)
{
    sample->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    sample->transform.basis_up = Vector3(0.0f, up_y, up_z);
    sample->transform.basis_up.normalize_vector();
    sample->transform.basis_forward.cross_vectors(
        &sample->transform.basis_right,
        &sample->transform.basis_up);
}

static inline void orient_previous_with_fixed_right(
    PathAttachmentSample* previous,
    PathAttachmentSample* next)
{
    previous->transform.basis_right = Vector3(1.0f, 0.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        next->transform.position.x - previous->transform.position.x,
        next->transform.position.y - previous->transform.position.y,
        next->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.normalize_vector();
    previous->transform.basis_up.cross_vectors(
        &previous->transform.basis_forward,
        &previous->transform.basis_right);
}

static inline void orient_previous_with_fixed_up(
    PathAttachmentSample* previous,
    PathAttachmentSample* next,
    float up_x,
    float up_y,
    float up_z,
    float roll)
{
    previous->transform.basis_up = Vector3(up_x, up_y, up_z);
    previous->transform.basis_forward = Vector3(
        next->transform.position.x - previous->transform.position.x,
        next->transform.position.y - previous->transform.position.y,
        next->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.normalize_vector();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
    if (roll != 0.0f)
        previous->transform.rotate_matrix_world_z(roll);
}

void Path::PATH_FUNCTION(PATH_SIGNATURE)
{
    int curve_count = PATH_CURVE_COUNT;
    float height_scale_value = PATH_HEIGHT_SCALE;
    int i;

    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;

#if PATH_VARIANT == 0 || PATH_VARIANT == 1
    float loop_wiggle = 0.0f;
    kind = 0x00;
    if (width_cells_ == 4) {
#if PATH_VARIANT == 1
        kind = 0x06;
#else
        kind = 0x00;
#endif
        loop_wiggle = 0.30000001f;
    }
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 1;

    for (i = 0; i < 7; ++i) {
        float z = (float)i;
        float center = (float)width_cells * 0.5f - 4.0f
            - z * 0.14285715f * loop_wiggle;
        initialize_sample_pair(
            &primary_samples[i],
            &secondary_samples[i],
            center,
            0.0f,
            0.49000001f,
            z,
            1);
    }

    for (i = 0; i < 7; ++i) {
        int sample_index = curve_count + 7 + i;
        float z = (float)(i + 7);
        float center = (1.0f - (float)i * 0.16666667f) * loop_wiggle
            + 4.0f - (float)width_cells * 0.5f;
        initialize_sample_pair(
            &primary_samples[sample_index],
            &secondary_samples[sample_index],
            center,
            0.0f,
            0.49000001f,
            z,
            1);
    }

    if (curve_count > 0) {
        float secondary_radius = loop_radius - 0.49000001f;
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 7;
            float sample_f = (float)i;
            float angle = sample_f * 6.2831855f / curve_count_f;
#if PATH_VARIANT == 1
            float roll = sine(angle * 0.5f) * sine(angle * 8.0f) * 0.39269909f;
#endif
            float center = (primary_samples[curve_count + 7].center_x
                    - primary_samples[0].center_x)
                * sample_f / curve_count_f + primary_samples[0].center_x;
            center += sine(angle * 0.5f + 4.712389f) * loop_wiggle;

            primary_samples[sample_index].center_x = center;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                sine(angle) * loop_radius + 7.0f;
            primary_samples[sample_index].transform.position.y =
                loop_radius - cosine(angle) * loop_radius;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                sine(angle) * secondary_radius + 7.0f;
            secondary_samples[sample_index].transform.position.y =
                loop_radius - cosine(angle) * secondary_radius;

            orient_loop_sample(
                &primary_samples[sample_index],
                loop_radius - primary_samples[sample_index].transform.position.y,
                7.0f - primary_samples[sample_index].transform.position.z);
            orient_loop_sample(
                &secondary_samples[sample_index],
                loop_radius - secondary_samples[sample_index].transform.position.y,
                7.0f - secondary_samples[sample_index].transform.position.z);

#if PATH_VARIANT == 1
            primary_samples[sample_index].transform.rotate_matrix_world_z(roll);
            secondary_samples[sample_index].transform.rotate_matrix_world_z(roll);
#endif
        }
    }
#elif PATH_VARIANT == 2
    kind = 0x19;
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 1;

    for (i = 0; i < 10; ++i) {
        float z = (float)i;
        float center = (float)width_cells * 0.5f - 4.0f
            - z * 0.11111111f * 0.30000001f;
        initialize_sample_pair(
            &primary_samples[i],
            &secondary_samples[i],
            center,
            0.0f,
            0.49000001f,
            z,
            1);
    }

    for (i = 0; i < 4; ++i) {
        int sample_index = curve_count + 10 + i;
        float z = (float)(i + 10);
        float center = (1.0f - (float)i * 0.33333334f) * 0.30000001f
            + 4.0f - (float)width_cells * 0.5f;
        initialize_sample_pair(
            &primary_samples[sample_index],
            &secondary_samples[sample_index],
            center,
            0.0f,
            0.49000001f,
            z,
            1);
    }

    if (curve_count > 0) {
        float center_y = -loop_radius;
        float secondary_radius = loop_radius + 0.49000001f;
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 10;
            float sample_f = (float)i;
            float angle = sample_f * 6.2831855f / curve_count_f;
            float center = (primary_samples[curve_count + 10].center_x
                    - primary_samples[0].center_x)
                * sample_f / curve_count_f + primary_samples[0].center_x;
            center += sine(angle * 0.5f + 4.712389f) * 0.30000001f;

            primary_samples[sample_index].center_x = center;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                sine(angle) * loop_radius + 10.0f;
            primary_samples[sample_index].transform.position.y =
                cosine(angle) * loop_radius + center_y;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                sine(angle) * secondary_radius + 10.0f;
            secondary_samples[sample_index].transform.position.y =
                cosine(angle) * secondary_radius + center_y;

            orient_loop_sample(
                &primary_samples[sample_index],
                primary_samples[sample_index].transform.position.y - center_y,
                primary_samples[sample_index].transform.position.z - 10.0f);
            orient_loop_sample(
                &secondary_samples[sample_index],
                secondary_samples[sample_index].transform.position.y - center_y,
                secondary_samples[sample_index].transform.position.z - 10.0f);
        }
    }
#elif PATH_VARIANT == 3 || PATH_VARIANT == 4
#if PATH_VARIANT == 3
    kind = 0x10;
    float vertical_sign = 1.0f;
    float start_center = (float)width_cells * 0.5f - 4.0f;
    float end_center = 4.0f - (float)width_cells * 0.5f;
#else
    kind = 0x11;
    float vertical_sign = -1.0f;
    float start_center = -(float)width_cells * 0.5f + 4.0f;
    float end_center = (float)width_cells * 0.5f - 4.0f;
#endif
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float hump_radius = curve_count_f * 0.095492966f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    for (i = 0; i < 7; ++i) {
        initialize_sample_pair(
            &primary_samples[i],
            &secondary_samples[i],
            start_center,
            0.0f,
            0.49000001f,
            (float)i,
            0);
    }

    for (i = 0; i < 7; ++i) {
        int sample_index = curve_count + 7 + i;
        initialize_sample_pair(
            &primary_samples[sample_index],
            &secondary_samples[sample_index],
            end_center,
            0.0f,
            0.49000001f,
            (float)(curve_count + 7 + i),
            0);
    }

    if (curve_count > 0) {
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 7;
            float angle = (float)i * 6.2831855f / curve_count_f;
            float y = vertical_sign
                * (1.0f - cosine(angle)) * hump_radius * height_scale_value;
            float center = cosine(angle * 0.5f) * start_center;
            initialize_sample_pair(
                &primary_samples[sample_index],
                &secondary_samples[sample_index],
                center,
                y,
                y + 0.49000001f,
                (float)(i + 7),
                0);
            if (sample_index <= 7) {
                primary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
                secondary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
            } else {
                orient_previous_with_fixed_right(
                    &primary_samples[sample_index - 1],
                    &primary_samples[sample_index]);
                orient_previous_with_fixed_right(
                    &secondary_samples[sample_index - 1],
                    &secondary_samples[sample_index]);
            }
        }
    }
#elif PATH_VARIANT == 5
    kind = 0x14;
    segment_count = curve_count + 2;
    segment_count_f = (float)(curve_count + 2);
    float curve_count_f = (float)curve_count;
    float dip_radius = curve_count_f * 0.047746483f;
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    initialize_sample_pair(
        &primary_samples[0],
        &secondary_samples[0],
        0.0f,
        0.0f,
        0.49000001f,
        0.0f,
        0);
    initialize_sample_pair(
        &primary_samples[curve_count + 1],
        &secondary_samples[curve_count + 1],
        0.0f,
        0.0f,
        0.49000001f,
        (float)(curve_count + 1),
        0);

    if (curve_count > 0) {
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 1;
            float angle = (float)i * 6.2831855f / curve_count_f;
            float y = -((1.0f - cosine(angle)) * dip_radius);
            initialize_sample_pair(
                &primary_samples[sample_index],
                &secondary_samples[sample_index],
                0.0f,
                y,
                y + 0.49000001f,
                (float)(i + 1),
                0);
            if (sample_index <= 1) {
                primary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
                secondary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
            } else {
                orient_previous_with_fixed_right(
                    &primary_samples[sample_index - 1],
                    &primary_samples[sample_index]);
                orient_previous_with_fixed_right(
                    &secondary_samples[sample_index - 1],
                    &secondary_samples[sample_index]);
            }
        }
    }
#elif PATH_VARIANT == 6
    kind = 0x15;
    segment_count = curve_count + 8;
    segment_count_f = (float)(curve_count + 8);
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    for (i = 0; i < 3; ++i) {
        initialize_sample_pair(
            &primary_samples[i],
            &secondary_samples[i],
            0.5f,
            0.0f,
            0.49000001f,
            (float)i,
            0);
    }

    for (i = 0; i < 5; ++i) {
        int sample_index = curve_count + 3 + i;
        initialize_sample_pair(
            &primary_samples[sample_index],
            &secondary_samples[sample_index],
            -0.5f,
            0.0f,
            0.49000001f,
            (float)(curve_count + 3 + i),
            0);
    }

    if (curve_count > 0) {
        float curve_count_f = (float)curve_count;
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 3;
            float angle = (float)i * 6.2831855f / curve_count_f;
            float center = cosine(angle * 0.5f) * 0.5f;
            initialize_sample_pair(
                &primary_samples[sample_index],
                &secondary_samples[sample_index],
                center,
                0.0f,
                cosine(angle) * 0.49000001f,
                (float)(i + 3),
                0);
            primary_samples[sample_index].rotation_scalar_94 = angle;
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x - sine(angle) * 0.49000001f;
            if (sample_index <= 3) {
                primary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
                secondary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
            } else {
                float up_x = -sine(angle);
                float up_y = cosine(angle);
                orient_previous_with_fixed_up(
                    &primary_samples[sample_index - 1],
                    &primary_samples[sample_index],
                    up_x,
                    up_y,
                    0.0f,
                    0.0f);
                orient_previous_with_fixed_up(
                    &secondary_samples[sample_index - 1],
                    &secondary_samples[sample_index],
                    up_x,
                    up_y,
                    0.0f,
                    0.0f);
            }
        }
    }
#elif PATH_VARIANT == 7
    kind = 0x16;
    segment_count = curve_count + 8;
    segment_count_f = (float)(curve_count + 8);
    allocate_path_template_samples();
    has_entry_mesh_transition = 0;

    for (i = 0; i < 4; ++i) {
        initialize_sample_pair(
            &primary_samples[i],
            &secondary_samples[i],
            0.0f,
            0.0f,
            0.49000001f,
            (float)i,
            0);
    }

    for (i = 0; i < 4; ++i) {
        int sample_index = curve_count + 4 + i;
        initialize_sample_pair(
            &primary_samples[sample_index],
            &secondary_samples[sample_index],
            0.0f,
            0.0f,
            0.49000001f,
            (float)(curve_count + 4 + i),
            0);
    }

    if (curve_count > 0) {
        float curve_count_f = (float)curve_count;
        for (i = 0; i < curve_count; ++i) {
            int sample_index = i + 4;
            float t = (float)i / curve_count_f;
            float angle = t * 6.2831855f;
            float falloff = t - 0.5f;
            if (falloff < 0.0f)
                falloff = -falloff;
            float center = sine(angle) * (1.0f - falloff) * (1.0f - falloff) * 5.0f;
            initialize_sample_pair(
                &primary_samples[sample_index],
                &secondary_samples[sample_index],
                center,
                0.0f,
                0.49000001f,
                (float)(i + 4),
                0);
            if (sample_index <= 4) {
                primary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
                secondary_samples[sample_index - 1].transform.set_matrix_rotation_identity();
            } else {
                float roll = primary_samples[sample_index - 1].center_x * 0.2617994f;
                orient_previous_with_fixed_up(
                    &primary_samples[sample_index - 1],
                    &primary_samples[sample_index],
                    0.0f,
                    1.0f,
                    0.0f,
                    roll);
                orient_previous_with_fixed_up(
                    &secondary_samples[sample_index - 1],
                    &secondary_samples[sample_index],
                    0.0f,
                    1.0f,
                    0.0f,
                    roll);
            }
        }
    }
#endif

    if (segment_count - 1 > 0) {
        for (i = 0; i < segment_count - 1; ++i) {
            primary_samples[i].delta_dir_to_next = Vector3(
                primary_samples[i + 1].transform.position.x
                    - primary_samples[i].transform.position.x,
                primary_samples[i + 1].transform.position.y
                    - primary_samples[i].transform.position.y,
                primary_samples[i + 1].transform.position.z
                    - primary_samples[i].transform.position.z);
            primary_samples[i].delta_length =
                primary_samples[i].delta_dir_to_next.normalize_vector();

            secondary_samples[i].delta_dir_to_next = Vector3(
                secondary_samples[i + 1].transform.position.x
                    - secondary_samples[i].transform.position.x,
                secondary_samples[i + 1].transform.position.y
                    - secondary_samples[i].transform.position.y,
                secondary_samples[i + 1].transform.position.z
                    - secondary_samples[i].transform.position.z);
            secondary_samples[i].delta_length =
                secondary_samples[i].delta_dir_to_next.normalize_vector();
        }
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->request_object_vertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->request_object_facequads(2 * width_cells * segment_count);

    Vector3* vertices = strip_mesh->vertices;
    PathTemplateFaceQuad* facequads = (PathTemplateFaceQuad*)strip_mesh->facequads;

    int mesh_row;
    int mesh_column;
    int face_row;
    int face_column;
    int face_index;

    for (mesh_row = 0; mesh_row <= segment_count; ++mesh_row) {
        for (mesh_column = 0; mesh_column <= width_cells; ++mesh_column) {
            float lateral = (float)mesh_column - (float)width_cells * 0.5f;
            Vector3* vertex = &vertices[mesh_column + mesh_row * (width_cells + 1)];
            if (mesh_row == segment_count) {
                PathAttachmentSample* previous = &primary_samples[mesh_row - 1];
                vertex->x = previous->transform.position.x
                    + lateral * previous->transform.basis_right.x;
                vertex->y = previous->transform.position.y
                    + lateral * previous->transform.basis_right.y;
                vertex->z = previous->transform.position.z + 1.0f
                    + lateral * previous->transform.basis_right.z;
            } else {
                PathAttachmentSample* sample = &primary_samples[mesh_row];
                vertex->x = sample->transform.position.x
                    + lateral * sample->transform.basis_right.x;
                vertex->y = sample->transform.position.y
                    + lateral * sample->transform.basis_right.y;
                vertex->z = sample->transform.position.z
                    + lateral * sample->transform.basis_right.z;
            }
        }
    }

    for (face_row = 0; face_row < segment_count; ++face_row) {
        if (width_cells > 0) {
            float v0 = (float)(face_row % 8) * 0.125f;
            float v1 = (float)(face_row % 8 + 1) * 0.125f;
            for (face_column = 0; face_column < width_cells; ++face_column) {
                float u0 = (float)face_column * 0.125f;
                float u1 = (float)(face_column + 1) * 0.125f;
                for (face_index = 0; face_index < 2; ++face_index) {
                    PathTemplateFaceQuad* face =
                        &facequads[2 * face_column + 2 * face_row * width_cells + face_index];
                    face->header_word = 0;
                    if (face_index == 0) {
                        face->vertex_0 = face_column + face_row * ((unsigned short)width_cells + 1);
                        face->vertex_1 = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        face->vertex_2 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        face->vertex_3 =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        face->texture_ref =
                            g_texture_refs.get_or_create_texture_ref(texture_a, 0, 0);
                        face->uv[0].u = u0;
                        face->uv[0].v = v0;
                        face->uv[1].u = u1;
                        face->uv[1].v = v0;
                        face->uv[2].u = u1;
                        face->uv[2].v = v1;
                        face->uv[3].u = u0;
                    } else {
                        face->vertex_0 = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        face->vertex_1 = face_column + face_row * ((unsigned short)width_cells + 1);
                        face->vertex_2 =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        face->vertex_3 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        face->texture_ref =
                            g_texture_refs.get_or_create_texture_ref(texture_b, 0, 0);
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

    finalize_path_template();
    (void)side_exit;
    (void)cap_texture;
}
