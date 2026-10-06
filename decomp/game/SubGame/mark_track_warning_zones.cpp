// mark_track_warning_zones @ 0x4354f0 (thiscall, ret)
// cRSubGame::DeSaltTrack() per Android symbols: stamps a 6-row x 2-col
// warning footprint behind every hazard-bearing tile, suppressing both random
// salt and garbage spawns in the approach corridor.

#include "subgame_runtime.h"

void cRSubGame::DeSaltTrack()
{
    int row = 0;
    if (runtime_row_count - 1 > 0) {
        do {
            for (int col = 0; col < 8; ++col) {
                char t = runtime_cells[row][col].tile_id;
                if (t == 2 || t == 3 || t == 4 || t == 5 || t == 6 || t == 7
                    || t == 8 || t == 9 || t == 10 || t == 11 || t == 12
                    || t == 13 || t == 14 || t == 23 || t == 25 || t == 33) {
                    int scan_row = row;
                    for (int back = 6; back; --back) {
                        for (int dc = -1; dc < 1; ++dc) {
                            if (scan_row >= 0 && scan_row < runtime_row_count - 1
                                && dc + col >= 0 && dc + col < 8)
                                runtime_cells[scan_row][col + dc].lane_and_flags |=
                                    SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED;
                        }
                        --scan_row;
                    }
                }
            }
            ++row;
        } while (row < runtime_row_count - 1);
    }
}
