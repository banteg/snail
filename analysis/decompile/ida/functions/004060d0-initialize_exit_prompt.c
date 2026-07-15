/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_exit_prompt @ 0x4060d0 */
/* selector: initialize_exit_prompt */

// Exact void Windows `Exit::initialize_exit_prompt`: builds the shared Yes/No root prompt, including the `Do you really want to quit?` title and state-specific button layouts. Android and iOS retain the side-effect-only `cRExit::Init()`, and the sole Windows caller discards EAX.
void __thiscall initialize_exit_prompt(Exit *exit_controller)
{
  tColour *v2; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  tColour *v8; // eax
  tColour *v9; // eax
  tColour *v10; // eax
  tColour *v11; // eax
  tColour *v12; // eax
  tColour *v13; // eax
  tColour *v14; // eax
  tColour *v15; // eax
  tColour *v16; // eax
  float y; // [esp+0h] [ebp-144h]
  tColour *v18; // [esp+4h] [ebp-140h]
  tColour *v19; // [esp+4h] [ebp-140h]
  tColour *v20; // [esp+4h] [ebp-140h]
  tColour *v21; // [esp+4h] [ebp-140h]
  Color4f v22; // [esp+14h] [ebp-130h] BYREF
  Color4f color; // [esp+24h] [ebp-120h] BYREF
  Color4f v24; // [esp+34h] [ebp-110h] BYREF
  Color4f v25; // [esp+44h] [ebp-100h] BYREF
  Color4f v26; // [esp+54h] [ebp-F0h] BYREF
  Color4f v27; // [esp+64h] [ebp-E0h] BYREF
  Color4f v28; // [esp+74h] [ebp-D0h] BYREF
  Color4f v29; // [esp+84h] [ebp-C0h] BYREF
  Color4f v30; // [esp+94h] [ebp-B0h] BYREF
  Color4f v31; // [esp+A4h] [ebp-A0h] BYREF
  Color4f v32; // [esp+B4h] [ebp-90h] BYREF
  Color4f v33; // [esp+C4h] [ebp-80h] BYREF
  Color4f v34; // [esp+D4h] [ebp-70h] BYREF
  Color4f v35; // [esp+E4h] [ebp-60h] BYREF
  Color4f v36; // [esp+F4h] [ebp-50h] BYREF
  Color4f v37; // [esp+104h] [ebp-40h] BYREF
  Color4f v38; // [esp+114h] [ebp-30h] BYREF
  Color4f v39; // [esp+124h] [ebp-20h] BYREF
  Color4f v40; // [esp+134h] [ebp-10h] BYREF

  hide_all_borders((int *)&g_game_base->border_manager);
  switch ( exit_controller->state )
  {
    case 2:
    case 7:
      exit_controller->prompt_title = allocate_border(&g_game_base->border_manager);
      v8 = set_color_rgba((tColour *)&v31, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v8, 2, 0.0);
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v9 = set_color_rgba((tColour *)&v22, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, 330.0, v9, 2, -80.0);
      stack_widget_below(exit_controller->yes_button, exit_controller->prompt_title);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v20 = set_color_rgba((tColour *)&v24, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->no_button, 0x14u, aNo, 20, 0.0, 330.0, v20, 2, 80.0);
      goto LABEL_6;
    case 3:
      exit_controller->prompt_title = allocate_border(&g_game_base->border_manager);
      v10 = set_color_rgba((tColour *)&v26, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v10, 2, 0.0);
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v11 = set_color_rgba((tColour *)&v28, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, 330.0, v11, 2, -80.0);
      stack_widget_below(exit_controller->yes_button, exit_controller->prompt_title);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v12 = set_color_rgba((tColour *)&v30, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->no_button, 0x14u, aNo, 20, 0.0, 330.0, v12, 2, 80.0);
      stack_widget_below(exit_controller->no_button, exit_controller->prompt_title);
      break;
    case 4:
      exit_controller->prompt_title = allocate_border(&g_game_base->border_manager);
      v13 = set_color_rgba((tColour *)&v32, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v13, 2, 0.0);
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v14 = set_color_rgba((tColour *)&v34, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->yes_button, 0x40000014u, off_4A16C8, 20, 468.0, 373.0, v14, 2, -80.0);
      stack_widget_below(exit_controller->yes_button, exit_controller->prompt_title);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v15 = set_color_rgba((tColour *)&v36, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->no_button, 0x14u, aNo, 20, 568.0, 296.0, v15, 2, 80.0);
      stack_widget_below(exit_controller->no_button, exit_controller->prompt_title);
      break;
    case 5:
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v16 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->yes_button, 0x14u, off_4A16C8, 20, 473.0, 33.0, v16, 0, 0.0);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v21 = set_color_rgba((tColour *)&v40, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->no_button, 0x14u, aNo, 20, 566.0, 108.0, v21, 0, 0.0);
      break;
    case 9:
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      y = exit_controller->prompt_y - 54.0;
      initialize_frontend_widget(exit_controller->yes_button, 0x14u, off_4A16C8, 20, 0.0, y, v2, 2, 140.0);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v18 = set_color_rgba((tColour *)&v39, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        exit_controller->no_button,
        0x14u,
        aNo,
        20,
        0.0,
        exit_controller->prompt_y,
        v18,
        2,
        268.0);
      break;
    case 0xA:
      exit_controller->prompt_title = allocate_border(&g_game_base->border_manager);
      v3 = set_color_rgba((tColour *)&v25, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v3, 2, 0.0);
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v4 = set_color_rgba((tColour *)&v33, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        exit_controller->yes_button,
        0x40000014u,
        off_4A16C8,
        20,
        0.0,
        exit_controller->prompt_y,
        v4,
        2,
        -80.0);
      stack_widget_below(exit_controller->yes_button, exit_controller->prompt_title);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v19 = set_color_rgba((tColour *)&v27, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        exit_controller->no_button,
        0x14u,
        aNo,
        20,
        0.0,
        exit_controller->prompt_y,
        v19,
        2,
        80.0);
LABEL_6:
      stack_widget_below(exit_controller->no_button, exit_controller->prompt_title);
      break;
    case 0xB:
      exit_controller->prompt_title = allocate_border(&g_game_base->border_manager);
      v5 = set_color_rgba((tColour *)&v37, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(exit_controller->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v5, 2, 0.0);
      exit_controller->yes_button = allocate_border(&g_game_base->border_manager);
      v6 = set_color_rgba((tColour *)&v29, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        exit_controller->yes_button,
        0x40000014u,
        off_4A16C8,
        20,
        0.0,
        exit_controller->prompt_y,
        v6,
        2,
        -80.0);
      stack_widget_below(exit_controller->yes_button, exit_controller->prompt_title);
      exit_controller->no_button = allocate_border(&g_game_base->border_manager);
      v7 = set_color_rgba((tColour *)&v35, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        exit_controller->no_button,
        0x14u,
        aNo,
        20,
        0.0,
        exit_controller->prompt_y,
        v7,
        2,
        80.0);
      stack_widget_below(exit_controller->no_button, exit_controller->prompt_title);
      break;
    default:
      return;
  }
}
