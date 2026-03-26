/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_weapon @ 0x445920 */
/* selector: set_snail_weapon */

// Maps the requested player weapon state onto the three visual-state channels rooted at +0x2984 and refreshes the active weapon presentation.
void __thiscall set_snail_weapon(PlayerPresentationController *presentation, int32_t movement_flags)
{
  char v3; // cl
  int32_t v4; // edi
  int32_t v5; // ebp
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp-4h]
  char movement_flagsa; // [esp+18h] [ebp+4h]
  char movement_flagsb; // [esp+18h] [ebp+4h]
  char movement_flagsc; // [esp+18h] [ebp+4h]

  v3 = 0;
  switch ( movement_flags )
  {
    case 1:
      v4 = 0;
      v5 = 0;
      v12 = 1;
      break;
    case 2:
      v4 = 1;
      v12 = 0;
      v5 = 1;
      break;
    case 4:
      v5 = 1;
      v4 = 1;
      v12 = 1;
      break;
    case 8:
      v4 = 0;
      v5 = 2;
      v12 = 0;
      break;
    case 16:
    case 144:
      v4 = 2;
      v12 = 0;
      v5 = 2;
      break;
    case 32:
    case 64:
    case 192:
      v4 = 0;
      v5 = 0;
      v12 = 3;
      break;
    default:
      v4 = movement_flags;
      v5 = movement_flags;
      break;
  }
  v6 = *(_DWORD *)&presentation->_pad_144[1548];
  movement_flagsa = 1;
  if ( v6 != v4 )
  {
    v7 = v6 - 1;
    if ( v7 )
    {
      if ( v7 != 1 )
      {
LABEL_15:
        if ( v4 )
        {
          if ( v4 == 1 )
          {
            set_weapon_animation((int)&presentation->_pad_144[1288], 1, movement_flagsa, 4);
            set_weapon_animation((int)&presentation->_pad_144[1288], 0, 0, -1);
          }
          else if ( v4 == 2 )
          {
            set_weapon_animation((int)&presentation->_pad_144[1288], 4, movement_flagsa, 4);
            set_weapon_animation((int)&presentation->_pad_144[1288], 3, 0, -1);
          }
        }
        else
        {
          set_weapon_animation((int)&presentation->_pad_144[1288], -1, 0, -1);
        }
        *(_DWORD *)&presentation->_pad_144[1548] = v4;
        v3 = 1;
        goto LABEL_22;
      }
      set_weapon_animation((int)&presentation->_pad_144[1288], 4, 1, 8);
    }
    else
    {
      set_weapon_animation((int)&presentation->_pad_144[1288], 1, 1, 8);
    }
    movement_flagsa = 0;
    goto LABEL_15;
  }
LABEL_22:
  v8 = *(_DWORD *)&presentation->_pad_144[2536];
  movement_flagsb = 1;
  if ( v8 == v5 )
    goto LABEL_35;
  v9 = v8 - 1;
  if ( !v9 )
  {
    set_weapon_animation((int)&presentation->_pad_144[2276], 1, 1, 8);
    goto LABEL_27;
  }
  if ( v9 == 1 )
  {
    set_weapon_animation((int)&presentation->_pad_144[2276], 4, 1, 8);
LABEL_27:
    movement_flagsb = 0;
  }
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      set_weapon_animation((int)&presentation->_pad_144[2276], 1, movement_flagsb, 4);
      set_weapon_animation((int)&presentation->_pad_144[2276], 0, 0, -1);
    }
    else if ( v5 == 2 )
    {
      set_weapon_animation((int)&presentation->_pad_144[2276], 4, movement_flagsb, 4);
      set_weapon_animation((int)&presentation->_pad_144[2276], 3, 0, -1);
    }
  }
  else
  {
    set_weapon_animation((int)&presentation->_pad_144[2276], -1, 0, -1);
  }
  *(_DWORD *)&presentation->_pad_144[2536] = v5;
  v3 = 1;
LABEL_35:
  v10 = *(_DWORD *)&presentation->_pad_144[3524];
  movement_flagsc = 1;
  if ( v10 == v12 )
  {
    if ( v3 )
      play_sound_effect(25);
    return;
  }
  v11 = v10 - 1;
  if ( !v11 )
  {
    set_weapon_animation((int)&presentation->_pad_144[3264], 1, 1, 8);
    goto LABEL_40;
  }
  if ( v11 == 2 )
  {
    set_weapon_animation((int)&presentation->_pad_144[3264], 4, 1, 8);
LABEL_40:
    movement_flagsc = 0;
  }
  if ( v12 )
  {
    if ( v12 == 1 )
    {
      set_weapon_animation((int)&presentation->_pad_144[3264], 1, movement_flagsc, 4);
      set_weapon_animation((int)&presentation->_pad_144[3264], 0, 0, -1);
      *(_DWORD *)&presentation->_pad_144[3524] = 1;
      play_sound_effect(25);
      return;
    }
    if ( v12 == 3 )
    {
      set_weapon_animation((int)&presentation->_pad_144[3264], 4, movement_flagsc, 4);
      set_weapon_animation((int)&presentation->_pad_144[3264], 3, 0, -1);
      *(_DWORD *)&presentation->_pad_144[3524] = 3;
      play_sound_effect(25);
      return;
    }
  }
  else
  {
    set_weapon_animation((int)&presentation->_pad_144[3264], -1, 0, -1);
  }
  *(_DWORD *)&presentation->_pad_144[3524] = v12;
  play_sound_effect(25);
}

