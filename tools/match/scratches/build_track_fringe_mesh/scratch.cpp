// build_track_fringe_mesh @ 0x4246a0 (thiscall, ret 0x8)

#include "game_root.h"
#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"

extern GameRoot* g_game; // data_4df904

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

void Path::build_track_fringe_mesh(char* texture_path, float clamp_side)
{
    fringe_mesh_bod.set_bod_object(g_object_list.add_object_to_list());

    Object* mesh;
    {
        tColour skirt_color;
        tColour* color = g_game->subgame.get_track_skirt_color(&skirt_color);
        mesh = fringe_mesh_bod.object;
        fringe_mesh_bod.color = *color;
    }

    mesh->flags |= OBJECT_FLAG_DISABLE_CULLING | 0x40;
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
                near_column = width_cells;
                far_column = width_cells - 1;
                far_inner_column = 1;
                near_inner_column = 0;
            } else {
                near_column = 0;
                far_column = 1;
                far_inner_column = width_cells - 1;
                near_inner_column = width_cells;
            }

            Vector3* row_vertices = &destination[row * 4];

            row_vertices[0] = strip_mesh->vertices[far_column + row * (width_cells + 1)];
            row_vertices[1] = strip_mesh->vertices[near_column + row * (width_cells + 1)];

            Vector3 direction;
            direction = row_vertices[1] - row_vertices[0];
            direction.normalize_vector();
            row_vertices[0] = row_vertices[1] + direction * 0.40000001f;

            row_vertices[2] = strip_mesh->vertices[far_inner_column + row * (width_cells + 1)];
            row_vertices[3] = strip_mesh->vertices[near_inner_column + row * (width_cells + 1)];

            direction = row_vertices[3] - row_vertices[2];
            direction.normalize_vector();
            row_vertices[2] = row_vertices[3] + direction * 0.40000001f;

            if (clamp_side == -1.0f) {
                int i = 0;
                do {
                    if (row_vertices[i].x > 0.0f)
                        row_vertices[i].x = 0.0f;
                    ++i;
                } while (i < 4);
            } else if (clamp_side == 1.0f) {
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

    row = 0;
    if (segment_count > 0) {
        do {
            ObjectFaceQuad* face = &facequads[row * 2];

            face[0].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[0].vertex_0 = row * 4 + 5;
            face[0].vertex_1 = row * 4 + 4;
            face[0].vertex_2 = row * 4;
            face[0].vertex_3 = row * 4 + 1;
            face[0].uv[3].u = 0.5f;
            face[0].uv[3].v = 0.0f;
            face[0].uv[0].u = 0.5f;
            face[0].uv[0].v = 0.0f;
            face[0].uv[1].u = 0.5f;
            face[0].uv[1].v = 1.0f;
            face[0].uv[2].u = 0.5f;
            face[0].uv[2].v = 1.0f;

            face[1].texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            face[1].vertex_0 = row * 4 + 6;
            face[1].vertex_1 = row * 4 + 7;
            face[1].vertex_2 = row * 4 + 3;
            face[1].vertex_3 = row * 4 + 2;
            face[1].uv[3].u = 0.5f;
            face[1].uv[3].v = 1.0f;
            face[1].uv[0].u = 0.5f;
            face[1].uv[0].v = 1.0f;
            face[1].uv[1].u = 0.5f;
            face[1].uv[1].v = 0.0f;
            face[1].uv[2].u = 0.5f;
            face[1].uv[2].v = 0.0f;

            ++row;
        } while (row < segment_count);
    }
}
