/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_font_text_queue @ 0x44a730 */

0044a730        int32_t result = data_777b24
0044a737        if (result != 0)
0044a747        void* esi_1 = result * 0x84 + &data_7544e8
0044a74e        int32_t ebx_1 = result
0044a77d        int32_t i
0044a750        result = *(esi_1 - 0x84)
0044a756        esi_1 -= 0x84
0044a766        if ((result & arg1 & 0xff000000) != 0)
0044a76b        if ((result.b & 1) == 0)
0044a774        result = draw_queued_font_quad_instance(esi_1)
0044a76d        result = draw_font_text_instance(esi_1)
0044a77c        i = ebx_1
0044a77c        ebx_1 -= 1
0044a77d        do while (i != 1)
0044a782        return result
