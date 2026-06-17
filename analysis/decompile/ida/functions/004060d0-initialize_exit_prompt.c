/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_exit_prompt @ 0x4060d0 */
/* selector: initialize_exit_prompt */

// Builds the shared Yes/No exit prompt used by the front-end completion return flow, including the `Do you really want to quit?` title and the per-owner button layout variants. Cross-port Android and iOS symbols match this helper to `cRExit::Init()`.
int __thiscall initialize_exit_prompt(CompletionPrompt *prompt)
{
  int result; // eax
  Color4f *v3; // eax
  Color4f *v4; // eax
  Color4f *v5; // eax
  Color4f *v6; // eax
  Color4f *v7; // eax
  Color4f *v8; // eax
  Color4f *v9; // eax
  Color4f *v10; // eax
  Color4f *v11; // eax
  Color4f *v12; // eax
  Color4f *v13; // eax
  Color4f *v14; // eax
  Color4f *v15; // eax
  Color4f *v16; // eax
  Color4f *v17; // eax
  float y; // [esp+0h] [ebp-144h]
  Color4f *v19; // [esp+4h] [ebp-140h]
  Color4f *v20; // [esp+4h] [ebp-140h]
  Color4f *v21; // [esp+4h] [ebp-140h]
  Color4f *v22; // [esp+4h] [ebp-140h]
  Color4f v23; // [esp+14h] [ebp-130h] BYREF
  Color4f color; // [esp+24h] [ebp-120h] BYREF
  Color4f v25; // [esp+34h] [ebp-110h] BYREF
  Color4f v26; // [esp+44h] [ebp-100h] BYREF
  Color4f v27; // [esp+54h] [ebp-F0h] BYREF
  Color4f v28; // [esp+64h] [ebp-E0h] BYREF
  Color4f v29; // [esp+74h] [ebp-D0h] BYREF
  Color4f v30; // [esp+84h] [ebp-C0h] BYREF
  Color4f v31; // [esp+94h] [ebp-B0h] BYREF
  Color4f v32; // [esp+A4h] [ebp-A0h] BYREF
  Color4f v33; // [esp+B4h] [ebp-90h] BYREF
  Color4f v34; // [esp+C4h] [ebp-80h] BYREF
  Color4f v35; // [esp+D4h] [ebp-70h] BYREF
  Color4f v36; // [esp+E4h] [ebp-60h] BYREF
  Color4f v37; // [esp+F4h] [ebp-50h] BYREF
  Color4f v38; // [esp+104h] [ebp-40h] BYREF
  Color4f v39; // [esp+114h] [ebp-30h] BYREF
  Color4f v40; // [esp+124h] [ebp-20h] BYREF
  Color4f v41; // [esp+134h] [ebp-10h] BYREF

  hide_all_borders((int *)MEMORY[0x4DF904] + 723);
  result = prompt->state - 2;
  switch ( prompt->state )
  {
    case 2:
    case 7:
      prompt->prompt_title = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v9 = set_color_rgba(&v32, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v9, 2, 0.0);
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v10 = set_color_rgba(&v23, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, 330.0, v10, 2, -80.0);
      stack_widget_below((int)prompt->yes_button, (int)prompt->prompt_title);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v21 = set_color_rgba(&v25, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 0.0, 330.0, v21, 2, 80.0);
      goto LABEL_6;
    case 3:
      prompt->prompt_title = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v11 = set_color_rgba(&v27, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v11, 2, 0.0);
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v12 = set_color_rgba(&v29, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, 330.0, v12, 2, -80.0);
      stack_widget_below((int)prompt->yes_button, (int)prompt->prompt_title);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v13 = set_color_rgba(&v31, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 0.0, 330.0, v13, 2, 80.0);
      result = (int)stack_widget_below((int)prompt->no_button, (int)prompt->prompt_title);
      break;
    case 4:
      prompt->prompt_title = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v14 = set_color_rgba(&v33, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v14, 2, 0.0);
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v15 = set_color_rgba(&v35, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x40000014u, off_4A16C8, 20, 468.0, 373.0, v15, 2, -80.0);
      stack_widget_below((int)prompt->yes_button, (int)prompt->prompt_title);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v16 = set_color_rgba(&v37, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 568.0, 296.0, v16, 2, 80.0);
      result = (int)stack_widget_below((int)prompt->no_button, (int)prompt->prompt_title);
      break;
    case 5:
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v17 = set_color_rgba(&v39, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x14u, off_4A16C8, 20, 473.0, 33.0, v17, 0, 0.0);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v22 = set_color_rgba(&v41, 1.0, 1.0, 1.0, 1.0);
      result = initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 566.0, 108.0, v22, 0, 0.0);
      break;
    case 9:
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v3 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      y = prompt->prompt_y - 54.0;
      initialize_frontend_widget(prompt->yes_button, 0x14u, off_4A16C8, 20, 0.0, y, v3, 2, 140.0);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v19 = set_color_rgba(&v40, 1.0, 1.0, 1.0, 1.0);
      result = initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 0.0, prompt->prompt_y, v19, 2, 268.0);
      break;
    case 0xA:
      prompt->prompt_title = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v4 = set_color_rgba(&v26, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v4, 2, 0.0);
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v5 = set_color_rgba(&v34, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, prompt->prompt_y, v5, 2, -80.0);
      stack_widget_below((int)prompt->yes_button, (int)prompt->prompt_title);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v20 = set_color_rgba(&v28, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 0.0, prompt->prompt_y, v20, 2, 80.0);
LABEL_6:
      result = (int)stack_widget_below((int)prompt->no_button, (int)prompt->prompt_title);
      break;
    case 0xB:
      prompt->prompt_title = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v6 = set_color_rgba(&v38, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->prompt_title, 0x400002u, aDoYouReallyWan, 20, 0.0, 200.0, v6, 2, 0.0);
      prompt->yes_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v7 = set_color_rgba(&v30, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->yes_button, 0x40000014u, off_4A16C8, 20, 0.0, prompt->prompt_y, v7, 2, -80.0);
      stack_widget_below((int)prompt->yes_button, (int)prompt->prompt_title);
      prompt->no_button = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v8 = set_color_rgba(&v36, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(prompt->no_button, 0x14u, aNo, 20, 0.0, prompt->prompt_y, v8, 2, 80.0);
      result = (int)stack_widget_below((int)prompt->no_button, (int)prompt->prompt_title);
      break;
    default:
      return result;
  }
  return result;
}

