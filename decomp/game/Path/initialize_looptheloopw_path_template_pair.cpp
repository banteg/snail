// initialize_looptheloopw_path_template_pair @ 0x41bb40 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

static inline void interpolate_path_center(
    AttachmentSample* const& bank, int sample_index, int loop_segment_count,
    float sample_f, float curve_count_f)
{
    (*((AttachmentSample *)((char *)((unsigned int)bank + (unsigned int)((sample_index) * (int)sizeof(AttachmentSample)))))).center_x =
        ((*((AttachmentSample *)((char *)((unsigned int)bank + (unsigned int)((loop_segment_count - 1) * (int)sizeof(AttachmentSample)))))).center_x - (*((AttachmentSample *)((char *)((unsigned int)bank + (unsigned int)((0) * (int)sizeof(AttachmentSample)))))).center_x)
        * sample_f / curve_count_f + (*((AttachmentSample *)((char *)((unsigned int)bank + (unsigned int)((0) * (int)sizeof(AttachmentSample)))))).center_x;
}

void cRPath::initialize_looptheloopw_path_template_pair(
    float curve_source, int width_cells_, bool side_exit,
    char* texture_a, char* texture_b, char* cap_texture)
{
    AttachmentSample* const& primary_bank = primary_samples;
    AttachmentSample* const& secondary_bank = secondary_samples;
    int curve_count;
    int i;
    float sample_f;

    kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    float loop_wiggle = 0.0f;
    if (width_cells_ == 4) {
        kind = PATH_TEMPLATE_KIND_LOOPTHELOOPW;
        loop_wiggle = 0.30000001f;
    }
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;
    curve_count = (int)(curve_source * 6.2831855f);
    width_or_scale = 1.0f;
    int loop_segment_count = curve_count + 14;
    segment_count = loop_segment_count;
    segment_count_f = (float)loop_segment_count;
    float curve_count_f = (float)curve_count;
    curve_source = curve_count_f * 0.15915494f;
    GetNodes();
    has_entry_mesh_transition = 1;

    for (i = 0; i < 7; ++i) {
        sample_f = (float)i;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).center_x = (float)width_cells * 0.5f - 4.0f
            - loop_wiggle * (sample_f / 7.0f);
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).rotation_scalar_98 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).rotation_scalar_94 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).special_scalar = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).lateral_scale = 1.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.x = (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.y = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.z = sample_f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).delta_length = 1.0f;

        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.x = (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.y = 0.49000001f;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).transform.position.z = sample_f;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (unsigned int)((i) * (int)sizeof(AttachmentSample)))))).delta_length = 1.0f;
    }

    for (i = 0; i < 7; ++i) {
        int sample_index = curve_count + 7 + i;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((sample_index) * (int)sizeof(AttachmentSample)))))).center_x =
            (1.0f - (float)i * 0.16666667f) * loop_wiggle
            + (4.0f - (float)width_cells * 0.5f);
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((sample_index) * (int)sizeof(AttachmentSample)))))).rotation_scalar_98 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((sample_index) * (int)sizeof(AttachmentSample)))))).rotation_scalar_94 = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (unsigned int)((sample_index) * (int)sizeof(AttachmentSample)))))).special_scalar = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).lateral_scale = 1.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y = 0.0f;
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z = (float)(i + 7);
        (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).delta_length = 1.0f;

        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).center_x;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y = 0.49000001f;
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z = (float)(i + 7);
        (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).delta_length = 1.0f;
    }

    i = 0;
    if (curve_count > 0) {
        float secondary_radius = curve_source - 0.49000001f;
        do {
            int sample_index = i + 7;
            sample_f = (float)i;
            float angle = sample_f * 6.2831855f / curve_count_f;
            float roll = Sin(angle * 0.5f) * Sin(angle * 8.0f) * 0.39269909f;
            interpolate_path_center(primary_samples, sample_index,
                loop_segment_count, sample_f, curve_count_f);
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).center_x +=
                Sin(angle * 0.5f + 4.712389f) * loop_wiggle;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_98 = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).rotation_scalar_94 = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).special_scalar = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).lateral_scale = 1.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).center_x;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z =
                Sin(angle) * curve_source + 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y =
                curve_source - Cos(angle) * curve_source;

            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.Identity();
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.x =
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).center_x;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z =
                Sin(angle) * secondary_radius + 7.0f;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y =
                curve_source - Cos(angle) * secondary_radius;

            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.x = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.y =
                (curve_source - (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y);
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.z =
                7.0f - (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.Normalize();
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_forward.Cross(
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right,
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up);
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.RotLocalZ(roll);

            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right =
                Vector3(1.0f, 0.0f, 0.0f);
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.x = 0.0f;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.y =
                (curve_source - (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.y);
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.z =
                7.0f - (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.position.z;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up.Normalize();
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_forward.Cross(
                (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_right,
                (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.basis_up);

            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (sample_index) * sizeof(AttachmentSample))))).transform.RotLocalZ(roll);
            ++i;
        } while (i < curve_count);
    }

    i = 0;
    if (segment_count - 1 > 0) {
        do {
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (i) * sizeof(AttachmentSample))))).delta_dir_to_next =
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (i + 1) * sizeof(AttachmentSample))))).transform.position -
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (i) * sizeof(AttachmentSample))))).transform.position;
            (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (i) * sizeof(AttachmentSample))))).delta_length =
                (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (i) * sizeof(AttachmentSample))))).delta_dir_to_next.Normalize();

            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (i) * sizeof(AttachmentSample))))).delta_dir_to_next =
                (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (i + 1) * sizeof(AttachmentSample))))).transform.position -
                (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (i) * sizeof(AttachmentSample))))).transform.position;
            (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (i) * sizeof(AttachmentSample))))).delta_length =
                (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (i) * sizeof(AttachmentSample))))).delta_dir_to_next.Normalize();
            ++i;
        } while (i < segment_count - 1);
    }

    (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (segment_count - 1) * sizeof(AttachmentSample))))).delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (segment_count - 1) * sizeof(AttachmentSample))))).delta_length = 1.0f;
    (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (segment_count - 1) * sizeof(AttachmentSample))))).delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    (*((AttachmentSample *)((char *)((unsigned int)secondary_bank + (segment_count - 1) * sizeof(AttachmentSample))))).delta_length = 1.0f;

    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    Vector3* vertices = strip_mesh->vertices;
    cRFaceQuad* facequads = strip_mesh->facequads;

    int row;
    int column;
    int face_index;

    for (row = 0; row <= segment_count; ++row) {
        for (column = 0; column <= width_cells; ++column) {
            if (row != segment_count) {
                double lateral =
                    (float)column - (float)width_cells * 0.5f;
                Vector3 generated_position =
                    (*((AttachmentSample *)((char *)((unsigned int)primary_bank + (row) * sizeof(AttachmentSample))))).transform.position
                    + ((*((AttachmentSample *)((char *)((unsigned int)primary_bank + (row) * sizeof(AttachmentSample))))).transform.basis_right * lateral);
                vertices[column + row * (width_cells + 1)] = generated_position;
            } else {
                double lateral =
                    (float)column - (float)width_cells * 0.5f;
                Vector3 generated_position =
                    ((primary_bank + row - 1)->transform.position
                     + Vector3(0.0f, 0.0f, 1.0f))
                    + ((primary_bank + row - 1)->transform.basis_right * lateral);
                vertices[column + row * (width_cells + 1)] = generated_position;
            }
        }
    }

    for (row = 0; row < segment_count; ++row) {
        column = 0;
        if (width_cells > 0) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            int next_column;
            do {
                face_index = 0;
                next_column = column + 1;
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;
                for (; face_index < 2; ++face_index) {
                    int face_array_index =
                        face_index
                        + 2 * (row * width_cells + column);
                    if (face_index == 0) {
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).header_word = 0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_0 = column + row * ((unsigned short)width_cells + 1);
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_1 = row * ((unsigned short)width_cells + 1) + column + 1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_2 =
                            (row + 1) * ((unsigned short)width_cells + 1) + column + 1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_3 =
                            column + (row + 1) * ((unsigned short)width_cells + 1);
                        if (((column ^ row) & 1) == 0)
                            (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).header_word = 0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_0 = row * ((unsigned short)width_cells + 1) + column + 1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_1 = column + row * ((unsigned short)width_cells + 1);
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_2 =
                            column + (row + 1) * ((unsigned short)width_cells + 1);
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).vertex_3 =
                            (row + 1) * ((unsigned short)width_cells + 1) + column + 1;
                        if (((column ^ row) & 1) == 0)
                            (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                    }
                    if (face_index == 0) {
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[0].u = u0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[0].v = v0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[1].u = u1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[1].v = v0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[2].u = u1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[2].v = v1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[3].u = u0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[3].v = v1;
                    } else {
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[0].u = u1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[0].v = v0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[1].u = u0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[1].v = v0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[2].u = u0;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[2].v = v1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[3].u = u1;
                        (*((cRFaceQuad *)((char *)((unsigned int)facequads + (face_array_index) * sizeof(cRFaceQuad))))).uv[3].v = v1;
                    }
                }
                column = next_column;
            } while (next_column < width_cells);
        }
    }

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
