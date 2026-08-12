// Shared source skeleton for the macro-configured path-template builders.
// The including scratch supplies PATH_FUNCTION, PATH_SIGNATURE,
// PATH_CURVE_COUNT, PATH_HEIGHT_SCALE, and PATH_VARIANT.

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathAttachmentSample;

#ifndef PATH_FACE_OWNER_MODE
#define PATH_FACE_OWNER_MODE 0
#endif

#ifndef PATH_VERTEX_OWNER_MODE
#define PATH_VERTEX_OWNER_MODE 0
#endif

#ifndef PATH_LOOP_SEGMENT_OWNER_MODE
#define PATH_LOOP_SEGMENT_OWNER_MODE 0
#endif

#ifndef PATH_LOOP_ENDPOINT_MODE
#define PATH_LOOP_ENDPOINT_MODE 0
#endif

#ifndef PATH_LOOP_CURVE_CONTROL_MODE
#define PATH_LOOP_CURVE_CONTROL_MODE 0
#endif

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
    sample->transform.basis_up.Normalize();
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
    previous->transform.basis_forward.Normalize();
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
    previous->transform.basis_forward.Normalize();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
    if (roll != 0.0f)
        previous->transform.RotLocalZ(roll);
}

void cRPath::PATH_FUNCTION(PATH_SIGNATURE)
{
    int curve_count;
    float height_scale_value = PATH_HEIGHT_SCALE;
    int i;

#if PATH_VARIANT == 0 || PATH_VARIANT == 1
#if PATH_VARIANT == 1
    kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    float loop_wiggle = 0.0f;
#else
    kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    float loop_wiggle = 0.0f;
#endif
    if (width_cells_ == 4) {
#if PATH_VARIANT == 1
        kind = PATH_TEMPLATE_KIND_LOOPTHELOOPW;
#else
        kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
#endif
        loop_wiggle = 0.30000001f;
    }
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    curve_count = PATH_CURVE_COUNT;
    width_or_scale = 1.0f;
#if PATH_LOOP_SEGMENT_OWNER_MODE == 1
    int loop_segment_count = curve_count + 14;
    segment_count = loop_segment_count;
    segment_count_f = (float)loop_segment_count;
#else
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
#endif
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    GetNodes();
    has_entry_mesh_transition = 1;

    for (i = 0; i < 7; ++i) {
        float z = (float)i;
        primary_samples[i].center_x = (float)width_cells * 0.5f - 4.0f
            - z * 0.14285715f * loop_wiggle;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        primary_samples[i].transform.Identity();
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;
        primary_samples[i].delta_length = 1.0f;

        secondary_samples[i].transform.Identity();
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
        secondary_samples[i].delta_length = 1.0f;
    }

    for (i = 0; i < 7; ++i) {
        int sample_index = curve_count + 7 + i;
        primary_samples[sample_index].center_x =
            (1.0f - (float)i * 0.16666667f) * loop_wiggle
            + (4.0f - (float)width_cells * 0.5f);
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        primary_samples[sample_index].transform.Identity();
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        primary_samples[sample_index].transform.position.y = 0.0f;
        primary_samples[sample_index].transform.position.z = (float)(i + 7);
        primary_samples[sample_index].delta_length = 1.0f;

        secondary_samples[sample_index].transform.Identity();
        secondary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        secondary_samples[sample_index].transform.position.y = 0.49000001f;
        secondary_samples[sample_index].transform.position.z = (float)(i + 7);
        secondary_samples[sample_index].delta_length = 1.0f;
    }

#if PATH_LOOP_CURVE_CONTROL_MODE != 0
    i = 0;
#endif
    if (curve_count > 0) {
        float secondary_radius = loop_radius - 0.49000001f;
#if PATH_LOOP_CURVE_CONTROL_MODE != 0
        do {
#else
        for (i = 0; i < curve_count; ++i) {
#endif
            int sample_index = i + 7;
            float sample_f = (float)i;
            float angle = sample_f * 6.2831855f / curve_count_f;
#if PATH_VARIANT == 1
            float roll = sine(angle * 0.5f) * sine(angle * 8.0f) * 0.39269909f;
#endif
            primary_samples[sample_index].center_x =
#if PATH_LOOP_ENDPOINT_MODE == 2
                (primary_samples[loop_segment_count - 1].center_x
#elif PATH_LOOP_ENDPOINT_MODE == 1
                (primary_samples[curve_count + 13].center_x
#else
                (primary_samples[curve_count + 7].center_x
#endif
                    - primary_samples[0].center_x)
                * sample_f / curve_count_f + primary_samples[0].center_x;
            primary_samples[sample_index].center_x +=
                sine(angle * 0.5f + 4.712389f) * loop_wiggle;
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

            primary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            primary_samples[sample_index].transform.basis_up.x = 0.0f;
            primary_samples[sample_index].transform.basis_up.y =
                loop_radius - primary_samples[sample_index].transform.position.y;
            primary_samples[sample_index].transform.basis_up.z =
                7.0f - primary_samples[sample_index].transform.position.z;
            primary_samples[sample_index].transform.basis_up.Normalize();
            primary_samples[sample_index].transform.basis_forward.cross_vectors(
                &primary_samples[sample_index].transform.basis_right,
                &primary_samples[sample_index].transform.basis_up);
#if PATH_VARIANT == 1
            primary_samples[sample_index].transform.RotLocalZ(roll);
#endif

            secondary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            secondary_samples[sample_index].transform.basis_up.x = 0.0f;
            secondary_samples[sample_index].transform.basis_up.y =
                loop_radius - secondary_samples[sample_index].transform.position.y;
            secondary_samples[sample_index].transform.basis_up.z =
                7.0f - secondary_samples[sample_index].transform.position.z;
            secondary_samples[sample_index].transform.basis_up.Normalize();
            secondary_samples[sample_index].transform.basis_forward.cross_vectors(
                &secondary_samples[sample_index].transform.basis_right,
                &secondary_samples[sample_index].transform.basis_up);

#if PATH_VARIANT == 1
            secondary_samples[sample_index].transform.RotLocalZ(roll);
#endif
#if PATH_LOOP_CURVE_CONTROL_MODE == 1
            ++i;
        } while (i < curve_count);
#elif PATH_LOOP_CURVE_CONTROL_MODE == 2
            ++i;
        } while (i != curve_count);
#elif PATH_LOOP_CURVE_CONTROL_MODE == 3
        } while (++i < curve_count);
#elif PATH_LOOP_CURVE_CONTROL_MODE == 4
        } while (++i != curve_count);
#else
        }
#endif
    }
#elif PATH_VARIANT == 2
    kind = PATH_TEMPLATE_KIND_LOOPOUT;
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    GetNodes();
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
    kind = PATH_TEMPLATE_KIND_FAMILY_10;
    float vertical_sign = 1.0f;
    float start_center = (float)width_cells * 0.5f - 4.0f;
    float end_center = 4.0f - (float)width_cells * 0.5f;
#else
    kind = PATH_TEMPLATE_KIND_FAMILY_11;
    float vertical_sign = -1.0f;
    float start_center = -(float)width_cells * 0.5f + 4.0f;
    float end_center = (float)width_cells * 0.5f - 4.0f;
#endif
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float hump_radius = curve_count_f * 0.095492966f;
    GetNodes();
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
                primary_samples[sample_index - 1].transform.RotIdentity();
                secondary_samples[sample_index - 1].transform.RotIdentity();
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
    kind = PATH_TEMPLATE_KIND_DIP;
    segment_count = curve_count + 2;
    segment_count_f = (float)(curve_count + 2);
    float curve_count_f = (float)curve_count;
    float dip_radius = curve_count_f * 0.047746483f;
    GetNodes();
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
                primary_samples[sample_index - 1].transform.RotIdentity();
                secondary_samples[sample_index - 1].transform.RotIdentity();
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
    kind = PATH_TEMPLATE_KIND_SCREW;
    segment_count = curve_count + 8;
    segment_count_f = (float)(curve_count + 8);
    GetNodes();
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
                primary_samples[sample_index - 1].transform.RotIdentity();
                secondary_samples[sample_index - 1].transform.RotIdentity();
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
    kind = PATH_TEMPLATE_KIND_SLALOM;
    segment_count = curve_count + 8;
    segment_count_f = (float)(curve_count + 8);
    GetNodes();
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
                primary_samples[sample_index - 1].transform.RotIdentity();
                secondary_samples[sample_index - 1].transform.RotIdentity();
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
        i = 0;
        do {
            primary_samples[i].delta_dir_to_next =
                primary_samples[i + 1].transform.position -
                primary_samples[i].transform.position;
            primary_samples[i].delta_length =
                primary_samples[i].delta_dir_to_next.Normalize();

            secondary_samples[i].delta_dir_to_next =
                secondary_samples[i + 1].transform.position -
                secondary_samples[i].transform.position;
            secondary_samples[i].delta_length =
                secondary_samples[i].delta_dir_to_next.Normalize();
            ++i;
        } while (i < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    Vector3* vertices = strip_mesh->vertices;
    cRFaceQuad* facequads = strip_mesh->facequads;

    int mesh_row;
    int mesh_column;
    int face_row;
    int face_column;
    int face_index;

    for (mesh_row = 0; mesh_row <= segment_count; ++mesh_row) {
        for (mesh_column = 0; mesh_column <= width_cells; ++mesh_column) {
#if PATH_MESH_LATERAL_MODE == 1
            double lateral =
                (float)mesh_column - (float)width_cells * 0.5f;
#elif PATH_MESH_LATERAL_MODE == 2
            float half_width = (float)width_cells * 0.5f;
            float lateral = (float)mesh_column - half_width;
#elif PATH_MESH_LATERAL_MODE == 3
            double lateral =
                (double)mesh_column - (double)width_cells * 0.5;
#elif PATH_MESH_LATERAL_MODE == 4
            volatile float lateral =
                (float)mesh_column - (float)width_cells * 0.5f;
#else
            float lateral =
                (float)mesh_column - (float)width_cells * 0.5f;
#endif
#if PATH_VERTEX_OWNER_MODE == 1
            int vertex_index =
                mesh_column + mesh_row * (width_cells + 1);
#endif
            if (mesh_row != segment_count) {
                PathAttachmentSample* sample = &primary_samples[mesh_row];
#if PATH_MESH_ORDINARY_SCALE_OPERATOR
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
#else
                Vector3 lateral_offset(
                    lateral * sample->transform.basis_right.x,
                    lateral * sample->transform.basis_right.y,
                    lateral * sample->transform.basis_right.z);
#endif
#if PATH_MESH_ORDINARY_ADD_ORDER == 1
                Vector3 generated_position =
                    sample->transform.position + lateral_offset;
#elif PATH_MESH_ORDINARY_ADD_ORDER == 2
                Vector3 generated_position =
                    lateral_offset + sample->transform.position;
#else
                Vector3 generated_position(
                    sample->transform.position.x + lateral_offset.x,
                    sample->transform.position.y + lateral_offset.y,
                    sample->transform.position.z + lateral_offset.z);
#endif
#if PATH_VERTEX_OWNER_MODE == 1
                vertices[vertex_index] = generated_position;
#else
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
#endif
            } else {
                PathAttachmentSample* previous = &primary_samples[mesh_row - 1];
#if PATH_MESH_TERMINAL_SCALE_OPERATOR
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
#else
                Vector3 lateral_offset(
                    lateral * previous->transform.basis_right.x,
                    lateral * previous->transform.basis_right.y,
                    lateral * previous->transform.basis_right.z);
#endif
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
#if PATH_MESH_TERMINAL_ADD_ORDER == 1
                Vector3 generated_position =
                    endpoint + lateral_offset;
#elif PATH_MESH_TERMINAL_ADD_ORDER == 2
                Vector3 generated_position =
                    lateral_offset + endpoint;
#else
                Vector3 generated_position(
                    endpoint.x + lateral_offset.x,
                    endpoint.y + lateral_offset.y,
                    endpoint.z + lateral_offset.z);
#endif
#if PATH_VERTEX_OWNER_MODE == 1
                vertices[vertex_index] = generated_position;
#else
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
#endif
            }
        }
    }

    for (face_row = 0; face_row < segment_count; ++face_row) {
        face_column = 0;
        if (width_cells > 0) {
            float v0 = (float)(face_row % 8) * 0.125f;
            float v1 = (float)(face_row % 8 + 1) * 0.125f;
            int next_column;
            do {
                next_column = face_column + 1;
                float u0 = (float)face_column * 0.125f;
                float u1 = (float)(face_column + 1) * 0.125f;
                for (face_index = 0; face_index < 2; ++face_index) {
#if PATH_FACE_OWNER_MODE == 1
                    cRFaceQuad* face = &facequads[
                        face_index
                        + 2 * (face_row * width_cells + face_column)];
#elif PATH_FACE_OWNER_MODE == 2
                    int face_array_index =
                        face_index
                        + 2 * (face_row * width_cells + face_column);
#elif PATH_FACE_OWNER_MODE == 3
                    int face_array_index =
                        2 * (face_row * width_cells + face_column)
                        + face_index;
#elif PATH_FACE_OWNER_MODE == 4
                    int face_array_index =
                        face_index
                        + 2 * (face_row * width_cells + face_column);
#endif
#if PATH_FACE_OWNER_MODE == 4
#define PATH_FACE_FIELD(field) facequads[face_array_index].field
#else
#define PATH_FACE_FIELD(field) face->field
#endif
                    if (face_index == 0) {
#if PATH_FACE_OWNER_MODE == 0
                        cRFaceQuad* face = &facequads[
                            face_index
                            + 2 * (face_row * width_cells + face_column)];
#elif PATH_FACE_OWNER_MODE == 2 || PATH_FACE_OWNER_MODE == 3
                        cRFaceQuad* face = &facequads[face_array_index];
#endif
                        PATH_FACE_FIELD(header_word) = 0;
                        PATH_FACE_FIELD(vertex_0) = face_column + face_row * ((unsigned short)width_cells + 1);
                        PATH_FACE_FIELD(vertex_1) = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        PATH_FACE_FIELD(vertex_2) =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        PATH_FACE_FIELD(vertex_3) =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        if ((face_column ^ face_row) & 1)
                            PATH_FACE_FIELD(texture_ref) =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            PATH_FACE_FIELD(texture_ref) =
                                g_texture_refs.Add(texture_a, 0, 0);
                        PATH_FACE_FIELD(uv[0].u) = u0;
                        PATH_FACE_FIELD(uv[0].v) = v0;
                        PATH_FACE_FIELD(uv[1].u) = u1;
                        PATH_FACE_FIELD(uv[1].v) = v0;
                        PATH_FACE_FIELD(uv[2].u) = u1;
                        PATH_FACE_FIELD(uv[2].v) = v1;
                        PATH_FACE_FIELD(uv[3].u) = u0;
                        PATH_FACE_FIELD(uv[3].v) = v1;
                    } else {
#if PATH_FACE_OWNER_MODE == 0
                        cRFaceQuad* face = &facequads[
                            face_index
                            + 2 * (face_row * width_cells + face_column)];
#elif PATH_FACE_OWNER_MODE == 2 || PATH_FACE_OWNER_MODE == 3
                        cRFaceQuad* face = &facequads[face_array_index];
#endif
                        PATH_FACE_FIELD(header_word) = 0;
                        PATH_FACE_FIELD(vertex_0) = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        PATH_FACE_FIELD(vertex_1) = face_column + face_row * ((unsigned short)width_cells + 1);
                        PATH_FACE_FIELD(vertex_2) =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        PATH_FACE_FIELD(vertex_3) =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        if ((face_column ^ face_row) & 1)
                            PATH_FACE_FIELD(texture_ref) =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            PATH_FACE_FIELD(texture_ref) =
                                g_texture_refs.Add(texture_b, 0, 0);
                        PATH_FACE_FIELD(uv[0].u) = u1;
                        PATH_FACE_FIELD(uv[0].v) = v0;
                        PATH_FACE_FIELD(uv[1].u) = u0;
                        PATH_FACE_FIELD(uv[1].v) = v0;
                        PATH_FACE_FIELD(uv[2].u) = u0;
                        PATH_FACE_FIELD(uv[2].v) = v1;
                        PATH_FACE_FIELD(uv[3].u) = u1;
                        PATH_FACE_FIELD(uv[3].v) = v1;
                    }
#undef PATH_FACE_FIELD
                }
                face_column = next_column;
            } while (next_column < width_cells);
        }
    }

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
