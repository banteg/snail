// initialize_cage2_path_template_pair @ 0x42e720 (thiscall, ret 0x10)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"

float Cos(float angle);

void cRPath::initialize_cage2_path_template_pair(int width_cells_, char *texture_a,
                                                 char *texture_b,
                                                 char *vertical_texture)
{
    int mesh_cursor = 0;
    kind = PATH_TEMPLATE_KIND_CAGE2;
    is_mirrored_x = 0;
    side_exit_mode = mesh_cursor;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 22;
    segment_count_f = 22.0f;
    GetNodes();

    has_entry_mesh_transition = 0;
    primary_samples[0].center_x = (float)width_cells * 0.5f - 4.0f;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    primary_samples[0].transform.Identity();
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;

    secondary_samples[0].transform.Identity();
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;

    primary_samples[21].center_x = 4.0f - (float)width_cells * 0.5f;
    primary_samples[21].rotation_scalar_98 = 0.0f;
    primary_samples[21].rotation_scalar_94 = 0.0f;
    primary_samples[21].special_scalar = 0.0f;
    primary_samples[21].lateral_scale = 1.0f;
    primary_samples[21].transform.Identity();
    primary_samples[21].transform.position.x = primary_samples[21].center_x;
    primary_samples[21].transform.position.y = 0.0f;
    primary_samples[21].transform.position.z = 21.0f;

    secondary_samples[21].transform.Identity();
    secondary_samples[21].transform.position.x = primary_samples[21].center_x;
    width_cells_ = mesh_cursor;
    secondary_samples[21].transform.position.y = 0.49000001f;
    secondary_samples[21].transform.position.z = 21.0f;

    int curve_sample_offset = sizeof(AttachmentSample);
    for (int sample_index = width_cells_;
         curve_sample_offset < 21 * (int)sizeof(AttachmentSample); ++sample_index)
    {
        int i = sample_index + 1;
        float sample_index_f = (float)sample_index;
        float curve_angle = sample_index_f * 0.31415927f;
        float angle = sample_index_f * 0.47123891f;
        ((AttachmentSample *)((char *)primary_samples + curve_sample_offset))
            ->center_x = Cos(angle) * primary_samples[0].center_x;
        AttachmentSample *const &primary_bank = primary_samples;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->special_scalar = 0.0f;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->transform.Identity();
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->transform.position.x =
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
                ->center_x;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->transform.position.y = 0.0f;
        float sample_z = (float)i;
        ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
            ->transform.position.z = sample_z;

        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.Identity();
        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.position.x =
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
                ->center_x;
        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.position.y =
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
                ->transform.position.y +
            0.49000001f;
        ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
            ->transform.position.z = sample_z;

        if (curve_sample_offset > (int)sizeof(AttachmentSample))
        {
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.basis_forward =
                ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))
                    ->transform.position -
                ((AttachmentSample *)((char *)primary_bank +
                                      curve_sample_offset))[-1]
                    .transform.position;
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.basis_forward.Normalize();
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.basis_right.Cross(
                    ((AttachmentSample *)((char *)primary_bank +
                                          curve_sample_offset))[-1]
                        .transform.basis_up,
                    ((AttachmentSample *)((char *)primary_bank +
                                          curve_sample_offset))[-1]
                        .transform.basis_forward);
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.RotLocalZ((float)((1.0f - Cos(curve_angle)) * 0.5f) *
                                     ((AttachmentSample *)((char *)primary_bank +
                                                           curve_sample_offset))[-1]
                                         .center_x *
                                     0.39269909f);

            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.basis_forward =
                ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))
                    ->transform.position -
                ((AttachmentSample *)((char *)secondary_samples +
                                      curve_sample_offset))[-1]
                    .transform.position;
            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.basis_forward.Normalize();
            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.basis_right.Cross(
                    ((AttachmentSample *)((char *)secondary_samples +
                                          curve_sample_offset))[-1]
                        .transform.basis_up,
                    ((AttachmentSample *)((char *)secondary_samples +
                                          curve_sample_offset))[-1]
                        .transform.basis_forward);
            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.RotLocalZ((float)((1.0f - Cos(curve_angle)) * 0.5f) *
                                     ((AttachmentSample *)((char *)primary_bank +
                                                           curve_sample_offset))[-1]
                                         .center_x *
                                     0.39269909f);
        }
        else
        {
            ((AttachmentSample *)((char *)primary_bank + curve_sample_offset))[-1]
                .transform.RotIdentity();
            ((AttachmentSample *)((char *)secondary_samples + curve_sample_offset))[-1]
                .transform.RotIdentity();
        }
        curve_sample_offset += sizeof(AttachmentSample);
    }

    int completed = 0;
    if (segment_count - 1 > 0)
    {
        int sample_offset = 0;
        do
        {
            ((AttachmentSample *)((char *)primary_samples + sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)primary_samples + sample_offset))[1]
                    .transform.position -
                ((AttachmentSample *)((char *)primary_samples + sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)primary_samples + sample_offset))
                ->delta_length =
                ((AttachmentSample *)((char *)primary_samples + sample_offset))
                    ->delta_dir_to_next.Normalize();

            ((AttachmentSample *)((char *)secondary_samples + sample_offset))
                ->delta_dir_to_next =
                ((AttachmentSample *)((char *)secondary_samples + sample_offset))[1]
                    .transform.position -
                ((AttachmentSample *)((char *)secondary_samples + sample_offset))
                    ->transform.position;
            ((AttachmentSample *)((char *)secondary_samples + sample_offset))
                ->delta_length =
                ((AttachmentSample *)((char *)secondary_samples + sample_offset))
                    ->delta_dir_to_next.Normalize();
            ++completed;
            sample_offset += sizeof(AttachmentSample);
        } while (completed < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    cRFaceQuad *facequads = strip_mesh->facequads;
    Vector3 *vertices = strip_mesh->vertices;

    int column;
    for (int row = 0; row <= segment_count; ++row)
    {
        column = 0;
        for (; column <= width_cells; ++column)
        {
            if (row != segment_count)
            {
                Vector3 lateral_offset =
                    primary_samples[row].transform.basis_right *
                    ((float)column - (float)width_cells * 0.5f);
                Vector3 generated_position =
                    lateral_offset + primary_samples[row].transform.position;
                Vector3 *vertex = &vertices[column + row * (width_cells + 1)];
                *vertex = generated_position;
            }
            else
            {
                Vector3 generated_position =
                    (primary_samples[row - 1].transform.position + Vector3(0.0f, 0.0f, 1.0f)) +
                    (primary_samples[row - 1].transform.basis_right *
                     ((float)column - (float)width_cells * 0.5f));
                Vector3 *vertex = &vertices[column + row * (width_cells + 1)];
                *vertex = generated_position;
            }
        }
    }

    mesh_cursor = 0;
    for (; mesh_cursor < segment_count; ++mesh_cursor)
    {
        column = 0;
        if (width_cells > 0)
        {
            float v0 = (float)(mesh_cursor % 8) * 0.125f;
            float v1 = (float)(mesh_cursor % 8 + 1) * 0.125f;
            do
            {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;
                for (int face_index = 0; face_index < 2; ++face_index)
                {
                    int face_offset = 2 * column + 2 * mesh_cursor * width_cells + face_index;
                    if (face_index == 0)
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            column +
                            mesh_cursor * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_1 =
                            mesh_cursor * ((unsigned short)width_cells + 1) +
                            column + 1;
                        facequads[face_offset].vertex_2 =
                            (mesh_cursor + 1) * ((unsigned short)width_cells + 1) +
                            column + 1;
                        facequads[face_offset].vertex_3 =
                            column +
                            (mesh_cursor + 1) * ((unsigned short)width_cells + 1);
                        if (((column ^ mesh_cursor) & 1) == 0)
                            facequads[face_offset].texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_offset].texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                    }
                    else
                    {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            mesh_cursor * ((unsigned short)width_cells + 1) +
                            column + 1;
                        facequads[face_offset].vertex_1 =
                            column +
                            mesh_cursor * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column +
                            (mesh_cursor + 1) * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (mesh_cursor + 1) * ((unsigned short)width_cells + 1) +
                            column + 1;
                        if (((column ^ mesh_cursor) & 1) == 0)
                            facequads[face_offset].texture_ref = g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_offset].texture_ref = g_texture_refs.Add(texture_b, 0, 0);
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
                ++column;
            } while (column < width_cells);
        }
    }

    CalcLengthZ();
}
