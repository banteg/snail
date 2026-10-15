// initialize_loopbow_path_template_pair @ 0x42ba80 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"

float Sin(float angle);
float Cos(float angle);

// The native caller ignores the incidental EAX state left by this finalizer.
void __fastcall calc_path_length_z(Path* path);

void cRPath::initialize_loopbow_path_template_pair(
    float curve_scale,
    unsigned int width_cells_arg,
    bool mode,
    char* texture_a,
    char* texture_b,
    char* vertical_texture)
{
    int cell_index = 0;
    kind = (PathTemplateKind)cell_index;
    float center_offset = 0.0f;
    if (width_cells_arg == 4) {
        kind = (PathTemplateKind)cell_index;
        center_offset = 0.5f;
    }

    is_mirrored_x = 0;
    side_exit_mode = cell_index;
    width_cells = width_cells_arg;

    int curve_segment_count = (int)(curve_scale * 6.2831855f);
    int total_segment_count = curve_segment_count + 14;
    width_or_scale = 1.0f;
    segment_count = total_segment_count;
    segment_count_f = (float)total_segment_count;

    float curve_segment_count_f = (float)curve_segment_count;
    curve_scale = curve_segment_count_f * 0.15915494f;

    GetNodes();
    has_entry_mesh_transition = 1;

    int i = 0;
    do {
        float fi = (float)i;
        float center_progress = fi * 0.14285715f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).center_x =
            (float)width_cells * 0.5f - 4.0f
            - center_progress * center_offset;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).rotation_scalar_98 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).rotation_scalar_94 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).special_scalar = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).lateral_scale = 1.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).transform.position.x = (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).transform.position.y = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).transform.position.z = fi;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).delta_length = 1.0f;

        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).transform.position.x = (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).transform.position.y = 0.49000001f;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).transform.position.z = fi;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).delta_length = 1.0f;
        ++i;
    } while (i < 7);

    i = 0;
    int sample_index = curve_segment_count + 7;
    do {
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x =
            (1.0f - (float)i * 0.16666667f) * center_offset
            + (4.0f - (float)width_cells * 0.5f);
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_98 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_94 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).special_scalar = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).lateral_scale = 1.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y = 0.0f;
        float z = (float)(i + 7);
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z = z;
        (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).delta_length = 1.0f;

        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
        ++i;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y = 0.49000001f;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z = z;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).delta_length = 1.0f;
        ++sample_index;
    } while (i < 7);

    i = 0;
    if (curve_segment_count > 0) {
        float secondary_radius = curve_scale - 0.49000001f;
        Vector3 primary_right(1.0f, 0.0f, 0.0f);
        Vector3 secondary_right(1.0f, 0.0f, 0.0f);

        do {
            float fi = (float)i;
            float angle = fi * 6.2831855f / curve_segment_count_f;
            int sample_index = i + 7;

            AttachmentSample* const& bank = primary_samples;
            float last_center = bank[total_segment_count - 1].center_x;
            bank[sample_index].center_x =
                (last_center
                    - bank[0].center_x)
                    * fi / curve_segment_count_f
                + bank[0].center_x;

            float half_angle = angle * 0.5f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x =
                Sin(half_angle + 4.712389f) * center_offset
                + (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_98 = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_94 = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).special_scalar = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).lateral_scale = 1.0f;

            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z =
                Sin(angle) * curve_scale + 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y =
                curve_scale - Cos(angle) * curve_scale;

            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).center_x;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z =
                Sin(angle) * secondary_radius + 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y =
                curve_scale - Cos(angle) * secondary_radius;

            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right = primary_right;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.x = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.y =
                curve_scale
                - (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.z =
                7.0f - (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.Normalize();
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_forward.Cross(
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right,
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up);

            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right = secondary_right;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.x = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.y =
                curve_scale
                - (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.y;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.z =
                7.0f - (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.Normalize();
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_forward.Cross(
                (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right,
                (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up);

            TransformMatrix rotation;
            rotation.Identity();
            float half_sine = Sin(half_angle);
            rotation.RotLocalY(
                Sin(half_angle) * half_sine * 0.52359879f);

            float primary_z_pivot = (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z;
            primary_z_pivot -= 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z = primary_z_pivot;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z -= 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Multiply(rotation);
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.Multiply(rotation);
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z += 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position.z += 7.0f;

            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform;

            Vector3 secondary_offset =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up * 0.49000001f;
            Vector3* secondary_position =
                &(*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (sample_index) * sizeof(AttachmentSample))))).transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;

            ++i;
        } while (i < curve_segment_count);
    }

    i = 0;
    if (segment_count - 1 > 0) {
        do {
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).delta_dir_to_next =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i + 1) * sizeof(AttachmentSample))))).transform.position
                - (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).transform.position;
            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).delta_length =
                (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (i) * sizeof(AttachmentSample))))).delta_dir_to_next.Normalize();

            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).delta_dir_to_next =
                (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i + 1) * sizeof(AttachmentSample))))).transform.position
                - (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).transform.position;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).delta_length =
                (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (i) * sizeof(AttachmentSample))))).delta_dir_to_next.Normalize();
            ++i;
        } while (i < segment_count - 1);
    }

    (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (segment_count - 1) * sizeof(AttachmentSample))))).delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (segment_count - 1) * sizeof(AttachmentSample))))).delta_length = 1.0f;
    (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (segment_count - 1) * sizeof(AttachmentSample))))).delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    (*((AttachmentSample *)((char *)((unsigned int)secondary_samples + (segment_count - 1) * sizeof(AttachmentSample))))).delta_length = 1.0f;

    strip_mesh->RequestVertices(
        (segment_count + 1) * (width_cells + 1));
    strip_mesh->RequestFaceQuads(
        2 * segment_count * width_cells);

    Vector3 *vertices = strip_mesh->vertices;
    cRFaceQuad *facequads = strip_mesh->facequads;

    cell_index = 0;
    if (segment_count >= 0)
    {
        do
        {
            i = 0;
            if (width_cells >= 0)
            {
                do
                {
                    if (cell_index != segment_count)
                    {
                        double lateral = (float)i - (float)width_cells * 0.5f;
                        Vector3 lateral_offset =
                            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (cell_index) * sizeof(AttachmentSample))))).transform.basis_right * lateral;
                        Vector3 point =
                            lateral_offset + (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (cell_index) * sizeof(AttachmentSample))))).transform.position;
                        int vertex_index = i + cell_index * (width_cells + 1);
                        vertices[vertex_index] = point;
                    }
                    else
                    {
                        double lateral = (float)i - (float)width_cells * 0.5f;
                        Vector3 lateral_offset =
                            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (cell_index - 1) * sizeof(AttachmentSample))))).transform.basis_right * lateral;
                        Vector3 endpoint =
                            (*((AttachmentSample *)((char *)((unsigned int)primary_samples + (cell_index - 1) * sizeof(AttachmentSample))))).transform.position +
                            Vector3(0.0f, 0.0f, 1.0f);
                        Vector3 point = endpoint + lateral_offset;
                        int vertex_index = i + cell_index * (width_cells + 1);
                        vertices[vertex_index] = point;
                    }
                    ++i;
                } while (i <= width_cells);
            }
            ++cell_index;
        } while (cell_index <= segment_count);
    }

    cell_index = 0;
    if (segment_count > 0) {
        do {
            i = 0;
            if (width_cells > 0) {
                float v0 = (float)(cell_index % 8) * 0.125f;
                float v1 = (float)(cell_index % 8 + 1) * 0.125f;
                do {
                    int side = 0;
                    int next_cell = i + 1;
                    float u0 = (float)i * 0.125f;
                    float u1 = (float)(i + 1) * 0.125f;
                    do {
                        int face_offset =
                            side
                            + 2 * (i + cell_index * width_cells);
                        if (side == 0) {
                            facequads[face_offset].header_word = 0;
                            facequads[face_offset].vertex_0 =
                                i + cell_index * (width_cells + 1);
                            facequads[face_offset].vertex_1 =
                                cell_index * (width_cells + 1) + i + 1;
                            facequads[face_offset].vertex_2 =
                                (cell_index + 1) * (width_cells + 1)
                                + i + 1;
                            facequads[face_offset].vertex_3 =
                                i + (cell_index + 1) * (width_cells + 1);

                            if (((i ^ cell_index) & 1) == 0) {
                                facequads[face_offset].texture_ref =
                                    g_texture_refs.Add(
                                        texture_a, 0, 0);
                            } else {
                                facequads[face_offset].texture_ref =
                                    g_texture_refs.Add(
                                        texture_a, 0, 0);
                            }
                        } else {
                            facequads[face_offset].header_word = 0;
                            facequads[face_offset].vertex_0 =
                                cell_index * (width_cells + 1) + i + 1;
                            facequads[face_offset].vertex_1 =
                                i + cell_index * (width_cells + 1);
                            facequads[face_offset].vertex_2 =
                                i + (cell_index + 1) * (width_cells + 1);
                            facequads[face_offset].vertex_3 =
                                (cell_index + 1) * (width_cells + 1)
                                + i + 1;

                            if (((i ^ cell_index) & 1) == 0) {
                                facequads[face_offset].texture_ref =
                                    g_texture_refs.Add(
                                        texture_b, 0, 0);
                            } else {
                                facequads[face_offset].texture_ref =
                                    g_texture_refs.Add(
                                        texture_b, 0, 0);
                            }
                        }
                        if (side == 0) {
                            facequads[face_offset].u0 = u0;
                            facequads[face_offset].v0 = v0;
                            facequads[face_offset].u1 = u1;
                            facequads[face_offset].v1 = v0;
                            facequads[face_offset].u2 = u1;
                            facequads[face_offset].v2 = v1;
                            facequads[face_offset].u3 = u0;
                            facequads[face_offset].v3 = v1;
                        } else {
                            facequads[face_offset].u0 = u1;
                            facequads[face_offset].v0 = v0;
                            facequads[face_offset].u1 = u0;
                            facequads[face_offset].v1 = v0;
                            facequads[face_offset].u2 = u0;
                            facequads[face_offset].v2 = v1;
                            facequads[face_offset].u3 = u1;
                            facequads[face_offset].v3 = v1;
                        }
                        ++side;
                    } while (side < 2);
                    i = next_cell;
                } while (i < width_cells);
            }
            ++cell_index;
        } while (cell_index < segment_count);
    }

    ::calc_path_length_z(this);
}
