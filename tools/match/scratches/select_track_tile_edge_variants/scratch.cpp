// select_track_tile_edge_variants @ 0x435a80 (thiscall)

#include <stddef.h>

#include "bod_types.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_row_cell_tile_views.h"

extern GameRoot* g_game; // data_4df904

#define IS_STRAIGHT_TRACK_FAMILY(tile) \
    ((tile) == 1 || (tile) == 0x14 || (tile) == 0x15 || (tile) == 0x1b \
        || (tile) == 0x21 || (tile) == 0x22)

void SubgameRuntime::select_track_tile_edge_variants()
{
    enum {
        TILE_VIEW_TO_CELL_BASE = offsetof(SubLoc, tile_id),
        TILE_VIEW_TO_PREVIOUS_LANE = sizeof(SubLoc) + offsetof(SubLoc, tile_id),
        TILE_VIEW_TO_NEXT_LANE = sizeof(SubLoc) - offsetof(SubLoc, tile_id),
        TILE_VIEW_TO_PREVIOUS_ROW =
            sizeof(runtime_cells[0]) + offsetof(SubLoc, tile_id),
        TILE_VIEW_TO_NEXT_ROW =
            sizeof(runtime_cells[0]) - offsetof(SubLoc, tile_id),
    };

    int row = 0;
    if (runtime_row_count > 0) {
        TrackRowCellTileByteView* cell = runtime_cell_tile_views();
        int variant_flag = 0x8000;
        do {
            int lane = 0;
            do {
                unsigned char* tile_flags_3d = &cell->tile_flags_3d;
                unsigned int* lane_and_flags = &cell->lane_and_flags;
                *tile_flags_3d = 0;
                *lane_and_flags &= ~0x8000u;

                unsigned char skip_tile = cell->tile_id;
                if (skip_tile != 0 && skip_tile != 0x23 && skip_tile != 0x1c
                    && skip_tile != 0x1d && skip_tile != 0x1e && skip_tile != 0x0e) {
                    if (lane == 0
                        || ((SubLoc*)((char*)cell - TILE_VIEW_TO_PREVIOUS_LANE))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->tile_flags_3d |= 8;
                    }
                    if (lane == 7
                        || ((SubLoc*)((char*)cell + TILE_VIEW_TO_NEXT_LANE))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->tile_flags_3d |= 4;
                    }
                    if (row == 0
                        || ((SubLoc*)((char*)cell - TILE_VIEW_TO_PREVIOUS_ROW))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->tile_flags_3d |= 1;
                    }
                    if (row >= runtime_row_count - 1
                        || ((SubLoc*)((char*)cell + TILE_VIEW_TO_NEXT_ROW))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->tile_flags_3d |= 2;
                    }

                    switch (cell->tile_flags_3d) {
                    case 9:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_0_STORAGE_INDEX]
                                            .object);
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                        ->is_sub_loc_ramp()
                                    == 0) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.slide_corners.storage[
                                                TRACK_CORNER_0_STORAGE_INDEX]
                                            .object);
                            }
                        }
                        break;

                    case 5:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_1_STORAGE_INDEX]
                                            .object);
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                        ->is_sub_loc_ramp()
                                    == 0) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.slide_corners.storage[
                                                TRACK_CORNER_1_STORAGE_INDEX]
                                            .object);
                            }
                        }
                        break;

                    case 10:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_3_STORAGE_INDEX]
                                            .object);
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                        ->is_sub_loc_ramp()
                                    == 0) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.slide_corners.storage[
                                                TRACK_CORNER_3_STORAGE_INDEX]
                                            .object);
                            }
                        }
                        break;

                    case 6:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_2_STORAGE_INDEX]
                                            .object);
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                        ->is_sub_loc_ramp()
                                    == 0) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.slide_corners.storage[
                                                TRACK_CORNER_2_STORAGE_INDEX]
                                            .object);
                            }
                        }
                        break;
                    }
                }
                ++lane;
                ++cell;
            } while (lane
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0])));

            ++row;
        } while (row < runtime_row_count);
    }
}

#undef IS_STRAIGHT_TRACK_FAMILY
