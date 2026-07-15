/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_all_borders @ 0x4033c0 */

004033c0        int32_t* ecx = &manager->borders[0].flags
004033c6        int32_t i_1 = 0x96
004033e6        int32_t i
004033cb        int32_t flags = (ecx - 0x824)->borders[0].flags
004033d6        if (flags != 0 && (flags & 0x10000400) == 0)
004033d8        flags.b &= 1
004033da        flags:1.b |= 2
004033dd        (ecx - 0x824)->borders[0].flags = flags
004033df        ecx = &ecx[0x1c9]
004033e5        i = i_1
004033e5        i_1 -= 1
004033e6        do while (i != 1)
004033e8        return
