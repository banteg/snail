// initialize_supertramp_path_template_pair @ 0x423f10 (thiscall, ret 0x1c)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void build_direct_strip_mesh(
    Path* path,
    char* top_texture,
    char* bottom_texture,
    char* cap_texture)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    Vector3* vertices = path->strip_mesh->vertices;
    cRFaceQuad* facequads = path->strip_mesh->facequads;
    int row;
    int column;

    row = 0;
    if (path->segment_count >= 0) {
        int sample_offset = 0;
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    PathTemplateSample* sample = (PathTemplateSample*)(
                        (char*)path->primary_samples + sample_offset);
                    float lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    Vector3* vertex =
                        &vertices[column + row * (path->width_cells + 1)];
                    Vector3 lateral_offset(
                        lateral * sample->transform.basis_right.x,
                        lateral * sample->transform.basis_right.y,
                        lateral * sample->transform.basis_right.z);
                    Vector3 generated_position =
                        sample->transform.position + lateral_offset;
                    *vertex = generated_position;
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (int face_row = 0; face_row < path->segment_count; ++face_row) {
        int face_column = 0;
        if (path->width_cells > 0) {
            float v0 = (float)(face_row % 8) * 0.125f;
            float v1 = (float)(face_row % 8 + 1) * 0.125f;
            do {
                float u0 = (float)face_column * 0.125f;
                float u1 = (float)(face_column + 1) * 0.125f;
                int side = 0;
                do {
                    int face_offset =
                        side
                        + 2 * (face_column + face_row * path->width_cells);
                    if (side == 0) {
                        facequads[face_offset].header_word = 0;
                        facequads[face_offset].vertex_0 =
                            face_column +
                            face_row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_1 = face_row *
                                ((unsigned short)path->width_cells + 1) +
                            face_column + 1;
                        facequads[face_offset].vertex_2 = (face_row + 1) *
                                ((unsigned short)path->width_cells + 1) +
                            face_column + 1;
                        facequads[face_offset].vertex_3 = face_column +
                            (face_row + 1) *
                                ((unsigned short)path->width_cells + 1);
                        if (face_row == path->segment_count - 1) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(
                                    cap_texture, 0, 0);
                        } else if ((face_column ^ face_row) & 1) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(
                                    top_texture, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(
                                    top_texture, 0, 0);
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
                        facequads[face_offset].vertex_0 = face_row *
                                ((unsigned short)path->width_cells + 1) +
                            face_column + 1;
                        facequads[face_offset].vertex_1 =
                            face_column +
                            face_row * ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_2 = face_column +
                            (face_row + 1) *
                                ((unsigned short)path->width_cells + 1);
                        facequads[face_offset].vertex_3 = (face_row + 1) *
                                ((unsigned short)path->width_cells + 1) +
                            face_column + 1;
                        if ((face_column ^ face_row) & 1) {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(
                                    bottom_texture, 0, 0);
                        } else {
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(
                                    bottom_texture, 0, 0);
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
                    ++side;
                } while (side < 2);
                ++face_column;
            } while (face_column < path->width_cells);
        }
    }
}

void cRPath::initialize_supertramp_path_template_pair(
    float length,
    int width_cells_,
    bool side_exit,
    char* texture_a,
    char* texture_b,
    char* unused_texture,
    char* cap_texture)
{
    kind = PATH_TEMPLATE_KIND_SUPERTRAMP;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int curve_segments = (int)(length * 1.0461504f);
    width_or_scale = 1.0f;
    segment_count = curve_segments + 8;
    segment_count_f = (float)(segment_count - 1);
    float curve_segments_f = (float)curve_segments;
    float radius = curve_segments_f * 0.95588547f;
    GetNodes();
    has_entry_mesh_transition = 0;
    segment_count = segment_count - 1;

    int lead_sample_index;
    int lead_offset;
    for (lead_sample_index = 0, lead_offset = 0;
         lead_offset < 7 * (int)sizeof(PathTemplateSample);
         ++lead_sample_index, lead_offset += (int)sizeof(PathTemplateSample)) {
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->center_x = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->lateral_scale = 1.0f;
        set_matrix_identity(&((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform);
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + lead_offset))->center_x;
        float z = (float)lead_sample_index;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.y = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->transform.position.z = z;
        ((PathTemplateSample*)((char*)primary_samples + lead_offset))->delta_length = 1.0f;

        set_matrix_identity(&((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform);
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + lead_offset))->center_x;
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->transform.position.z = z;
        ((PathTemplateSample*)((char*)secondary_samples + lead_offset))->delta_length = 1.0f;
    }

    if (curve_segments >= 0) {
        float secondary_radius = radius - 0.49000001f;
        int curve_index = 0;
        do {
            int sample_index = curve_index + 7;
            float angle =
                (float)curve_index * 1.0461504f / curve_segments_f;

            primary_samples[sample_index].center_x = 0.0f;
            primary_samples[sample_index].rotation_scalar_98 = 0.0f;
            primary_samples[sample_index].rotation_scalar_94 = 0.0f;
            primary_samples[sample_index].special_scalar = 0.0f;
            primary_samples[sample_index].lateral_scale = 1.0f;
            set_matrix_identity(&primary_samples[sample_index].transform);
            primary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            primary_samples[sample_index].transform.position.z =
                sine(angle) * radius + 7.0f;
            primary_samples[sample_index].transform.position.y =
                radius - cosine(angle) * radius;

            set_matrix_identity(&secondary_samples[sample_index].transform);
            secondary_samples[sample_index].transform.position.x =
                primary_samples[sample_index].center_x;
            secondary_samples[sample_index].transform.position.z =
                sine(angle) * secondary_radius + 7.0f;
            secondary_samples[sample_index].transform.position.y =
                radius - cosine(angle) * secondary_radius;

            primary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            primary_samples[sample_index].transform.basis_up.x = 0.0f;
            primary_samples[sample_index].transform.basis_up.y =
                radius - primary_samples[sample_index].transform.position.y;
            primary_samples[sample_index].transform.basis_up.z =
                7.0f - primary_samples[sample_index].transform.position.z;
            primary_samples[sample_index].transform.basis_up.Normalize();
            primary_samples[sample_index].transform.basis_forward.cross_vectors(
                &primary_samples[sample_index].transform.basis_right,
                &primary_samples[sample_index].transform.basis_up);

            secondary_samples[sample_index].transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            secondary_samples[sample_index].transform.basis_up.x = 0.0f;
            secondary_samples[sample_index].transform.basis_up.y =
                radius - secondary_samples[sample_index].transform.position.y;
            secondary_samples[sample_index].transform.basis_up.z =
                7.0f - secondary_samples[sample_index].transform.position.z;
            secondary_samples[sample_index].transform.basis_up.Normalize();
            secondary_samples[sample_index].transform.basis_forward.cross_vectors(
                &secondary_samples[sample_index].transform.basis_right,
                &secondary_samples[sample_index].transform.basis_up);
            ++curve_index;
        } while (curve_index <= curve_segments);
    }

    int delta_index = 0;
    if (segment_count > 0) {
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
        } while (delta_index < segment_count);
    }
    build_direct_strip_mesh(this, texture_a, texture_b, cap_texture);
    CalcLengthZ();
    (void)side_exit;
    (void)unused_texture;
}
