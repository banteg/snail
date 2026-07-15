/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_global_font3d_bods @ 0x449c20 */

00449c22        struct BodBase* esi = &g_font3d_bods
00449c27        int32_t i_1 = 0x80
00449c37        int32_t i
00449c2e        initialize_bod_base(esi)
00449c33        esi = &esi[1]
00449c36        i = i_1
00449c36        i_1 -= 1
00449c37        do while (i != 1)
00449c3b        return
