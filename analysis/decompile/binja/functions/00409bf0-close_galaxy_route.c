/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: close_galaxy_route @ 0x409bf0 */

00409bf3        void* ecx = *(arg1 + 0x10f8c)
00409bf9        *(arg1 + 8) = 0
00409c00        *(arg1 + 0x10f80) = 0xffffffff
00409c0a        hide_border_init(ecx)
00409c15        hide_border_init(*(arg1 + 0x10f90))
00409c20        hide_border_init(*(arg1 + 0x10f94))
00409c2b        hide_border_init(*(arg1 + 0x10f98))
00409c36        hide_border_init(*(arg1 + 0x10f9c))
00409c47        return hide_border_init(*(arg1 + 0x10fa0))
