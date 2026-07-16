/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_j @ 0x434b10 */
/* selector: initialize_track_colour_bank_j */

// Runs the folded no-op tColour constructor across the 51-entry Windows gLocColourLookupPathWorm counterpart, which BuildColours intentionally visits twice.
void __cdecl initialize_track_colour_bank_j()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_path_worm;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
