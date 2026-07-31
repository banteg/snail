// initialize_snake_path_template_pair @ 0x423580 (thiscall, ret 0x18)

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
            if (row != path->segment_count) {
                PathTemplateSample* sample = &path->primary_samples[row];
                Vector3 lateral_offset =
                    sample->transform.basis_right * lateral;
                Vector3 generated_position =
                    sample->transform.position + lateral_offset;
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
            } else {
                PathTemplateSample* previous = &path->primary_samples[row - 1];
                Vector3 lateral_offset =
                    previous->transform.basis_right * lateral;
                Vector3 endpoint(
                    previous->transform.position.x,
                    previous->transform.position.y,
                    previous->transform.position.z + 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;
                Vector3* vertex =
                    &vertices[column + row * (path->width_cells + 1)];
                *vertex = generated_position;
            }
        }
    }

    for (row = 0; row < path->segment_count; ++row) {
        if (path->width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            column = 0;
            int next_column;
            do {
                next_column = column + 1;
                float u0 = (float)column * 0.125f;
                float u1 = (float)next_column * 0.125f;
                int face_index;
                for (face_index = 0; face_index < 2; ++face_index) {
                    int face_offset =
                        2 * column
                        + 2 * row * path->width_cells + face_index;
                    if (face_index == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_3 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        if ((column ^ row) & 1) {
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
                        facequads[face_offset].vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                        facequads[face_offset].vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            column + (row + 1) * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                        if ((column ^ row) & 1) {
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
                column = next_column;
            } while (next_column < path->width_cells);
        }
    }
}

void cRPath::initialize_snake_path_template_pair(
    float scale_arg,
    int width_cells_,
    bool side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    kind = PATH_TEMPLATE_KIND_SNAKE;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    width_or_scale = 1.0f;
    segment_count = 27;
    segment_count_f = 27.0f;
    get_path_nodes();
    has_entry_mesh_transition = 0;

    int i;
    int lead_offset;

    for (i = 0, lead_offset = 0;
         lead_offset < 6 * (int)sizeof(PathTemplateSample);
         ++i, lead_offset += (int)sizeof(PathTemplateSample)) {
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->center_x = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->lateral_scale = 1.0f;
        set_matrix_identity(&((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform);
        float z = (float)i;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.x = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.y = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.z = z;

        set_matrix_identity(&((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform);
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.x = 0.0f;
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.z = z;
    }

    int departure_index = 24;
    int departure_offset = 24 * (int)sizeof(PathTemplateSample);
    do {
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))->center_x =
            4.0f - (float)width_cells * 0.5f;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->lateral_scale = 1.0f;
        set_matrix_identity(
            &((PathTemplateSample*)((char*)primary_samples + departure_offset))
                ->transform);
        float z = (float)departure_index;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + departure_offset))
                ->center_x;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_offset))
            ->transform.position.z = z;

        set_matrix_identity(
            &((PathTemplateSample*)((char*)secondary_samples + departure_offset))
                ->transform);
        ((PathTemplateSample*)((char*)secondary_samples + departure_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + departure_offset))
                ->center_x;
        ((PathTemplateSample*)((char*)secondary_samples + departure_offset))
            ->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + departure_offset))
            ->transform.position.z = z;
        departure_offset += (int)sizeof(PathTemplateSample);
        ++departure_index;
    } while (departure_index - 24 < 3);

    int curve_index = 0;
    for (i = 6 * (int)sizeof(PathTemplateSample);
         i < 24 * (int)sizeof(PathTemplateSample);
         i += (int)sizeof(PathTemplateSample)) {
        float angle = (float)curve_index * 0.34906587f;
        ((PathTemplateSample*)((char*)primary_samples + i))->center_x =
            (0.5f - cosine(angle * 0.5f) * 0.5f)
            * primary_samples[24].center_x;
        ((PathTemplateSample*)((char*)primary_samples + i))->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + i))->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + i))->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + i))->lateral_scale = 1.0f;
        set_matrix_identity(
            &((PathTemplateSample*)((char*)primary_samples + i))->transform);
        ((PathTemplateSample*)((char*)primary_samples + i))->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + i))->center_x;
        ((PathTemplateSample*)((char*)primary_samples + i))->transform.position.y =
            -(1.0f - cosine(angle));
        float z = (float)(curve_index + 6);
        ((PathTemplateSample*)((char*)primary_samples + i))->transform.position.z = z;

        set_matrix_identity(
            &((PathTemplateSample*)((char*)secondary_samples + i))->transform);
        ((PathTemplateSample*)((char*)secondary_samples + i))->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + i))->center_x;
        ((PathTemplateSample*)((char*)secondary_samples + i))->transform.position.y =
            0.49000001f - (1.0f - cosine(angle));
        ((PathTemplateSample*)((char*)secondary_samples + i))->transform.position.z = z;

        if (i <= 6 * (int)sizeof(PathTemplateSample)) {
            ((PathTemplateSample*)((char*)primary_samples + i) - 1)
                ->transform.RotIdentity();
            ((PathTemplateSample*)((char*)secondary_samples + i) - 1)
                ->transform.RotIdentity();
        } else {
            PathTemplateSample* primary_current =
                (PathTemplateSample*)((char*)primary_samples + i);
            PathTemplateSample* primary_previous = primary_current - 1;
            PathTemplateSample* secondary_current =
                (PathTemplateSample*)((char*)secondary_samples + i);
            PathTemplateSample* secondary_previous = secondary_current - 1;
            primary_previous->transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            primary_previous->transform.basis_forward = Vector3(
                primary_current->transform.position.x
                    - primary_previous->transform.position.x,
                primary_current->transform.position.y
                    - primary_previous->transform.position.y,
                primary_current->transform.position.z
                    - primary_previous->transform.position.z);
            primary_previous->transform.basis_forward.Normalize();
            primary_previous->transform.basis_up.cross_vectors(
                &primary_previous->transform.basis_forward,
                &primary_previous->transform.basis_right);

            secondary_previous->transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            secondary_previous->transform.basis_forward = Vector3(
                secondary_current->transform.position.x
                    - secondary_previous->transform.position.x,
                secondary_current->transform.position.y
                    - secondary_previous->transform.position.y,
                secondary_current->transform.position.z
                    - secondary_previous->transform.position.z);
            secondary_previous->transform.basis_forward.Normalize();
            secondary_previous->transform.basis_up.cross_vectors(
                &secondary_previous->transform.basis_forward,
                &secondary_previous->transform.basis_right);
        }
        ++curve_index;
    }

    int delta_index = 0;
    int delta_offset = 0;
    if (segment_count - 1 > 0) {
        do {
            ((PathTemplateSample*)((char*)primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)primary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)primary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)primary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample*)((char*)secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)secondary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)secondary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)secondary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)secondary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ++delta_index;
            delta_offset += (int)sizeof(PathTemplateSample);
        } while (delta_index < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
    (void)scale_arg;
    (void)side_exit;
    (void)cap_texture;
}
