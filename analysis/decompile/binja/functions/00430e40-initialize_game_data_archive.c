/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_data_archive @ 0x430e40 */

00430e4b        g_archive_startup_flag = 0
00430e51        g_tracked_allocation_total_bytes = 0
00430e57        initialize_enemy_manager(&g_tracked_allocation_stack)
00430e61        g_text_input_repeat_accumulator = 0f
00430e67        g_text_input_repeat_step = 0f
00430e6d        g_text_input_last_repeat_code = 0
00430e73        uint8_t archive_ready = load_archive_index("SnailMail.dat")
00430e7d        if (archive_ready == 0)
00430e83        return archive_ready
00430e84        reset_registered_sound_sample_count()
00430ea2        g_archive_data_base = allocate_tracked_memory(0x400000, "Scratch Pad")
00430eac        g_music_memory_buffer = allocate_tracked_memory(0x64000, "Music Memory Buffer")
00430eb4        float* slot_axis_y_cursor = &g_input_controller_slot0.axis_y
00430ec3        slot_axis_y_cursor[-1] = 0
00430ec6        *slot_axis_y_cursor = 0f
00430ec8        slot_axis_y_cursor[1] = 0
00430ecb        __builtin_memcpy(&slot_axis_y_cursor[4], "\x00\x00\xa0\x43\x00\x00\x70\x43", 8)
00430ed1        slot_axis_y_cursor[6] = 0
00430ed4        slot_axis_y_cursor = &slot_axis_y_cursor[0xe]
00430edc        do while (slot_axis_y_cursor s< 0x5033b0)
00430ee3        RECT clip_rect
00430ee3        GetClipCursor(&clip_rect)
00430ee9        BOOL eax_3
00430ee9        eax_3.b = 1
00430eef        return 1
