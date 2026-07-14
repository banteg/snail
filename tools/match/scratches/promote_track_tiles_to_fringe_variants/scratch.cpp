// promote_track_tiles_to_fringe_variants @ 0x4355f0 (thiscall)

#include "bod_types.h"
#include "game_root.h"
#include "root_bod_catalog.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern GameRoot* g_game; // data_4df904

unsigned char __fastcall is_sub_loc_empty(TrackRowCell* cell);

void SubgameRuntime::promote_track_tiles_to_fringe_variants()
{
    int row = 0;
    if (runtime_row_count - 1 > 0) {
        TrackRowCell* cell = &runtime_cells[0][0];
        int promoted_flag = 0x20;
        do {
            int lane_count = sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
            do {
                cell->lane_and_flags &= ~0x20u;
                if (is_sub_loc_empty(cell + 8) != 0) {
                    GameRoot* game = g_game;
                    int offset = 0;
                    do {
                        void* object = ((BodBase*)cell)->object;
                        if (object
                                == ((BodBase*)((char*)&game->root_bod_catalog.floor_slices
                                    + offset))
                                       ->object
                            || object
                                == ((BodBase*)((char*)&game->root_bod_catalog.slide_slices
                                    + offset))
                                       ->object) {
                            ((BodBase*)cell)->set_bod_object(
                                ((BodBase*)((char*)&game->root_bod_catalog.warning_slices
                                    + offset))
                                    ->object);
                            cell->lane_and_flags |= promoted_flag;
                            game = g_game;
                        }
                        offset += sizeof(BodBase);
                    } while (offset
                        < (int)sizeof(game->root_bod_catalog.floor_slices));

                    offset = 0;
                    do {
                        void* object = ((BodBase*)cell)->object;
                        if (object
                                == ((BodBase*)((char*)&game->root_bod_catalog.floor_corners
                                    + offset))
                                       ->object
                            || object
                                == ((BodBase*)((char*)&game->root_bod_catalog.slide_corners
                                    + offset))
                                       ->object) {
                            ((BodBase*)cell)->set_bod_object(
                                ((BodBase*)((char*)&game->root_bod_catalog.warning_corners
                                    + offset))
                                    ->object);
                            cell->lane_and_flags |= promoted_flag;
                            game = g_game;
                        }
                        offset += sizeof(BodBase);
                    } while (offset
                        < (int)sizeof(game->root_bod_catalog.floor_corners));
                }
                ++cell;
                --lane_count;
            } while (lane_count != 0);

            ++row;
        } while (row < runtime_row_count - 1);
    }
}
