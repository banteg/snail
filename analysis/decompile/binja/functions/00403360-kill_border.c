/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_border @ 0x403360 */

0040336a        if (arg1 == 0)
0040336a        return 
0040336c        int32_t eax = *(arg1 + 0x1a0)
00403379        if (eax == 0 || (eax:1.b & 4) != 0)
00403379        return 
0040337b        eax.b &= 1
0040337d        eax:1.b |= 2
00403385        *(arg1 + 0x1a0) = eax
0040338b        if ((eax & 0x100000) == 0)
0040338b        return 
00403394        kill_border(*(arg1 + 0x718))
004033a2        kill_border(*(arg1 + 0x71c))
004033b0        kill_border(*(arg1 + 0x720))
004033b7        return
