// build_track_fringe_mesh @ 0x4246a0 (thiscall, ret 0x8)

#include "game_root.h"
#include "object_render_types.h"
#include "sprite.h"
#include "track_attachment_types.h"


void cRPath::build_track_fringe_mesh(char* texture_path, float clamp_side)
{
    fringe_mesh_bod.SetObject(g_object_list.Add());

    Object* mesh;
    {
        tColour skirt_color;
        tColour* color = g_game->subgame.GetSkirtColour(&skirt_color);
        mesh = fringe_mesh_bod.object;
        fringe_mesh_bod.color = *color;
    }

    mesh->flags |= OBJECT_FLAG_DISABLE_CULLING | OBJECT_FLAG_TINT_DIRTY;
    mesh->blend_mode = 5;
    mesh->RequestVertices((segment_count << 2) + 4);
    mesh->RequestFaceQuads(segment_count << 1);

    Vector3* destination = mesh->vertices;
    cRFaceQuad* facequads = mesh->facequads;

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


            destination[row * 4 + 0] = strip_mesh->vertices[far_column + row * (width_cells + 1)];
            destination[row * 4 + 1] = strip_mesh->vertices[near_column + row * (width_cells + 1)];

            Vector3 direction;
            direction = destination[row * 4 + 1] - destination[row * 4 + 0];
            direction.Normalize();
            destination[row * 4 + 0] = destination[row * 4 + 1] + direction * 0.40000001f;

            destination[row * 4 + 2] = strip_mesh->vertices[far_inner_column + row * (width_cells + 1)];
            destination[row * 4 + 3] = strip_mesh->vertices[near_inner_column + row * (width_cells + 1)];

            direction = destination[row * 4 + 3] - destination[row * 4 + 2];
            direction.Normalize();
            destination[row * 4 + 2] = destination[row * 4 + 3] + direction * 0.40000001f;

            if (clamp_side == -1.0f) {
                int i = 0;
                do {
                    if (destination[row * 4 + i].x > 0.0f)
                        destination[row * 4 + i].x = 0.0f;
                    ++i;
                } while (i < 4);
            } else if (clamp_side == 1.0f) {
                int i = 0;
                do {
                    if (destination[row * 4 + i].x < 0.0f)
                        destination[row * 4 + i].x = 0.0f;
                    ++i;
                } while (i < 4);
            }

            ++row;
        } while (row <= segment_count);
    }

    row = 0;
    if (segment_count > 0) {
        do {

            facequads[row * 2].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
            facequads[row * 2].vertex_0 = row * 4 + 5;
            facequads[row * 2].vertex_1 = row * 4 + 4;
            facequads[row * 2].vertex_2 = row * 4;
            facequads[row * 2].vertex_3 = row * 4 + 1;
            facequads[row * 2].uv[3].u = 0.5f;
            facequads[row * 2].uv[3].v = 0.0f;
            facequads[row * 2].uv[0].u = 0.5f;
            facequads[row * 2].uv[0].v = 0.0f;
            facequads[row * 2].uv[1].u = 0.5f;
            facequads[row * 2].uv[1].v = 1.0f;
            facequads[row * 2].uv[2].u = 0.5f;
            facequads[row * 2].uv[2].v = 1.0f;

            facequads[row * 2 + 1].texture_ref = g_texture_refs.Add(texture_path, 0, 0);
            facequads[row * 2 + 1].vertex_0 = row * 4 + 6;
            facequads[row * 2 + 1].vertex_1 = row * 4 + 7;
            facequads[row * 2 + 1].vertex_2 = row * 4 + 3;
            facequads[row * 2 + 1].vertex_3 = row * 4 + 2;
            facequads[row * 2 + 1].uv[3].u = 0.5f;
            facequads[row * 2 + 1].uv[3].v = 1.0f;
            facequads[row * 2 + 1].uv[0].u = 0.5f;
            facequads[row * 2 + 1].uv[0].v = 1.0f;
            facequads[row * 2 + 1].uv[1].u = 0.5f;
            facequads[row * 2 + 1].uv[1].v = 0.0f;
            facequads[row * 2 + 1].uv[2].u = 0.5f;
            facequads[row * 2 + 1].uv[2].v = 0.0f;

            ++row;
        } while (row < segment_count);
    }
}
