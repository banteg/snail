/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: game_startup_and_main_loop @ 0x406dc0 */
/* selector: game_startup_and_main_loop */

int __stdcall game_startup_and_main_loop(int hInstance, int hPrevInstance, int lpCmdLine, int nShowCmd)
{
  int v4; // edi
  #95 *v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // esi
  double v10; // st7
  float v11; // ecx
  double v13; // st7
  char v14; // c0
  int v15; // esi
  int v16; // esi
  int v17; // eax
  double v18; // st7
  _DWORD Msg[7]; // [esp+10h] [ebp-1Ch] BYREF

  v4 = 0;
  if ( ((int (__stdcall *)(_DWORD, _DWORD, char *, _DWORD))FindWindowExA)(0, 0, szClass, 0) )
    return 0;
  if ( sub_44AFC0() < 2049 )
    abort_startup_with_3d_error();
  rebuild_game_archive_if_needed();
  load_config_file(aSnailmailCfg, &unk_4DF918);
  unk_4DF949 = std::codecvt_base::do_always_noconv(v6);
  MEMORY[0x4DFAD8] = hInstance;
  initialize_trigonometry_tables();
  if ( !initialize_game_data_archive() )
    return 0;
  snapshot_current_display_mode();
  initialize_mouse_authored_scale_from_clip_rect();
  probe_display_mode_count();
  read_current_display_resolution((uint8_t *)&unk_4DF858, (uint8_t *)&unk_4B775C);
  unk_4DF85C = 1142947840;
  unk_4B7760 = 1139802112;
  unk_4DF90C = 1;
  unk_4B7654 = 0;
  log_startup_timestamp();
  do
  {
    while ( ((int (__stdcall *)(_DWORD *, _DWORD, _DWORD, _DWORD, int))PeekMessageA)(Msg, 0, 0, 0, 1) )
    {
      if ( Msg[1] == 18 )
      {
        v4 = 1;
      }
      else
      {
        ((void (__stdcall *)(_DWORD *))TranslateMessage)(Msg);
        ((void (__stdcall *)(_DWORD *))DispatchMessageA)(Msg);
      }
    }
    if ( unk_4DF90C )
    {
      initialize_audio_subsystem();
      sub_4119C0(aSnailmail);
      noop_runtime_ai(v7);
      set_fullscreen_mode(v4, byte_4DF920[0]);
      sub_406D70();
      initialize_loading_screen(&flt_4DFAFC[36325]);
      v8 = ((int (*)(void))timeGetTime)() % 1000;
      if ( v8 > 0 )
      {
        v9 = v8;
        do
        {
          random_float_below(1.0);
          next_math_random_value();
          --v9;
        }
        while ( v9 );
      }
      construct_game_runtime();
      set_tracked_allocation_mark();
      if ( !initialize_game_assets_and_world((int)MEMORY[0x4DF904]) )
        v4 = 1;
      sub_412A00();
      initialize_game_last(MEMORY[0x4DF904]);
      unk_4DF90C = 0;
      unk_4B7759 = 0;
      destroy_loading_screen(&flt_4DFAFC[36325]);
      begin_frontend_fade_in((_DWORD *)MEMORY[0x4DF904] + 9);
      show_and_focus_game_window();
    }
    if ( unk_4B7759 )
    {
      sub_4134C0();
      if ( !*((_DWORD *)MEMORY[0x4DF904] + 347) )
        sub_413520();
      unk_4B7759 = 0;
    }
    do
      flt_4DFAFC[2] = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
    while ( flt_4DFAFC[0] + flt_4DFAFC[2] - flt_4DFAFC[1] < 0.0008333333333333334 );
    v10 = flt_4DFAFC[2] - flt_4DFAFC[1];
    v11 = flt_4DFAFC[2];
    flt_4DFAFC[1] = flt_4DFAFC[2];
    flt_4DFAFC[0] = v10 + flt_4DFAFC[0];
    if ( flt_4DFAFC[0] > 0.41666666 )
      flt_4DFAFC[0] = 0.41666666;
    unk_4B7758 = 0;
    flt_4B763C[0] = 0.0;
    while ( flt_4DFAFC[0] > 0.0 )
    {
      if ( unk_4B7758 || v4 )
        break;
      flt_4B763C[0] = flt_4B763C[0] + 1.0;
      flt_4DFAFC[0] = flt_4DFAFC[0] - 0.016666668;
      v13 = flt_4DFAFC[0];
      if ( v14 )
        v13 = -v13;
      if ( v13 >= 0.0000083333334 )
      {
        unk_4B7236 = flt_4DFAFC[0] <= 0.0;
      }
      else
      {
        flt_4DFAFC[0] = 0.0;
        unk_4B7236 = 1;
      }
      v15 = ((int (*)(void))GetActiveWindow)();
      if ( v15 == MEMORY[0x4DFAF0] )
      {
        if ( unk_753C70 == 1 )
          resume_audio_backend_if_paused(unk_753C58);
        if ( v15 == MEMORY[0x4DFAF0] )
          goto LABEL_42;
      }
      if ( unk_4B7654 )
      {
LABEL_42:
        v16 = 0;
        if ( *((int *)MEMORY[0x4DF904] + 15) > 0 )
        {
          while ( 1 )
          {
            update_keyboard_input();
            update_joystick_input();
            update_mouse(MEMORY[0x4DFAF0]);
            update_font_wave_state();
            v17 = run_frame_update((int)MEMORY[0x4DF904]);
            unk_4B7759 = 1;
            if ( v17 == 1 || v17 == 2 || v17 == 3 )
              break;
            if ( ++v16 >= *((_DWORD *)MEMORY[0x4DF904] + 15) )
              goto LABEL_49;
          }
          v4 = 1;
        }
      }
      else
      {
        ((void (__stdcall *)(_DWORD))ClipCursor)(0);
        unk_4B7236 = 1;
        unk_4B7759 = 1;
        if ( byte_4DF920[0] )
          sub_407490();
      }
LABEL_49:
      ;
    }
    unk_4B7758 = 0;
    v18 = unk_4B7768 * unk_4B7638 + flt_4B763C[0];
    unk_4B7768 = unk_4B7768 + 1.0;
    unk_4B7638 = v18 / unk_4B7768;
    noop_runtime_ai(LODWORD(v11));
  }
  while ( !unk_4DF864 && !v4 );
  stop_audio_backend();
  sub_407B00();
  save_high_scores_and_config(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], 1);
  save_high_scores_and_config(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], 2);
  save_high_scores_and_config(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], 4);
  save_high_scores_and_config(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], 8);
  save_high_scores_and_config(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], 16);
  noop_runtime_ai(MEMORY[0x4DF904]);
  free_tracked_allocations_to_mark();
  operator delete(MEMORY[0x4DF904]);
  uninitialize_game_data_archive();
  save_config_file(aSnailmailCfg, &unk_4DF918, 196);
  uninitialize_input_devices();
  unk_4DF90C = 1;
  unk_4DF864 = 0;
  restore_desktop_display_mode();
  return 0;
}

