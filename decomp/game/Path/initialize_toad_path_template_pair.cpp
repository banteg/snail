// initialize_toad_path_template_pair @ 0x42cbf0 (thiscall, ret 0x10)

#include "path_helpers.h"

typedef AttachmentSample PathTemplateSample;

void cRPath::initialize_toad_path_template_pair(bool turn_left, char *texture_a,
                                                char *texture_b, char *vertical_texture)
{
    int lead_count;
    int tail_count;
    float start_x;
    float turn_sign;
    int i;

    kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = 4;

    if (turn_left)
    {
        start_x = -2.0f;
        turn_sign = -1.0f;
        lead_count = 1;
        tail_count = 3;
    }
    else
    {
        start_x = 2.0f;
        turn_sign = 1.0f;
        lead_count = 2;
        tail_count = 1;
    }

    width_or_scale = 1.0f;
    segment_count = lead_count + tail_count + 26;
    segment_count_f = (float)segment_count;
    GetNodes();

    has_entry_mesh_transition = 0;
    i = 0;
    if (lead_count > 0)
    {
        int lead_sample_offset = 0;
        do
        {
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->center_x = start_x;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                    ->center_x;
            float z = (float)i;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.y = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->delta_length = 1.0f;

            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.y = 0.49000001f;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->transform.position.z = z;
            ++i;
            ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
                ->delta_length = 1.0f;
            lead_sample_offset += sizeof(AttachmentSample);
        } while (i < lead_count);
    }

    if (tail_count > 0)
    {
        int tail_start = lead_count + 26;
        int tail_index = tail_start;
        int tail_sample_offset = tail_start * (int)sizeof(AttachmentSample);
        int tail_control_base = -26 - lead_count;
        do
        {
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->center_x = start_x;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->special_scalar = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->lateral_scale = 1.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.Identity();
            float z = (float)tail_index;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.y = 0.0f;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                ->delta_length = 1.0f;

            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.Identity();
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.x =
                ((AttachmentSample *)((char *)primary_samples + tail_sample_offset))
                    ->center_x;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.y = 0.49000001f;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->transform.position.z = z;
            ((AttachmentSample *)((char *)secondary_samples + tail_sample_offset))
                ->delta_length = 1.0f;
            tail_sample_offset += (int)sizeof(AttachmentSample);
            ++tail_index;
        } while (tail_index + tail_control_base < tail_count);
    }

    int curve_sample_offset = lead_count * sizeof(AttachmentSample);
    for (i = 0; i < 26; ++i)
    {
        float phase = (float)i * 6.2831855f / 26.0f;
        float angle = (1.0f - Cos(phase)) * 0.5f;
        angle = angle * turn_sign * 3.1415927f * 0.5f;

        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->center_x = start_x;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->special_scalar = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.Identity();
        float turn_x = Sin(angle);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.x = turn_x + turn_x + start_x;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.z = (float)(lead_count + i);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.position.y = 0.0f;

        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_forward =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.position -
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))[-1]
                .transform.position;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_forward.Normalize();
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.basis_right.Cross(
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.basis_up,
                ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                    ->transform.basis_forward);
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->transform.RotLocalZ(angle);

        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform;
        Vector3 lane_offset =
            ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
                ->transform.basis_up *
            0.49000001f;
        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.position += lane_offset;
        curve_sample_offset += sizeof(AttachmentSample);
    }

    compute_path_deltas(segment_count, primary_samples, secondary_samples);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
}
