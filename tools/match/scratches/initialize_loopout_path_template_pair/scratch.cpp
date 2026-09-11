// initialize_loopout_path_template_pair @ 0x41c5f0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

void cRPath::initialize_loopout_path_template_pair(
    float curve_source, int width_cells_, bool side_exit,
    char *texture_a, char *texture_b, char *cap_texture)
{
    int curve_count;
    int i;

    kind = PATH_TEMPLATE_KIND_LOOPOUT;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    curve_count = (int)(curve_source * 6.2831855f);
    width_or_scale = 1.0f;
    segment_count = curve_count + 14;
    segment_count_f = (float)(curve_count + 14);
    float curve_count_f = (float)curve_count;
    float loop_radius = curve_count_f * 0.15915494f;
    GetNodes();
    has_entry_mesh_transition = 1;

    for (i = 0; i < 10; ++i)
    {
        float z = (float)i;
        float z_taper = z * 0.11111111f;
        primary_samples[i].center_x =
            (float)width_cells * 0.5f - 4.0f - z_taper * 0.30000001f;
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

    int departure_start = curve_count + 10;
    for (i = 0; i < 4; ++i)
    {
        int sample_index = departure_start + i;
        primary_samples[sample_index].center_x =
            (1.0f - (float)i * 0.33333334f) * 0.30000001f +
            (4.0f - (float)width_cells * 0.5f);
        primary_samples[sample_index].rotation_scalar_98 = 0.0f;
        primary_samples[sample_index].rotation_scalar_94 = 0.0f;
        primary_samples[sample_index].special_scalar = 0.0f;
        primary_samples[sample_index].lateral_scale = 1.0f;
        primary_samples[sample_index].transform.Identity();
        primary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        primary_samples[sample_index].transform.position.y = 0.0f;
        primary_samples[sample_index].transform.position.z = (float)(i + 10);
        primary_samples[sample_index].delta_length = 1.0f;

        secondary_samples[sample_index].transform.Identity();
        secondary_samples[sample_index].transform.position.x =
            primary_samples[sample_index].center_x;
        secondary_samples[sample_index].transform.position.y = 0.49000001f;
        secondary_samples[sample_index].transform.position.z = (float)(i + 10);
        secondary_samples[sample_index].delta_length = 1.0f;
    }

    Vector3 circle_center(0.0f, -loop_radius, 10.0f);
    i = 0;
    if (curve_count > 0)
    {
        float secondary_radius = loop_radius + 0.49000001f;
        do
        {
            int sample_index = i + 10;
            float sample_f = (float)i;
            float angle = sample_f * 6.2831855f / curve_count_f;
            PathAttachmentSample *curve_samples = primary_samples;
            curve_samples[sample_index].center_x =
                (curve_samples[departure_start].center_x -
                 curve_samples[0].center_x) *
                    sample_f / curve_count_f +
                curve_samples[0].center_x;
            primary_samples[sample_index].center_x +=
                Sin(angle * 0.5f + 4.712389f) * 0.30000001f;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            primary_samples[sample_index].transform.Identity();
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                Sin(angle) * loop_radius + circle_center.z;
            primary_samples[sample_index].transform.position.y =
                Cos(angle) * loop_radius + circle_center.y;

            secondary_samples[sample_index].transform.Identity();
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                Sin(angle) * secondary_radius + circle_center.z;
            secondary_samples[sample_index].transform.position.y =
                Cos(angle) * secondary_radius + circle_center.y;

            primary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            primary_samples[sample_index].transform.basis_up.x = 0.0f;
            primary_samples[sample_index].transform.basis_up.y =
                -(circle_center.y - primary_samples[sample_index].transform.position.y);
            primary_samples[sample_index].transform.basis_up.z =
                -(circle_center.z - primary_samples[sample_index].transform.position.z);
            primary_samples[sample_index].transform.basis_up.Normalize();
            primary_samples[sample_index].transform.basis_forward.Cross(
                primary_samples[sample_index].transform.basis_right,
                primary_samples[sample_index].transform.basis_up);

            secondary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            secondary_samples[sample_index].transform.basis_up.x = 0.0f;
            secondary_samples[sample_index].transform.basis_up.y =
                -(circle_center.y - secondary_samples[sample_index].transform.position.y);
            secondary_samples[sample_index].transform.basis_up.z =
                -(circle_center.z - secondary_samples[sample_index].transform.position.z);
            secondary_samples[sample_index].transform.basis_up.Normalize();
            secondary_samples[sample_index].transform.basis_forward.Cross(
                secondary_samples[sample_index].transform.basis_right,
                secondary_samples[sample_index].transform.basis_up);
            ++i;
        } while (i < curve_count);
    }

    for (i = 0; i < segment_count - 1; ++i)
    {
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
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    Vector3 *vertices = strip_mesh->vertices;
    cRFaceQuad *facequads = strip_mesh->facequads;

    int mesh_row;
    int mesh_column;
    int face_row;
    int face_column;
    int face_index;

    for (mesh_row = 0; mesh_row <= segment_count; ++mesh_row)
    {
        for (mesh_column = 0; mesh_column <= width_cells; ++mesh_column)
        {
            double lateral = (float)mesh_column - (float)width_cells * 0.5f;
            if (mesh_row != segment_count)
            {
                Vector3 lateral_offset = primary_samples[mesh_row].transform.basis_right * lateral;
                Vector3 generated_position = primary_samples[mesh_row].transform.position + lateral_offset;
                Vector3 *vertex = &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
            }
            else
            {
                Vector3 lateral_offset = primary_samples[mesh_row - 1].transform.basis_right * lateral;
                Vector3 endpoint = primary_samples[mesh_row - 1].transform.position + Vector3(0.0f, 0.0f, 1.0f);
                Vector3 generated_position = endpoint + lateral_offset;
                Vector3 *vertex = &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
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
                face_index = 0;
                next_column = face_column + 1;
                float u0 = (float)face_column * 0.125f;
                float u1 = (float)(face_column + 1) * 0.125f;
                for (; face_index < 2; ++face_index) {
                    int face_array_index =
                        face_index
                        + 2 * (face_row * width_cells + face_column);
                    if (face_index == 0) {
                        facequads[face_array_index].header_word = 0;
                        facequads[face_array_index].vertex_0 = face_column + face_row * ((unsigned short)width_cells + 1);
                        facequads[face_array_index].vertex_1 = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        facequads[face_array_index].vertex_2 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        facequads[face_array_index].vertex_3 =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        if ((face_column & 1) == (face_row & 1))
                            facequads[face_array_index].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_array_index].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        facequads[face_array_index].header_word = 0;
                        facequads[face_array_index].vertex_0 = face_row * ((unsigned short)width_cells + 1) + face_column + 1;
                        facequads[face_array_index].vertex_1 = face_column + face_row * ((unsigned short)width_cells + 1);
                        facequads[face_array_index].vertex_2 =
                            face_column + (face_row + 1) * ((unsigned short)width_cells + 1);
                        facequads[face_array_index].vertex_3 =
                            (face_row + 1) * ((unsigned short)width_cells + 1) + face_column + 1;
                        if ((face_column & 1) == (face_row & 1))
                            facequads[face_array_index].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_array_index].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                    }
                    if (face_index == 0) {
                        facequads[face_array_index].uv[0].u = u0;
                        facequads[face_array_index].uv[0].v = v0;
                        facequads[face_array_index].uv[1].u = u1;
                        facequads[face_array_index].uv[1].v = v0;
                        facequads[face_array_index].uv[2].u = u1;
                        facequads[face_array_index].uv[2].v = v1;
                        facequads[face_array_index].uv[3].u = u0;
                        facequads[face_array_index].uv[3].v = v1;
                    } else {
                        facequads[face_array_index].uv[0].u = u1;
                        facequads[face_array_index].uv[0].v = v0;
                        facequads[face_array_index].uv[1].u = u0;
                        facequads[face_array_index].uv[1].v = v0;
                        facequads[face_array_index].uv[2].u = u0;
                        facequads[face_array_index].uv[2].v = v1;
                        facequads[face_array_index].uv[3].u = u1;
                        facequads[face_array_index].uv[3].v = v1;
                    }
                }
                face_column = next_column;
            } while (next_column < width_cells);
        }
    }

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
