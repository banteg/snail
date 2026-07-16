/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_banks_b_c @ 0x4349c0 */
/* selector: initialize_track_colour_banks_b_c */

// Runs the folded no-op tColour constructor across the contiguous 102-entry Windows owner holding gLocColourLookupFloor followed by the first Slide view.
void __cdecl initialize_track_colour_banks_b_c()
{
  TrackFloorSlideColourBanks *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_floor_slide_0;
  v1 = 102;
  do
  {
    noop_this_constructor(v0);
    v0 = (TrackFloorSlideColourBanks *)((char *)v0 + 16);
    --v1;
  }
  while ( v1 );
}
