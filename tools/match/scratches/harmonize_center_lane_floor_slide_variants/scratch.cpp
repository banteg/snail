// harmonize_center_lane_floor_slide_variants @ 0x4356f0 (thiscall)

#include "bod_types.h"
#include "root_bod_catalog.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904

unsigned char __fastcall is_sub_loc_floor(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_slide(TrackRowCell* cell);

void SubgameRuntime::harmonize_center_lane_floor_slide_variants()
{
    SubgameRuntime* game_runtime = this;
    int row = 0;
    if (game_runtime->runtime_row_count - 1 > 0) {
        int transition_flag = 0x40;
        do {
            int lane = 0;
            int row_mod = row & 7;
            do {
                if (row_mod == 3) {
                    TrackRowCell* cell =
                        (TrackRowCell*)((char*)game_runtime + 0x3bfac8
                            + (lane + row * 8) * sizeof(TrackRowCell));
                    TrackRowCell* next = cell + 8;
                    if ((cell->lane_and_flags & 0x20) == 0) {
                        if ((next->lane_and_flags & 0x20) == 0
                            && is_sub_loc_slide(cell) == 1
                            && (is_sub_loc_floor(next) == 1
                                || next->tile_id == 0x1e)) {
                            char* game = g_game_base;
                            if (((BodBase*)cell)->object
                                == ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                       ->floor_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->slide_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game_base;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&((RootBodCatalog*)(game
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                            ->floor_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&((RootBodCatalog*)(game
                                                    + ROOT_BOD_CATALOG_GAME_OFFSET))
                                                    ->slide_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game_base;
                                }
                                offset += 0x38;
                            } while (offset < 0xe0);
                        }
                    }

                    if ((cell->lane_and_flags & 0x20) == 0) {
                        if ((next->lane_and_flags & 0x20) == 0
                            && is_sub_loc_floor(cell) == 1
                            && is_sub_loc_slide(next) == 1) {
                            char* game = g_game_base;
                            if (((BodBase*)cell)->object
                                == ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                       ->slide_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->floor_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game_base;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&((RootBodCatalog*)(game
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                            ->slide_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&((RootBodCatalog*)(game
                                                    + ROOT_BOD_CATALOG_GAME_OFFSET))
                                                    ->floor_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game_base;
                                }
                                offset += 0x38;
                            } while (offset < 0xe0);
                        }
                    }
                }

                if (row_mod == 5) {
                    TrackRowCell* cell =
                        (TrackRowCell*)((char*)game_runtime + 0x3bfac8
                            + (lane + row * 8) * sizeof(TrackRowCell));
                    TrackRowCell* previous = cell - 8;
                    if ((cell->lane_and_flags & 0x20) == 0) {
                        if ((previous->lane_and_flags & 0x20) == 0
                            && is_sub_loc_slide(cell) == 1
                            && (is_sub_loc_floor(previous) == 1
                                || previous->tile_id == 0x20)) {
                            char* game = g_game_base;
                            if (((BodBase*)cell)->object
                                == ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                       ->floor_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->slide_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game_base;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&((RootBodCatalog*)(game
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                            ->floor_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&((RootBodCatalog*)(game
                                                    + ROOT_BOD_CATALOG_GAME_OFFSET))
                                                    ->slide_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game_base;
                                }
                                offset += 0x38;
                            } while (offset < 0xe0);
                        }
                    }

                    if ((cell->lane_and_flags & 0x20) == 0) {
                        if ((previous->lane_and_flags & 0x20) == 0
                            && is_sub_loc_floor(cell) == 1
                            && is_sub_loc_slide(previous) == 1) {
                            char* game = g_game_base;
                            if (((BodBase*)cell)->object
                                == ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                       ->slide_slices.storage[0]
                                       .object) {
                                ((BodBase*)cell)->set_bod_object(
                                    ((RootBodCatalog*)(game
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->floor_slices.storage[0]
                                        .object);
                                cell->lane_and_flags |= transition_flag;
                                game = g_game_base;
                            }
                            int offset = 0;
                            do {
                                if (((BodBase*)cell)->object
                                    == ((BodBase*)((char*)&((RootBodCatalog*)(game
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                            ->slide_corners
                                        + offset))
                                           ->object) {
                                    ((BodBase*)cell)
                                        ->set_bod_object(
                                            ((BodBase*)((char*)&((RootBodCatalog*)(game
                                                    + ROOT_BOD_CATALOG_GAME_OFFSET))
                                                    ->floor_corners
                                                + offset))
                                                ->object);
                                    cell->lane_and_flags |= transition_flag;
                                    game = g_game_base;
                                }
                                offset += 0x38;
                            } while (offset < 0xe0);
                        }
                    }
                }

                ++lane;
            } while (lane < 8);

            ++row;
        } while (row < game_runtime->runtime_row_count - 1);
    }
}
