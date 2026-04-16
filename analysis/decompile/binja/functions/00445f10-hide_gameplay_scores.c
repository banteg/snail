/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_gameplay_scores @ 0x445f10 */

00445f13        void* ecx = *(arg1 + 0x35bb8c)
00445f1b        if (ecx != 0)
00445f1d        hide_border_init(ecx)
00445f22        void* ecx_1 = *(arg1 + 0x35bb88)
00445f2b        if (ecx_1 == 0)
00445f32        return 
00445f2d        return hide_border_init(ecx_1) __tailcall
