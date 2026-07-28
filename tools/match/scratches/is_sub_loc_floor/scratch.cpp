// is_sub_loc_floor @ 0x439a40 (thiscall, ret) — cRSubLoc::IsFloor()

#include "track_attachment.h"

bool cRSubLoc::IsFloor()
{
    unsigned char tile_id = this->tile_id;
    bool result;
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
