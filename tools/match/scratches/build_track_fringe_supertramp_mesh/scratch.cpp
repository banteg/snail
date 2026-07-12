// build_track_fringe_supertramp_mesh @ 0x424ad0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

void Path::build_track_fringe_supertramp_mesh(char* texture_path)
{
    fringe_mesh_bod.set_bod_object(g_object_list.add_object_to_list());

    Object* mesh = (Object*)fringe_mesh_bod.object;
    mesh->blend_mode = 5;
    mesh->flags |= 0x100000;
    mesh->request_object_vertices((segment_count << 2) + 6);
    mesh->request_object_facequads((segment_count << 1) + 1);

    Vector3* vertices = mesh->vertices;
    ObjectFaceQuad* facequads = mesh->facequads;

    int row = 0;
    if (segment_count >= 0) {
        do {
            Vector3* row_vertices = &vertices[row * 4];
            int row_base = row * (width_cells + 1);

            row_vertices[0] = strip_mesh->vertices[row_base + 1];
            row_vertices[1] = strip_mesh->vertices[row_base];

            Vector3 direction;
            direction = row_vertices[1] - row_vertices[0];
            direction.normalize_vector();
            row_vertices[0] = row_vertices[1] + direction * 0.40000001f;

            row_vertices[2] = strip_mesh->vertices[row_base + width_cells - 1];
            row_vertices[3] = strip_mesh->vertices[row_base + width_cells];

            direction = row_vertices[3] - row_vertices[2];
            direction.normalize_vector();

            ++row;
            row_vertices[2] = row_vertices[3] + direction * 0.40000001f;
        } while (row <= segment_count);
    }

    row = 0;
    if (segment_count > 0) {
        do {
            ObjectFaceQuad* face = &facequads[row * 2];

            face[0].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            int vertex_base = row << 2;
            face[0].vertex_0 = vertex_base + 4;
            face[0].vertex_1 = vertex_base + 5;
            face[0].vertex_2 = vertex_base + 1;
            face[0].vertex_3 = vertex_base;
            face[0].uv[3].u = 0.5f;
            face[0].uv[3].v = 1.0f;
            face[0].uv[0].u = 0.5f;
            face[0].uv[0].v = 1.0f;
            face[0].uv[1].u = 0.5f;
            face[0].uv[1].v = 0.0f;
            face[0].uv[2].u = 0.5f;
            face[0].uv[2].v = 0.0f;

            face[1].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[1].vertex_0 = vertex_base + 7;
            face[1].vertex_1 = vertex_base + 6;
            face[1].vertex_2 = vertex_base + 2;
            face[1].vertex_3 = vertex_base + 3;
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

    Vector3* previous_row = &vertices[(segment_count - 1) * 4];
    Vector3* final_row = &vertices[segment_count * 4];
    Vector3* cap = &vertices[segment_count * 4 + 4];

    cap[0] = final_row[0] + (final_row[0] - previous_row[0]) * 0.40000001f;
    cap[1] = final_row[2] + (final_row[2] - previous_row[2]) * 0.40000001f;

    final_row[0] = cap[0];
    final_row[2] = cap[1];

    ObjectFaceQuad* cap_face = &facequads[segment_count * 2];
    int vertex_base = segment_count << 2;

    cap_face->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
    cap_face->vertex_0 = vertex_base + 1;
    cap_face->vertex_1 = vertex_base + 3;
    cap_face->vertex_2 = vertex_base + 5;
    cap_face->vertex_3 = (segment_count + 1) << 2;
    cap_face->uv[0].u = 0.5f;
    cap_face->uv[0].v = 0.0f;
    cap_face->uv[1].u = 0.5f;
    cap_face->uv[1].v = 0.0f;
    cap_face->uv[2].u = 0.5f;
    cap_face->uv[2].v = 1.0f;
    cap_face->uv[3].u = 0.5f;
    cap_face->uv[3].v = 1.0f;
}
