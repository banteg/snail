// sample_track_floor_height_at_position @ 0x43d4d0 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_attachment.h"

static const float kFlatFloorHeight = 0.0f;
static const float kInvalidFloorHeight = -100.0f;

double SubgameRuntime::sample_track_floor_height_at_position(Vector3* position)
{
    TrackRowCell* cell = get_track_grid_cell_at_world_position(position);
    char tile_id = cell->tile_id;

    if (tile_id == SUBLOC_TILE_FLOOR_DOT
        || tile_id == SUBLOC_TILE_SLIDE_UNDERSCORE
        || tile_id == SUBLOC_TILE_WALL2) {
        return kFlatFloorHeight;
    }

    if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE
        || tile_id == SUBLOC_TILE_RAMP_GREATER
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE
        || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET
        || tile_id == SUBLOC_TILE_RAMP_LESS
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET
        || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
        || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH) {
        return (position->z - (int)position->z) * 0.40000001f;
    }

    if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
        || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED) {
        return (position->z - (int)position->z) * 0.40000001f + 0.5f;
    }

    if (tile_id == SUBLOC_TILE_TRAMPOLINE) {
        return cell->position.y;
    }

    return kInvalidFloorHeight;
}
