/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: cache_music_file @ 0x432d50 */

00432d58        if (g_archive_index_records == 0)
00432dbf        return ensure_music_stream_from_path(&g_audio_backend, path, 1)
00432d5a        char* path_1 = path
00432d64        char result = prepare_music_stream_reload_if_path_changed(&g_audio_backend, path_1)
00432d6b        if (result == 0)
00432dc5        return result
00432d7b        void* eax = load_file_bytes_from_archive_or_fs(path_1, g_music_memory_buffer, &path)
00432d8e        if (path s>= 0x64000)
00432d95        report_errorf("Music buffer overflow Increase RSHELL_MUSIC_MEMORY_BUFFER_SIZE")
00432db2        return play_music_stream_from_bytes(&g_audio_backend, path_1, eax, path, 1)
