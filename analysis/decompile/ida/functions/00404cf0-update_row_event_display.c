/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_row_event_display @ 0x404cf0 */
/* selector: update_row_event_display */

// Runs the gameplay row-event display state machine, including staged score payout, widget show or hide transitions, and the final handoff into `flush_row_event_display`.
void __fastcall update_row_event_display(RowEventDisplayController *controller)
{
  _DWORD *widget_b; // ecx
  double v3; // st7
  int32_t staged_parcel_count; // eax
  char *v5; // eax
  int v6; // ecx
  int32_t parcel_target_count; // eax
  int32_t v8; // ecx
  double v9; // st7
  int32_t bonus_enabled; // eax
  float *v11; // eax
  double v12; // st7
  _DWORD *widget_c; // ecx
  int32_t delivered_parcel_count; // ecx
  float v15; // [esp+8h] [ebp-3Ch]
  float v16; // [esp+Ch] [ebp-38h]
  float v17; // [esp+Ch] [ebp-38h]
  float v18; // [esp+10h] [ebp-34h]
  float v19; // [esp+10h] [ebp-34h]
  float v20; // [esp+18h] [ebp-2Ch]
  float v21; // [esp+1Ch] [ebp-28h]
  float v22; // [esp+24h] [ebp-20h]
  float v23; // [esp+28h] [ebp-1Ch]
  float v24; // [esp+30h] [ebp-14h]
  float v25; // [esp+34h] [ebp-10h]
  float v26; // [esp+3Ch] [ebp-8h]
  float v27; // [esp+40h] [ebp-4h]

  if ( controller->state )
  {
    widget_b = controller->widget_b;
    if ( *((_BYTE *)MEMORY[0x4DF904] + 476705) )
    {
      hide_border_init(widget_b);
      hide_border_init(controller->widget_a);
      hide_border_init((_DWORD *)controller->widget_d);
      hide_border_init((_DWORD *)controller->widget_c);
      hide_border_init((_DWORD *)controller->widget_e);
    }
    else
    {
      unhide_border_init(widget_b);
      unhide_border_init(controller->widget_a);
      unhide_border_init((_DWORD *)controller->widget_d);
      unhide_border_init((_DWORD *)controller->widget_e);
      switch ( controller->state )
      {
        case 0:
          return;
        case 1:
          v3 = controller->progress_step + controller->progress;
          controller->progress = v3;
          if ( v3 > 1.0 )
          {
            staged_parcel_count = controller->staged_parcel_count;
            if ( staged_parcel_count < controller->parcel_target_count )
            {
              controller->staged_parcel_count = staged_parcel_count + 1;
              v5 = spawn_track_parcel(
                     (int *)MEMORY[0x4DF904] + 119174,
                     (float *)MEMORY[0x4DF904] + 1101773,
                     (int)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]);
              v6 = *((_DWORD *)v5 + 21);
              *((_DWORD *)v5 + 14) = 6;
              *(_DWORD *)(v6 + 100) = 0;
              *(_DWORD *)(*((_DWORD *)v5 + 21) + 96) = 0;
            }
            parcel_target_count = controller->parcel_target_count;
            v8 = controller->staged_parcel_count;
            controller->progress = 0.0;
            if ( v8 == parcel_target_count )
            {
              if ( parcel_target_count )
              {
                controller->state = 2;
              }
              else
              {
                controller->state = 6;
                controller->progress = 0.0;
                controller->progress_step = 0.0083333338;
              }
            }
          }
          goto LABEL_27;
        case 3:
          unhide_border_init((_DWORD *)controller->widget_e);
          bonus_enabled = controller->bonus_enabled;
          controller->gate_18 = 0;
          controller->state = 4;
          if ( !bonus_enabled )
            goto LABEL_18;
          unhide_border_init((_DWORD *)controller->widget_c);
          if ( controller->parcel_target_count )
            goto LABEL_18;
          v11 = (float *)MEMORY[0x4DF904];
          if ( *((_DWORD *)MEMORY[0x4DF904] + 119190) == 1 )
          {
            add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), SUBGOLDY_SCORE_BONUS, controller->bonus_score);
            play_sound_effect(49);
LABEL_18:
            v11 = (float *)MEMORY[0x4DF904];
          }
          if ( controller->bonus_enabled )
          {
            v12 = controller->bonus_blink_step + controller->bonus_blink_progress;
            controller->bonus_blink_progress = v12;
            if ( v12 > 1.0 )
            {
              widget_c = controller->widget_c;
              controller->bonus_blink_progress = 0.0;
              if ( (widget_c[104] & 0x1000) != 0 )
                unhide_border_init(widget_c);
              else
                hide_border_init(widget_c);
            }
            v11 = (float *)MEMORY[0x4DF904];
          }
          if ( (*(_DWORD *)(*((_DWORD *)v11 + 163) + 60) & 0x4000) != 0 )
          {
            controller->state = 5;
            play_sound_effect(8);
LABEL_27:
            v11 = (float *)MEMORY[0x4DF904];
          }
          v26 = v11[96] * 6.0;
          v27 = v11[97] * 6.0;
          v22 = v11[92] + v11[92];
          v23 = v11[93] + v11[93];
          v16 = v11[88] * 7.3000002;
          v18 = v11[89] * 7.3000002;
          v20 = v16 + v11[100];
          v21 = v18 + v11[101];
          v24 = v20 + v22;
          v25 = v21 + v23;
          v15 = v11[91] + v11[91] + v11[87] * 7.3000002 + v11[99] + v11[95] * 6.0;
          controller->widget_world_x = v15;
          v17 = v24 + v26;
          controller->widget_world_y = v17;
          v19 = v25 + v27;
          controller->widget_world_z = v19;
          delivered_parcel_count = controller->delivered_parcel_count;
          if ( delivered_parcel_count >= 10 )
            *((_BYTE *)controller->widget_b + 716) = delivered_parcel_count / 10 + 48;
          else
            *((_BYTE *)controller->widget_b + 716) = 32;
          *((_BYTE *)controller->widget_b + 717) = controller->delivered_parcel_count % 10 + 48;
          break;
        case 4:
          goto LABEL_18;
        case 6:
          v9 = controller->progress_step + controller->progress;
          controller->progress = v9;
          if ( v9 > 1.0 )
            controller->state = 3;
          goto LABEL_27;
        default:
          goto LABEL_27;
      }
    }
  }
}
