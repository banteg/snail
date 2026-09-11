// initialize_turnunder_path_template_pair @ 0x427fe0 (thiscall, ret 0x18)

#include "attachment_sample.h"
#include "track_attachment_types.h"
#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

float Sin(float angle);
float Cos(float angle);

typedef AttachmentSample PathTemplateSample;

static __forceinline void compute_path_deltas(Path *path)
{
    int i = 0;
    if (path->segment_count - 1 > 0)
    {
        int delta_offset = 0;
        do
        {
            ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->primary_samples + delta_offset))
                    ->delta_dir_to_next.Normalize();

            ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_dir_to_next =
                ((PathTemplateSample *)((char *)path->secondary_samples +
                                        delta_offset) +
                 1)
                    ->transform.position -
                ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                    ->transform.position;
            ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
                ->delta_length =
                ((PathTemplateSample *)((char *)path->secondary_samples + delta_offset))
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

static __forceinline void build_strip_mesh(Path *path, char *texture_a, char *texture_b)
{
    path->strip_mesh->RequestVertices((path->width_cells + 1) *
                                      (path->segment_count + 1));
    path->strip_mesh->RequestFaceQuads(2 * path->width_cells * path->segment_count);

    cRFaceQuad *facequads = path->strip_mesh->facequads;
    Vector3 *vertices = path->strip_mesh->vertices;

    int row = 0;
    int column;
    int face_index;
    if (path->segment_count >= 0)
    {
        int sample_offset = 0;
        do
        {
            column = 0;
            if (path->width_cells >= 0)
            {
                do
                {
                    if (row != path->segment_count)
                    {
                        float lateral = (float)column - (float)path->width_cells * 0.5f;
                        Vector3 lateral_offset =
                            ((PathTemplateSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.basis_right *
                            lateral;
                        Vector3 generated_position =
                            ((PathTemplateSample *)((char *)path->primary_samples +
                                                    sample_offset))
                                ->transform.position +
                            lateral_offset;
                        Vector3 *vertex =
                            &vertices[column + row * (path->width_cells + 1)];
                        *vertex = generated_position;
                    }
                    else
                    {
                        float lateral = (float)column - (float)path->width_cells * 0.5f;
                        Vector3 generated_position =
                            (((PathTemplateSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.position +
                             Vector3(0.0f, 0.0f, 1.0f)) +
                            (((PathTemplateSample *)((char *)path->primary_samples +
                                                     sample_offset))[-1]
                                 .transform.basis_right *
                             lateral);
                        Vector3 *vertex =
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

    for (row = 0; row < path->segment_count; ++row)
    {
        column = 0;
        if (path->width_cells > 0)
        {
            float v0 = (float)(row % 8) * 0.125f;
            float v1 = (float)(row % 8 + 1) * 0.125f;
            do
            {
                float u0 = (float)column * 0.125f;
                float u1 = (float)(column + 1) * 0.125f;

                for (face_index = 0; face_index < 2; ++face_index)
                {
                    cRFaceQuad *face =
                        &facequads[2 * column + 2 * row * path->width_cells +
                                   face_index];
                    face->header_word = 0;
                    if (face_index == 0) {
                        face->vertex_0 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_1 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_2 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        face->vertex_3 =
                            column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        if (((column ^ row) & 1) == 0)
                        {
                            face->texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                        }
                        else
                        {
                            face->texture_ref = g_texture_refs.Add(texture_a, 0, 0);
                        }
                    } else {
                        face->vertex_0 =
                            row * ((unsigned short)path->width_cells + 1) + column + 1;
                        face->vertex_1 =
                            column + row * ((unsigned short)path->width_cells + 1);
                        face->vertex_2 =
                            column +
                            (row + 1) * ((unsigned short)path->width_cells + 1);
                        face->vertex_3 =
                            (row + 1) * ((unsigned short)path->width_cells + 1) +
                            column + 1;
                        if (((column ^ row) & 1) == 0)
                        {
                            face->texture_ref = g_texture_refs.Add(texture_b, 0, 0);
                        }
                        else
                        {
                            face->texture_ref = g_texture_refs.Add(texture_b, 0, 0);
                        }
                    }
                    if (face_index == 0) {
                        face->uv[0].u = u0;
                        face->uv[0].v = v0;
                        face->uv[1].u = u1;
                        face->uv[1].v = v0;
                        face->uv[2].u = u1;
                        face->uv[2].v = v1;
                        face->uv[3].u = u0;
                    } else {
                        face->uv[0].u = u1;
                        face->uv[0].v = v0;
                        face->uv[1].u = u0;
                        face->uv[1].v = v0;
                        face->uv[2].u = u0;
                        face->uv[2].v = v1;
                        face->uv[3].u = u1;
                    }
                    face->uv[3].v = v1;
                }
                ++column;
            } while (column < path->width_cells);
        }
    }
}

static __forceinline void initialize_tail_pair(PathTemplateSample *&primary,
                                               PathTemplateSample *&secondary,
                                               int offset, int index, int width)
{
    ((AttachmentSample *)((char *)primary + offset))->center_x =
        -(4.0f - (float)width * 0.5f);
    ((AttachmentSample *)((char *)primary + offset))->rotation_scalar_98 = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->rotation_scalar_94 = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->special_scalar = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->lateral_scale = 1.0f;
    ((AttachmentSample *)((char *)primary + offset))->transform.Identity();
    float z = (float)index;
    ((AttachmentSample *)((char *)primary + offset))->transform.position.x =
        ((AttachmentSample *)((char *)primary + offset))->center_x;
    ((AttachmentSample *)((char *)primary + offset))->transform.position.y = 0.0f;
    ((AttachmentSample *)((char *)primary + offset))->transform.position.z = z;
    ((AttachmentSample *)((char *)primary + offset))->delta_length = 1.0f;

    ((AttachmentSample *)((char *)secondary + offset))->transform.Identity();
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.x =
        ((AttachmentSample *)((char *)primary + offset))->center_x;
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.y =
        0.49000001f;
    ((AttachmentSample *)((char *)secondary + offset))->transform.position.z = z;
    ((AttachmentSample *)((char *)secondary + offset))->delta_length = 1.0f;
}

void cRPath::initialize_turnunder_path_template_pair(float turns, int width_cells_,
                                                     bool side_exit, char *texture_a,
                                                     char *texture_b,
                                                     char *vertical_texture)
{
    kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
    is_mirrored_x = 0;
    side_exit_mode = 0;
    width_cells = width_cells_;

    int interior_count = (int)(turns * 6.2831855f);
    width_or_scale = 1.0f;
    segment_count = interior_count + 8;
    segment_count_f = (float)segment_count;
    float interior_count_f = (float)interior_count;
    turns = interior_count_f * 0.15915494f;
    GetNodes();
    has_entry_mesh_transition = 0;

    int lead_z_index = 0;
    int i = 0;
    do
    {
        primary_samples[i].center_x = -((float)width_cells * 0.5f - 4.0f);
        primary_samples[i].rotation_scalar_98 = 0.0f;
        primary_samples[i].rotation_scalar_94 = 0.0f;
        primary_samples[i].special_scalar = 0.0f;
        primary_samples[i].lateral_scale = 1.0f;
        primary_samples[i].transform.Identity();
        primary_samples[i].transform.position.x = primary_samples[i].center_x;
        float z = (float)lead_z_index;
        primary_samples[i].transform.position.y = 0.0f;
        primary_samples[i].transform.position.z = z;
        primary_samples[i].delta_length = 1.0f;

        secondary_samples[i].transform.Identity();
        secondary_samples[i].transform.position.x = primary_samples[i].center_x;
        secondary_samples[i].transform.position.y = 0.49000001f;
        secondary_samples[i].transform.position.z = z;
        ++i;
        secondary_samples[i - 1].delta_length = 1.0f;
        ++lead_z_index;
    } while (i < 6);

    i = interior_count + 6;
    int tail_sample_offset = i * sizeof(AttachmentSample);
    int tail_origin = -6 - interior_count;
    do
    {
        initialize_tail_pair(primary_samples, secondary_samples, tail_sample_offset, i,
                             width_cells);
        tail_sample_offset += sizeof(AttachmentSample);
        ++i;
    } while (i + tail_origin < 2);

    int curve_index = 0;
    if (interior_count > 0)
    {
        i = 6;
        do
        {
            float t = (float)curve_index;
            float angle = t * -6.2831855f / interior_count_f;

            primary_samples[i].center_x =
                (primary_samples[interior_count + 6].center_x -
                 primary_samples[0].center_x) *
                    t / interior_count_f +
                primary_samples[0].center_x;
            primary_samples[i].rotation_scalar_98 = 0.0f;
            primary_samples[i].rotation_scalar_94 = 0.0f;
            primary_samples[i].special_scalar = 0.0f;
            primary_samples[i].lateral_scale = 1.0f;
            primary_samples[i].transform.Identity();

            primary_samples[i].transform.position.x =
                primary_samples[i].center_x - (Sin(angle) * Sin(angle * 0.5f) * 2.0f);
            primary_samples[i].transform.position.z = (float)(curve_index + 6);
            primary_samples[i].transform.position.y =
                (turns - Cos(angle) * turns) * -0.2f;

            float roll_cosine = Cos(Sin(angle) * 1.0471976f);
            float roll_sine = Sin(Sin(angle) * 1.0471976f);
            primary_samples[i].transform.basis_up =
                Vector3(-roll_sine, roll_cosine, 0.0f);
            primary_samples[i].transform.basis_forward =
                primary_samples[i].transform.position -
                primary_samples[i - 1].transform.position;
            primary_samples[i].transform.basis_forward.Normalize();
            primary_samples[i].transform.basis_right.Cross(
                primary_samples[i].transform.basis_up,
                primary_samples[i].transform.basis_forward);

            secondary_samples[i].transform = primary_samples[i].transform;
            Vector3 secondary_offset =
                primary_samples[i].transform.basis_up * 0.49000001f;
            Vector3 *secondary_position = &secondary_samples[i].transform.position;
            secondary_position->x += secondary_offset.x;
            secondary_position->y += secondary_offset.y;
            secondary_position->z += secondary_offset.z;

            ++i;
            ++curve_index;
        } while (curve_index < interior_count);
    }

    compute_path_deltas(this);
    build_strip_mesh(this, texture_a, texture_b);
    CalcLengthZ();
    (void)side_exit;
    (void)vertical_texture;
}
