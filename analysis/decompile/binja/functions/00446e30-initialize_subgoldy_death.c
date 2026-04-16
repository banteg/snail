/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy_death @ 0x446e30 */

00446e36        int32_t result = *(*(arg1 + 0x408) + 0x40)
00446e3e        switch (result)
00446e4d        case 0
00446e4d        if (*(arg1 + 0x4340) s> 0)
00446e59        return initialize_subgoldy_resurrect(arg1, 0)
00446e56        return initialize_subgoldy_resurrect(arg1, 1)
00446e56        case 1, 4
00446e56        return initialize_subgoldy_resurrect(arg1, 1)
00446e59        case 7
00446e59        return initialize_subgoldy_resurrect(arg1, 0)
00446e5e        return result
