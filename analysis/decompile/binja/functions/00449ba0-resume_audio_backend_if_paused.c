/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: resume_audio_backend_if_paused @ 0x449ba0 */

00449ba7        if (backend->is_paused == 1)
00449ba9        data_751660()
00449baf        backend->is_paused = 0
00449bb4        return
