// initialize_slalom_path_template_pair @ 0x41f760 (thiscall, ret 0x18)

#define PATH_FUNCTION initialize_slalom_path_template_pair
#define PATH_SIGNATURE int curve_source, int width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture
#define PATH_CURVE_COUNT (curve_source)
#define PATH_HEIGHT_SCALE 1.0f
#define PATH_VARIANT 7

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

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
    previous->transform.RotLocalZ(roll);
}

void cRPath::PATH_FUNCTION(PATH_SIGNATURE)
{
    int curve_count = PATH_CURVE_COUNT;
    float height_scale_value = PATH_HEIGHT_SCALE;
    int i;

#if PATH_VARIANT != 7
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
#endif

#if PATH_VARIANT == 0 || PATH_VARIANT == 1
    float loop_wiggle = 0.0f;
    kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    if (width_cells_ == 4) {
#if PATH_VARIANT == 1
        kind = PATH_TEMPLATE_KIND_LOOPTHELOOPW;
#else
        kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
#endif
        loop_wiggle = 0.30000001f;
    }
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    GetNodes();
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
            float center = (primary_samples[curve_count + 7].center_x
                    - primary_samples[0].center_x)
                * sample_f / curve_count_f + primary_samples[0].center_x;
            center += Sin(angle * 0.5f + 4.712389f) * loop_wiggle;

            primary_samples[sample_index].center_x = center;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                Sin(angle) * loop_radius + 7.0f;
            primary_samples[sample_index].transform.position.y =
                loop_radius - Cos(angle) * loop_radius;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                Sin(angle) * secondary_radius + 7.0f;
            secondary_samples[sample_index].transform.position.y =
                loop_radius - Cos(angle) * secondary_radius;

            orient_loop_sample(
                &primary_samples[sample_index],
                loop_radius - primary_samples[sample_index].transform.position.y,
                7.0f - primary_samples[sample_index].transform.position.z);
            orient_loop_sample(
                &secondary_samples[sample_index],
                loop_radius - secondary_samples[sample_index].transform.position.y,
                7.0f - secondary_samples[sample_index].transform.position.z);

#if PATH_VARIANT == 1
            float roll = Sin(angle * 0.5f) * Sin(angle * 8.0f) * 0.39269909f;
            primary_samples[sample_index].transform.RotLocalZ(roll);
            secondary_samples[sample_index].transform.RotLocalZ(roll);
#endif
        }
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
            center += Sin(angle * 0.5f + 4.712389f) * 0.30000001f;

            primary_samples[sample_index].center_x = center;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                Sin(angle) * loop_radius + 10.0f;
            primary_samples[sample_index].transform.position.y =
                Cos(angle) * loop_radius + center_y;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                Sin(angle) * secondary_radius + 10.0f;
            secondary_samples[sample_index].transform.position.y =
                Cos(angle) * secondary_radius + center_y;

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
                * (1.0f - Cos(angle)) * hump_radius * height_scale_value;
            float center = Cos(angle * 0.5f) * start_center;
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
            float y = -((1.0f - Cos(angle)) * dip_radius);
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
            float center = Cos(angle * 0.5f) * 0.5f;
            initialize_sample_pair(
                &primary_samples[sample_index],
                &secondary_samples[sample_index],
                center,
                0.0f,
                Cos(angle) * 0.49000001f,
                (float)(i + 3),
                0);
            primary_samples[sample_index].rotation_scalar_94 = angle;
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x - Sin(angle) * 0.49000001f;
            if (sample_index <= 3) {
                primary_samples[sample_index - 1].transform.RotIdentity();
                secondary_samples[sample_index - 1].transform.RotIdentity();
            } else {
                float up_x = -Sin(angle);
                float up_y = Cos(angle);
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
    width_cells = width_cells_;
    kind = PATH_TEMPLATE_KIND_SLALOM;
    int lead_out_start = curve_count + 4;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    int total_segments = lead_out_start + 4;
    width_or_scale = 1.0f;
    segment_count = total_segments;
    segment_count_f = (float)total_segments;
    GetNodes();
    has_entry_mesh_transition = 0;

    for (i = 0; i < 4; ++i) {
        primary_samples[i].center_x = 0.0f;
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[i].transform);
        float z = (float)i;
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;

        set_matrix_identity(&secondary_samples[i].transform);
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
    }

    int departure_index = lead_out_start;
    do {
        primary_samples[departure_index].center_x = 0.0f;
        primary_samples[departure_index].rotation_scalar_98 = 0.0f;
        primary_samples[departure_index].rotation_scalar_94 = 0.0f;
        primary_samples[departure_index].special_scalar = 0.0f;
        primary_samples[departure_index].lateral_scale = 1.0f;
        set_matrix_identity(&primary_samples[departure_index].transform);
        primary_samples[departure_index].transform.position.x =
            primary_samples[departure_index].center_x;
        float z = (float)departure_index;
        primary_samples[departure_index].transform.position.y = 0.0f;
        primary_samples[departure_index].transform.position.z = z;

        set_matrix_identity(&secondary_samples[departure_index].transform);
        secondary_samples[departure_index].transform.position.x =
            primary_samples[departure_index].center_x;
        secondary_samples[departure_index].transform.position.y = 0.49000001f;
        secondary_samples[departure_index].transform.position.z = z;
        ++departure_index;
    } while (departure_index - 4 - curve_count < 4);

    if (curve_count > 0) {
        float curve_count_f = (float)curve_count;
        int curve_sample_offset = 4 * sizeof(PathAttachmentSample);
#define PRIMARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)primary_samples + curve_sample_offset))
#define SECONDARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)secondary_samples + curve_sample_offset))
        for (i = 0; i < curve_count;
             ++i, curve_sample_offset += sizeof(PathAttachmentSample)) {
            int sample_index = i + 4;
            float t = (float)i / curve_count_f;
            float angle = t * 6.2831855f;
            float falloff = t - 0.5f;
            float falloff_copy;
            if (falloff >= 0.0f)
                falloff_copy = falloff;
            else
                falloff_copy = -falloff;
            if (falloff < 0.0f)
                falloff = -falloff;
            float center = Sin(angle) * (1.0f - falloff) * (1.0f - falloff_copy) * 5.0f;
            PRIMARY_CURVE_SAMPLE->center_x = center;
            PRIMARY_CURVE_SAMPLE->rotation_scalar_98 = 0.0f;
            PRIMARY_CURVE_SAMPLE->rotation_scalar_94 = 0.0f;
            PRIMARY_CURVE_SAMPLE->special_scalar = 0.0f;
            PRIMARY_CURVE_SAMPLE->lateral_scale = 1.0f;
            set_matrix_identity(&PRIMARY_CURVE_SAMPLE->transform);
            PRIMARY_CURVE_SAMPLE->transform.position.x =
                PRIMARY_CURVE_SAMPLE->center_x;
            float z = (float)(i + 4);
            PRIMARY_CURVE_SAMPLE->transform.position.y = 0.0f;
            PRIMARY_CURVE_SAMPLE->transform.position.z = z;
            set_matrix_identity(&SECONDARY_CURVE_SAMPLE->transform);
            SECONDARY_CURVE_SAMPLE->transform.position.x =
                PRIMARY_CURVE_SAMPLE->center_x;
            SECONDARY_CURVE_SAMPLE->transform.position.y = 0.49000001f;
            SECONDARY_CURVE_SAMPLE->transform.position.z = z;
            if (i <= 0) {
                (PRIMARY_CURVE_SAMPLE - 1)->transform.RotIdentity();
                (SECONDARY_CURVE_SAMPLE - 1)->transform.RotIdentity();
            } else {
                (PRIMARY_CURVE_SAMPLE - 1)->transform.basis_up =
                    Vector3(0.0f, 1.0f, 0.0f);
                (PRIMARY_CURVE_SAMPLE - 1)->transform.basis_forward =
                    Vector3(
                        PRIMARY_CURVE_SAMPLE->transform.position.x
                            - (PRIMARY_CURVE_SAMPLE - 1)->transform.position.x,
                        PRIMARY_CURVE_SAMPLE->transform.position.y
                            - (PRIMARY_CURVE_SAMPLE - 1)->transform.position.y,
                        PRIMARY_CURVE_SAMPLE->transform.position.z
                            - (PRIMARY_CURVE_SAMPLE - 1)->transform.position.z);
                (PRIMARY_CURVE_SAMPLE - 1)
                    ->transform.basis_forward.Normalize();
                (PRIMARY_CURVE_SAMPLE - 1)
                    ->transform.basis_right.cross_vectors(
                        &(PRIMARY_CURVE_SAMPLE - 1)->transform.basis_up,
                        &(PRIMARY_CURVE_SAMPLE - 1)->transform.basis_forward);
                float primary_roll =
                    (PRIMARY_CURVE_SAMPLE - 1)->center_x * 0.2617994f;
                (PRIMARY_CURVE_SAMPLE - 1)
                    ->transform.RotLocalZ(primary_roll);

                (SECONDARY_CURVE_SAMPLE - 1)->transform.basis_up =
                    Vector3(0.0f, 1.0f, 0.0f);
                (SECONDARY_CURVE_SAMPLE - 1)->transform.basis_forward =
                    Vector3(
                        SECONDARY_CURVE_SAMPLE->transform.position.x
                            - (SECONDARY_CURVE_SAMPLE - 1)->transform.position.x,
                        SECONDARY_CURVE_SAMPLE->transform.position.y
                            - (SECONDARY_CURVE_SAMPLE - 1)->transform.position.y,
                        SECONDARY_CURVE_SAMPLE->transform.position.z
                            - (SECONDARY_CURVE_SAMPLE - 1)->transform.position.z);
                (SECONDARY_CURVE_SAMPLE - 1)
                    ->transform.basis_forward.Normalize();
                (SECONDARY_CURVE_SAMPLE - 1)
                    ->transform.basis_right.cross_vectors(
                        &(SECONDARY_CURVE_SAMPLE - 1)->transform.basis_up,
                        &(SECONDARY_CURVE_SAMPLE - 1)->transform.basis_forward);

                float secondary_roll =
                    (PRIMARY_CURVE_SAMPLE - 1)->center_x * 0.2617994f;
                (SECONDARY_CURVE_SAMPLE - 1)
                    ->transform.RotLocalZ(secondary_roll);
            }
        }
#undef SECONDARY_CURVE_SAMPLE
#undef PRIMARY_CURVE_SAMPLE
    }
#endif

    int delta_offset = 0;
    if (segment_count - 1 > 0) {
        for (i = 0; i < segment_count - 1;
             ++i, delta_offset += (int)sizeof(PathAttachmentSample)) {
            ((PathAttachmentSample*)((char*)primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample*)((char*)primary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathAttachmentSample*)((char*)primary_samples + delta_offset))
                    ->transform.position;
            ((PathAttachmentSample*)((char*)primary_samples + delta_offset))
                ->delta_length =
                ((PathAttachmentSample*)((char*)primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathAttachmentSample*)((char*)secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathAttachmentSample*)((char*)secondary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathAttachmentSample*)((char*)secondary_samples + delta_offset))
                    ->transform.position;
            ((PathAttachmentSample*)((char*)secondary_samples + delta_offset))
                ->delta_length =
                ((PathAttachmentSample*)((char*)secondary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();
        }
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    cRFaceQuad* facequads = strip_mesh->facequads;
    Vector3* vertices = strip_mesh->vertices;

    int mesh_row;
    int mesh_column;
    int face_row;
    int face_index;

    for (mesh_row = 0; mesh_row <= segment_count; ++mesh_row) {
        for (mesh_column = 0; mesh_column <= width_cells; ++mesh_column) {
            double lateral = (float)mesh_column - (float)width_cells * 0.5f;
            if (mesh_row != segment_count) {
                PathAttachmentSample* sample = &primary_samples[mesh_row];
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position(
                    sample->transform.position.x + lateral_offset.x,
                    sample->transform.position.y + lateral_offset.y,
                    sample->transform.position.z + lateral_offset.z);
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
            } else {
                PathAttachmentSample* previous = &primary_samples[mesh_row - 1];
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
            }
        }
    }

    for (face_row = 0; face_row < segment_count; ++face_row) {
        if (width_cells > 0) {
            float v0 = (float)(face_row % 8) * 0.125f;
            float v1 = (float)(face_row % 8 + 1) * 0.125f;
            mesh_column = 0;
            int next_column;
            do {
                next_column = mesh_column + 1;
                float u0 = (float)mesh_column * 0.125f;
                float u1 = (float)(mesh_column + 1) * 0.125f;
                for (face_index = 0; face_index < 2; ++face_index) {
                    int face_record_index =
                        face_index
                        + 2 * (face_row * width_cells + mesh_column);
                    cRFaceQuad* front_face =
                        &facequads[face_record_index];
                    if (face_index == 0) {
                        front_face->header_word = 0;
                        front_face->vertex_0 = mesh_column + face_row * ((unsigned short)width_cells + 1);
                        front_face->vertex_1 = face_row * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        front_face->vertex_2 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        front_face->vertex_3 =
                            mesh_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        front_face->texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                        front_face->uv[0].u = u0;
                        front_face->uv[0].v = v0;
                        front_face->uv[1].u = u1;
                        front_face->uv[1].v = v0;
                        front_face->uv[2].u = u1;
                        front_face->uv[2].v = v1;
                        front_face->uv[3].u = u0;
                        front_face->uv[3].v = v1;
                    } else {
                        cRFaceQuad* back_face =
                            &facequads[face_record_index];
                        back_face->header_word = 0;
                        back_face->vertex_0 = face_row * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        back_face->vertex_1 = mesh_column + face_row * ((unsigned short)width_cells + 1);
                        back_face->vertex_2 =
                            mesh_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        back_face->vertex_3 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        back_face->texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                        back_face->uv[0].u = u1;
                        back_face->uv[0].v = v0;
                        back_face->uv[1].u = u0;
                        back_face->uv[1].v = v0;
                        back_face->uv[2].u = u0;
                        back_face->uv[2].v = v1;
                        back_face->uv[3].u = u1;
                        back_face->uv[3].v = v1;
                    }
                }
                mesh_column = next_column;
            } while (next_column < width_cells);
        }
    }

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
