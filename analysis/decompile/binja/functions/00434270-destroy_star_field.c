/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_star_field @ 0x434270 */

00434274        int32_t ebx = 0
00434276        int32_t count = manager->count
0043427b        if (count s<= 0)
004342ac        manager->state = 0
004342b5        return count
0043427e        int32_t edi = 0
0043429f        int32_t count_1
00434283        *(manager->entries + edi) = 0
00434291        kill_sprite(*(&manager->entries->sprite + edi))
00434296        count_1 = manager->count
00434299        ebx += 1
0043429a        edi += 0x2c
0043429f        do while (ebx s< count_1)
004342a1        manager->state = 0
004342ab        return count_1
