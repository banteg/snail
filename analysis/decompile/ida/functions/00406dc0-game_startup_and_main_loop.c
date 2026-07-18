/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: game_startup_and_main_loop @ 0x406dc0 */
/* selector: game_startup_and_main_loop */

// WinMain startup and fixed-step frame loop. It constructs and initializes the global cRGame root, drives its owned fade and render/update gates, then persists the embedded cRSubHighScore bank before releasing the root and process subsystems.
int __stdcall game_startup_and_main_loop(void *hInstance, void *hPrevInstance, char *lpCmdLine, int nShowCmd)
{
  FrontendWidget *v4; // ebp
  FrontendWidget *v5; // esi
  int v6; // edi
  ObjectIndexBufferResource *v8; // ecx
  int v9; // edx
  int v10; // esi
  double v11; // st7
  double v13; // st7
  char v14; // c0
  int v15; // esi
  int v16; // esi
  int v17; // eax
  double v18; // st7
  _DWORD Msg[7]; // [esp+10h] [ebp-1Ch] BYREF

  v6 = 0;
  if ( ((int (__stdcall *)(_DWORD, _DWORD, ObjectFaceQuad *, _DWORD))FindWindowExA)(0, 0, szClass, 0) )
    return 0;
  if ( query_directx_runtime_version() < 2049 )
    abort_startup_with_3d_error();
  rebuild_game_archive_if_needed(nullptr, v4, nullptr, v5);
  load_config_file(nullptr, aSnailmailCfg, &g_runtime_config);
  g_runtime_config.load_valid_flag = validate_config_tail_stub(v8);
  g_application_instance = hInstance;
  initialize_trigonometry_tables();
  if ( !initialize_game_data_archive() )
    return 0;
  snapshot_current_display_mode();
  initialize_mouse_authored_scale_from_clip_rect();
  probe_display_mode_count();
  read_current_display_resolution(&g_current_display_width, &g_current_display_height);
  g_authored_view_width = 1142947840;
  g_authored_view_height = 1139802112;
  g_game_initialization_pending = 1;
  g_window_deactivated = 0;
  log_startup_timestamp();
  do
  {
    while ( ((int (__stdcall *)(_DWORD *, _DWORD, _DWORD, _DWORD, int))PeekMessageA)(Msg, 0, 0, 0, 1) )
    {
      if ( Msg[1] == 18 )
      {
        v6 = 1;
      }
      else
      {
        TranslateMessage((const MSG *)Msg);
        ((void (__stdcall *)(_DWORD *))DispatchMessageA)(Msg);
      }
    }
    if ( g_game_initialization_pending )
    {
      initialize_audio_subsystem();
      initialize_game_window_and_input_wrapper((char *)window_name);
      noop_runtime_ai();
      set_fullscreen_mode(g_runtime_config.fullscreen_enabled);
      initialize_main_loop_display_state();
      initialize_loading_screen(&g_loading_bar);
      v9 = ((int (*)(void))timeGetTime)() % 1000;
      if ( v9 > 0 )
      {
        v10 = v9;
        do
        {
          random_float_below(1.0);
          next_math_random_value();
          --v10;
        }
        while ( v10 );
      }
      construct_game_runtime();
      set_tracked_allocation_mark();
      if ( !initialize_game_assets_and_world(g_game_base) )
        v6 = 1;
      load_registered_texture_refs();
      initialize_game_last((char *)g_game_base);
      g_game_initialization_pending = 0;
      g_frame_render_requested = 0;
      destroy_loading_screen(&g_loading_bar);
      begin_frontend_fade_in(&g_game_base->fade.state);
      show_and_focus_game_window();
    }
    if ( g_frame_render_requested )
    {
      render_game_frame_scene();
      if ( !g_game_base->render_skip_count )
        present_backbuffer();
      g_frame_render_requested = 0;
    }
    do
      g_current_frame_timestamp_seconds = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
    while ( g_frame_time_accumulator + g_current_frame_timestamp_seconds - g_previous_frame_timestamp_seconds < 0.0008333333333333334 );
    v11 = g_current_frame_timestamp_seconds - g_previous_frame_timestamp_seconds;
    g_previous_frame_timestamp_seconds = g_current_frame_timestamp_seconds;
    g_frame_time_accumulator = v11 + g_frame_time_accumulator;
    if ( g_frame_time_accumulator > 0.41666666 )
      g_frame_time_accumulator = 0.41666666;
    g_fixed_update_abort_requested = 0;
    g_current_frame_update_steps[0] = 0.0;
    while ( g_frame_time_accumulator > 0.0 )
    {
      if ( g_fixed_update_abort_requested || v6 )
        break;
      g_current_frame_update_steps[0] = g_current_frame_update_steps[0] + 1.0;
      g_frame_time_accumulator = g_frame_time_accumulator - 0.016666668;
      v13 = g_frame_time_accumulator;
      if ( v14 )
        v13 = -v13;
      if ( v13 >= 0.0000083333334 )
      {
        g_render_queue_active = g_frame_time_accumulator <= 0.0;
      }
      else
      {
        g_frame_time_accumulator = 0.0;
        g_render_queue_active = 1;
      }
      v15 = ((int (*)(void))GetActiveWindow)();
      if ( v15 == g_main_window )
      {
        if ( g_audio_backend.is_paused == 1 )
          resume_audio_backend_if_paused(&g_audio_backend);
        if ( v15 == g_main_window )
          goto LABEL_42;
      }
      if ( g_window_deactivated )
      {
LABEL_42:
        v16 = 0;
        if ( g_game_base->fixed_update_count > 0 )
        {
          while ( 1 )
          {
            update_keyboard_input();
            update_joystick_input();
            update_mouse(g_main_window);
            update_font_wave_state();
            v17 = run_frame_update(g_game_base);
            g_frame_render_requested = 1;
            if ( v17 == 1 || v17 == 2 || v17 == 3 )
              break;
            if ( ++v16 >= g_game_base->fixed_update_count )
              goto LABEL_49;
          }
          v6 = 1;
        }
      }
      else
      {
        ClipCursor(nullptr);
        g_render_queue_active = 1;
        g_frame_render_requested = 1;
        if ( g_runtime_config.fullscreen_enabled )
          minimize_game_window();
      }
LABEL_49:
      ;
    }
    g_fixed_update_abort_requested = 0;
    v18 = *(float *)&g_main_loop_frame_count * *(float *)&g_mean_update_steps_per_frame
        + g_current_frame_update_steps[0];
    *(float *)&g_main_loop_frame_count = *(float *)&g_main_loop_frame_count + 1.0;
    *(float *)&g_mean_update_steps_per_frame = v18 / *(float *)&g_main_loop_frame_count;
    noop_runtime_ai();
  }
  while ( !g_main_loop_exit_requested && !v6 );
  stop_audio_backend(&g_audio_backend);
  shutdown_bass_audio_window();
  save_high_scores_and_config(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)g_game_base),
    1u);
  save_high_scores_and_config(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)g_game_base),
    2u);
  save_high_scores_and_config(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)g_game_base),
    4u);
  save_high_scores_and_config(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)g_game_base),
    8u);
  save_high_scores_and_config(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)g_game_base),
    0x10u);
  noop_runtime_ai();
  free_tracked_allocations_to_mark();
  scalar_delete(g_game_base);
  uninitialize_game_data_archive();
  save_config_file(aSnailmailCfg, &g_runtime_config, 196);
  uninitialize_input_devices();
  g_game_initialization_pending = 1;
  g_main_loop_exit_requested = 0;
  restore_desktop_display_mode();
  return 0;
}
