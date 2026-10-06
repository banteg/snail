// build_track_fringe_supertramp_mesh @ 0x424ad0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

void cRPath::build_track_fringe_supertramp_mesh(char* texture_path)
{
    fringe_mesh_bod.SetObject(g_object_list.Add());

    Object* mesh = fringe_mesh_bod.object;
    mesh->blend_mode = 5;
    mesh->flags |= OBJECT_FLAG_DISABLE_CULLING;
    mesh->RequestVertices((segment_count << 2) + 6);
    mesh->RequestFaceQuads((segment_count << 1) + 1);

    Vector3* vertices = mesh->vertices;
    cRFaceQuad* facequads = mesh->facequads;

    Vector3 direction;
    int row = 0;
    if (segment_count >= 0) {
        do {
            vertices[row * 4 + 0] = strip_mesh->vertices[row * (width_cells + 1) + 1];
            vertices[row * 4 + 1] = strip_mesh->vertices[row * (width_cells + 1)];

            direction = vertices[row * 4 + 1] - vertices[row * 4 + 0];
            direction.Normalize();
            vertices[row * 4 + 0] = vertices[row * 4 + 1] + direction * 0.40000001f;

            vertices[row * 4 + 2] =
                strip_mesh->vertices[row * (width_cells + 1) + width_cells - 1];
            vertices[row * 4 + 3] =
                strip_mesh->vertices[row * (width_cells + 1) + width_cells];

            direction = vertices[row * 4 + 3] - vertices[row * 4 + 2];
            direction.Normalize();

            vertices[row * 4 + 2] = vertices[row * 4 + 3] + direction * 0.40000001f;
            ++row;
        } while (row <= segment_count);
    }

    row = 0;
    if (segment_count > 0) {
        do {
            facequads[row * 2].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
            facequads[row * 2].vertex_0 = row * 4 + 4;
            facequads[row * 2].vertex_1 = row * 4 + 5;
            facequads[row * 2].vertex_2 = row * 4 + 1;
            facequads[row * 2].vertex_3 = row * 4;
            facequads[row * 2].uv[3].u = 0.5f;
            facequads[row * 2].uv[3].v = 1.0f;
            facequads[row * 2].uv[0].u = 0.5f;
            facequads[row * 2].uv[0].v = 1.0f;
            facequads[row * 2].uv[1].u = 0.5f;
            facequads[row * 2].uv[1].v = 0.0f;
            facequads[row * 2].uv[2].u = 0.5f;
            facequads[row * 2].uv[2].v = 0.0f;

            facequads[row * 2 + 1].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
            facequads[row * 2 + 1].vertex_0 = row * 4 + 7;
            facequads[row * 2 + 1].vertex_1 = row * 4 + 6;
            facequads[row * 2 + 1].vertex_2 = row * 4 + 2;
            facequads[row * 2 + 1].vertex_3 = row * 4 + 3;
            facequads[row * 2 + 1].uv[3].u = 0.5f;
            facequads[row * 2 + 1].uv[3].v = 0.0f;
            facequads[row * 2 + 1].uv[0].u = 0.5f;
            facequads[row * 2 + 1].uv[0].v = 0.0f;
            facequads[row * 2 + 1].uv[1].u = 0.5f;
            facequads[row * 2 + 1].uv[1].v = 1.0f;
            facequads[row * 2 + 1].uv[2].u = 0.5f;
            facequads[row * 2 + 1].uv[2].v = 1.0f;

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
        g_texture_refs.Add(texture_path, 0, 0);
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
