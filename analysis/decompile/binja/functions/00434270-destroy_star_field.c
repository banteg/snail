/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_star_field @ 0x434270 */

00434274        int32_t ebx = 0
00434276        int32_t eax = *(arg1 + 0x40)
0043427b        if (eax s<= 0)
004342ac        *(arg1 + 0x38) = 0
004342b5        return eax
0043427e        int32_t edi = 0
0043429f        int32_t eax_2
00434283        *(*(arg1 + 0x3c) + edi) = 0
00434291        kill_sprite(*(*(arg1 + 0x3c) + edi + 0x1c))
00434296        eax_2 = *(arg1 + 0x40)
00434299        ebx += 1
0043429a        edi += 0x2c
0043429f        do while (ebx s< eax_2)
004342a1        *(arg1 + 0x38) = 0
004342ab        return eax_2
