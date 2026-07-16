/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: pause_audio_backend_if_running @ 0x449bc0 */

00449bc3        uint8_t is_paused = backend->is_paused
00449bc8        if (is_paused == 0)
00449bca        is_paused = data_753cc0()
00449bd0        backend->is_paused = 1
00449bd5        return is_paused
