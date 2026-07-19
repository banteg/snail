// select_track_tile_edge_variants @ 0x435a80 (thiscall)

#include <stddef.h>

#include "bod_types.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_row_cell_tile_views.h"


#define IS_STRAIGHT_TRACK_FAMILY(tile) \
    ((tile) == SUBLOC_TILE_FLOOR_DOT \
        || (tile) == SUBLOC_TILE_FLOOR_VARIANT_14 \
        || (tile) == SUBLOC_TILE_FLOOR_DASH \
        || (tile) == SUBLOC_TILE_FLOOR_VARIANT_1B \
        || (tile) == SUBLOC_TILE_GARBAGE_HAZARD \
        || (tile) == SUBLOC_TILE_SALT_HAZARD)

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
        int variant_flag = SUBLOC_FLAG_CORNER_OBJECT;
        do {
            int lane = 0;
            do {
                unsigned char* open_edge_mask = &cell->open_edge_mask;
                unsigned int* lane_and_flags = &cell->lane_and_flags;
                *open_edge_mask = 0;
                *lane_and_flags &= ~SUBLOC_FLAG_CORNER_OBJECT;

                unsigned char skip_tile = cell->tile_id;
                if (skip_tile != SUBLOC_TILE_EMPTY
                    && skip_tile != SUBLOC_TILE_RING_MARKER
                    && skip_tile != SUBLOC_TILE_UNIVERSE_HOLE
                    && skip_tile != SUBLOC_TILE_PATH_ENTRY_LOWERCASE
                    && skip_tile != SUBLOC_TILE_PATH_ENTRY_UPPERCASE
                    && skip_tile != SUBLOC_TILE_WALL2) {
                    if (lane == 0
                        || ((SubLoc*)((char*)cell - TILE_VIEW_TO_PREVIOUS_LANE))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->open_edge_mask |= SUBLOC_OPEN_PREVIOUS_LANE;
                    }
                    if (lane == SUBGAME_TRACK_LANE_COUNT - 1
                        || ((SubLoc*)((char*)cell + TILE_VIEW_TO_NEXT_LANE))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->open_edge_mask |= SUBLOC_OPEN_NEXT_LANE;
                    }
                    if (row == 0
                        || ((SubLoc*)((char*)cell - TILE_VIEW_TO_PREVIOUS_ROW))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->open_edge_mask |= SUBLOC_OPEN_PREVIOUS_ROW;
                    }
                    if (row >= runtime_row_count - 1
                        || ((SubLoc*)((char*)cell + TILE_VIEW_TO_NEXT_ROW))
                                ->is_sub_loc_empty()
                            != 0) {
                        cell->open_edge_mask |= SUBLOC_OPEN_NEXT_ROW;
                    }

                    switch (cell->open_edge_mask) {
                    case SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_PREVIOUS_ROW:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_0_STORAGE_INDEX]
                                            .object);
                            } else if (tile != SUBLOC_TILE_TRAMPOLINE
                                && tile != SUBLOC_TILE_WALL2
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

                    case SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_PREVIOUS_ROW:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_1_STORAGE_INDEX]
                                            .object);
                            } else if (tile != SUBLOC_TILE_TRAMPOLINE
                                && tile != SUBLOC_TILE_WALL2
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

                    case SUBLOC_OPEN_PREVIOUS_LANE | SUBLOC_OPEN_NEXT_ROW:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_3_STORAGE_INDEX]
                                            .object);
                            } else if (tile != SUBLOC_TILE_TRAMPOLINE
                                && tile != SUBLOC_TILE_WALL2
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

                    case SUBLOC_OPEN_NEXT_LANE | SUBLOC_OPEN_NEXT_ROW:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - TILE_VIEW_TO_CELL_BASE))
                                    ->set_bod_object(
                                        g_game->root_bod_catalog.floor_corners.storage[
                                                TRACK_CORNER_2_STORAGE_INDEX]
                                            .object);
                            } else if (tile != SUBLOC_TILE_TRAMPOLINE
                                && tile != SUBLOC_TILE_WALL2
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
