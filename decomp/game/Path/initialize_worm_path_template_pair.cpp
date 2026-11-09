// initialize_worm_path_template_pair @ 0x420170 (thiscall, ret 0x4)

#include "font_system.h"
#include "object_render_types.h"
#include "track_attachment_types.h"
#include "transform_matrix.h"
#include "path_helpers.h"

const float WORM_TAU = 6.2831855f;
const float WORM_RADIUS = 4.0f;
const float WORM_UNDERSIDE_SCALE = 0.30000001f;
const float WORM_UV_ROW_STEP = 0.125f;

void cRPath::initialize_worm_path_template_pair(char* texture_path)
{
    kind = PATH_TEMPLATE_KIND_WORM;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = 16;
    width_or_scale = 4.0f;
    segment_count = 24;
    segment_count_f = 96.0f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int sample_index = 0;
    int entry_offset = 0;
    do {
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->center_x = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->rotation_scalar_98 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->rotation_scalar_94 = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->special_scalar = 0.0f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->lateral_scale = 1.0f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->transform.Identity();

        AttachmentSample* const& bank = primary_samples;
        ((AttachmentSample *)((char *)bank + entry_offset))->transform.position.x =
            ((AttachmentSample *)((char *)bank + entry_offset))->center_x;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->transform.position.y = 0.49000001f;
        ((AttachmentSample *)((char *)primary_samples + entry_offset))->transform.position.z =
            (float)sample_index * width_or_scale;

        ((AttachmentSample *)((char *)secondary_samples + entry_offset))->transform.Identity();
        ((AttachmentSample *)((char *)secondary_samples + entry_offset))->transform.position.x =
            ((AttachmentSample *)((char *)primary_samples + entry_offset))->center_x;
        ((AttachmentSample *)((char *)secondary_samples + entry_offset))->transform.position.y = 0.49000001f;
        ((AttachmentSample *)((char *)secondary_samples + entry_offset))->transform.position.z =
            (float)sample_index * width_or_scale;
        ++sample_index;
        entry_offset += sizeof(AttachmentSample);
    } while (entry_offset < 4 * (int)sizeof(AttachmentSample));

    for (int exit_step = 0; exit_step < 4; ++exit_step) {
        int exit_index = exit_step + 20;
        primary_samples[exit_index].center_x = 0.0f;
        primary_samples[exit_index].rotation_scalar_98 = 0.0f;
        primary_samples[exit_index].rotation_scalar_94 = 0.0f;
        primary_samples[exit_index].special_scalar = 0.0f;
        primary_samples[exit_index].lateral_scale = 1.0f;
        primary_samples[exit_index].transform.Identity();

        AttachmentSample* const& bank = primary_samples;
        bank[exit_index].transform.position.x = bank[exit_index].center_x;
        primary_samples[exit_index].transform.position.y = 0.49000001f;
        primary_samples[exit_index].transform.position.z =
            (float)exit_index * width_or_scale;

        secondary_samples[exit_index].transform.Identity();
        secondary_samples[exit_index].transform.position.x =
            primary_samples[exit_index].center_x;
        secondary_samples[exit_index].transform.position.y = 0.49000001f;
        secondary_samples[exit_index].transform.position.z =
            (float)exit_index * width_or_scale;
    }

    for (int middle_index = 0; middle_index < 16; ++middle_index) {
        int current_sample = middle_index + 4;
        primary_samples[current_sample].center_x = 0.0f;
        primary_samples[current_sample].rotation_scalar_98 = 0.0f;
        primary_samples[current_sample].rotation_scalar_94 = 0.0f;
        primary_samples[current_sample].special_scalar = 0.0f;
        primary_samples[current_sample].lateral_scale = 1.0f;
        primary_samples[current_sample].transform.Identity();
        AttachmentSample* const& bank = primary_samples;
        bank[current_sample].transform.position.x = bank[current_sample].center_x;

        primary_samples[current_sample].transform.position.y = 0.49000001f;
        primary_samples[current_sample].transform.position.z =
            (float)current_sample * width_or_scale;

        AttachmentSample* const& secondary_bank = secondary_samples;
        secondary_bank[current_sample].transform.Identity();
        secondary_bank[current_sample].transform.position.x = primary_samples[current_sample].center_x;
        secondary_bank[current_sample].transform.position.y = 0.49000001f;
        secondary_bank[current_sample].transform.position.z =
            (float)current_sample * width_or_scale;

        if (middle_index > 0) {
            primary_samples[current_sample - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);

            primary_samples[current_sample - 1].transform.basis_forward =
                primary_samples[current_sample].transform.position -
                primary_samples[current_sample - 1].transform.position;
            primary_samples[current_sample - 1].transform.basis_forward.Normalize();
            primary_samples[current_sample - 1].transform.basis_right.Cross(
                primary_samples[current_sample - 1].transform.basis_up,
                primary_samples[current_sample - 1].transform.basis_forward);
            primary_samples[current_sample - 1].transform.basis_up.Cross(
                primary_samples[current_sample - 1].transform.basis_forward,
                primary_samples[current_sample - 1].transform.basis_right);

            secondary_bank[current_sample - 1].transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);

            secondary_bank[current_sample - 1].transform.basis_forward =
                secondary_bank[current_sample].transform.position -
                secondary_bank[current_sample - 1].transform.position;
            secondary_bank[current_sample - 1].transform.basis_forward.Normalize();
            secondary_bank[current_sample - 1].transform.basis_right.Cross(
                secondary_bank[current_sample - 1].transform.basis_up,
                secondary_bank[current_sample - 1].transform.basis_forward);
            secondary_bank[current_sample - 1].transform.basis_up.Cross(
                secondary_bank[current_sample - 1].transform.basis_forward,
                secondary_bank[current_sample - 1].transform.basis_right);
        } else {
            primary_samples[current_sample - 1].transform.RotIdentity();
            secondary_bank[current_sample - 1].transform.RotIdentity();
        }

    }

    int delta_index = 0;
    if (segment_count - 1 > 0) {
        do {
            primary_samples[delta_index].delta_dir_to_next =
                primary_samples[delta_index + 1].transform.position -
                primary_samples[delta_index].transform.position;
            primary_samples[delta_index].delta_length =
                primary_samples[delta_index].delta_dir_to_next.Normalize();

            secondary_samples[delta_index].delta_dir_to_next =
                secondary_samples[delta_index + 1].transform.position -
                secondary_samples[delta_index].transform.position;
            secondary_samples[delta_index].delta_length =
                secondary_samples[delta_index].delta_dir_to_next.Normalize();

            ++delta_index;
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = width_or_scale;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = width_or_scale;

    strip_mesh->flags |= OBJECT_FLAG_TEXTURE_TRANSFORM;
    strip_mesh->RequestVertices((segment_count + 1) * width_cells);
    strip_mesh->RequestFaceQuads(2 * segment_count * width_cells);
    strip_mesh->RequestColours();
    sample_index = 0;
    int mesh_column;
    float column_as_float;
    strip_mesh->flags |= OBJECT_FLAG_USE_VERTEX_COLOURS;

    Vector3* vertices = strip_mesh->vertices;
    cRFaceQuad* facequads = strip_mesh->facequads;
    tColour* vertex_colours = strip_mesh->vertex_colours;

    if (segment_count >= 0) {
        do {
            float row_angle = (float)sample_index * WORM_TAU / segment_count;
            mesh_column = 0;
            if (width_cells > 0) {
                do {
                    if (sample_index < segment_count) {
                        float radius = primary_samples[sample_index].lateral_scale;
                        radius *= WORM_RADIUS;

                        Vector3 up_radius = primary_samples[sample_index].transform.basis_up * radius;
                        column_as_float = (float)mesh_column;
                        Vector3 up_component =
                            up_radius * Cos((column_as_float / (float)width_cells) * WORM_TAU);
                        // The Wii builder adds the zero vector after each of these sums.
                        Vector3 base_plus_right =
                            primary_samples[sample_index].transform.position +
                            primary_samples[sample_index].transform.basis_right * radius *
                                Sin(column_as_float / (float)width_cells * WORM_TAU) +
                            Vector3(0.0f, 0.0f, 0.0f);
                        vertices[mesh_column + sample_index * width_cells] =
                            base_plus_right + up_component + Vector3(0.0f, 0.0f, 0.0f);

                        vertex_colours[mesh_column + sample_index * width_cells].store_color4f(
                            1.0f, 1.0f, 1.0f, 0.5f - Cos(row_angle + row_angle) * 0.5f);
                    } else {
                        vertices[mesh_column + sample_index * width_cells] =
                            vertices[mesh_column + (sample_index - 1) * width_cells];
                        vertices[mesh_column + sample_index * width_cells].z += width_or_scale;
                        vertex_colours[mesh_column + sample_index * width_cells].store_color4f(
                            0.0f, 0.0f, 0.0f, 0.0f);
                    }

                    if (vertices[mesh_column + sample_index * width_cells].y < 0.0f) {
                        float lowered_y = vertices[mesh_column + sample_index * width_cells].y;
                        lowered_y *= WORM_UNDERSIDE_SCALE;
                        vertices[mesh_column + sample_index * width_cells].y = lowered_y;
                    }

                    ++mesh_column;
                } while (mesh_column < width_cells);
            }

            ++sample_index;
        } while (sample_index <= segment_count);
    }

    sample_index = 0;
    if (segment_count > 0) {
        do {
            mesh_column = 0;
            if (width_cells > 0) {
                float row_v = (float)sample_index * WORM_UV_ROW_STEP;
                float next_row_v = (float)(sample_index + 1) * WORM_UV_ROW_STEP;
                do {
                    int next_column = mesh_column + 1;
                    column_as_float = (float)mesh_column;
                    float next_column_f = (float)next_column;
                    int side = 0;
                    do {
                        int face_offset = side + 2 * (sample_index * width_cells + mesh_column);
                        facequads[face_offset].header_word = 0;
                        if (side == 0) {
                            facequads[face_offset].vertex_0 =
                                (unsigned short)(sample_index * width_cells + mesh_column);
                            facequads[face_offset].vertex_1 =
                                (unsigned short)(sample_index * width_cells + next_column % width_cells);
                            facequads[face_offset].vertex_2 =
                                (unsigned short)((sample_index + 1) * width_cells + next_column % width_cells);
                            facequads[face_offset].vertex_3 =
                                (unsigned short)((sample_index + 1) * width_cells + mesh_column);
                        } else {
                            facequads[face_offset].vertex_0 =
                                (unsigned short)(sample_index * width_cells + next_column % width_cells);
                            facequads[face_offset].vertex_1 =
                                (unsigned short)(sample_index * width_cells + mesh_column);
                            facequads[face_offset].vertex_2 =
                                (unsigned short)((sample_index + 1) * width_cells + mesh_column);
                            facequads[face_offset].vertex_3 =
                                (unsigned short)((sample_index + 1) * width_cells + next_column % width_cells);
                        }

                        if (side == 0) {
                            if (((mesh_column ^ sample_index) & 1) == 0)
                                facequads[face_offset].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
                            else
                                facequads[face_offset].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
                        } else {
                            if (((mesh_column ^ sample_index) & 1) == 0)
                                facequads[face_offset].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
                            else
                                facequads[face_offset].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
                        }

                        float width_f = (float)width_cells;
                        float u0 = column_as_float / width_f;
                        float u1 = next_column_f / width_f;
                        if (side == 0) {
                            facequads[face_offset].u0 = u0;
                            facequads[face_offset].v0 = row_v;
                            facequads[face_offset].u1 = u1;
                            facequads[face_offset].v1 = row_v;
                            facequads[face_offset].u2 = u1;
                            facequads[face_offset].v2 = next_row_v;
                            facequads[face_offset].u3 = u0;
                            facequads[face_offset].v3 = next_row_v;
                        } else {
                            facequads[face_offset].u0 = u1;
                            facequads[face_offset].v0 = row_v;
                            facequads[face_offset].u1 = u0;
                            facequads[face_offset].v1 = row_v;
                            facequads[face_offset].u2 = u0;
                            facequads[face_offset].v2 = next_row_v;
                            facequads[face_offset].u3 = u1;
                            facequads[face_offset].v3 = next_row_v;
                        }

                        ++side;
                    } while (side < 2);

                    ++mesh_column;
                } while (mesh_column < width_cells);
            }

            ++sample_index;
        } while (sample_index < segment_count);
    }

    CalcLengthZ();
}
