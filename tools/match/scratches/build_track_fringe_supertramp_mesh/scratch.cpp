// build_track_fringe_supertramp_mesh @ 0x424ad0 (thiscall, ret 0x4)

#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

void AttachmentPathTemplate::build_track_fringe_supertramp_mesh(char* texture_path)
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
            Object* source_mesh = (Object*)strip_mesh;
            Vector3* row_vertices = &vertices[row * 4];
            int row_base = row * (width_cells + 1);

            row_vertices[0] = source_mesh->vertices[row_base + 1];
            row_vertices[1] = source_mesh->vertices[row_base];

            Vector3 direction;
            direction.x = row_vertices[1].x - row_vertices[0].x;
            direction.y = row_vertices[1].y - row_vertices[0].y;
            direction.z = row_vertices[1].z - row_vertices[0].z;
            direction.normalize_vector();

            float extended_x = row_vertices[1].x + direction.x * 0.40000001f;
            float extended_y = row_vertices[1].y + direction.y * 0.40000001f;
            float extended_z = row_vertices[1].z + direction.z * 0.40000001f;
            row_vertices[0].x = extended_x;
            row_vertices[0].y = extended_y;
            row_vertices[0].z = extended_z;

            row_vertices[2] = source_mesh->vertices[row_base + width_cells - 1];
            row_vertices[3] = source_mesh->vertices[row_base + width_cells];

            direction.x = row_vertices[3].x - row_vertices[2].x;
            direction.y = row_vertices[3].y - row_vertices[2].y;
            direction.z = row_vertices[3].z - row_vertices[2].z;
            direction.normalize_vector();

            ++row;

            extended_x = row_vertices[3].x + direction.x * 0.40000001f;
            extended_y = row_vertices[3].y + direction.y * 0.40000001f;
            extended_z = row_vertices[3].z + direction.z * 0.40000001f;
            row_vertices[2].x = extended_x;
            row_vertices[2].y = extended_y;
            row_vertices[2].z = extended_z;
        } while (row <= segment_count);
    }

    int segment = 0;
    if (segment_count > 0) {
        do {
            ObjectFaceQuad* face = &facequads[segment * 2];
            int vertex_base = segment << 2;

            face[0].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[0].vertex_0 = vertex_base + 4;
            face[0].vertex_1 = vertex_base + 5;
            face[0].vertex_2 = vertex_base + 1;
            face[0].vertex_3 = vertex_base;
            face[0].uv[0].u = 0.5f;
            face[0].uv[0].v = 1.0f;
            face[0].uv[1].u = 0.5f;
            face[0].uv[1].v = 0.0f;
            face[0].uv[2].u = 0.5f;
            face[0].uv[2].v = 0.0f;
            face[0].uv[3].u = 0.5f;
            face[0].uv[3].v = 1.0f;

            face[1].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[1].vertex_0 = vertex_base + 7;
            face[1].vertex_1 = vertex_base + 6;
            face[1].vertex_2 = vertex_base + 2;
            face[1].vertex_3 = vertex_base + 3;
            face[1].uv[0].u = 0.5f;
            face[1].uv[0].v = 0.0f;
            face[1].uv[1].u = 0.5f;
            face[1].uv[1].v = 1.0f;
            face[1].uv[2].u = 0.5f;
            face[1].uv[2].v = 1.0f;
            face[1].uv[3].u = 0.5f;
            face[1].uv[3].v = 0.0f;

            ++segment;
        } while (segment < segment_count);
    }

    Vector3* previous_row = &vertices[(segment_count - 1) * 4];
    Vector3* final_row = &vertices[segment_count * 4];
    Vector3* cap = &vertices[segment_count * 4 + 4];

    float cap_x = final_row[0].x + (final_row[0].x - previous_row[0].x) * 0.40000001f;
    float cap_y = final_row[0].y + (final_row[0].y - previous_row[0].y) * 0.40000001f;
    float cap_z = final_row[0].z + (final_row[0].z - previous_row[0].z) * 0.40000001f;
    cap[0].x = cap_x;
    cap[0].y = cap_y;
    cap[0].z = cap_z;

    cap_x = final_row[2].x + (final_row[2].x - previous_row[2].x) * 0.40000001f;
    cap_y = final_row[2].y + (final_row[2].y - previous_row[2].y) * 0.40000001f;
    cap_z = final_row[2].z + (final_row[2].z - previous_row[2].z) * 0.40000001f;
    cap[1].x = cap_x;
    cap[1].y = cap_y;
    cap[1].z = cap_z;

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
