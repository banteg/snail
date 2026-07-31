// initialize_slalombig_path_template_pair @ 0x4221f0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float sine(float angle);
float cosine(float angle);

typedef AttachmentSample PathTemplateSample;


static __forceinline void initialize_pair_sample(
    Path* path, int index, float center_x, float y, float z)
{
    PathTemplateSample* primary = &path->primary_samples[index];
    PathTemplateSample* secondary = &path->secondary_samples[index];

    primary->center_x = center_x;
    primary->rotation_scalar_98 = 0.0f;
    primary->rotation_scalar_94 = 0.0f;
    primary->special_scalar = 0.0f;
    primary->lateral_scale = 1.0f;
    set_matrix_identity(&primary->transform);
    primary->transform.position.x = center_x;
    primary->transform.position.y = y;
    primary->transform.position.z = z;

    set_matrix_identity(&secondary->transform);
    secondary->transform.position.x = center_x;
    secondary->transform.position.y = y + 0.49000001f;
    secondary->transform.position.z = z;
}

static __forceinline void orient_previous_with_up(
    PathTemplateSample* samples,
    int current_index,
    int curve_index,
    PathTemplateSample* roll_source)
{
    PathTemplateSample* previous = &samples[current_index - 1];
    PathTemplateSample* current = &samples[current_index];

    if (curve_index == 0) {
        previous->transform.RotIdentity();
        return;
    }

    previous->transform.basis_up = Vector3(0.0f, 1.0f, 0.0f);
    previous->transform.basis_forward = Vector3(
        current->transform.position.x - previous->transform.position.x,
        current->transform.position.y - previous->transform.position.y,
        current->transform.position.z - previous->transform.position.z);
    previous->transform.basis_forward.Normalize();
    previous->transform.basis_right.cross_vectors(
        &previous->transform.basis_up,
        &previous->transform.basis_forward);
    float roll_angle = roll_source->center_x * 0.2617994f;
    previous->transform.RotLocalZ(roll_angle);
}

static __forceinline void compute_terminal_deltas(Path* path)
{
    int i = 0;
    if (path->segment_count - 1 > 0) {
        int delta_offset = 0;
        do {
            ((PathTemplateSample*)((char*)path->primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)path->primary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)path->primary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)path->primary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)path->primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample*)((char*)path->secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample*)((char*)path->secondary_samples + delta_offset) + 1)
                    ->transform.position -
                ((PathTemplateSample*)((char*)path->secondary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample*)((char*)path->secondary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample*)((char*)path->secondary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ++i;
            delta_offset += (int)sizeof(PathTemplateSample);
        } while (i < path->segment_count - 1);
    }

    path->primary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->primary_samples[path->segment_count - 1].delta_length = 1.0f;
    path->secondary_samples[path->segment_count - 1].delta_dir_to_next =
        Vector3(0.0f, 0.0f, 1.0f);
    path->secondary_samples[path->segment_count - 1].delta_length = 1.0f;
}

static __forceinline void build_extrapolated_strip_mesh(
    Path* path, char* texture_a, char* texture_b)
{
    path->strip_mesh->RequestVertices(
        (path->width_cells + 1) * (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(
        2 * path->width_cells * path->segment_count);

    cRFaceQuad* facequads = path->strip_mesh->facequads;
    Vector3* vertices = path->strip_mesh->vertices;

    int row = 0;
    int column;
    int face_index;
    if (path->segment_count >= 0) {
        int sample_offset = 0;
        do {
            column = 0;
            if (path->width_cells >= 0) {
                do {
                    double lateral =
                        (float)column - (float)path->width_cells * 0.5f;
                    if (row != path->segment_count) {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset);
                        Vector3 lateral_offset =
                            sample->transform.basis_right * lateral;
                        Vector3 generated_position(
                            sample->transform.position.x + lateral_offset.x,
                            sample->transform.position.y + lateral_offset.y,
                            sample->transform.position.z + lateral_offset.z);
                        Vector3* vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    } else {
                        PathTemplateSample* sample =
                            (PathTemplateSample*)((char*)path->primary_samples
                                + sample_offset);
                        Vector3 lateral_offset =
                            sample[-1].transform.basis_right * lateral;
                        Vector3 endpoint(
                            sample[-1].transform.position.x,
                            sample[-1].transform.position.y,
                            sample[-1].transform.position.z + 1.0f);
                        Vector3 generated_position =
                            endpoint + lateral_offset;
                        Vector3* vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    ++column;
                } while (column <= path->width_cells);
            }
            ++row;
            sample_offset += sizeof(PathTemplateSample);
        } while (row <= path->segment_count);
    }

    for (row = 0; row < path->segment_count; ++row) {
        for (column = 0; column < path->width_cells; ++column) {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            float u0 = (float)column * 0.125f;
            float u1 = (float)(column + 1) * 0.125f;

            for (face_index = 0; face_index < 2; ++face_index) {
                int face_offset = 2 * column + 2 * row * path->width_cells + face_index;
                facequads[face_offset].header_word = 0;

                if (face_index == 0) {
                    facequads[face_offset].vertex_0 = column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_1 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_2 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_3 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
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
                    facequads[face_offset].vertex_0 = row * ((unsigned short)path->width_cells + 1) + column + 1;
                    facequads[face_offset].vertex_1 = column + row * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_2 = column + (row + 1) * ((unsigned short)path->width_cells + 1);
                    facequads[face_offset].vertex_3 = (row + 1) * ((unsigned short)path->width_cells + 1) + column + 1;
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
        }
    }
}

void cRPath::initialize_slalombig_path_template_pair(
    int curve_segments,
    int width_cells_,
    bool side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture)
{
    width_cells = width_cells_;
    kind = PATH_TEMPLATE_KIND_SLALOMBIG;
    int lead_out_start = curve_segments + 4;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    int total_segments = lead_out_start + 4;
    width_or_scale = 1.0f;
    segment_count = total_segments;
    segment_count_f = (float)total_segments;
    get_path_nodes();
    has_entry_mesh_transition = 0;

    int i;
    int lead_sample_index = 0;
    int lead_sample_offset = 0;
    do {
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->center_x = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->lateral_scale = 1.0f;
        set_matrix_identity(
            &((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
                ->transform);
        float z = (float)lead_sample_index;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
                ->center_x;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
            ->transform.position.z = z;

        set_matrix_identity(
            &((PathTemplateSample*)((char*)secondary_samples + lead_sample_offset))
                ->transform);
        ((PathTemplateSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + lead_sample_offset))
                ->center_x;
        ((PathTemplateSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + lead_sample_offset))
            ->transform.position.z = z;
        ++lead_sample_index;
        lead_sample_offset += (int)sizeof(PathTemplateSample);
    } while (lead_sample_offset < 4 * (int)sizeof(PathTemplateSample));

    int departure_index = lead_out_start;
    int departure_sample_offset =
        departure_index * (int)sizeof(PathTemplateSample);
    do {
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->center_x = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->rotation_scalar_98 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->rotation_scalar_94 = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->special_scalar = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->lateral_scale = 1.0f;
        set_matrix_identity(
            &((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
                ->transform);
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
                ->center_x;
        float z = (float)departure_index;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.y = 0.0f;
        ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
            ->transform.position.z = z;
        set_matrix_identity(
            &((PathTemplateSample*)((char*)secondary_samples + departure_sample_offset))
                ->transform);
        ((PathTemplateSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + departure_sample_offset))
                ->center_x;
        ((PathTemplateSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + departure_sample_offset))
            ->transform.position.z = z;
        departure_sample_offset += (int)sizeof(PathTemplateSample);
        ++departure_index;
    } while (departure_index - 4 - curve_segments < 4);

    int curve_sample_index = 0;
    int curve_sample_offset = 4 * (int)sizeof(PathTemplateSample);
    for (i = 0; i < curve_segments;
         ++i,
         ++curve_sample_index,
         curve_sample_offset += (int)sizeof(PathTemplateSample)) {
        float t = (float)i / (float)curve_segments;
        float folded = t - 0.5f;
        float folded_copy;
        if (folded >= 0.0f)
            folded_copy = folded;
        else
            folded_copy = -folded;
        if (folded < 0.0f)
            folded = -folded;

        float angle = t * 6.2831855f;
        float center = sine(angle) * (1.0f - folded) * (1.0f - folded_copy) * 4.4444447f;
        ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
            ->center_x = center;
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
        ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
            ->transform.position.x =
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset))
                ->center_x;
        float z = (float)(curve_sample_index + 4);
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
            ->transform.position.y = 0.49000001f;
        ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset))
            ->transform.position.z = z;

        if (curve_sample_offset == 4 * (int)sizeof(PathTemplateSample)) {
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.RotIdentity();
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.RotIdentity();
        } else {
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.basis_up =
                Vector3(0.0f, 1.0f, 0.0f);
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.basis_forward =
                Vector3(
                    ((PathTemplateSample*)((char*)primary_samples
                        + curve_sample_offset))->transform.position.x
                        - ((PathTemplateSample*)((char*)primary_samples
                            + curve_sample_offset) - 1)->transform.position.x,
                    ((PathTemplateSample*)((char*)primary_samples
                        + curve_sample_offset))->transform.position.y
                        - ((PathTemplateSample*)((char*)primary_samples
                            + curve_sample_offset) - 1)->transform.position.y,
                    ((PathTemplateSample*)((char*)primary_samples
                        + curve_sample_offset))->transform.position.z
                        - ((PathTemplateSample*)((char*)primary_samples
                            + curve_sample_offset) - 1)->transform.position.z);
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.basis_forward.Normalize();
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.basis_right.cross_vectors(
                    &((PathTemplateSample*)((char*)primary_samples
                        + curve_sample_offset) - 1)->transform.basis_up,
                    &((PathTemplateSample*)((char*)primary_samples
                        + curve_sample_offset) - 1)->transform.basis_forward);
            float primary_roll =
                ((PathTemplateSample*)((char*)primary_samples
                    + curve_sample_offset) - 1)->center_x * 0.2617994f;
            ((PathTemplateSample*)((char*)primary_samples + curve_sample_offset) - 1)
                ->transform.RotLocalZ(primary_roll);

            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.basis_up =
                Vector3(0.0f, 1.0f, 0.0f);
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.basis_forward =
                Vector3(
                    ((PathTemplateSample*)((char*)secondary_samples
                        + curve_sample_offset))->transform.position.x
                        - ((PathTemplateSample*)((char*)secondary_samples
                            + curve_sample_offset) - 1)->transform.position.x,
                    ((PathTemplateSample*)((char*)secondary_samples
                        + curve_sample_offset))->transform.position.y
                        - ((PathTemplateSample*)((char*)secondary_samples
                            + curve_sample_offset) - 1)->transform.position.y,
                    ((PathTemplateSample*)((char*)secondary_samples
                        + curve_sample_offset))->transform.position.z
                        - ((PathTemplateSample*)((char*)secondary_samples
                            + curve_sample_offset) - 1)->transform.position.z);
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.basis_forward.Normalize();
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.basis_right.cross_vectors(
                    &((PathTemplateSample*)((char*)secondary_samples
                        + curve_sample_offset) - 1)->transform.basis_up,
                    &((PathTemplateSample*)((char*)secondary_samples
                        + curve_sample_offset) - 1)->transform.basis_forward);

            float secondary_roll =
                ((PathTemplateSample*)((char*)primary_samples
                    + curve_sample_offset) - 1)->center_x * 0.2617994f;
            ((PathTemplateSample*)((char*)secondary_samples + curve_sample_offset) - 1)
                ->transform.RotLocalZ(secondary_roll);
        }
    }

    compute_terminal_deltas(this);
    build_extrapolated_strip_mesh(this, texture_a, texture_b);
    calc_path_length_z();
    (void)side_exit;
    (void)cap_texture;
}
