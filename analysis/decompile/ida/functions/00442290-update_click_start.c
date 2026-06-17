/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_click_start @ 0x442290 */
/* selector: update_click_start */

// Advances the subgame `Click to Start` startup owner and its selected-replay handoff: state `2` branches between replay-driven startup and player confirm, recenters the authored mouse-pointer widgets, plays SFX `8` on the start transition, and then advances the prompt teardown lane.
void __thiscall update_click_start(ClickStartController *controller)
{
  FrontendWidget *prompt; // ecx
  _DWORD *v3; // eax
  FrontendWidget *v4; // ecx
  char *v5; // ecx
  int32_t list_flags; // eax
  struct ClickStartController *list_next; // eax
  struct ClickStartController *list_prev; // eax
  int32_t v9; // eax

  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    prompt = controller->prompt;
    if ( controller->hide_prompt )
      hide_border_init(prompt);
    else
      unhide_border_init(prompt);
    switch ( controller->state )
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
        else if ( controller->hide_prompt || (*(_DWORD *)(v3[163] + 60) & 0x4000) == 0 )
        {
          return;
        }
        controller->player->startup_track_index = v3[4299517];
        controller->state = 3;
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
        v4 = controller->prompt;
        controller->state = 4;
        controller->teardown_progress = 0.0;
        controller->teardown_progress_step = 0.016666668;
        kill_border(v4);
        goto LABEL_17;
      case 4:
LABEL_17:
        controller->transform.position.y = controller->teardown_progress * 16.0 + controller->transform.position.y;
        controller->teardown_progress = controller->teardown_progress_step + controller->teardown_progress;
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        list_flags = controller->list_flags;
        if ( (list_flags & 0x200) != 0 )
        {
          if ( (list_flags & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
            controller->state = 0;
          }
          else
          {
            list_next = controller->list_next;
            if ( list_next )
              list_next->list_prev = controller->list_prev;
            list_prev = controller->list_prev;
            if ( list_prev )
              list_prev->list_next = controller->list_next;
            else
              *((_DWORD *)v5 + 1) = controller->list_next;
            controller->list_next = *((struct ClickStartController **)v5 + 2);
            *((_DWORD *)v5 + 2) = controller;
            v9 = controller->list_flags;
            controller->state = 0;
            BYTE1(v9) &= ~2u;
            controller->list_flags = v9;
          }
        }
        else
        {
          report_errorf(aListRemove);
          controller->state = 0;
        }
        return;
      default:
        return;
    }
  }
}

