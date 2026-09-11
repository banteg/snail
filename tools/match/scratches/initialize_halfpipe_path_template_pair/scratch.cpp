// initialize_halfpipe_path_template_pair @ 0x429b20 (thiscall, ret 0x18)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

float Sin(float angle);

void cRPath::initialize_halfpipe_path_template_pair(float scale, int width_cells_,
                                                    bool side_exit, char *texture_a,
                                                    char *texture_b,
                                                    char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_NONLINEAR_42;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 66;
    segment_count_f = 66.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int sample_step = 0;
    int lead_sample_offset = 0;
    do
    {
        float index = (float)sample_step;
        float angle_base = index * 0.0625f;
        float angle = angle_base * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - Sin(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))->center_x =
            (float)width_cells * 0.5f - 4.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->special_scalar = (depth * depth + 16.0f) / (depth + depth);
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.Identity();
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.x =
            ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
                ->center_x;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.y = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + lead_sample_offset))
            ->transform.position.z = index;
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
            ->transform.position.z = index;
        ((AttachmentSample *)((char *)secondary_samples + lead_sample_offset))
            ->delta_length = 1.0f;
        ++sample_step;
        lead_sample_offset += sizeof(AttachmentSample);
    } while (lead_sample_offset < 16 * (int)sizeof(AttachmentSample));

    sample_step = 0;
    do
    {
        int sample_index = sample_step + 50;
        float angle_base = 1.0f - (float)sample_step * 0.0625f;
        float angle = angle_base * 3.1415927f + 1.5707964f;
        float depth = ((0.5f - Sin(angle) * 0.5f) * 0.94999999f + 0.050000001f) * 4.0f;
        primary_samples[sample_index].center_x = 4.0f - (float)width_cells * 0.5f;
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar =
            (depth * depth + 16.0f) / (depth + depth);
        primary_samples[sample_index].lateral_scale = 1.0f;
        primary_samples[sample_index].transform.Identity();
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        primary_samples[sample_index].transform.position.y = 0.0f;
        primary_samples[sample_index].transform.position.z = (float)sample_index;
        primary_samples[sample_index].delta_length = 1.0f;

        secondary_samples[sample_index].transform.Identity();
        secondary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        secondary_samples[sample_index].transform.position.y = 0.49000001f;
        secondary_samples[sample_index].transform.position.z = (float)sample_index;
        secondary_samples[sample_index].delta_length = 1.0f;
        ++sample_step;
    } while (sample_step < 16);

    float out_angle;
    int middle = 0;
    int middle_offset = 16 * sizeof(AttachmentSample);
    do
    {
        float middle_f = (float)middle;
        out_angle = middle_f * 0.18479957f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))->center_x =
            (primary_samples[50].center_x - primary_samples[0].center_x) * middle_f *
                0.029411765f +
            primary_samples[0].center_x;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->special_scalar = 4.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))->lateral_scale =
            1.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.Identity();
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.position.x = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.position.z = (float)(middle + 16);
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.position.y = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.basis_forward =
            ((AttachmentSample *)((char *)primary_samples + middle_offset))
                ->transform.position -
            ((AttachmentSample *)((char *)primary_samples + middle_offset))[-1]
                .transform.position;
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.basis_forward.Normalize();
        ((AttachmentSample *)((char *)primary_samples + middle_offset))
            ->transform.basis_right.Cross(
                ((AttachmentSample *)((char *)primary_samples + middle_offset))
                    ->transform.basis_up,
                ((AttachmentSample *)((char *)primary_samples + middle_offset))
                    ->transform.basis_forward);

        ((AttachmentSample *)((char *)secondary_samples + middle_offset))->transform =
            ((AttachmentSample *)((char *)primary_samples + middle_offset))->transform;
        Vector3 secondary_offset =
            ((AttachmentSample *)((char *)primary_samples + middle_offset))
                ->transform.basis_up *
            0.49000001f;
        Vector3 *secondary_position =
            &((AttachmentSample *)((char *)secondary_samples + middle_offset))
                 ->transform.position;
        secondary_position->x += secondary_offset.x;
        secondary_position->y += secondary_offset.y;
        secondary_position->z += secondary_offset.z;
        ++middle;
        middle_offset += sizeof(AttachmentSample);
    } while (middle_offset < 50 * (int)sizeof(AttachmentSample));

    int sample_index = 0;
    if (segment_count - 1 > 0)
    {
        do
        {
            primary_samples[sample_index].delta_dir_to_next =
                primary_samples[sample_index + 1].transform.position -
                primary_samples[sample_index].transform.position;
            primary_samples[sample_index].delta_length =
                primary_samples[sample_index].delta_dir_to_next.Normalize();

            secondary_samples[sample_index].delta_dir_to_next =
                secondary_samples[sample_index + 1].transform.position -
                secondary_samples[sample_index].transform.position;
            secondary_samples[sample_index].delta_length =
                secondary_samples[sample_index].delta_dir_to_next.Normalize();
            ++sample_index;
        } while (sample_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * segment_count * width_cells);

    cRFaceQuad *facequads = strip_mesh->facequads;
    Vector3 *vertices = strip_mesh->vertices;
    TransformMatrix kind42_transform;
    kind42_transform.Identity();

    int sample_offset = 0;
    for (int row = 0; row <= segment_count; ++row)
    {
        int column = 0;
        for (; column <= width_cells; ++column)
        {
            double lateral = (float)column - (float)width_cells * 0.5f;
            TransformMatrix *transform =
                (TransformMatrix *)((char *)&primary_samples[0].transform +
                                    sample_offset);
            if (row != segment_count)
            {
                Vector3 lateral_offset = transform->basis_right * lateral;
                Vector3 generated_position(transform->position.x + lateral_offset.x,
                                           transform->position.y + lateral_offset.y,
                                           transform->position.z + lateral_offset.z);
                vertices[column + row * (width_cells + 1)] = generated_position;
            }
            else
            {
                TransformMatrix *previous =
                    (TransformMatrix *)((char *)transform - sizeof(AttachmentSample));
                Vector3 lateral_offset = previous->basis_right * lateral;
                Vector3 endpoint = previous->position + Vector3(0.0f, 0.0f, 1.0f);
                Vector3 generated_position = endpoint + lateral_offset;
                vertices[column + row * (width_cells + 1)] = generated_position;
            }

            int radius_sample = row - 1;
            if (row != segment_count)
                radius_sample = row;
            compute_kind42_attachment_transform(
                primary_samples[radius_sample].special_scalar, vertices[column + row * (width_cells + 1)].x, 0.0f,
                &kind42_transform, &out_angle);
            if (sample_offset > sizeof(AttachmentSample) && row != segment_count)
            {
                vertices[column + row * (width_cells + 1)].x = kind42_transform.position.x;
                vertices[column + row * (width_cells + 1)].y = kind42_transform.position.y;
            }
        }
        sample_offset += sizeof(AttachmentSample);
    }

    for (int mesh_row = 0; mesh_row < segment_count; ++mesh_row)
    {
        int mesh_column = 0;
        if (width_cells > 0)
        {
            float v0 = (float)(mesh_row % 8) * 0.125f;
            float v1 = (float)(mesh_row % 8 + 1) * 0.125f;
            int next_column;
            do
            {
                next_column = mesh_column + 1;
                float u0 = (float)mesh_column * 0.125f;
                float u1 = (float)(mesh_column + 1) * 0.125f;
                for (int face_index = 0; face_index < 2; ++face_index)
                {
                    int face_offset =
                        face_index + 2 * (mesh_row * width_cells + mesh_column);
                    if (face_index == 0)
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            mesh_column + mesh_row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            mesh_row * ((unsigned short)width_cells + 1) + mesh_column +
                            1;
                        facequads[face_offset].vertex_2 =
                            (mesh_row + 1) * ((unsigned short)width_cells + 1) +
                            mesh_column + 1;
                        facequads[face_offset].vertex_3 =
                            mesh_column +
                            (mesh_row + 1) * ((unsigned short)width_cells + 1);
                        if ((mesh_column ^ mesh_row) & 1)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                    }
                    else
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            mesh_row * ((unsigned short)width_cells + 1) + mesh_column +
                            1;
                        facequads[face_offset].vertex_1 =
                            mesh_column + mesh_row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            mesh_column +
                            (mesh_row + 1) * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (mesh_row + 1) * ((unsigned short)width_cells + 1) +
                            mesh_column + 1;
                        if ((mesh_column ^ mesh_row) & 1)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                    }
                    if (face_index == 0)
                    {
                        facequads[face_offset].uv[0].u = u0;
                        facequads[face_offset].uv[0].v = v0;
                        facequads[face_offset].uv[1].u = u1;
                        facequads[face_offset].uv[1].v = v0;
                        facequads[face_offset].uv[2].u = u1;
                        facequads[face_offset].uv[2].v = v1;
                        facequads[face_offset].uv[3].u = u0;
                        facequads[face_offset].uv[3].v = v1;
                    }
                    else
                    {
                        facequads[face_offset].uv[0].u = u1;
                        facequads[face_offset].uv[0].v = v0;
                        facequads[face_offset].uv[1].u = u0;
                        facequads[face_offset].uv[1].v = v0;
                        facequads[face_offset].uv[2].u = u0;
                        facequads[face_offset].uv[2].v = v1;
                        facequads[face_offset].uv[3].u = u1;
                        facequads[face_offset].uv[3].v = v1;
                    }
                }
                mesh_column = next_column;
            } while (next_column < width_cells);
        }
    }

    CalcLengthZ();
}
