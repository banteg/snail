// build_track_fringe_supertramp_mesh @ 0x424ad0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

void Path::build_track_fringe_supertramp_mesh(char* texture_path)
{
    fringe_mesh_bod.set_bod_object(g_object_list.add_object_to_list());

    Object* mesh = fringe_mesh_bod.object;
    mesh->blend_mode = 5;
    mesh->flags |= OBJECT_FLAG_DISABLE_CULLING;
    mesh->request_object_vertices((segment_count << 2) + 6);
    mesh->request_object_facequads((segment_count << 1) + 1);

    Vector3* vertices = mesh->vertices;
    ObjectFaceQuad* facequads = mesh->facequads;

    Vector3* row_vertices = vertices;
    int row = 0;
    if (segment_count >= 0) {
        do {
            row_vertices[0] = strip_mesh->vertices[row * (width_cells + 1) + 1];
            row_vertices[1] = strip_mesh->vertices[row * (width_cells + 1)];

            Vector3 direction;
            direction = row_vertices[1] - row_vertices[0];
            direction.normalize_vector();
            row_vertices[0] = row_vertices[1] + direction * 0.40000001f;

            row_vertices[2] =
                strip_mesh->vertices[row * (width_cells + 1) + width_cells - 1];
            row_vertices[3] =
                strip_mesh->vertices[row * (width_cells + 1) + width_cells];

            direction = row_vertices[3] - row_vertices[2];
            direction.normalize_vector();

            ++row;
            row_vertices[2] = row_vertices[3] + direction * 0.40000001f;
            row_vertices += 4;
        } while (row <= segment_count);
    }

    row = 0;
    if (segment_count > 0) {
        do {
            ObjectFaceQuad* face = &facequads[row * 2];

            face[0].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[0].vertex_0 = row * 4 + 4;
            face[0].vertex_1 = row * 4 + 5;
            face[0].vertex_2 = row * 4 + 1;
            face[0].vertex_3 = row * 4;
            face[0].uv[3].u = 0.5f;
            face[0].uv[3].v = 1.0f;
            face[0].uv[0].u = 0.5f;
            face[0].uv[0].v = 1.0f;
            face[0].uv[1].u = 0.5f;
            face[0].uv[1].v = 0.0f;
            face[0].uv[2].u = 0.5f;
            face[0].uv[2].v = 0.0f;

            face[1].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[1].vertex_0 = row * 4 + 7;
            face[1].vertex_1 = row * 4 + 6;
            face[1].vertex_2 = row * 4 + 2;
            face[1].vertex_3 = row * 4 + 3;
            face[1].uv[3].u = 0.5f;
            face[1].uv[3].v = 0.0f;
            face[1].uv[0].u = 0.5f;
            face[1].uv[0].v = 0.0f;
            face[1].uv[1].u = 0.5f;
            face[1].uv[1].v = 1.0f;
            face[1].uv[2].u = 0.5f;
            face[1].uv[2].v = 1.0f;

            ++row;
        } while (row < segment_count);
    }

    vertices[segment_count * 4 + 4] =
        vertices[segment_count * 4] +
        (vertices[segment_count * 4] - vertices[(segment_count - 1) * 4]) * 0.40000001f;
    vertices[segment_count * 4 + 5] =
        vertices[segment_count * 4 + 2] +
        (vertices[segment_count * 4 + 2] - vertices[(segment_count - 1) * 4 + 2]) *
            0.40000001f;

    vertices[segment_count * 4] = vertices[segment_count * 4 + 4];
    vertices[segment_count * 4 + 2] = vertices[segment_count * 4 + 5];

    facequads[segment_count * 2].texture_ref =
        g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
    facequads[segment_count * 2].vertex_0 = segment_count * 4 + 1;
    facequads[segment_count * 2].vertex_1 = segment_count * 4 + 3;
    facequads[segment_count * 2].vertex_2 = segment_count * 4 + 5;
    facequads[segment_count * 2].vertex_3 = (segment_count + 1) << 2;
    facequads[segment_count * 2].uv[0].u = 0.5f;
    facequads[segment_count * 2].uv[0].v = 0.0f;
    facequads[segment_count * 2].uv[1].u = 0.5f;
    facequads[segment_count * 2].uv[1].v = 0.0f;
    facequads[segment_count * 2].uv[2].u = 0.5f;
    facequads[segment_count * 2].uv[2].v = 1.0f;
    facequads[segment_count * 2].uv[3].u = 0.5f;
    facequads[segment_count * 2].uv[3].v = 1.0f;
}
