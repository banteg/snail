// select_track_tile_edge_variants @ 0x435a80 (thiscall)

#include "bod_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_row_cell_tile_views.h"

extern char* g_game_base; // data_4df904

#define IS_STRAIGHT_TRACK_FAMILY(tile) \
    ((tile) == 1 || (tile) == 0x14 || (tile) == 0x15 || (tile) == 0x1b \
        || (tile) == 0x21 || (tile) == 0x22)

void SubgameRuntime::select_track_tile_edge_variants()
{
    int row = 0;
    if (runtime_row_count > 0) {
        TrackRowCellTileByteView* cell =
            (TrackRowCellTileByteView*)((char*)this + 0x3bfb04);
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
                        || ((SubLoc*)((char*)cell - 0x90))
                                ->is_open_neighbor_tile_family()
                            != 0) {
                        cell->tile_flags_3d |= 8;
                    }
                    if (lane == 7
                        || ((SubLoc*)((char*)cell + 0x18))
                                ->is_open_neighbor_tile_family()
                            != 0) {
                        cell->tile_flags_3d |= 4;
                    }
                    if (row == 0
                        || ((SubLoc*)((char*)cell - 0x2dc))
                                ->is_open_neighbor_tile_family()
                            != 0) {
                        cell->tile_flags_3d |= 1;
                    }
                    if (row >= runtime_row_count - 1
                        || ((SubLoc*)((char*)cell + 0x264))
                                ->is_open_neighbor_tile_family()
                            != 0) {
                        cell->tile_flags_3d |= 2;
                    }

                    switch (cell->tile_flags_3d) {
                    case 9:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x4423c));
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - 0x3c))
                                        ->is_ramp_cache_tile_family()
                                    == 0) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x443fc));
                            }
                        }
                        break;

                    case 5:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x44274));
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - 0x3c))
                                        ->is_ramp_cache_tile_family()
                                    == 0) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x44434));
                            }
                        }
                        break;

                    case 10:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x442ac));
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - 0x3c))
                                        ->is_ramp_cache_tile_family()
                                    == 0) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x4446c));
                            }
                        }
                        break;

                    case 6:
                        *lane_and_flags |= variant_flag;
                        {
                            unsigned char tile = cell->tile_id;
                            if (IS_STRAIGHT_TRACK_FAMILY(tile)) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x442e4));
                            } else if (tile != 0x16 && tile != 0x0e
                                && ((SubLoc*)((char*)cell - 0x3c))
                                        ->is_ramp_cache_tile_family()
                                    == 0) {
                                ((BodBase*)((char*)cell - 0x3c))
                                    ->set_bod_object(*(void**)(g_game_base + 0x444a4));
                            }
                        }
                        break;
                    }
                }
                ++lane;
                ++cell;
            } while (lane < 8);

            ++row;
        } while (row < runtime_row_count);
    }
}

#undef IS_STRAIGHT_TRACK_FAMILY
