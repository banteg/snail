/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: classify_archive_entry_extension @ 0x4050c0 */

004050c0        char* eax = arg1
004050c4        char* edx = arg2
004050c8        char i = *eax
004050cc        if (i != 0)
004050d1        while (i != 0x2e)
004050d3        eax = &eax[1]
004050d4        *edx = i
004050d6        edx = &edx[1]
004050d7        i = *eax
004050db        if (i == 0)
004050db        break
004050dd        *edx = 0
004050e4        if (*eax != 0)
004050e6        i = eax[1]
004050fa        if (i == 0x54 && eax[2] == 0x47 && eax[3] == 0x41)
00405101        return 1
00405110        if (i == 0x57 && eax[2] == 0x41 && eax[3] == 0x56)
00405117        return 2
00405127        if (i == 0x4d && eax[2] == 0x50 && eax[3] == 0x33)
0040512e        return 3
00405131        return 0
