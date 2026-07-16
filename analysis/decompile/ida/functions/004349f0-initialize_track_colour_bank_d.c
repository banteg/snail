/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_d @ 0x4349f0 */
/* selector: initialize_track_colour_bank_d */

// Runs the folded no-op tColour constructor across the second 51-entry Windows Slide bank; mobile BuildColours aliases both Slide calls to one gLocColourLookupSlide owner.
void __cdecl initialize_track_colour_bank_d()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_slide_1;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
