// is_sub_loc_slide @ 0x439ad0 (thiscall, ret) — cRSubLoc::IsSlide()

#include "track_attachment.h"

bool cRSubLoc::IsSlide()
{
    unsigned char tile_id = this->tile_id;
    bool result;
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
