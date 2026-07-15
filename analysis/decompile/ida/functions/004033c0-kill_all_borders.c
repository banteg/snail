/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_all_borders @ 0x4033c0 */
/* selector: kill_all_borders */

// Exact void cRBorderManager::KillBorders() pool teardown. All three Windows callers discard EAX, proving the final per-record flags value is loop residue rather than an API result.
void __thiscall kill_all_borders(BorderManager *manager)
{
  int32_t *p_flags; // ecx
  int v2; // edx
  int32_t v3; // eax

  p_flags = &manager->borders[0].flags;
  v2 = 150;
  do
  {
    v3 = *p_flags;
    if ( *p_flags )
    {
      if ( (v3 & 0x10000400) == 0 )
      {
        LOBYTE(v3) = v3 & 1;
        BYTE1(v3) |= 2u;
        *p_flags = v3;
      }
    }
    p_flags += 457;
    --v2;
  }
  while ( v2 );
}
