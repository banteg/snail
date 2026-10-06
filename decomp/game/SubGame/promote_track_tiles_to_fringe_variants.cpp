// promote_track_tiles_to_fringe_variants @ 0x4355f0 (thiscall)
// Authored cRSubGame::WarnTrack(): promotes floor/slide cells to warning
// variants when the same lane in the next generated row is empty.

#include "bod_types.h"
#include "game_root.h"
#include "root_bod_catalog.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

void cRSubGame::WarnTrack()
{
    int row = 0;
    if (runtime_row_count - 1 > 0) {
        unsigned int promoted_flag = SUBLOC_FLAG_WARNING_CACHE_FAMILY;
        do {
            for (int lane = 0; lane < SUBGAME_TRACK_LANE_COUNT; ++lane) {
                runtime_cells[row][lane].lane_and_flags &= ~SUBLOC_FLAG_WARNING_CACHE_FAMILY;
                if (runtime_cells[row + 1][lane].IsEmpty() != 0) {
                    // Physical slice index is also the rendered strip width - 1.
                    int slice_index = 0;
                    do {
                        if (runtime_cells[row][lane].object
                                == g_game->root_bod_catalog.floor_slices
                                       .storage[slice_index]
                                       .object
                            || runtime_cells[row][lane].object
                                == g_game->root_bod_catalog.slide_slices
                                       .storage[slice_index]
                                       .object) {
                            runtime_cells[row][lane].SetObject(
                                g_game->root_bod_catalog.warning_slices
                                    .storage[slice_index]
                                    .object);
                            runtime_cells[row][lane].lane_and_flags |= promoted_flag;
                        }
                        ++slice_index;
                    } while (slice_index < TRACK_SLICE_BOD_COUNT);

                    // All three corner banks share the 0, 1, 3, 2 storage map.
                    int corner_index = 0;
                    do {
                        if (runtime_cells[row][lane].object
                                == g_game->root_bod_catalog.floor_corners
                                       .storage[corner_index]
                                       .object
                            || runtime_cells[row][lane].object
                                == g_game->root_bod_catalog.slide_corners
                                       .storage[corner_index]
                                       .object) {
                            runtime_cells[row][lane].SetObject(
                                g_game->root_bod_catalog.warning_corners
                                    .storage[corner_index]
                                    .object);
                            runtime_cells[row][lane].lane_and_flags |= promoted_flag;
                        }
                        ++corner_index;
                    } while (corner_index < TRACK_CORNER_BOD_COUNT);
                }
            }

            ++row;
        } while (row < runtime_row_count - 1);
    }
}
