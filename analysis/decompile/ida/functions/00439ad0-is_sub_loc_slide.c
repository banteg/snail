/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_slide @ 0x439ad0 */
/* selector: is_sub_loc_slide */

// Exact Windows counterpart of Android `cRSubLoc::IsSlide()`: accepts tile ids 15, 23, 24, 25, 26, 16, 18, and 19. This retires the historical cache-family labels that had Floor and Slide reversed.
int32_t __fastcall is_sub_loc_slide(TrackRowCell *cell)
{
  SubLocTileId tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == SUBLOC_TILE_SLIDE_UNDERSCORE
                || tile_id == SUBLOC_TILE_HEALTH_PICKUP
                || tile_id == SUBLOC_TILE_SPEEDUP_PICKUP
                || tile_id == SUBLOC_TILE_JETPACK_PICKUP
                || tile_id == SUBLOC_TILE_SLIDE_VARIANT_1A
                || tile_id == SUBLOC_TILE_SLIDE_O
                || tile_id == SUBLOC_TILE_SLUG_HAZARD
                || tile_id == SUBLOC_TILE_SLIDE_F;
  return result;
}
