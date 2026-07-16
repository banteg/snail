/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_a @ 0x434990 */
/* selector: initialize_track_colour_bank_a */

// Runs the folded no-op tColour constructor across the 51-entry Windows gLocColourLookupCheckBlack counterpart before build_track_colours seeds authored white values.
void __cdecl initialize_track_colour_bank_a()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_check_black;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
