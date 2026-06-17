/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_click_start @ 0x442170 */
/* selector: initialize_click_start */

// Initializes the `Click to Start` prompt owner for the subgame intro and hides that prompt immediately when the app-side replay-launch active bit is already set, so persistent replay starts skip the normal click gate.
void __thiscall initialize_click_start(ClickStartController *controller, ClickStartPlayer *player)
{
  Color4f *v3; // eax
  int32_t list_flags; // eax
  char *v5; // eax
  int v6; // ecx
  int v7; // ecx
  ClickStartPlayer *v8; // edx
  FrontendWidget *prompt; // ecx
  Color4f color; // [esp+8h] [ebp-10h] BYREF

  controller->prompt = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(&color, 1.0, 1.0, 1.0, 0.029999999);
  initialize_frontend_widget(controller->prompt, 0x400002u, aClickToStart, 20, 0.0, 200.0, v3, 2, 0.0);
  hide_border_init(controller->prompt->_pad_00);
  list_flags = controller->list_flags;
  controller->hide_prompt = 1;
  controller->player = player;
  if ( (list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v5 = (char *)MEMORY[0x4DF904] + 1452;
    v6 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v6 )
    {
      *(_DWORD *)(v6 + 8) = controller;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v5 + 8) + 12) = *(_DWORD *)v5;
      v7 = *(_DWORD *)(*(_DWORD *)v5 + 8);
      *(_DWORD *)v5 = v7;
      *(_DWORD *)(v7 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v5 = controller;
      controller->list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v5 + 12) = 0;
    }
    controller->list_flags |= 0x200u;
  }
  v8 = controller->player;
  controller->state = 2;
  v8->startup_track_index = 0;
  controller->render_arg_1c = 0;
  controller->render_arg_20 = 0.0;
  prompt = controller->prompt;
  if ( *((_BYTE *)MEMORY[0x4DF904] + 17198056) )
    hide_border_init(prompt);
  else
    unhide_border_init(prompt);
}

