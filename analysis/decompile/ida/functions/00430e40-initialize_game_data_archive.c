/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_data_archive @ 0x430e40 */
/* selector: initialize_game_data_archive */

// Windows RShellInit(): resets the global shell, tracked-allocation, key-repeat, sound, and input state; initializes the DAT index; allocates the shared RShell scratch and music workspaces; and samples the current cursor clip rectangle.
unsigned __int8 __cdecl initialize_game_data_archive()
{
  unsigned __int8 archive_ready; // al
  float *slot_axis_y_cursor; // eax
  Win32Rect clip_rect; // [esp+4h] [ebp-10h] BYREF

  g_archive_startup_flag = 0;
  g_tracked_allocation_total_bytes = 0;
  initialize_enemy_manager(&g_tracked_allocation_stack.depth);
  g_text_input_repeat_accumulator = 0.0;
  g_text_input_repeat_step = 0.0;
  g_text_input_last_repeat_code = 0;
  archive_ready = load_archive_index(FileName);
  if ( archive_ready )
  {
    reset_registered_sound_sample_count();
    g_archive_data_base = allocate_tracked_memory(0x400000, aScratchPad);
    g_music_memory_buffer = (char *)allocate_tracked_memory(409600, aMusicMemoryBuf);
    slot_axis_y_cursor = &g_input_controller_slot0.axis_y;
    do
    {
      *(slot_axis_y_cursor - 1) = 0.0;
      *slot_axis_y_cursor = 0.0;
      slot_axis_y_cursor[1] = 0.0;
      slot_axis_y_cursor[4] = 320.0;
      slot_axis_y_cursor[5] = 240.0;
      slot_axis_y_cursor[6] = 0.0;
      slot_axis_y_cursor += 14;
    }
    while ( (int)slot_axis_y_cursor < (int)g_input_controller_slots_end );
    ((void (__stdcall *)(Win32Rect *))GetClipCursor)(&clip_rect);
    return 1;
  }
  return archive_ready;
}
