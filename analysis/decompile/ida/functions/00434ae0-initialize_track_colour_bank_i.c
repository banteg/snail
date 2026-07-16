/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_i @ 0x434ae0 */
/* selector: initialize_track_colour_bank_i */

// Runs the folded no-op tColour constructor across the 51-entry Windows gLocColourLookupPath counterpart.
void __cdecl initialize_track_colour_bank_i()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_path;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
