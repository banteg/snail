/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: stop_music_stream @ 0x4498d0 */

004498d6        if (backend->music_stream_active == 0)
004498d6        return
004498d8        uint32_t active_music_stream_sync_1 = g_active_music_stream_sync
004498df        if (active_music_stream_sync_1 != 0)
004498e8        g_bass_channel_remove_sync(g_active_music_stream, active_music_stream_sync_1)
004498ee        g_active_music_stream_sync = 0
004498ff        g_bass_channel_stop(g_active_music_stream)
0044990c        g_bass_stream_free(g_active_music_stream)
00449912        backend->music_stream_active = 0
00449916        return
