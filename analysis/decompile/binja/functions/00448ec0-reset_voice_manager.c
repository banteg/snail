/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_voice_manager @ 0x448ec0 */

00448ec0        manager->global_progress = 0f
00448eca        float* cooldown_cursor = &manager->sets[0].cooldown
00448ecd        int32_t i_1 = 0x10
00448edc        int32_t i
00448ed2        *cooldown_cursor = 0f
00448ed8        cooldown_cursor = &cooldown_cursor[6]
00448edb        i = i_1
00448edb        i_1 -= 1
00448edc        do while (i != 1)
00448ede        return
