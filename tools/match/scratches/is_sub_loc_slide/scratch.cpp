// is_sub_loc_slide @ 0x439ad0 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_slide()
{
    unsigned char tile_id = this->tile_id;
    unsigned char result;
    if (tile_id == SUBLOC_TILE_SLIDE_UNDERSCORE
        || tile_id == SUBLOC_TILE_HEALTH_PICKUP
        || tile_id == SUBLOC_TILE_SPEEDUP_PICKUP
        || tile_id == SUBLOC_TILE_JETPACK_PICKUP
        || tile_id == SUBLOC_TILE_SLIDE_VARIANT_1A
        || tile_id == SUBLOC_TILE_SLIDE_O
        || tile_id == SUBLOC_TILE_SLUG_HAZARD
        || tile_id == SUBLOC_TILE_SLIDE_F) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
