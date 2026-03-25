/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_weapon @ 0x445920 */
/* selector: set_snail_weapon */

// Maps the requested player weapon state onto the three visual-state channels rooted at +0x2984 and refreshes the active weapon presentation.
void __thiscall sub_445920(_DWORD *this, int a2)
{
  char v3; // cl
  int v4; // edi
  int v5; // ebp
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp-4h]
  char v13; // [esp+18h] [ebp+4h]
  char v14; // [esp+18h] [ebp+4h]
  char v15; // [esp+18h] [ebp+4h]

  v3 = 0;
  switch ( a2 )
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
      v4 = a2;
      v5 = a2;
      break;
  }
  v6 = *(this + 468);
  v13 = 1;
  if ( v6 != v4 )
  {
    v7 = v6 - 1;
    if ( v7 )
    {
      if ( v7 != 1 )
      {
LABEL_14:
        if ( v4 )
        {
          if ( v4 == 1 )
          {
            set_weapon_animation((int)(this + 403), 1, v13, 4);
            set_weapon_animation((int)(this + 403), 0, 0, -1);
          }
          else if ( v4 == 2 )
          {
            set_weapon_animation((int)(this + 403), 4, v13, 4);
            set_weapon_animation((int)(this + 403), 3, 0, -1);
          }
        }
        else
        {
          set_weapon_animation((int)(this + 403), -1, 0, -1);
        }
        *(this + 468) = v4;
        v3 = 1;
        goto LABEL_21;
      }
      set_weapon_animation((int)(this + 403), 4, 1, 8);
    }
    else
    {
      set_weapon_animation((int)(this + 403), 1, 1, 8);
    }
    v13 = 0;
    goto LABEL_14;
  }
LABEL_21:
  v8 = *(this + 715);
  v14 = 1;
  if ( v8 == v5 )
    goto LABEL_34;
  v9 = v8 - 1;
  if ( !v9 )
  {
    set_weapon_animation((int)(this + 650), 1, 1, 8);
    goto LABEL_26;
  }
  if ( v9 == 1 )
  {
    set_weapon_animation((int)(this + 650), 4, 1, 8);
LABEL_26:
    v14 = 0;
  }
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      set_weapon_animation((int)(this + 650), 1, v14, 4);
      set_weapon_animation((int)(this + 650), 0, 0, -1);
    }
    else if ( v5 == 2 )
    {
      set_weapon_animation((int)(this + 650), 4, v14, 4);
      set_weapon_animation((int)(this + 650), 3, 0, -1);
    }
  }
  else
  {
    set_weapon_animation((int)(this + 650), -1, 0, -1);
  }
  *(this + 715) = v5;
  v3 = 1;
LABEL_34:
  v10 = *(this + 962);
  v15 = 1;
  if ( v10 == v12 )
  {
    if ( v3 )
      play_sound_effect(25);
    return;
  }
  v11 = v10 - 1;
  if ( !v11 )
  {
    set_weapon_animation((int)(this + 897), 1, 1, 8);
    goto LABEL_39;
  }
  if ( v11 == 2 )
  {
    set_weapon_animation((int)(this + 897), 4, 1, 8);
LABEL_39:
    v15 = 0;
  }
  if ( v12 )
  {
    if ( v12 == 1 )
    {
      set_weapon_animation((int)(this + 897), 1, v15, 4);
      set_weapon_animation((int)(this + 897), 0, 0, -1);
      *(this + 962) = 1;
      play_sound_effect(25);
      return;
    }
    if ( v12 == 3 )
    {
      set_weapon_animation((int)(this + 897), 4, v15, 4);
      set_weapon_animation((int)(this + 897), 3, 0, -1);
      *(this + 962) = 3;
      play_sound_effect(25);
      return;
    }
  }
  else
  {
    set_weapon_animation((int)(this + 897), -1, 0, -1);
  }
  *(this + 962) = v12;
  play_sound_effect(25);
}

