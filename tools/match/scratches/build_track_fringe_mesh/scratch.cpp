// build_track_fringe_mesh @ 0x4246a0 (thiscall, ret 0x8)

#include "object_render_types.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904

void AttachmentPathTemplate::build_track_fringe_mesh(char* texture_path, float clamp_side)
{
    fringe_mesh_bod.set_bod_object(g_object_list.add_object_to_list());

    Color4f skirt_color;
    Color4f* color =
        ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&skirt_color);
    Object* mesh = (Object*)fringe_mesh_bod.object;
    fringe_mesh_bod.color = *color;

    mesh->flags |= 0x100040;
    mesh->blend_mode = 5;
    mesh->request_object_vertices((segment_count << 2) + 4);
    mesh->request_object_facequads(segment_count << 1);

    ObjectFaceQuad* facequads = mesh->facequads;
    Vector3* destination = mesh->vertices;

    int row = 0;
    if (segment_count >= 0) {
        do {
            int far_column;
            int near_column;
            int far_inner_column;
            int near_inner_column;

            if (is_mirrored_x != 0) {
                far_column = width_cells - 1;
                near_column = width_cells;
                far_inner_column = 1;
                near_inner_column = 0;
            } else {
                far_column = 1;
                near_column = 0;
                far_inner_column = width_cells - 1;
                near_inner_column = width_cells;
            }

            Vector3* row_vertices = &destination[row * 4];
            Object* source_mesh = (Object*)strip_mesh;

            row_vertices[0] = source_mesh->vertices[far_column + row * (width_cells + 1)];
            row_vertices[1] = source_mesh->vertices[near_column + row * (width_cells + 1)];

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

            row_vertices[2] = source_mesh->vertices[far_inner_column + row * (width_cells + 1)];
            row_vertices[3] = source_mesh->vertices[near_inner_column + row * (width_cells + 1)];

            direction.x = row_vertices[3].x - row_vertices[2].x;
            direction.y = row_vertices[3].y - row_vertices[2].y;
            direction.z = row_vertices[3].z - row_vertices[2].z;
            direction.normalize_vector();

            extended_x = row_vertices[3].x + direction.x * 0.40000001f;
            extended_y = row_vertices[3].y + direction.y * 0.40000001f;
            extended_z = row_vertices[3].z + direction.z * 0.40000001f;
            row_vertices[2].x = extended_x;
            row_vertices[2].y = extended_y;
            row_vertices[2].z = extended_z;

            if (clamp_side == -1.0f) {
                int i = 0;
                do {
                    if (row_vertices[i].x > 0.0f)
                        row_vertices[i].x = 0.0f;
                    ++i;
                } while (i < 4);
            } else if (clamp_side != 1.0f) {
                int i = 0;
                do {
                    if (row_vertices[i].x < 0.0f)
                        row_vertices[i].x = 0.0f;
                    ++i;
                } while (i < 4);
            }

            ++row;
        } while (row <= segment_count);
    }

    int segment = 0;
    if (segment_count > 0) {
        do {
            ObjectFaceQuad* face = &facequads[segment * 2];
            int vertex_base = segment << 2;

            face[0].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[0].vertex_0 = vertex_base + 5;
            face[0].vertex_1 = vertex_base + 4;
            face[0].vertex_2 = vertex_base;
            face[0].vertex_3 = vertex_base + 1;
            face[0].uv[0].u = 0.5f;
            face[0].uv[0].v = 0.0f;
            face[0].uv[1].u = 0.5f;
            face[0].uv[1].v = 1.0f;
            face[0].uv[2].u = 0.5f;
            face[0].uv[2].v = 1.0f;
            face[0].uv[3].u = 0.5f;
            face[0].uv[3].v = 0.0f;

            face[1].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[1].vertex_0 = vertex_base + 6;
            face[1].vertex_1 = vertex_base + 7;
            face[1].vertex_2 = vertex_base + 3;
            face[1].vertex_3 = vertex_base + 2;
            face[1].uv[0].u = 0.5f;
            face[1].uv[0].v = 1.0f;
            face[1].uv[1].u = 0.5f;
            face[1].uv[1].v = 0.0f;
            face[1].uv[2].u = 0.5f;
            face[1].uv[2].v = 0.0f;
            face[1].uv[3].u = 0.5f;
            face[1].uv[3].v = 1.0f;

            ++segment;
        } while (segment < segment_count);
    }
}
