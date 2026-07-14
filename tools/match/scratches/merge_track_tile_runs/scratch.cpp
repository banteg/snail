// merge_track_tile_runs @ 0x435180 (thiscall, ret)

#include "bod_types.h"
#include "root_bod_catalog.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904

unsigned char __fastcall is_sub_loc_floor(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_slide(TrackRowCell* cell);

#define IS_FLOOR_RUN_TILE(tile) \
    ((tile) == 1 || (tile) == 0x15 || (tile) == 0x1b || (tile) == 0x21 \
        || (tile) == 0x22)

#define CELL_FROM_LANE_FLAGS(lane_flags) \
    ((TrackRowCell*)((char*)(lane_flags) - 0x40))

#define CLEAR_MERGED_CONTINUATIONS(game, row, first_lane, run_length)          \
    do {                                                                       \
        int clear_count = (run_length) - 1;                                    \
        if (clear_count > 0) {                                                 \
            unsigned int* clear_lane_flags =                                   \
                &(game)->runtime_cells[(row)][(first_lane) + clear_count]       \
                     .lane_and_flags;                                           \
            do {                                                               \
                TrackRowCell* clear_cell = (TrackRowCell*)(                     \
                    (char*)clear_lane_flags - 0x40);                            \
                clear_cell->bod.list_flags &= ~0x20;                           \
                *clear_lane_flags &= ~0x6000u;                                 \
                clear_lane_flags -=                                           \
                    sizeof(TrackRowCell) / sizeof(unsigned int);               \
                --clear_count;                                                 \
            } while (clear_count != 0);                                        \
        }                                                                      \
    } while (0)

void SubgameRuntime::merge_track_tile_runs()
{
    int row = 0;
    if (runtime_row_count > 0) {
        unsigned int* lane_flags = &runtime_cells[0][0].lane_and_flags;
        do {
            int lane_count = 8;
            do {
                *lane_flags |= 0x6000;
                lane_flags += sizeof(TrackRowCell) / sizeof(unsigned int);
                --lane_count;
            } while (lane_count != 0);

            ++row;
        } while (row < runtime_row_count);
    }

    int row_index = 0;
    if (runtime_row_count > 0) {
        int* row_attachment_flags =
            &runtime_rows[0].attachment_body.list_flags;
        unsigned int* cell_lane_flags =
            &runtime_cells[0][0].lane_and_flags;
        do {
            int lane = 0;
            do {
                TrackRowCell* cell = CELL_FROM_LANE_FLAGS(cell_lane_flags);
                if (is_sub_loc_floor(cell) != 0
                    && (*cell_lane_flags & 0x8000) == 0
                    && (*cell_lane_flags & 0x40) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor < 8 && IS_FLOOR_RUN_TILE(cursor->tile_id)
                           && (cursor->lane_and_flags & 0x8000) == 0
                           && (cursor->lane_and_flags & 0x4000) != 0
                           && (cursor->lane_and_flags & 0x60) == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                            ->set_bod_object(
                                ((RootBodCatalog*)(g_game_base
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                    ->floor_slices.storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else if (is_sub_loc_slide(cell) != 0
                           && (*cell_lane_flags & 0x8000) == 0
                           && (*cell_lane_flags & 0x40) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor < 8 && is_sub_loc_slide(cursor) != 0
                           && (cursor->lane_and_flags & 0x8000) == 0
                           && (cursor->lane_and_flags & 0x4000) != 0
                           && (cursor->lane_and_flags & 0x60) == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                            ->set_bod_object(
                                ((RootBodCatalog*)(g_game_base
                                        + ROOT_BOD_CATALOG_GAME_OFFSET))
                                    ->slide_slices.storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else {
                    unsigned char tile = cell->tile_id;
                    if (tile == 0x0e) {
                        int flags = *cell_lane_flags;
                        flags &= ~0x0e00;
                        flags |= 0x0100;
                        *cell_lane_flags = flags;

                        int run_length = 0;
                        TrackRowCell* cursor = cell;
                        int lane_cursor = lane;
                        while (lane_cursor < 8 && cursor->tile_id == 0x0e
                               && (*cell_lane_flags & 0x4000) == 0x4000) {
                            *cell_lane_flags =
                                (*cell_lane_flags & ~0x0e00) | 0x0100;
                            ++run_length;
                            ++cursor;
                            ++lane_cursor;
                        }

                        if (run_length > 1) {
                            ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                                ->set_bod_object(
                                    ((RootBodCatalog*)(g_game_base
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->pillars[run_length - 1]
                                        .object);
                            *cell_lane_flags =
                                (*cell_lane_flags & ~0x0f00)
                                | ((run_length & 0xf) << 8);
                            CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                        }
                    } else if (tile == 0 || tile == 0x23) {
                        *cell_lane_flags &= ~0x2000u;
                        if (level_mode == 2) {
                            ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                                ->set_bod_object(
                                    ((RootBodCatalog*)(g_game_base
                                            + ROOT_BOD_CATALOG_GAME_OFFSET))
                                        ->universe_hole.object);
                        } else {
                            *cell_lane_flags &= ~0x4000u;
                        }
                    }
                }

                if ((((unsigned char*)row_attachment_flags)[-0xb4] & 4) != 0) {
                    CELL_FROM_LANE_FLAGS(cell_lane_flags)->bod.list_flags &= ~0x222;
                    *cell_lane_flags &= ~0x4000u;
                    *row_attachment_flags &= ~0x20;
                }

                ++lane;
                cell_lane_flags +=
                    sizeof(TrackRowCell) / sizeof(unsigned int);
            } while (lane < 8);

            ++row_index;
            row_attachment_flags +=
                sizeof(TrackAttachmentRuntimeRow) / sizeof(int);
        } while (row_index < runtime_row_count);
    }
}

#undef CLEAR_MERGED_CONTINUATIONS
#undef CELL_FROM_LANE_FLAGS
#undef IS_FLOOR_RUN_TILE
