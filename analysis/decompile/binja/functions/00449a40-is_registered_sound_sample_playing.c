/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_registered_sound_sample_playing @ 0x449a40 */

00449a55        int32_t result
00449a55        result.b = data_753ca8(*((arg1 << 2) + &data_7537e0)) == 1
00449a58        return result
