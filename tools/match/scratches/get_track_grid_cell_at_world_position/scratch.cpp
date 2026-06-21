// get_track_grid_cell_at_world_position @ 0x43d410 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_attachment_types.h"

TrackRowCell* SubgameRuntime::get_track_grid_cell_at_world_position(Vector3* position)
{
    int lane = (int)(position->x + 4.0f);
    int row = (int)position->z;

    if (lane < 0) {
        lane = 0;
    } else if (lane > 7) {
        lane = 7;
    }

    if (row < 0) {
        row = 0;
    } else if (row > 3199) {
        row = 3199;
    }

    return (TrackRowCell*)((char*)this + 0x3bfac8 + (lane + row * 8) * 0x54);
}
