// mirror_path_template_pair_x @ 0x421dc0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

void __fastcall request_object_vertex_colours(Object* object);
void __fastcall finalize_path_template(AttachmentPathTemplate* path);

struct MirroredPathTemplateStripMesh : public PathTemplateStripMesh {
    char unknown_14[0x38 - 0x14];
    Vector3* vertices;           // +0x38
    char unknown_3c[0x48 - 0x3c];
    Color4f* vertex_colours;     // +0x48
    char unknown_4c[0x5c - 0x4c];
    ObjectFaceQuad* facequads;   // +0x5c
};

typedef char MirroredPathTemplateStripMesh_must_be_0x60[
    (sizeof(MirroredPathTemplateStripMesh) == 0x60) ? 1 : -1];

void AttachmentPathTemplate::mirror_path_template_pair_x(AttachmentPathTemplate* source)
{
    is_mirrored_x = 1;
    segment_count = source->segment_count;
    segment_count_f = source->segment_count_f;
    width_or_scale = source->width_or_scale;
    width_cells = source->width_cells;
    allocate_path_template_samples();

    special_runtime_flag_9c = source->special_runtime_flag_9c;
    strip_mesh->flags = source->strip_mesh->flags;
    kind = source->kind;
    side_exit_mode = source->side_exit_mode;

    int sample_index = 0;
    if (segment_count > 0) {
        int sample_offset = 0;
        do {
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->center_x =
                -((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->center_x;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->lateral_scale =
                ((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->lateral_scale;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->rotation_scalar_98 =
                -((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->rotation_scalar_98;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->rotation_scalar_94 =
                -((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->rotation_scalar_94;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->special_scalar =
                ((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->special_scalar;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->transform =
                ((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->transform;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->transform.basis_right.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->transform.basis_up.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->transform.basis_forward.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->transform.position.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->delta_dir_to_next =
                ((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->delta_dir_to_next;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->delta_dir_to_next.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)primary_samples))->delta_length =
                ((AttachmentSample*)(sample_offset + (char*)source->primary_samples))->delta_length;

            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->transform =
                ((AttachmentSample*)(sample_offset + (char*)source->secondary_samples))->transform;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->transform.basis_right.x *= -1.0f;
            ++sample_index;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->transform.basis_up.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->transform.basis_forward.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->transform.position.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->delta_dir_to_next =
                ((AttachmentSample*)(sample_offset + (char*)source->secondary_samples))->delta_dir_to_next;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->delta_dir_to_next.x *= -1.0f;
            ((AttachmentSample*)(sample_offset + (char*)secondary_samples))->delta_length =
                ((AttachmentSample*)(sample_offset + (char*)source->secondary_samples))->delta_length;

            sample_offset += sizeof(AttachmentSample);
        } while (sample_index < segment_count);
    }

    ((Object*)strip_mesh)->request_object_vertices((width_cells + 1) * (segment_count + 1));
    ((Object*)strip_mesh)->request_object_facequads(2 * width_cells * segment_count);

    MirroredPathTemplateStripMesh* destination_mesh =
        (MirroredPathTemplateStripMesh*)strip_mesh;
    Color4f* destination_colours = 0;
    if ((destination_mesh->flags & 0x10000) != 0) {
        request_object_vertex_colours((Object*)destination_mesh);
        destination_mesh = (MirroredPathTemplateStripMesh*)strip_mesh;
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
                        -((MirroredPathTemplateStripMesh*)source->strip_mesh)
                             ->vertices[column + row * (width_cells + 1)]
                             .x;
                    destination_vertices[column + row * (width_cells + 1)].y =
                        ((MirroredPathTemplateStripMesh*)source->strip_mesh)
                            ->vertices[column + row * (width_cells + 1)]
                            .y;
                    destination_vertices[column + row * (width_cells + 1)].z =
                        ((MirroredPathTemplateStripMesh*)source->strip_mesh)
                            ->vertices[column + row * (width_cells + 1)]
                            .z;

                    if ((strip_mesh->flags & 0x10000) != 0) {
                        destination_colours[column + row * (width_cells + 1)] =
                            ((MirroredPathTemplateStripMesh*)source->strip_mesh)
                                ->vertex_colours[column + row * (width_cells + 1)];
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
                            &((MirroredPathTemplateStripMesh*)source->strip_mesh)->facequads[face_index];

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

    finalize_path_template(this);
}
