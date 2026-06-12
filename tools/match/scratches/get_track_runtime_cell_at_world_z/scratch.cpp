// get_track_runtime_cell_at_world_z @ 0x43d480 (thiscall, ret)

#include "golb.h"

class Game {
public:
    void* get_track_runtime_cell_at_world_z(Vector3* position);
};

void* Game::get_track_runtime_cell_at_world_z(Vector3* position)
{
    int row = (int)position->z;

    if (row < 0) {
        row = 0;
    } else if (row > 3199) {
        row = 3199;
    }

    return (char*)this + 0x5ccac8 + row * 0xf4;
}
