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
00430e73        uint8_t result = load_archive_index("SnailMail.dat")
00430e7d        if (result == 0)
00430e83        return result
00430e84        sub_432d40()
00430ea2        g_archive_data_base = allocate_tracked_memory(&__dos_header, "Scratch Pad")
00430eac        g_music_memory_buffer = allocate_tracked_memory(0x64000, "Music Memory Buffer")
00430eb4        int32_t* i = &g_input_slot0_axis_y
00430edc        while (i s< 0x5033b0)
00430ec3        i[-1] = 0
00430ec6        *i = 0
00430ec8        i[1] = 0
00430ecb        i[4] = 0x43a00000
00430ece        i[5] = 0x43700000
00430ed1        i[6] = 0
00430ed4        i = &i[0xe]
00430ee3        RECT rect
00430ee3        GetClipCursor(&rect)
00430ee9        BOOL eax_3
00430ee9        eax_3.b = 1
00430eef        return 1
