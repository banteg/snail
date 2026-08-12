// initialize_p_path_template_pair @ 0x425a40 (thiscall, ret 0x24)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void build_strip_mesh(Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;
    int row;
    int column;

    for (row = 0; row <= path->segment_count; ++row) {
        for (column = 0; column <= path->width_cells; ++column) {
            double lateral = (float)column - (float)path->width_cells * 0.5f;
            PathTemplateSample* sample = &path->primary_samples[row];
            int vertex_index = column + row * (path->width_cells + 1);
            if (row != path->segment_count) {
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position(
                    sample->transform.position.x + lateral_offset.x,
                    sample->transform.position.y + lateral_offset.y,
                    sample->transform.position.z + lateral_offset.z);
                vertices[vertex_index] = generated_position;
            } else {
                PathTemplateSample* previous = sample - 1;
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;
                vertices[vertex_index] = generated_position;
            }
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            int face_index;
            for (face_index = 0; face_index < 2; ++face_index) {
                int face_offset = face_index + 2 * (row * path->width_cells + column);
                if (face_index == 0) {
                    facequads[face_offset].header_word = 0;
                    facequads[face_offset].vertex_0 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_1 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_2 =
                        (row + 1) * ((unsigned short)path->width_cells + 1)
                        + column + 1;
                    facequads[face_offset].vertex_3 =
                        column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    if (!((column ^ row) & 1)) {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_a, 0, 0);
                    }
                    facequads[face_offset].uv[0].u = u0;
                    facequads[face_offset].uv[0].v = v0;
                    facequads[face_offset].uv[1].u = u1;
                    facequads[face_offset].uv[1].v = v0;
                    facequads[face_offset].uv[2].u = u1;
                    facequads[face_offset].uv[2].v = v1;
                    facequads[face_offset].uv[3].u = u0;
                    facequads[face_offset].uv[3].v = v1;
                } else {
                    facequads[face_offset].header_word = 0;
                    facequads[face_offset].vertex_0 =
                        row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_1 =
                        column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_2 =
                        column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_3 =
                        (row + 1) * ((unsigned short)path->width_cells + 1)
                        + column + 1;
                    if (!((column ^ row) & 1)) {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    } else {
                        facequads[face_offset].texture_ref =
                            g_texture_refs.Add(texture_b, 0, 0);
                    }
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
        }
    }
}

void cRPath::initialize_p_path_template_pair(
    int variant,
    float scale_arg,
    int width_cells_,
    float start_x,
    float end_x,
    int curve_segments,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = (PathTemplateKind)(variant + 0x21);
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    int last_index = curve_segments + 1;
    int sample_count = last_index + 1;
    segment_count = sample_count;
    segment_count_f = (float)sample_count;

    float half_distance = (end_x - start_x) * 0.5f;
    if (half_distance < 0.0f)
        scale_arg = -half_distance;
    else
        scale_arg = half_distance;

    GetNodes();
    has_entry_mesh_transition = 0;

    primary_samples[0].center_x = start_x;
    primary_samples[0].rotation_scalar_98 = 0.0f;
    primary_samples[0].rotation_scalar_94 = 0.0f;
    primary_samples[0].special_scalar = 0.0f;
    primary_samples[0].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[0].transform);
    primary_samples[0].transform.position.x = primary_samples[0].center_x;
    primary_samples[0].transform.position.y = 0.0f;
    primary_samples[0].transform.position.z = 0.0f;
    set_matrix_identity(&secondary_samples[0].transform);
    secondary_samples[0].transform.position.x = primary_samples[0].center_x;
    secondary_samples[0].transform.position.y = 0.49000001f;
    secondary_samples[0].transform.position.z = 0.0f;

    primary_samples[last_index].center_x = end_x;
    primary_samples[last_index].rotation_scalar_98 = 0.0f;
    primary_samples[last_index].rotation_scalar_94 = 0.0f;
    primary_samples[last_index].special_scalar = 0.0f;
    primary_samples[last_index].lateral_scale = 1.0f;
    set_matrix_identity(&primary_samples[last_index].transform);
    float terminal_z = (float)last_index;
    primary_samples[last_index].transform.position.x = primary_samples[last_index].center_x;
    primary_samples[last_index].transform.position.y = 0.0f;
    primary_samples[last_index].transform.position.z = terminal_z;
    set_matrix_identity(&secondary_samples[last_index].transform);
    secondary_samples[last_index].transform.position.x = primary_samples[last_index].center_x;
    secondary_samples[last_index].transform.position.y = 0.49000001f;
    secondary_samples[last_index].transform.position.z = terminal_z;

    int curve_index = 0;
    if (curve_segments > 0) {
        float curve_segments_f = (float)curve_segments;
        int i = 1;
        int curve_sample_offset = sizeof(PathTemplateSample);
        do {
            float angle = (float)curve_index * 3.1415927f / curve_segments_f;
            switch (kind) {
            case 0x21:
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->center_x =
                    sine(angle + 1.5707964f) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x22:
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->center_x =
                    2.0f - cosine(angle) * scale_arg - scale_arg + 0.5f;
                break;
            case 0x23:
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->center_x =
                    (sine(angle + 1.5707964f) + 1.0f) * scale_arg + 0.5f;
                break;
            }

            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->rotation_scalar_98 = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->rotation_scalar_94 = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->special_scalar = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->lateral_scale = 1.0f;
            set_matrix_identity(
                &((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->transform);
            ++curve_index;
            float z = (float)i;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->transform.position.y = 0.0f;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->transform.position.z = z;

            set_matrix_identity(
                &((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset))
                    ->transform);
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset))
                ->transform.position.x =
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->center_x;
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset))
                ->transform.position.y =
                ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                    ->transform.position.y + 0.49000001f;
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset))
                ->transform.position.z = z;
            PathTemplateSample* primary_previous =
                (PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1;
            PathTemplateSample* primary_current =
                (PathTemplateSample*)((char*)primary_samples + curve_sample_offset);
            PathTemplateSample* secondary_previous =
                (PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1;
            PathTemplateSample* secondary_current =
                (PathTemplateSample*)((char*)secondary_samples + curve_sample_offset);
            if (i <= 1) {
                primary_previous->transform.RotIdentity();
                secondary_previous->transform.RotIdentity();
            } else {
                primary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                primary_previous->transform.basis_forward = Vector3(
                    primary_current->transform.position.x - primary_previous->transform.position.x,
                    primary_current->transform.position.y - primary_previous->transform.position.y,
                    primary_current->transform.position.z - primary_previous->transform.position.z);
                primary_previous->transform.basis_forward.Normalize();
                primary_previous->transform.basis_right.cross_vectors(
                    &primary_previous->transform.basis_up,
                    &primary_previous->transform.basis_forward);

                secondary_previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
                secondary_previous->transform.basis_forward = Vector3(
                    secondary_current->transform.position.x - secondary_previous->transform.position.x,
                    secondary_current->transform.position.y - secondary_previous->transform.position.y,
                    secondary_current->transform.position.z - secondary_previous->transform.position.z);
                secondary_previous->transform.basis_forward.Normalize();
                secondary_previous->transform.basis_right.cross_vectors(
                    &secondary_previous->transform.basis_up,
                    &secondary_previous->transform.basis_forward);
            }
            ++i;
            curve_sample_offset += sizeof(PathTemplateSample);
        } while (curve_index < curve_segments);
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
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)cap_texture;
}
