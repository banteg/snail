// is_sub_loc_ramp @ 0x439a70 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_ramp()
{
    unsigned char tile_id = this->tile_id;
    unsigned char result;
    if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE
        || tile_id == SUBLOC_TILE_RAMP_GREATER
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE
        || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
        || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
        || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
        || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
        || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET
        || tile_id == SUBLOC_TILE_RAMP_LESS
        || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
