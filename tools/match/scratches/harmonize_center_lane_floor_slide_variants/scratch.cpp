// harmonize_center_lane_floor_slide_variants @ 0x4356f0 (thiscall)

#include "bod_types.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"


unsigned char __fastcall is_sub_loc_floor(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_slide(TrackRowCell* cell);

void SubgameRuntime::harmonize_center_lane_floor_slide_variants()
{
    SubgameRuntime* game_runtime = this;
    int row = 0;
    if (game_runtime->runtime_row_count - 1 > 0) {
        int transition_flag = SUBLOC_FLAG_CACHE_FAMILY_SWAPPED;
        do {
            int lane = 0;
            int row_mod = row & 7;
            do {
                if (row_mod == 3) {
                    TrackRowCell* cell = &game_runtime->runtime_cells[row][lane];
                    TrackRowCell* next = cell
                        + sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
                    if ((cell->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0) {
                        if ((next->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0
                            && is_sub_loc_floor(cell) == 1
                            && (is_sub_loc_slide(next) == 1
                                || next->tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE)) {
                            GameRoot* game = g_game;
                            if (((BodBase*)cell)->object
                                == game->root_bod_catalog.floor_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    game->root_bod_catalog.slide_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&game->root_bod_catalog.floor_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&game->root_bod_catalog.slide_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game;
                                }
                                offset += sizeof(BodBase);
                            } while (offset
                                < (int)sizeof(game->root_bod_catalog.floor_corners));
                        }
                    }

                    if ((cell->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0) {
                        if ((next->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0
                            && is_sub_loc_slide(cell) == 1
                            && is_sub_loc_floor(next) == 1) {
                            GameRoot* game = g_game;
                            if (((BodBase*)cell)->object
                                == game->root_bod_catalog.slide_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    game->root_bod_catalog.floor_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&game->root_bod_catalog.slide_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&game->root_bod_catalog.floor_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game;
                                }
                                offset += sizeof(BodBase);
                            } while (offset
                                < (int)sizeof(game->root_bod_catalog.slide_corners));
                        }
                    }
                }

                if (row_mod == 5) {
                    TrackRowCell* cell = &game_runtime->runtime_cells[row][lane];
                    TrackRowCell* previous = cell
                        - sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
                    if ((cell->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0) {
                        if ((previous->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0
                            && is_sub_loc_floor(cell) == 1
                            && (is_sub_loc_slide(previous) == 1
                                || previous->tile_id == SUBLOC_TILE_FLOOR_HASH_MARKER)) {
                            GameRoot* game = g_game;
                            if (((BodBase*)cell)->object
                                == game->root_bod_catalog.floor_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    game->root_bod_catalog.slide_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&game->root_bod_catalog.floor_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&game->root_bod_catalog.slide_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game;
                                }
                                offset += sizeof(BodBase);
                            } while (offset
                                < (int)sizeof(game->root_bod_catalog.floor_corners));
                        }
                    }

                    if ((cell->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0) {
                        if ((previous->lane_and_flags & SUBLOC_FLAG_WARNING_CACHE_FAMILY) == 0
                            && is_sub_loc_slide(cell) == 1
                            && is_sub_loc_floor(previous) == 1) {
                            GameRoot* game = g_game;
                            if (((BodBase*)cell)->object
                                == game->root_bod_catalog.slide_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    game->root_bod_catalog.floor_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&game->root_bod_catalog.slide_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&game->root_bod_catalog.floor_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game;
                                }
                                offset += sizeof(BodBase);
                            } while (offset
                                < (int)sizeof(game->root_bod_catalog.slide_corners));
                        }
                    }
                }

                ++lane;
            } while (lane
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0])));

            ++row;
        } while (row < game_runtime->runtime_row_count - 1);
    }
}
