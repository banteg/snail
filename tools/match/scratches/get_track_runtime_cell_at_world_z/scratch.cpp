// get_track_runtime_cell_at_world_z @ 0x43d480 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_attachment_types.h"

SubRow* SubgameRuntime::get_track_runtime_cell_at_world_z(Vector3* position)
{
    int row = (int)position->z;

    if (row < 0) {
        row = 0;
    } else if (row > 3199) {
        row = 3199;
    }

    return &runtime_rows[row];
}
