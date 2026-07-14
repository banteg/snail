// merge_track_tile_runs @ 0x435180 (thiscall, ret)

#include <stddef.h>

#include "bod_types.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern GameRoot* g_game; // data_4df904

unsigned char __fastcall is_sub_loc_floor(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_slide(TrackRowCell* cell);

#define IS_FLOOR_RUN_TILE(tile) \
    ((tile) == 1 || (tile) == 0x15 || (tile) == 0x1b || (tile) == 0x21 \
        || (tile) == 0x22)

#define CELL_FROM_LANE_FLAGS(lane_flags) \
    ((TrackRowCell*)((char*)(lane_flags) \
        - offsetof(TrackRowCell, lane_and_flags)))

#define CLEAR_MERGED_CONTINUATIONS(game, row, first_lane, run_length)          \
    do {                                                                       \
        --(run_length);                                                        \
        if ((run_length) > 0) {                                                \
            unsigned int* clear_lane_flags =                                   \
                &(game)->runtime_cells[(row)][(first_lane) + (run_length)]      \
                     .lane_and_flags;                                           \
            do {                                                               \
                CELL_FROM_LANE_FLAGS(clear_lane_flags)->list_flags &= ~0x20;    \
                *clear_lane_flags &=                                           \
                    ~(SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY);     \
                clear_lane_flags -=                                           \
                    sizeof(TrackRowCell) / sizeof(unsigned int);               \
                --(run_length);                                                \
            } while ((run_length) != 0);                                       \
        }                                                                      \
    } while (0)

void SubgameRuntime::merge_track_tile_runs()
{
    int row = 0;
    if (runtime_row_count > 0) {
        unsigned int* lane_flags = &runtime_cells[0][0].lane_and_flags;
        do {
            int lane_count = sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
            do {
                *lane_flags |=
                    SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY;
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
                    && (*cell_lane_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                    && (*cell_lane_flags & SUBLOC_FLAG_CACHE_FAMILY_SWAPPED) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor
                               < (int)(sizeof(runtime_cells[0])
                                   / sizeof(runtime_cells[0][0]))
                           && IS_FLOOR_RUN_TILE(cursor->tile_id)
                           && (cursor->lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (cursor->lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY) != 0
                           && (cursor->lane_and_flags
                                   & (SUBLOC_FLAG_WARNING_CACHE_FAMILY
                                       | SUBLOC_FLAG_CACHE_FAMILY_SWAPPED))
                               == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                            ->set_bod_object(
                                g_game->root_bod_catalog.floor_slices
                                    .storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else if (is_sub_loc_slide(cell) != 0
                           && (*cell_lane_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (*cell_lane_flags & SUBLOC_FLAG_CACHE_FAMILY_SWAPPED) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor
                               < (int)(sizeof(runtime_cells[0])
                                   / sizeof(runtime_cells[0][0]))
                           && is_sub_loc_slide(cursor) != 0
                           && (cursor->lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (cursor->lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY) != 0
                           && (cursor->lane_and_flags
                                   & (SUBLOC_FLAG_WARNING_CACHE_FAMILY
                                       | SUBLOC_FLAG_CACHE_FAMILY_SWAPPED))
                               == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                            ->set_bod_object(
                                g_game->root_bod_catalog.slide_slices
                                    .storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else {
                    unsigned char tile = cell->tile_id;
                    if (tile == 0x0e) {
                        int flags = *cell_lane_flags;
                        flags &= ~SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK;
                        flags |= SUBLOC_MERGED_RUN_WIDTH_ONE;
                        *cell_lane_flags = flags;

                        int run_length = 0;
                        TrackRowCell* cursor = cell;
                        int lane_cursor = lane;
                        while (lane_cursor
                                   < (int)(sizeof(runtime_cells[0])
                                       / sizeof(runtime_cells[0][0]))
                               && cursor->tile_id == 0x0e
                               && (*cell_lane_flags & SUBLOC_FLAG_UNCACHED_BODY)
                                   == SUBLOC_FLAG_UNCACHED_BODY) {
                            *cell_lane_flags =
                                (*cell_lane_flags
                                    & ~SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK)
                                | SUBLOC_MERGED_RUN_WIDTH_ONE;
                            ++run_length;
                            ++cursor;
                            ++lane_cursor;
                        }

                        if (run_length > 1) {
                            ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                                ->set_bod_object(
                                    g_game->root_bod_catalog.pillars[run_length - 1]
                                        .object);
                            *cell_lane_flags =
                                (*cell_lane_flags & ~SUBLOC_MERGED_RUN_WIDTH_MASK)
                                | ((run_length & SUBLOC_MERGED_RUN_WIDTH_VALUE_MASK)
                                    << SUBLOC_MERGED_RUN_WIDTH_SHIFT);
                            CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                        }
                    } else if (tile == 0 || tile == 0x23) {
                        *cell_lane_flags &= ~SUBLOC_FLAG_AI_ENABLED;
                        if (level_mode == 2) {
                            ((BodBase*)CELL_FROM_LANE_FLAGS(cell_lane_flags))
                                ->set_bod_object(
                                    g_game->root_bod_catalog.universe_hole.object);
                        } else {
                            *cell_lane_flags &= ~SUBLOC_FLAG_UNCACHED_BODY;
                        }
                    }
                }

                if ((((unsigned char*)row_attachment_flags)[-0xb4]
                        & SUBROW_FLAG_SUPPRESS_TRACK_RENDER)
                    != 0) {
                    CELL_FROM_LANE_FLAGS(cell_lane_flags)->list_flags &= ~0x222;
                    *cell_lane_flags &= ~SUBLOC_FLAG_UNCACHED_BODY;
                    *row_attachment_flags &= ~0x20;
                }

                ++lane;
                cell_lane_flags +=
                    sizeof(TrackRowCell) / sizeof(unsigned int);
            } while (lane
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0])));

            ++row_index;
            row_attachment_flags +=
                sizeof(SubRow) / sizeof(int);
        } while (row_index < runtime_row_count);
    }
}

#undef CLEAR_MERGED_CONTINUATIONS
#undef CELL_FROM_LANE_FLAGS
#undef IS_FLOOR_RUN_TILE
