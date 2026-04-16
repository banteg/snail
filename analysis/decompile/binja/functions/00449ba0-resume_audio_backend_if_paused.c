/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: resume_audio_backend_if_paused @ 0x449ba0 */

00449ba7        if (*(arg1 + 0x18) == 1)
00449ba9        data_751660()
00449baf        *(arg1 + 0x18) = 0
00449bb4        return
