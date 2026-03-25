/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_click_start @ 0x442290 */
/* selector: update_click_start */

// Advances the subgame `Click to Start` startup owner and its selected-replay handoff: state `2` branches between replay-driven startup and player confirm, recenters the authored mouse-pointer widgets, plays SFX `8` on the start transition, and then advances the prompt teardown lane.
void __thiscall update_click_start(int this)
{
  _DWORD *v2; // ecx
  _DWORD *v3; // eax
  _DWORD *v4; // ecx
  char *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    v2 = *(_DWORD **)(this + 132);
    if ( *(_BYTE *)(this + 168) )
      hide_border_init(v2);
    else
      unhide_border_init(v2);
    switch ( *(_DWORD *)(this + 128) )
    {
      case 2:
        *((_BYTE *)MEMORY[0x4DF904] + 324208) = 1;
        v3 = MEMORY[0x4DF904];
        if ( *((int *)MEMORY[0x4DF904] + 4299517) > 8 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 4299517) = 8;
          v3 = MEMORY[0x4DF904];
        }
        if ( *((_BYTE *)v3 + 17198056) )
        {
          if ( (*(_BYTE *)(v3[4299515] + 6 * v3[4299517] + 116) & 0x20) == 0 )
            return;
        }
        else if ( *(_BYTE *)(this + 168) || (*(_DWORD *)(v3[163] + 60) & 0x4000) == 0 )
        {
          return;
        }
        *(_DWORD *)(*(_DWORD *)(this + 152) + 772) = v3[4299517];
        *(_DWORD *)(this + 128) = 3;
        if ( !*((_BYTE *)MEMORY[0x4DF904] + 17198056) )
        {
          *((_BYTE *)MEMORY[0x4DF904] + 6 * *((_DWORD *)MEMORY[0x4DF904] + 4299517) + 17068444) |= 0x20u;
          *((_WORD *)MEMORY[0x4DF904] + 3 * *((_DWORD *)MEMORY[0x4DF904] + 4299517) + 8534222) &= ~1u;
          *((_DWORD *)MEMORY[0x4DF904] + 4267091) = *((_DWORD *)MEMORY[0x4DF904] + 4299517);
        }
        set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
        set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
        play_sound_effect(8);
        break;
      case 3:
        set_math_random_seed(*((_DWORD *)MEMORY[0x4DF904] + 4267108));
        v4 = *(_DWORD **)(this + 132);
        *(_DWORD *)(this + 128) = 4;
        *(_DWORD *)(this + 136) = 0;
        *(_DWORD *)(this + 140) = 1015580809;
        kill_border(v4);
        goto LABEL_17;
      case 4:
LABEL_17:
        *(float *)(this + 108) = *(float *)(this + 136) * 16.0 + *(float *)(this + 108);
        *(float *)(this + 136) = *(float *)(this + 140) + *(float *)(this + 136);
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        v6 = *(_DWORD *)(this + 4);
        if ( (v6 & 0x200) != 0 )
        {
          if ( (v6 & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
            *(_DWORD *)(this + 128) = 0;
          }
          else
          {
            v7 = *(_DWORD *)(this + 12);
            if ( v7 )
              *(_DWORD *)(v7 + 8) = *(_DWORD *)(this + 8);
            v8 = *(_DWORD *)(this + 8);
            if ( v8 )
              *(_DWORD *)(v8 + 12) = *(_DWORD *)(this + 12);
            else
              *((_DWORD *)v5 + 1) = *(_DWORD *)(this + 12);
            *(_DWORD *)(this + 12) = *((_DWORD *)v5 + 2);
            *((_DWORD *)v5 + 2) = this;
            v9 = *(_DWORD *)(this + 4);
            *(_DWORD *)(this + 128) = 0;
            BYTE1(v9) &= ~2u;
            *(_DWORD *)(this + 4) = v9;
          }
        }
        else
        {
          report_errorf(aListRemove);
          *(_DWORD *)(this + 128) = 0;
        }
        return;
      default:
        return;
    }
  }
}

