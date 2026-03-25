/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_jetpack @ 0x445860 */
/* selector: set_snail_jetpack */

void __thiscall sub_445860(_DWORD *this, int a2)
{
  int v3; // ebx
  int v4; // eax
  char v5; // [esp+Ch] [ebp+4h]

  if ( a2 )
  {
    if ( a2 == 1 )
      v3 = 4;
    else
      v3 = a2;
  }
  else
  {
    v3 = 0;
  }
  v4 = *(this + 1209);
  v5 = 1;
  if ( v4 != v3 )
  {
    if ( v4 == 4 )
    {
      set_weapon_animation((int)(this + 1144), 1, 1, 8);
      v5 = 0;
      play_sound_effect(26);
    }
    if ( v3 )
    {
      if ( v3 == 4 )
      {
        set_weapon_animation((int)(this + 1144), 1, v5, 4);
        set_weapon_animation((int)(this + 1144), 0, 0, -1);
        play_sound_effect(16);
        *(this + 1209) = 4;
        return;
      }
    }
    else
    {
      set_weapon_animation((int)(this + 1144), -1, 0, -1);
    }
    *(this + 1209) = v3;
  }
}

