// merge_track_tile_runs @ 0x435180 (thiscall, ret)

#include "bod_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904

unsigned char __fastcall is_slide_cache_tile_family(TrackRowCell* cell);
unsigned char __fastcall is_floor_cache_tile_family(TrackRowCell* cell);

#define IS_SLIDE_RUN_TILE(tile) \
    ((tile) == 1 || (tile) == 0x15 || (tile) == 0x1b || (tile) == 0x21 \
        || (tile) == 0x22)

#define CLEAR_MERGED_CONTINUATIONS(first_cell, run_length)                     \
    do {                                                                       \
        int clear_count = (run_length) - 1;                                    \
        if (clear_count > 0) {                                                 \
            TrackRowCell* clear_cell = (first_cell) + clear_count;             \
            do {                                                               \
                clear_cell->bod.list_flags &= ~0x20;                           \
                clear_cell->lane_and_flags &= ~0x6000u;                        \
                --clear_cell;                                                  \
                --clear_count;                                                 \
            } while (clear_count != 0);                                        \
        }                                                                      \
    } while (0)

void SubgameRuntime::merge_track_tile_runs()
{
    int row = 0;
    if (runtime_row_count > 0) {
        TrackRowCell* cell = (TrackRowCell*)((char*)this + 0x3bfac8);
        do {
            int lane_count = 8;
            do {
                cell->lane_and_flags |= 0x6000;
                ++cell;
                --lane_count;
            } while (lane_count != 0);

            ++row;
        } while (row < runtime_row_count);
    }

    int row_index = 0;
    if (runtime_row_count > 0) {
        TrackAttachmentRuntimeRow* row_record =
            (TrackAttachmentRuntimeRow*)((char*)this + 0x5ccac8);
        TrackRowCell* row_first_cell = (TrackRowCell*)((char*)this + 0x3bfac8);
        do {
            int lane = 0;
            TrackRowCell* cell = row_first_cell;
            do {
                unsigned char tile = cell->tile_id;

                if (is_slide_cache_tile_family(cell) != 0
                    && (cell->lane_and_flags & 0x8000) == 0
                    && (cell->lane_and_flags & 0x40) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor < 8 && IS_SLIDE_RUN_TILE(cursor->tile_id)
                           && (cursor->lane_and_flags & 0x8000) == 0
                           && (cursor->lane_and_flags & 0x4000) != 0
                           && (cursor->lane_and_flags & 0x60) == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)cell)
                            ->set_bod_object(
                                *(void**)(g_game_base + run_length * 0x38 + 0x4477c));
                        CLEAR_MERGED_CONTINUATIONS(cell, run_length);
                    }
                } else if (is_floor_cache_tile_family(cell) != 0
                           && (cell->lane_and_flags & 0x8000) == 0
                           && (cell->lane_and_flags & 0x40) == 0) {
                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor < 8 && is_floor_cache_tile_family(cursor) != 0
                           && (cursor->lane_and_flags & 0x8000) == 0
                           && (cursor->lane_and_flags & 0x4000) != 0
                           && (cursor->lane_and_flags & 0x60) == 0) {
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)cell)
                            ->set_bod_object(
                                *(void**)(g_game_base + run_length * 0x38 + 0x44afc));
                        CLEAR_MERGED_CONTINUATIONS(cell, run_length);
                    }
                } else if (tile == 0x0e) {
                    int flags = cell->lane_and_flags;
                    flags &= ~0x0e00;
                    flags |= 0x0100;
                    cell->lane_and_flags = flags;

                    int run_length = 0;
                    TrackRowCell* cursor = cell;
                    int lane_cursor = lane;
                    while (lane_cursor < 8 && cursor->tile_id == 0x0e
                           && (cursor->lane_and_flags & 0x4000) == 0x4000) {
                        cursor->lane_and_flags =
                            (cursor->lane_and_flags & ~0x0e00) | 0x0100;
                        ++run_length;
                        ++cursor;
                        ++lane_cursor;
                    }

                    if (run_length > 1) {
                        ((BodBase*)cell)
                            ->set_bod_object(
                                *(void**)(g_game_base + run_length * 0x38 + 0x445bc));
                        cell->lane_and_flags =
                            (cell->lane_and_flags & ~0x0f00) | ((run_length & 0xf) << 8);
                        CLEAR_MERGED_CONTINUATIONS(cell, run_length);
                    }
                } else if (tile == 0 || tile == 0x23) {
                    cell->lane_and_flags &= ~0x2000u;
                    if (level_mode == 2) {
                        ((BodBase*)cell)->set_bod_object(*(void**)(g_game_base + 0x44124));
                    } else {
                        cell->lane_and_flags &= ~0x4000u;
                    }
                }

                if ((row_record->flags & 4) != 0) {
                    cell->bod.list_flags &= ~0x222;
                    cell->lane_and_flags &= ~0x4000u;
                    row_record->primary_body.list_flags &= ~0x20;
                }

                ++lane;
                ++cell;
            } while (lane < 8);

            ++row_index;
            ++row_record;
            row_first_cell += 8;
        } while (row_index < runtime_row_count);
    }
}

#undef CLEAR_MERGED_CONTINUATIONS
#undef IS_SLIDE_RUN_TILE
