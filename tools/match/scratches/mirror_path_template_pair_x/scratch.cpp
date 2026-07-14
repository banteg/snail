// mirror_path_template_pair_x @ 0x421dc0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

void __fastcall request_object_vertex_colours(Object* object);

void Path::mirror_path_template_pair_x(Path* source)
{
    is_mirrored_x = 1;
    segment_count = source->segment_count;
    segment_count_f = source->segment_count_f;
    width_or_scale = source->width_or_scale;
    width_cells = source->width_cells;
    allocate_path_template_samples();

    has_entry_mesh_transition = source->has_entry_mesh_transition;
    strip_mesh->flags = source->strip_mesh->flags;
    kind = source->kind;
    side_exit_mode = source->side_exit_mode;

    int sample_index = 0;
    if (segment_count > 0) {
        do {
            primary_samples[sample_index].center_x = -source->primary_samples[sample_index].center_x;
            primary_samples[sample_index].lateral_scale = source->primary_samples[sample_index].lateral_scale;
            primary_samples[sample_index].rotation_scalar_98 =
                -source->primary_samples[sample_index].rotation_scalar_98;
            primary_samples[sample_index].rotation_scalar_94 =
                -source->primary_samples[sample_index].rotation_scalar_94;
            primary_samples[sample_index].special_scalar = source->primary_samples[sample_index].special_scalar;
            AttachmentSample* destination_primary = &primary_samples[sample_index];
            AttachmentSample* source_primary = &source->primary_samples[sample_index];
            destination_primary->transform = source_primary->transform;
            primary_samples[sample_index].transform.basis_right.x *= -1.0f;
            primary_samples[sample_index].transform.basis_up.x *= -1.0f;
            primary_samples[sample_index].transform.basis_forward.x *= -1.0f;
            primary_samples[sample_index].transform.position.x *= -1.0f;
            primary_samples[sample_index].delta_dir_to_next = source->primary_samples[sample_index].delta_dir_to_next;
            primary_samples[sample_index].delta_dir_to_next.x *= -1.0f;
            primary_samples[sample_index].delta_length = source->primary_samples[sample_index].delta_length;

            AttachmentSample* source_secondary = &source->secondary_samples[sample_index];
            AttachmentSample* destination_secondary = &secondary_samples[sample_index];
            destination_secondary->transform = source_secondary->transform;
            secondary_samples[sample_index].transform.basis_right.x *= -1.0f;
            secondary_samples[sample_index].transform.basis_up.x *= -1.0f;
            secondary_samples[sample_index].transform.basis_forward.x *= -1.0f;
            secondary_samples[sample_index].transform.position.x *= -1.0f;
            secondary_samples[sample_index].delta_dir_to_next =
                source->secondary_samples[sample_index].delta_dir_to_next;
            secondary_samples[sample_index].delta_dir_to_next.x *= -1.0f;
            secondary_samples[sample_index].delta_length =
                source->secondary_samples[sample_index].delta_length;
            ++sample_index;
        } while (sample_index < segment_count);
    }

    ((Object*)strip_mesh)->request_object_vertices((width_cells + 1) * (segment_count + 1));
    ((Object*)strip_mesh)->request_object_facequads(2 * width_cells * segment_count);

    Object* destination_mesh = strip_mesh;
    tColour* destination_colours = 0;
    if ((destination_mesh->flags & 0x10000) != 0) {
        request_object_vertex_colours((Object*)destination_mesh);
        destination_mesh = strip_mesh;
        destination_colours = destination_mesh->vertex_colours;
    }

    Vector3* destination_vertices = destination_mesh->vertices;
    ObjectFaceQuad* destination_facequads = destination_mesh->facequads;

    int row = 0;
    if (segment_count >= 0) {
        do {
            int column = 0;
            if (width_cells >= 0) {
                do {
                    destination_vertices[column + row * (width_cells + 1)].x =
                        -source->strip_mesh->vertices[column + row * (width_cells + 1)].x;
                    destination_vertices[column + row * (width_cells + 1)].y =
                        source->strip_mesh->vertices[column + row * (width_cells + 1)].y;
                    destination_vertices[column + row * (width_cells + 1)].z =
                        source->strip_mesh->vertices[column + row * (width_cells + 1)].z;

                    if ((strip_mesh->flags & 0x10000) != 0) {
                        destination_colours[column + row * (width_cells + 1)] =
                            source->strip_mesh->vertex_colours[column + row * (width_cells + 1)];
                    }

                    ++column;
                } while (column <= width_cells);
            }

            ++row;
        } while (row <= segment_count);
    }

    int segment = 0;
    if (segment_count > 0) {
        do {
            int cell = 0;
            if (width_cells > 0) {
                do {
                    int quad_pair = 0;
                    do {
                        int face_index = quad_pair + 2 * (cell + segment * width_cells);
                        ObjectFaceQuad* destination_face = &destination_facequads[face_index];
                        ObjectFaceQuad* source_face =
                            &source->strip_mesh->facequads[face_index];

                        *destination_face = *source_face;

                        int swap_vertex = destination_face->vertex_0;
                        destination_face->vertex_0 = destination_face->vertex_1;
                        destination_face->vertex_1 = swap_vertex;

                        swap_vertex = destination_face->vertex_2;
                        destination_face->vertex_2 = destination_face->vertex_3;
                        destination_face->vertex_3 = swap_vertex;

                        float swap_uv = destination_face->uv[0].u;
                        destination_face->uv[0].u = destination_face->uv[1].u;
                        destination_face->uv[1].u = swap_uv;

                        swap_uv = destination_face->uv[2].u;
                        destination_face->uv[2].u = destination_face->uv[3].u;
                        destination_face->uv[3].u = swap_uv;

                        ++quad_pair;
                    } while (quad_pair < 2);

                    ++cell;
                } while (cell < width_cells);
            }

            ++segment;
        } while (segment < segment_count);
    }

    finalize_path_template();
}
