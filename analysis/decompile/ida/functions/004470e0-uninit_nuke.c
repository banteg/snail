/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_nuke @ 0x4470e0 */
/* selector: uninit_nuke */

// Kills the 25 sprite slots owned by the collision ring-effect controller and clears its active state. Cross-port Android symbols match this helper to `cRNuke::UnInit()`.
void __thiscall sub_4470E0(int *this)
{
  int *v2; // esi
  int v3; // edi

  if ( *this == 1 )
  {
    v2 = this + 6;
    v3 = 25;
    do
    {
      kill_sprite(*v2++);
      --v3;
    }
    while ( v3 );
    *this = 0;
  }
}

