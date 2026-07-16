/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_banner @ 0x441d40 */
/* selector: update_banner */

// Exact Windows `cRBanner::AI()`: updates one of the two fixed Banner actors embedded at `SubgameRuntime +0x359080`, toggles its inherited BOD visibility flag from the borrowed Player row position, wraps its phase, and writes the sinusoidal bob into `BodBase::position.y`. Android preserves the same four-field class tail after its smaller platform BodBase, while iOS preserves the authored owner in `SubGame.o`.
void __thiscall update_banner(Banner *banner)
{
  int32_t visibility_mode; // eax
  bool v2; // c0
  uint32_t list_flags; // eax
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  float v8; // [esp+0h] [ebp-8h]

  visibility_mode = banner->visibility_mode;
  if ( !visibility_mode )
  {
    v2 = banner->owner_player->body.transform.position.z < 40.0;
    goto LABEL_5;
  }
  if ( visibility_mode == 1 )
  {
    v2 = banner->bod.position.z - banner->owner_player->body.transform.position.z < 46.0;
LABEL_5:
    list_flags = banner->bod.bod.list_flags;
    if ( v2 )
      LOBYTE(list_flags) = list_flags | 0x20;
    else
      LOBYTE(list_flags) = list_flags & 0xDF;
    banner->bod.bod.list_flags = list_flags;
  }
  v4 = banner->phase_step + banner->phase;
  banner->phase = v4;
  if ( !(v6 | v7) )
    banner->phase = v4 - 1.0;
  v8 = banner->phase * 6.2831855;
  banner->bod.position.y = sine(v8) * 0.25999999;
}
