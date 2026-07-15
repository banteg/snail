/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: activate_all_borders @ 0x403300 */

00403300        int32_t* eax = &manager->borders[0].flags
00403306        int32_t i_1 = 0x96
00403350        int32_t i
0040330b        int32_t flags = (eax - 0x824)->borders[0].flags
00403313        if ((flags & 0x80000000) == 0)
00403315        flags:1.b &= 0x7f
00403318        (eax - 0x824)->borders[0].flags = flags
0040331a        int32_t flags_1 = (eax - 0x824)->borders[0].flags
0040331c        eax = &eax[0x1c9]
00403327        i = i_1
00403327        i_1 -= 1
00403328        (eax - 0x824)->border_stack.entries[0x18].generation = flags_1 & 0x7fffffff
00403334        (eax - 0x824)->border_stack.entries[0x27].widget = (eax - 0x824)->border_stack.entries[0x26].widget
00403340        (eax - 0x824)->border_stack.entries[0x28].generation = (eax - 0x824)->border_stack.entries[0x26].widget
00403346        (eax - 0x824)->border_stack.entries[0x25].widget = nullptr
00403350        do while (i != 1)
00403352        return
