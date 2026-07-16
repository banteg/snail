/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_colour_bank_f @ 0x434a50 */
/* selector: initialize_track_colour_bank_f */

// Runs the folded no-op tColour constructor across the 51-entry Windows gLocColourLookupTrampoline counterpart.
void __cdecl initialize_track_colour_bank_f()
{
  tColour *v0; // esi
  int v1; // edi

  v0 = &g_loc_colour_lookup_trampoline;
  v1 = 51;
  do
  {
    noop_this_constructor(v0++);
    --v1;
  }
  while ( v1 );
}
