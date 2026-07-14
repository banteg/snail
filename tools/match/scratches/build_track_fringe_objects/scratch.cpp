// build_track_fringe_objects @ 0x434be0 (thiscall, ret)
// Structure-first scratch for directional runtime fringe object emission.

#include "track_attachment_types.h"
#include "fringe_object.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "track_fringe_bod_catalog.h"

extern char* g_game_base; // data_4df904

#define FRINGE_BOD(direction, family, edge_a, edge_b) \
    (((TrackFringeBodCatalog*)(g_game_base + TRACK_FRINGE_BOD_CATALOG_GAME_OFFSET)) \
            ->entries[family][direction][edge_a][edge_b].object)

struct Vec3Bits {
    int x;
    int y;
    int z;
};

int debug_report_stub(char* format, ...);
extern char g_used_fringe_bods_format[]; // "Used %i fringe bods\n"

int SubgameRuntime::build_track_fringe_objects()
{
    ((SubgameRuntime*)(g_game_base + 0x74618))
        ->fringe_manager.initialize_fringe_manager();

    int edge_a = 0;
    int row = 0;
    if (runtime_row_count > 0) {
        SubRow* row_record = runtime_rows;
        TrackRowCell* cell = &runtime_cells[0][0];
        SubRow* row_record_head = row_record;

        do {
            int lane_count = 8;
            do {
                unsigned char edge_id = cell->tile_flags_3d;
                int family = 0;
                if (edge_id == 9) {
                    family = 1;
                } else if (edge_id == 5) {
                    family = 3;
                } else if (edge_id == 10) {
                    family = 2;
                } else if (edge_id == 6) {
                    family = 4;
                }

                unsigned char tile_id = cell->tile_id;
                if (tile_id == 2 || tile_id == 8 || tile_id == 5)
                    family = 5;
                if (tile_id == 3 || tile_id == 9 || tile_id == 11
                    || tile_id == 12 || tile_id == 13 || tile_id == 6)
                    family = 6;
                if (tile_id == 4 || tile_id == 10 || tile_id == 7)
                    family = 7;

                if ((row_record->flags & 4) != 0 || edge_id == 0 || tile_id == 0x20
                    || (g_runtime_config.render_flags & 0x20) == 0) {
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
                            ((SubgameRuntime*)(g_game_base + 0x74618))
                                ->fringe_manager.allocate_fringe_object();
                        cell->fringe_front = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_FRONT, family, edge_a, edge_b));
                        cell->fringe_front->list_flags |= 0x20;
                        cell->fringe_front->position = cell->anchor_position;
                        Color4f color0;
                        Color4f* skirt_color = get_track_skirt_color(&color0);
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
                            ((SubgameRuntime*)(g_game_base + 0x74618))
                                ->fringe_manager.allocate_fringe_object();
                        cell->fringe_right = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_RIGHT, family, edge_a, edge_b));
                        cell->fringe_right->list_flags |= 0x20;
                        cell->fringe_right->position = cell->anchor_position;
                        Color4f color1;
                        Color4f* skirt_color = get_track_skirt_color(&color1);
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
                            ((SubgameRuntime*)(g_game_base + 0x74618))
                                ->fringe_manager.allocate_fringe_object();
                        cell->fringe_left = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_LEFT, family, edge_a, edge_b));
                        cell->fringe_left->list_flags |= 0x20;
                        cell->fringe_left->position = cell->anchor_position;
                        Color4f color2;
                        Color4f* skirt_color = get_track_skirt_color(&color2);
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
                            ((SubgameRuntime*)(g_game_base + 0x74618))
                                ->fringe_manager.allocate_fringe_object();
                        cell->fringe_back = object;
                        object->set_bod_object(
                            FRINGE_BOD(TRACK_FRINGE_BACK, family, edge_a, edge_b));
                        cell->fringe_back->list_flags |= 0x20;
                        cell->fringe_back->position = cell->anchor_position;
                        Color4f color3;
                        Color4f* skirt_color = get_track_skirt_color(&color3);
                        edge_a = 0;
                        cell->fringe_back->color = *skirt_color;
                    } else {
                        cell->fringe_back = 0;
                    }
                }

                row_record = row_record_head;
                if ((row_record_head->flags & 4) != 0) {
                    Fringe* object = cell->fringe_front;
                    if (object != 0)
                        object->list_flags &= ~0x20;
                    object = cell->fringe_back;
                    if (object != 0)
                        object->list_flags &= ~0x20;
                    object = cell->fringe_right;
                    if (object != 0)
                        object->list_flags &= ~0x20;
                    object = cell->fringe_left;
                    if (object != 0)
                        object->list_flags &= ~0x20;
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
        ((SubgameRuntime*)(g_game_base + 0x74618))->fringe_manager.count);
}
