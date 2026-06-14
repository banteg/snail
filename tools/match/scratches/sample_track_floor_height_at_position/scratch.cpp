// sample_track_floor_height_at_position @ 0x43d4d0 (thiscall, ret)

#include "golb.h"

struct TrackRowCell {
    char unknown_00[0x14];
    float floor_height;
    char unknown_18[0x3c - 0x18];
    unsigned char tile_id;
};

class Game {
public:
    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);
    double sample_track_floor_height_at_position(Vector3* position);
};

static const float kFlatFloorHeight = 0.0f;
static const float kInvalidFloorHeight = -100.0f;

double Game::sample_track_floor_height_at_position(Vector3* position)
{
    TrackRowCell* cell = get_track_grid_cell_at_world_position(position);
    char tile_id = cell->tile_id;

    if (tile_id == 1 || tile_id == 0xf || tile_id == 0xe) {
        return kFlatFloorHeight;
    }

    if (tile_id == 2 || tile_id == 3 || tile_id == 4 || tile_id == 5 || tile_id == 6 ||
        tile_id == 7 || tile_id == 0xb || tile_id == 0xc || tile_id == 0xd) {
        return (position->z - (int)position->z) * 0.40000001f;
    }

    if (tile_id == 8 || tile_id == 9 || tile_id == 0xa) {
        return (position->z - (int)position->z) * 0.40000001f + 0.5f;
    }

    if (tile_id == 0x16) {
        return cell->floor_height;
    }

    return kInvalidFloorHeight;
}
