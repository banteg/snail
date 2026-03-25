/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: open_star_field @ 0x4342c0 */

004342dc        arg1[0xf] = allocate_tracked_memory(arg2 * 0x2c, "StarField")
004342df        arg1[0x10] = arg2
004342e2        void* result
004342e2        result.b = data_4df934
004342ec        if ((result.b & 4) == 0)
00434301        arg1[0xe] = 0
0043430a        return result
004342f0        arg1[0xe] = 1
004342fe        return initialize_star_field(arg1)
