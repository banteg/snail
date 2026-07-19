// build_track_fringe_objects @ 0x434be0 (thiscall, ret)
// Structure-first scratch for directional runtime fringe object emission.

#include "track_attachment_types.h"
#include "fringe_object.h"
#include "game_root.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "track_fringe_bod_catalog.h"


#define FRINGE_BOD(direction, family, edge_a, edge_b) \
    (g_game->root_bod_catalog.fringe_catalog \
            .entries[family][direction][edge_a][edge_b].object)

int debug_report_stub(char* format, ...);
extern char g_used_fringe_bods_format[]; // "Used %i fringe bods\n"

int SubgameRuntime::build_track_fringe_objects()
{
    g_game->subgame.fringe_manager.initialize_fringe_manager();

    int edge_a = 0;
    int row = 0;
    if (runtime_row_count > 0) {
        SubRow* row_record = runtime_rows;
        TrackRowCell* cell = &runtime_cells[0][0];
        SubRow* row_record_head = row_record;

        do {
            int lane_count =
                sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
            do {
                unsigned char open_edge_mask = cell->open_edge_mask;
                int family = 0;
                if (open_edge_mask
                    == (SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_PREVIOUS_ROW)) {
                    family = 1;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_PREVIOUS_ROW)) {
                    family = 3;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_NEXT_ROW)) {
                    family = 2;
                } else if (open_edge_mask
                    == (SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_NEXT_ROW)) {
                    family = 4;
                }

                unsigned char tile_id = cell->tile_id;
                if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET)
                    family = 5;
                if (tile_id == SUBLOC_TILE_RAMP_GREATER
                    || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
                    || tile_id == SUBLOC_TILE_RAMP_LESS)
                    family = 6;
                if (tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
                    || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET)
                    family = 7;

                if ((row_record->flags & SUBROW_FLAG_SUPPRESS_TRACK_RENDER) != 0
                    || open_edge_mask == 0
                    || tile_id == SUBLOC_TILE_FLOOR_HASH_MARKER
                    || (g_runtime_config.render_flags & RUNTIME_RENDER_TRACK_FRINGE) == 0) {
                    cell->fringe_front = 0;
                    cell->fringe_right = 0;
                    cell->fringe_left = 0;
                    cell->fringe_back = 0;
                } else if (is_neighbor_cell_solid(cell, 0, 0) == 1) {
                    if (!is_neighbor_cell_solid(cell, 0, 1)) {
                        if (is_neighbor_cell_solid(cell, 1, 1) != 1)
                            edge_a = (is_neighbor_cell_solid(cell, 1, 0) != 1) + 1;
                        int edge_b;
                        if (is_neighbor_cell_solid(cell, -1, 1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (is_neighbor_cell_solid(cell, -1, 0) != 1) + 1;

                        Fringe* object =
                            g_game->subgame.fringe_manager.allocate_fringe_object();
                        cell->fringe_front = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_FRONT, family, edge_a, edge_b));
                        cell->fringe_front->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        cell->fringe_front->position = cell->position;
                        tColour color0;
                        tColour* skirt_color = get_track_skirt_color(&color0);
                        edge_a = 0;
                        cell->fringe_front->color = *skirt_color;
                    } else {
                        cell->fringe_front = 0;
                    }

                    if (!is_neighbor_cell_solid(cell, 1, 0)) {
                        if (is_neighbor_cell_solid(cell, 1, -1) != 1)
                            edge_a = (is_neighbor_cell_solid(cell, 0, -1) != 1) + 1;
                        int edge_b;
                        if (is_neighbor_cell_solid(cell, 1, 1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (is_neighbor_cell_solid(cell, 0, 1) != 1) + 1;

                        Fringe* object =
                            g_game->subgame.fringe_manager.allocate_fringe_object();
                        cell->fringe_right = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_RIGHT, family, edge_a, edge_b));
                        cell->fringe_right->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        cell->fringe_right->position = cell->position;
                        tColour color1;
                        tColour* skirt_color = get_track_skirt_color(&color1);
                        edge_a = 0;
                        cell->fringe_right->color = *skirt_color;
                    } else {
                        cell->fringe_right = 0;
                    }

                    if (!is_neighbor_cell_solid(cell, -1, 0)) {
                        if (is_neighbor_cell_solid(cell, -1, 1) != 1)
                            edge_a = (is_neighbor_cell_solid(cell, 0, 1) != 1) + 1;
                        int edge_b;
                        if (is_neighbor_cell_solid(cell, -1, -1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (is_neighbor_cell_solid(cell, 0, -1) != 1) + 1;

                        Fringe* object =
                            g_game->subgame.fringe_manager.allocate_fringe_object();
                        cell->fringe_left = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_LEFT, family, edge_a, edge_b));
                        cell->fringe_left->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        cell->fringe_left->position = cell->position;
                        tColour color2;
                        tColour* skirt_color = get_track_skirt_color(&color2);
                        edge_a = 0;
                        cell->fringe_left->color = *skirt_color;
                    } else {
                        cell->fringe_left = 0;
                    }

                    if (!is_neighbor_cell_solid(cell, 0, -1)) {
                        if (is_neighbor_cell_solid(cell, -1, -1) != 1)
                            edge_a = (is_neighbor_cell_solid(cell, -1, 0) != 1) + 1;
                        int edge_b;
                        if (is_neighbor_cell_solid(cell, 1, -1) == 1)
                            edge_b = 0;
                        else
                            edge_b = (is_neighbor_cell_solid(cell, 1, 0) != 1) + 1;

                        Fringe* object =
                            g_game->subgame.fringe_manager.allocate_fringe_object();
                        cell->fringe_back = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_BACK, family, edge_a, edge_b));
                        cell->fringe_back->list_flags |= BOD_FLAG_RENDER_ENABLED;
                        cell->fringe_back->position = cell->position;
                        tColour color3;
                        tColour* skirt_color = get_track_skirt_color(&color3);
                        edge_a = 0;
                        cell->fringe_back->color = *skirt_color;
                    } else {
                        cell->fringe_back = 0;
                    }
                }

                row_record = row_record_head;
                if ((row_record_head->flags
                        & SUBROW_FLAG_SUPPRESS_TRACK_RENDER)
                    != 0) {
                    Fringe* object = cell->fringe_front;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = cell->fringe_back;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = cell->fringe_right;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                    object = cell->fringe_left;
                    if (object != 0)
                        object->list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                }

                ++cell;
                --lane_count;
            } while (lane_count);

            row_record = row_record_head + 1;
            ++row;
            row_record_head = row_record;
        } while (row < runtime_row_count);
    }

    return debug_report_stub(
        g_used_fringe_bods_format,
        g_game->subgame.fringe_manager.count);
}
