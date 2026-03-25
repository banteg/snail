/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: arm_jetpack_gauge @ 0x43a980 */
/* selector: arm_jetpack_gauge */

// Arms the player jetpack countdown controller at +0x2750 from the pickup path: sets the active flag, zeros progress and wobble offsets, plays the jetpack start cue, and seeds the warning visuals.
int __thiscall sub_43A980(int this)
{
  int result; // eax

  result = 0;
  if ( !*(_DWORD *)(this + 12) )
  {
    *(_DWORD *)(this + 12) = 1;
    *(_DWORD *)this = 0;
    *(_DWORD *)(this + 28) = 0;
    *(_DWORD *)(this + 24) = 0;
    *(_DWORD *)(this + 20) = 0;
    set_snail_jetpack((_DWORD *)MEMORY[0x4DF904] + 1100224, 1);
    return initialize_jet_particles((char *)this);
  }
  return result;
}

