/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_damage_gauge_delta @ 0x4413f0 */
/* selector: apply_damage_gauge_delta */

// Applies one signed delta to the player contact-damage gauge controller at +0x3c4, clamps the live fill to [0,1], and triggers the matching sound or animation side effects. Windows collision callsites feed this helper with -0.5 health recovery, +0.04 garbage, +0.15 salt, +1.0 slug, and the smaller +0.02 `Wall2` ambient-hazard path.
void __thiscall sub_4413F0(float *this, float a2, char a3)
{
  double v4; // st7
  char v6; // c0

  if ( (*((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 || a3)
    && (*(_DWORD *)this != 2 || a2 <= 0.0 && (a2 >= 0.0 || *((_BYTE *)MEMORY[0x4DF904] + 4390752) != 1)) )
  {
    if ( *(this + 9) == 0.0 && a2 > 0.0 )
    {
      change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 1, 0.2);
      if ( play_voice_manager((int)unk_751498, 0, 1u, -1) )
      {
        *(this + 9) = *(this + 10);
      }
      else
      {
        if ( play_voice_manager((int)unk_751498, 9, 0, -1) )
          *(this + 9) = *(this + 10);
        if ( !*((_BYTE *)MEMORY[0x4DF904] + 4390996) )
        {
          dispatch_cutscene_animation((int)MEMORY[0x4DF904] + 4400896, 6, 1, -1);
          dispatch_cutscene_animation((int)MEMORY[0x4DF904] + 4400896, 1, 0, -1);
        }
      }
    }
    v4 = a2 + *(this + 7);
    *(this + 7) = v4;
    if ( v6 )
    {
      *(this + 7) = 0.0;
    }
    else
    {
      if ( v4 > 1.0 )
        v4 = 1.0;
      *(this + 7) = v4;
    }
  }
}

