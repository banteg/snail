// initialize_screw_path_template_pair @ 0x41eda0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathAttachmentSample;

static __forceinline void build_strip_mesh(
    const int &width_cells, const int &segment_count,
    cRObject *const &strip_mesh, PathAttachmentSample *const &primary_samples,
    char *texture_a, char *texture_b)
{
    strip_mesh->RequestVertices((width_cells + 1) * (segment_count + 1));
    strip_mesh->RequestFaceQuads(2 * width_cells * segment_count);

    Vector3* vertices = strip_mesh->vertices;
    cRFaceQuad* facequads = strip_mesh->facequads;

    int mesh_row;
    int mesh_column;
    int face_index;

    for (mesh_row = 0; mesh_row <= segment_count; ++mesh_row) {
        for (mesh_column = 0; mesh_column <= width_cells; ++mesh_column) {
            double lateral = (float)mesh_column - (float)width_cells * 0.5f;
            if (mesh_row != segment_count) {
                Vector3 lateral_offset =
                    primary_samples[mesh_row].transform.basis_right * lateral;
                Vector3 generated_position =
                    primary_samples[mesh_row].transform.position + lateral_offset;
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
            } else {
                Vector3 lateral_offset =
                    primary_samples[mesh_row - 1].transform.basis_right * lateral;
                Vector3 endpoint = primary_samples[mesh_row - 1].transform.position
                    + Vector3(0.0f, 0.0f, 1.0f);
                Vector3 generated_position =
                    endpoint + lateral_offset;
                Vector3* vertex =
                    &vertices[mesh_column + mesh_row * (width_cells + 1)];
                *vertex = generated_position;
            }
        }
    }

    for (mesh_row = 0; mesh_row < segment_count; ++mesh_row) {
        mesh_column = 0;
        if (width_cells > 0) {
            float v0 = (float)(mesh_row % 8) * 0.125f;
            float v1 = (float)(mesh_row % 8 + 1) * 0.125f;
            int next_column;
            do {
                next_column = mesh_column + 1;
                float u0 = (float)mesh_column * 0.125f;
                float u1 = (float)(mesh_column + 1) * 0.125f;
                for (face_index = 0; face_index < 2; ++face_index) {
                    int face_offset = 2 * mesh_column + 2 * mesh_row * width_cells + face_index;
                    facequads[face_offset].header_word = 0;
                    if (face_index == 0) {
                        facequads[face_offset].vertex_0 = mesh_column + mesh_row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_1 = mesh_row * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        facequads[face_offset].vertex_2 =
                            (mesh_row + 1) * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        facequads[face_offset].vertex_3 =
                            mesh_column + (mesh_row + 1) * ((unsigned short)width_cells + 1);
                        if (((mesh_column ^ mesh_row) & 1) == 0)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_a, 0, 0);
                    } else {
                        facequads[face_offset].vertex_0 = mesh_row * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        facequads[face_offset].vertex_1 = mesh_column + mesh_row * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_2 =
                            mesh_column + (mesh_row + 1) * ((unsigned short)width_cells + 1);
                        facequads[face_offset].vertex_3 =
                            (mesh_row + 1) * ((unsigned short)width_cells + 1) + mesh_column + 1;
                        if (((mesh_column ^ mesh_row) & 1) == 0)
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                        else
                            facequads[face_offset].texture_ref =
                                g_texture_refs.Add(texture_b, 0, 0);
                    }
                    if (face_index == 0) {
                        facequads[face_offset].uv[0].u = u0;
                        facequads[face_offset].uv[0].v = v0;
                        facequads[face_offset].uv[1].u = u1;
                        facequads[face_offset].uv[1].v = v0;
                        facequads[face_offset].uv[2].u = u1;
                        facequads[face_offset].uv[2].v = v1;
                        facequads[face_offset].uv[3].u = u0;
                        facequads[face_offset].uv[3].v = v1;
                    } else {
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

}

void cRPath::initialize_screw_path_template_pair(
    int curve_source, int width_cells_, bool side_exit,
    char *texture_a, char *texture_b, char *cap_texture)
{
    int curve_count = curve_source;
    int i;

    width_cells = width_cells_;
    kind = PATH_TEMPLATE_KIND_SCREW;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_or_scale = 1.0f;
    segment_count = curve_count + 8;
    segment_count_f = (float)(curve_count + 8);
    GetNodes();
    has_entry_mesh_transition = 0;

    i = 0;
    int lead_sample_offset = 0;
    do {
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->center_x = 0.5f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->special_scalar = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->lateral_scale = 1.0f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
                ->transform.Identity();
        float z = (float)i;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
                ->center_x;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.z = z;
        ((PathAttachmentSample*)((char*)secondary_samples + lead_sample_offset))
                ->transform.Identity();
        ((PathAttachmentSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathAttachmentSample*)((char*)primary_samples + lead_sample_offset))
                ->center_x;
        ((PathAttachmentSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.y = 0.49000001f;
        ((PathAttachmentSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.z = z;
        ++i;
        lead_sample_offset += sizeof(PathAttachmentSample);
    } while (lead_sample_offset < 3 * (int)sizeof(PathAttachmentSample));

    int departure_start = curve_count + 3;
    i = departure_start;
    int departure_sample_offset =
        departure_start * (int)sizeof(PathAttachmentSample);
    int departure_origin = -3 - curve_count;
    do {
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->center_x = -0.5f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->special_scalar = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->lateral_scale = 1.0f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
                ->transform.Identity();
        float z = (float)i;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
                ->center_x;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.z = z;
        ((PathAttachmentSample*)((char*)secondary_samples + departure_sample_offset))
                ->transform.Identity();
        ((PathAttachmentSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathAttachmentSample*)((char*)primary_samples + departure_sample_offset))
                ->center_x;
        ((PathAttachmentSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.y = 0.49000001f;
        ((PathAttachmentSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.z = z;
        departure_sample_offset += sizeof(PathAttachmentSample);
        ++i;
    } while (i + departure_origin < 5);

    i = 0;
    if (i < curve_count) {
        float curve_count_f = (float)curve_count;
        int curve_sample_offset = 3 * (int)sizeof(PathAttachmentSample);
#define PRIMARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)primary_samples + curve_sample_offset))
#define SECONDARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)secondary_samples + curve_sample_offset))
#define PREVIOUS_PRIMARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)primary_samples + curve_sample_offset - \
        sizeof(PathAttachmentSample)))
#define PREVIOUS_SECONDARY_CURVE_SAMPLE \
    ((PathAttachmentSample*)((char*)secondary_samples + curve_sample_offset - \
        sizeof(PathAttachmentSample)))
        do {
            int sample_index = i + 3;
            float angle = (float)i * 6.2831855f / curve_count_f;
            PRIMARY_CURVE_SAMPLE->center_x = Cos(angle * 0.5f) * 0.5f;
            PRIMARY_CURVE_SAMPLE->rotation_scalar_98 = 0.0f;
            PRIMARY_CURVE_SAMPLE->rotation_scalar_94 = angle;
            PRIMARY_CURVE_SAMPLE->special_scalar = 0.0f;
            PRIMARY_CURVE_SAMPLE->lateral_scale = 1.0f;
            PRIMARY_CURVE_SAMPLE->transform.Identity();
            float z = (float)sample_index;
            PRIMARY_CURVE_SAMPLE->transform.position.x =
                PRIMARY_CURVE_SAMPLE->center_x;
            PRIMARY_CURVE_SAMPLE->transform.position.y = 0.0f;
            PRIMARY_CURVE_SAMPLE->transform.position.z = z;
            SECONDARY_CURVE_SAMPLE->transform.Identity();
            SECONDARY_CURVE_SAMPLE->transform.position.x =
                PRIMARY_CURVE_SAMPLE->center_x - Sin(angle) * 0.49000001f;
            SECONDARY_CURVE_SAMPLE->transform.position.y =
                Cos(angle) * 0.49000001f;
            SECONDARY_CURVE_SAMPLE->transform.position.z = z;
            if (curve_sample_offset >
                3 * (int)sizeof(PathAttachmentSample)) {
                float primary_up_y = Cos(angle);
                float primary_up_x = -Sin(angle);
                PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_up =
                    Vector3(primary_up_x, primary_up_y, 0.0f);
                PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_forward =
                    PRIMARY_CURVE_SAMPLE->transform.position -
                    PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.position;
                PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_forward.Normalize();
                PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_right.Cross(
                    PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_up,
                    PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.basis_forward);

                float secondary_up_y = Cos(angle);
                float secondary_up_x = -Sin(angle);
                PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_up =
                    Vector3(secondary_up_x, secondary_up_y, 0.0f);
                PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_forward =
                    SECONDARY_CURVE_SAMPLE->transform.position -
                    PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.position;
                PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_forward.Normalize();
                PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_right.Cross(
                    PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_up,
                    PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.basis_forward);
            } else {
                PREVIOUS_PRIMARY_CURVE_SAMPLE->transform.RotIdentity();
                PREVIOUS_SECONDARY_CURVE_SAMPLE->transform.RotIdentity();
            }
            ++i;
            curve_sample_offset += sizeof(PathAttachmentSample);
        } while (i < curve_count);
#undef PREVIOUS_SECONDARY_CURVE_SAMPLE
#undef PREVIOUS_PRIMARY_CURVE_SAMPLE
#undef SECONDARY_CURVE_SAMPLE
#undef PRIMARY_CURVE_SAMPLE
    }

    i = 0;
    if (segment_count - 1 > 0) {
        do {
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
            ++i;
        } while (i < segment_count - 1);
    }

    primary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    primary_samples[segment_count - 1].delta_length = 1.0f;
    secondary_samples[segment_count - 1].delta_dir_to_next = Vector3(0.0f, 0.0f, 1.0f);
    secondary_samples[segment_count - 1].delta_length = 1.0f;

    build_strip_mesh(width_cells, segment_count, strip_mesh, primary_samples,
                     texture_a, texture_b);

    CalcLengthZ();
    (void)side_exit;
    (void)cap_texture;
}
