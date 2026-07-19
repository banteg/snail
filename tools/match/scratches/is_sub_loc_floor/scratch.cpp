// is_sub_loc_floor @ 0x439a40 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_floor()
{
    unsigned char tile_id = this->tile_id;
    unsigned char result;
    if (tile_id == SUBLOC_TILE_FLOOR_DOT
        || tile_id == SUBLOC_TILE_FLOOR_VARIANT_14
        || tile_id == SUBLOC_TILE_FLOOR_DASH
        || tile_id == SUBLOC_TILE_GARBAGE_HAZARD
        || tile_id == SUBLOC_TILE_SALT_HAZARD
        || tile_id == SUBLOC_TILE_FLOOR_VARIANT_1B) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
