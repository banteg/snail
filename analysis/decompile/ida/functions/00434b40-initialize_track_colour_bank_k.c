/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_k @ 0x434b40 */
/* selector: initialize_track_colour_bank_k */

// Runs the folded no-op tColour constructor across the 51-entry Windows gLocColourLookupPathWarp counterpart, which BuildColours intentionally visits twice.
void __cdecl initialize_track_colour_bank_k()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_path_warp;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
