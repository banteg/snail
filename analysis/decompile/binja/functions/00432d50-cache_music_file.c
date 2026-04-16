/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: cache_music_file @ 0x432d50 */

00432d58        if (data_53c7f8 == 0)
00432dbf        return ensure_music_stream_from_path(0x753c58, arg1, 1)
00432d5a        char* esi_1 = arg1
00432d64        char result = prepare_music_stream_reload_if_path_changed(0x753c58, esi_1)
00432d6b        if (result == 0)
00432dc5        return result
00432d7b        char* eax = load_file_bytes_from_archive_or_fs(esi_1, data_53c7e8, &arg1)
00432d8e        if (arg1 s>= 0x64000)
00432d95        report_errorf("Music buffer overflow Increase RSHELL_MUSIC_MEMORY_BUFFER_SIZE")
00432db2        return play_music_stream_from_bytes(0x753c58, esi_1, eax, arg1, 1)
