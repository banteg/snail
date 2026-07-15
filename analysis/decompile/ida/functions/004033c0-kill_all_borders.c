/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_all_borders @ 0x4033c0 */
/* selector: kill_all_borders */

// Exact void cRBorderManager::KillBorders() pool teardown. All three Windows callers discard EAX, proving the final per-record flags value is loop residue rather than an API result.
void __thiscall kill_all_borders(FrameBorderManager *manager)
{
  uint8_t *v1; // ecx
  int v2; // edx
  int v3; // eax

  v1 = &manager->unknown_000010[2068];
  v2 = 150;
  do
  {
    v3 = *(_DWORD *)v1;
    if ( *(_DWORD *)v1 )
    {
      if ( (v3 & 0x10000400) == 0 )
      {
        LOBYTE(v3) = v3 & 1;
        BYTE1(v3) |= 2u;
        *(_DWORD *)v1 = v3;
      }
    }
    v1 += 1828;
    --v2;
  }
  while ( v2 );
}
