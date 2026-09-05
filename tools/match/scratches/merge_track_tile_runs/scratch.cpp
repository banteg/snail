// merge_track_tile_runs @ 0x435180 (thiscall, ret)

#include "bod_types.h"
#include "game_root.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

#define IS_FLOOR_RUN_TILE(tile) \
    ((tile) == SUBLOC_TILE_FLOOR_DOT \
        || (tile) == SUBLOC_TILE_FLOOR_DASH \
        || (tile) == SUBLOC_TILE_FLOOR_VARIANT_1B \
        || (tile) == SUBLOC_TILE_GARBAGE_HAZARD \
        || (tile) == SUBLOC_TILE_SALT_HAZARD)

#define CLEAR_MERGED_CONTINUATIONS(game, row, first_lane, run_length) \
    do { \
        --(run_length); \
        while ((run_length) > 0) { \
            (game)->runtime_cells[(row)][(first_lane) + (run_length)].list_flags &= \
                ~BOD_FLAG_RENDER_ENABLED; \
            (game)->runtime_cells[(row)][(first_lane) + (run_length)].lane_and_flags &= \
                ~(SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY); \
            --(run_length); \
        } \
    } while (0)

void cRSubGame::CondenseTrack()
{
    for (int row = 0; row < runtime_row_count; ++row) {
        for (int lane = 0; lane < SUBGAME_TRACK_LANE_COUNT; ++lane) {
            runtime_cells[row][lane].lane_and_flags |=
                SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY;
        }
    }

    int row_index = 0;
    if (runtime_row_count > 0) {
        do {
            int lane = 0;
            do {
                if (runtime_cells[row_index][lane].IsFloor() != 0
                    && (runtime_cells[row_index][lane].lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                    && (runtime_cells[row_index][lane].lane_and_flags & SUBLOC_FLAG_CACHE_FAMILY_SWAPPED) == 0) {
                    int run_length = 0;
                    while (lane + run_length
                               < (int)(sizeof(runtime_cells[0])
                                   / sizeof(runtime_cells[0][0]))
                           && IS_FLOOR_RUN_TILE(runtime_cells[row_index][lane + run_length].tile_id)
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY) != 0
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags
                                   & (SUBLOC_FLAG_WARNING_CACHE_FAMILY
                                       | SUBLOC_FLAG_CACHE_FAMILY_SWAPPED))
                               == 0) {
                        ++run_length;
                    }

                    if (run_length > 1) {
                        runtime_cells[row_index][lane].SetObject(
                                g_game->root_bod_catalog.floor_slices
                                    .storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else if (runtime_cells[row_index][lane].IsSlide() != 0
                           && (runtime_cells[row_index][lane].lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (runtime_cells[row_index][lane].lane_and_flags & SUBLOC_FLAG_CACHE_FAMILY_SWAPPED) == 0) {
                    int run_length = 0;
                    while (lane + run_length
                               < (int)(sizeof(runtime_cells[0])
                                   / sizeof(runtime_cells[0][0]))
                           && runtime_cells[row_index][lane + run_length].IsSlide() != 0
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags & SUBLOC_FLAG_CORNER_OBJECT) == 0
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY) != 0
                           && (runtime_cells[row_index][lane + run_length].lane_and_flags
                                   & (SUBLOC_FLAG_WARNING_CACHE_FAMILY
                                       | SUBLOC_FLAG_CACHE_FAMILY_SWAPPED))
                               == 0) {
                        ++run_length;
                    }

                    if (run_length > 1) {
                        runtime_cells[row_index][lane].SetObject(
                                g_game->root_bod_catalog.slide_slices
                                    .storage[run_length - 1]
                                    .object);
                        CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                    }
                } else {
                    unsigned char tile = runtime_cells[row_index][lane].tile_id;
                    if (tile == SUBLOC_TILE_WALL2) {
                        int flags = runtime_cells[row_index][lane].lane_and_flags;
                        flags &= ~SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK;
                        flags |= SUBLOC_MERGED_RUN_WIDTH_ONE;
                        runtime_cells[row_index][lane].lane_and_flags = flags;

                        int run_length = 0;
                        while (lane + run_length
                                   < (int)(sizeof(runtime_cells[0])
                                       / sizeof(runtime_cells[0][0]))
                               && runtime_cells[row_index][lane + run_length].tile_id == SUBLOC_TILE_WALL2
                               && (runtime_cells[row_index][lane].lane_and_flags & SUBLOC_FLAG_UNCACHED_BODY)
                                   == SUBLOC_FLAG_UNCACHED_BODY) {
                            runtime_cells[row_index][lane].lane_and_flags =
                                (runtime_cells[row_index][lane].lane_and_flags
                                    & ~SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK)
                                | SUBLOC_MERGED_RUN_WIDTH_ONE;
                            ++run_length;
                        }

                        if (run_length > 1) {
                            runtime_cells[row_index][lane].SetObject(
                                    g_game->root_bod_catalog.pillars[run_length - 1]
                                        .object);
                            runtime_cells[row_index][lane].lane_and_flags =
                                (runtime_cells[row_index][lane].lane_and_flags & ~SUBLOC_MERGED_RUN_WIDTH_MASK)
                                | ((run_length & SUBLOC_MERGED_RUN_WIDTH_VALUE_MASK)
                                    << SUBLOC_MERGED_RUN_WIDTH_SHIFT);
                            CLEAR_MERGED_CONTINUATIONS(this, row_index, lane, run_length);
                        }
                    } else if (tile == SUBLOC_TILE_EMPTY
                        || tile == SUBLOC_TILE_RING_MARKER) {
                        runtime_cells[row_index][lane].lane_and_flags&= ~SUBLOC_FLAG_AI_ENABLED;
                        if (level_mode == 2) {
                            runtime_cells[row_index][lane].SetObject(
                                    g_game->root_bod_catalog.universe_hole.object);
                        } else {
                            runtime_cells[row_index][lane].lane_and_flags&= ~SUBLOC_FLAG_UNCACHED_BODY;
                        }
                    }
                }

                if ((runtime_rows[row_index].flags
                        & SUBROW_FLAG_SUPPRESS_TRACK_RENDER)
                    != 0) {
                    runtime_cells[row_index][lane].list_flags &=
                        ~(BOD_FLAG_HAS_OBJECT | BOD_FLAG_RENDER_ENABLED
                            | BOD_FLAG_LINKED);
                    runtime_cells[row_index][lane].lane_and_flags&= ~SUBLOC_FLAG_UNCACHED_BODY;
                    runtime_rows[row_index].attachment_body.list_flags &= ~BOD_FLAG_RENDER_ENABLED;
                }

                ++lane;
            } while (lane
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0])));

            ++row_index;
        } while (row_index < runtime_row_count);
    }
}

#undef CLEAR_MERGED_CONTINUATIONS
#undef IS_FLOOR_RUN_TILE
