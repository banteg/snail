/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_exit_prompt @ 0x4060d0 */
/* selector: initialize_exit_prompt */

// Builds the shared Yes/No exit prompt used by the front-end completion return flow, including the `Do you really want to quit?` title and the per-owner button layout variants. Cross-port Android and iOS symbols match this helper to `cRExit::Init()`.
float *__thiscall sub_4060D0(void *this)
{
  float *result; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  _DWORD *v10; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // eax
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  _DWORD *v17; // eax
  float v18; // [esp+0h] [ebp-144h]
  _DWORD *v19; // [esp+4h] [ebp-140h]
  _DWORD *v20; // [esp+4h] [ebp-140h]
  _DWORD *v21; // [esp+4h] [ebp-140h]
  _DWORD *v22; // [esp+4h] [ebp-140h]
  _DWORD v23[4]; // [esp+14h] [ebp-130h] BYREF
  _DWORD v24[4]; // [esp+24h] [ebp-120h] BYREF
  _DWORD v25[4]; // [esp+34h] [ebp-110h] BYREF
  _DWORD v26[4]; // [esp+44h] [ebp-100h] BYREF
  _DWORD v27[4]; // [esp+54h] [ebp-F0h] BYREF
  _DWORD v28[4]; // [esp+64h] [ebp-E0h] BYREF
  _DWORD v29[4]; // [esp+74h] [ebp-D0h] BYREF
  _DWORD v30[4]; // [esp+84h] [ebp-C0h] BYREF
  _DWORD v31[4]; // [esp+94h] [ebp-B0h] BYREF
  _DWORD v32[4]; // [esp+A4h] [ebp-A0h] BYREF
  _DWORD v33[4]; // [esp+B4h] [ebp-90h] BYREF
  _DWORD v34[4]; // [esp+C4h] [ebp-80h] BYREF
  _DWORD v35[4]; // [esp+D4h] [ebp-70h] BYREF
  _DWORD v36[4]; // [esp+E4h] [ebp-60h] BYREF
  _DWORD v37[4]; // [esp+F4h] [ebp-50h] BYREF
  _DWORD v38[4]; // [esp+104h] [ebp-40h] BYREF
  _DWORD v39[4]; // [esp+114h] [ebp-30h] BYREF
  _DWORD v40[4]; // [esp+124h] [ebp-20h] BYREF
  _DWORD v41[4]; // [esp+134h] [ebp-10h] BYREF

  hide_all_borders((int *)MEMORY[0x4DF904] + 723);
  result = (float *)(*(_DWORD *)this - 2);
  switch ( *(_DWORD *)this )
  {
    case 2:
    case 7:
      *((_DWORD *)this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v9 = set_color_rgba(v32, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 4), 4194306, aDoYouReallyWan, 20, 0, 200.0, (int)v9, 2, 0.0);
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v10 = set_color_rgba(v23, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *((_DWORD *)this + 5),
        1073741844,
        (char *)&off_4A16C8,
        20,
        0,
        330.0,
        (int)v10,
        2,
        -80.0);
      stack_widget_below(*((_DWORD *)this + 5), *((_DWORD *)this + 4));
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v21 = set_color_rgba(v25, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 0, 330.0, (int)v21, 2, 80.0);
      goto LABEL_6;
    case 3:
      *((_DWORD *)this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v11 = set_color_rgba(v27, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 4), 4194306, aDoYouReallyWan, 20, 0, 200.0, (int)v11, 2, 0.0);
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v12 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *((_DWORD *)this + 5),
        1073741844,
        (char *)&off_4A16C8,
        20,
        0,
        330.0,
        (int)v12,
        2,
        -80.0);
      stack_widget_below(*((_DWORD *)this + 5), *((_DWORD *)this + 4));
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v13 = set_color_rgba(v31, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 0, 330.0, (int)v13, 2, 80.0);
      result = stack_widget_below(*((_DWORD *)this + 6), *((_DWORD *)this + 4));
      break;
    case 4:
      *((_DWORD *)this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v14 = set_color_rgba(v33, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 4), 4194306, aDoYouReallyWan, 20, 0, 200.0, (int)v14, 2, 0.0);
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v15 = set_color_rgba(v35, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *((_DWORD *)this + 5),
        1073741844,
        (char *)&off_4A16C8,
        20,
        1139408896,
        373.0,
        (int)v15,
        2,
        -80.0);
      stack_widget_below(*((_DWORD *)this + 5), *((_DWORD *)this + 4));
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v16 = set_color_rgba(v37, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 1141768192, 296.0, (int)v16, 2, 80.0);
      result = stack_widget_below(*((_DWORD *)this + 6), *((_DWORD *)this + 4));
      break;
    case 5:
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v17 = set_color_rgba(v39, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 5), 20, (char *)&off_4A16C8, 20, 1139572736, 33.0, (int)v17, 0, 0.0);
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v22 = set_color_rgba(v41, 1065353216, 1065353216, 1065353216, 1065353216);
      result = initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 1141735424, 108.0, (int)v22, 0, 0.0);
      break;
    case 9:
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v3 = set_color_rgba(v24, 1065353216, 1065353216, 1065353216, 1065353216);
      v18 = *((float *)this + 3) - 54.0;
      initialize_frontend_widget(*((_DWORD *)this + 5), 20, (char *)&off_4A16C8, 20, 0, v18, (int)v3, 2, 140.0);
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v19 = set_color_rgba(v40, 1065353216, 1065353216, 1065353216, 1065353216);
      result = initialize_frontend_widget(
                 *((_DWORD *)this + 6),
                 20,
                 aNo,
                 20,
                 0,
                 *((float *)this + 3),
                 (int)v19,
                 2,
                 268.0);
      break;
    case 0xA:
      *((_DWORD *)this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v4 = set_color_rgba(v26, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 4), 4194306, aDoYouReallyWan, 20, 0, 200.0, (int)v4, 2, 0.0);
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v5 = set_color_rgba(v34, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *((_DWORD *)this + 5),
        1073741844,
        (char *)&off_4A16C8,
        20,
        0,
        *((float *)this + 3),
        (int)v5,
        2,
        -80.0);
      stack_widget_below(*((_DWORD *)this + 5), *((_DWORD *)this + 4));
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v20 = set_color_rgba(v28, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 0, *((float *)this + 3), (int)v20, 2, 80.0);
LABEL_6:
      result = stack_widget_below(*((_DWORD *)this + 6), *((_DWORD *)this + 4));
      break;
    case 0xB:
      *((_DWORD *)this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v6 = set_color_rgba(v38, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 4), 4194306, aDoYouReallyWan, 20, 0, 200.0, (int)v6, 2, 0.0);
      *((_DWORD *)this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v7 = set_color_rgba(v30, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *((_DWORD *)this + 5),
        1073741844,
        (char *)&off_4A16C8,
        20,
        0,
        *((float *)this + 3),
        (int)v7,
        2,
        -80.0);
      stack_widget_below(*((_DWORD *)this + 5), *((_DWORD *)this + 4));
      *((_DWORD *)this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v8 = set_color_rgba(v36, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*((_DWORD *)this + 6), 20, aNo, 20, 0, *((float *)this + 3), (int)v8, 2, 80.0);
      result = stack_widget_below(*((_DWORD *)this + 6), *((_DWORD *)this + 4));
      break;
    default:
      return result;
  }
  return result;
}

