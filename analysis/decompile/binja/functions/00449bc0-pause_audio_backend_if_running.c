/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: pause_audio_backend_if_running @ 0x449bc0 */

00449bc3        char result = *(arg1 + 0x18)
00449bc8        if (result == 0)
00449bca        result = data_753cc0()
00449bd0        *(arg1 + 0x18) = 1
00449bd5        return result
