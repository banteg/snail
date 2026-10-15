// initialize_turnunder_path_template_pair @ 0x427fe0 (thiscall, ret 0x18)

#include "path_helpers.h"

typedef AttachmentSample PathTemplateSample;

void cRPath::initialize_turnunder_path_template_pair(float turns, int width_cells_,
                                                     bool side_exit, char *texture_a,
                                                     char *texture_b,
                                                     char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int interior_count = (int)(turns * 6.2831855f);
    width_or_scale = 1.0f;
    segment_count = interior_count + 8;
    segment_count_f = ((float)segment_count);
    float interior_count_f = (float)interior_count;
    turns = (interior_count_f * 0.15915494f);
    GetNodes();
    has_entry_mesh_transition = 0;

    int sample_step = 0;
    int i = 0;
    do
    {
        primary_samples[i].center_x = -((float)width_cells * 0.5f - 4.0f);
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        primary_samples[i].transform.Identity();
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        float z = (float)sample_step;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;
        primary_samples[i].delta_length = 1.0f;

        secondary_samples[i].transform.Identity();
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
        secondary_samples[i].delta_length = 1.0f;
        ++i;
        ++sample_step;
    } while (i < 6);

    int endpoint_index = interior_count + 6;
    int endpoint_offset = endpoint_index * sizeof(AttachmentSample);
    i = endpoint_index;
    int tail_sample_offset = endpoint_offset;
    int tail_origin = -6 - interior_count;
    do
    {
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->center_x =
            -(4.0f - (float)width_cells * 0.5f);
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->special_scalar = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->transform.Identity();
        float z = (float)i;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->transform.position.x =
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->center_x;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->transform.position.y = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->transform.position.z = z;
        ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->delta_length = 1.0f;

        ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))->transform.Identity();
        ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))->transform.position.x =
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))->center_x;
        ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))->transform.position.y = 0.49000001f;
        ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))->transform.position.z = z;
        ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))->delta_length = 1.0f;
        tail_sample_offset += sizeof(AttachmentSample);
        ++i;
    } while (i + tail_origin < 2);

    sample_step = 0;
    if (interior_count > 0)
    {
        for (; sample_step < interior_count; ++sample_step)
        {
            i = sample_step + 6;
            float t = (float)sample_step;
            float angle = t * -6.2831855f / interior_count_f;

            AttachmentSample *const &primary_bank = primary_samples;
            primary_samples[i].center_x =
                (((AttachmentSample *)((char *)primary_bank + endpoint_offset))
                     ->center_x -
                 primary_bank[0].center_x) *
                    t / interior_count_f +
                primary_bank[0].center_x;
            primary_samples[i].rotation_scalar_98 = 0.0f;
            primary_samples[i].rotation_scalar_94 = 0.0f;
            primary_samples[i].special_scalar = 0.0f;
            primary_samples[i].lateral_scale = 1.0f;
            primary_samples[i].transform.Identity();

            primary_samples[i].transform.position.x =
                primary_samples[i].center_x - (Sin(angle) * Sin(angle * 0.5f) * 2.0f);
            primary_samples[i].transform.position.z = (float)(sample_step + 6);
            primary_samples[i].transform.position.y =
                (turns - Cos(angle) * turns) * -0.2f;

            float roll_cosine = Cos(Sin(angle) * 1.0471976f);
            Vector3 up;
            up.x = -Sin(Sin(angle) * 1.0471976f);
            up.y = roll_cosine;
            up.z = 0.0f;
            primary_samples[i].transform.basis_up = up;
            primary_samples[i].transform.basis_forward =
                primary_samples[i].transform.position -
                primary_samples[i - 1].transform.position;
            primary_samples[i].transform.basis_forward.Normalize();
            primary_samples[i].transform.basis_right.Cross(
                primary_samples[i].transform.basis_up,
                primary_samples[i].transform.basis_forward);

            secondary_samples[i].transform = primary_samples[i].transform;
            Vector3 secondary_offset =
                primary_samples[i].transform.basis_up * 0.49000001f;
            Vector3 *secondary_position = &secondary_samples[i].transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;
        }
    }

    compute_path_deltas(segment_count, primary_samples, secondary_samples);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)vertical_texture;
}
