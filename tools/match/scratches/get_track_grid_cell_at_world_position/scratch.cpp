// get_track_grid_cell_at_world_position @ 0x43d410 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_attachment_types.h"

TrackRowCell* SubgameRuntime::get_track_grid_cell_at_world_position(Vector3* position)
{
    int lane = (int)(position->x + 4.0f);
    int row = (int)position->z;

    if (lane < 0) {
        lane = 0;
    } else if (lane > SUBGAME_TRACK_LANE_COUNT - 1) {
        lane = SUBGAME_TRACK_LANE_COUNT - 1;
    }

    if (row < 0) {
        row = 0;
    } else if (row > SUBGAME_RUNTIME_ROW_CAPACITY - 1) {
        row = SUBGAME_RUNTIME_ROW_CAPACITY - 1;
    }

    return &runtime_cells[row][lane];
}
