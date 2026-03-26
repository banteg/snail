/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_weapon @ 0x445920 */
/* selector: set_snail_weapon */

// Maps the requested player weapon state onto the three visual-state channels rooted at +0x2984 and refreshes the active weapon presentation.
void __thiscall set_snail_weapon(PlayerPresentationController *presentation, int32_t movement_flags)
{
  char v3; // cl
  int32_t v4; // edi
  int32_t v5; // ebp
  int32_t selected_state; // eax
  int v7; // eax
  int32_t v8; // eax
  int v9; // eax
  int32_t v10; // eax
  int v11; // eax
  int32_t v12; // [esp+10h] [ebp-4h]

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
  selected_state = presentation->weapon_channels[0].selected_state;
  LOBYTE(movement_flags) = 1;
  if ( selected_state != v4 )
  {
    v7 = selected_state - 1;
    if ( v7 )
    {
      if ( v7 != 1 )
      {
LABEL_15:
        if ( v4 )
        {
          if ( v4 == 1 )
          {
            set_weapon_animation(presentation->weapon_channels, 1, movement_flags, 4);
            set_weapon_animation(presentation->weapon_channels, 0, 0, -1);
          }
          else if ( v4 == 2 )
          {
            set_weapon_animation(presentation->weapon_channels, 4, movement_flags, 4);
            set_weapon_animation(presentation->weapon_channels, 3, 0, -1);
          }
        }
        else
        {
          set_weapon_animation(presentation->weapon_channels, -1, 0, -1);
        }
        presentation->weapon_channels[0].selected_state = v4;
        v3 = 1;
        goto LABEL_22;
      }
      set_weapon_animation(presentation->weapon_channels, 4, 1, 8);
    }
    else
    {
      set_weapon_animation(presentation->weapon_channels, 1, 1, 8);
    }
    LOBYTE(movement_flags) = 0;
    goto LABEL_15;
  }
LABEL_22:
  v8 = presentation->weapon_channels[1].selected_state;
  LOBYTE(movement_flags) = 1;
  if ( v8 == v5 )
    goto LABEL_35;
  v9 = v8 - 1;
  if ( !v9 )
  {
    set_weapon_animation(&presentation->weapon_channels[1], 1, 1, 8);
    goto LABEL_27;
  }
  if ( v9 == 1 )
  {
    set_weapon_animation(&presentation->weapon_channels[1], 4, 1, 8);
LABEL_27:
    LOBYTE(movement_flags) = 0;
  }
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      set_weapon_animation(&presentation->weapon_channels[1], 1, movement_flags, 4);
      set_weapon_animation(&presentation->weapon_channels[1], 0, 0, -1);
    }
    else if ( v5 == 2 )
    {
      set_weapon_animation(&presentation->weapon_channels[1], 4, movement_flags, 4);
      set_weapon_animation(&presentation->weapon_channels[1], 3, 0, -1);
    }
  }
  else
  {
    set_weapon_animation(&presentation->weapon_channels[1], -1, 0, -1);
  }
  presentation->weapon_channels[1].selected_state = v5;
  v3 = 1;
LABEL_35:
  v10 = presentation->weapon_channels[2].selected_state;
  LOBYTE(movement_flags) = 1;
  if ( v10 == v12 )
  {
    if ( v3 )
      play_sound_effect(25);
    return;
  }
  v11 = v10 - 1;
  if ( !v11 )
  {
    set_weapon_animation(&presentation->weapon_channels[2], 1, 1, 8);
    goto LABEL_40;
  }
  if ( v11 == 2 )
  {
    set_weapon_animation(&presentation->weapon_channels[2], 4, 1, 8);
LABEL_40:
    LOBYTE(movement_flags) = 0;
  }
  if ( v12 )
  {
    if ( v12 == 1 )
    {
      set_weapon_animation(&presentation->weapon_channels[2], 1, movement_flags, 4);
      set_weapon_animation(&presentation->weapon_channels[2], 0, 0, -1);
      presentation->weapon_channels[2].selected_state = 1;
      play_sound_effect(25);
      return;
    }
    if ( v12 == 3 )
    {
      set_weapon_animation(&presentation->weapon_channels[2], 4, movement_flags, 4);
      set_weapon_animation(&presentation->weapon_channels[2], 3, 0, -1);
      presentation->weapon_channels[2].selected_state = 3;
      play_sound_effect(25);
      return;
    }
  }
  else
  {
    set_weapon_animation(&presentation->weapon_channels[2], -1, 0, -1);
  }
  presentation->weapon_channels[2].selected_state = v12;
  play_sound_effect(25);
}

