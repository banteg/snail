// promote_track_tiles_to_fringe_variants @ 0x4355f0 (thiscall)

#include "bod_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904

unsigned char __fastcall is_open_neighbor_tile_family(TrackRowCell* cell);

void SubgameRuntime::promote_track_tiles_to_fringe_variants()
{
    int row = 0;
    if (runtime_row_count - 1 > 0) {
        TrackRowCell* cell = (TrackRowCell*)((char*)this + 0x3bfac8);
        int promoted_flag = 0x20;
        do {
            int lane_count = 8;
            do {
                cell->lane_and_flags &= ~0x20u;
                if (is_open_neighbor_tile_family(cell + 8) != 0) {
                    char* game = g_game_base;
                    int offset = 0;
                    do {
                        void* object = ((BodBase*)cell)->object;
                        if (object == *(void**)(game + offset + 0x447b4)
                            || object == *(void**)(game + offset + 0x44b34)) {
                            ((BodBase*)cell)->set_bod_object(*(void**)(game + offset + 0x44974));
                            cell->lane_and_flags |= promoted_flag;
                            game = g_game_base;
                        }
                        offset += 0x38;
                    } while (offset < 0x1c0);

                    offset = 0;
                    do {
                        void* object = ((BodBase*)cell)->object;
                        if (object == *(void**)(game + offset + 0x4423c)
                            || object == *(void**)(game + offset + 0x443fc)) {
                            ((BodBase*)cell)->set_bod_object(*(void**)(game + offset + 0x4431c));
                            cell->lane_and_flags |= promoted_flag;
                            game = g_game_base;
                        }
                        offset += 0x38;
                    } while (offset < 0xe0);
                }
                ++cell;
                --lane_count;
            } while (lane_count != 0);

            ++row;
        } while (row < runtime_row_count - 1);
    }
}
