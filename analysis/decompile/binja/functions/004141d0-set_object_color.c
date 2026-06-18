/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_object_color @ 0x4141d0 */

004141e6        struct ColorBGRA8 out
004141e6        void color
004141e6        struct ColorBGRA8* result = pack_color_rgba_u8(&out, &color)
004141f6        if ((*(arg1 + 0x10) & 0x80000) == 0)
0041425a        return result
00414200        int32_t* eax = *(*(arg1 + 0xc0) + 8)
0041421a        int32_t var_4
0041421a        (*(*eax + 0x2c))(eax, 0, g_object_grouped_vertex_cursor * 0x18, &var_4, 0)
00414223        int32_t i = 0
00414227        if (*(arg1 + 0xc4) s> 0)
0041422a        int32_t ecx_7 = 0
00414230        int32_t edx_3
00414230        edx_3.b = out.b
00414230        edx_3:1.b = out.g
00414230        edx_3:2.b = out.r
00414230        edx_3:3.b = out.a
00414234        i += 1
00414235        *(ecx_7 + var_4 + 0xc) = edx_3
0041423f        ecx_7 += 0x18
00414244        do while (i s< *(arg1 + 0xc4))
0041424d        int32_t* eax_2 = *(*(arg1 + 0xc0) + 8)
00414253        return (*(*eax_2 + 0x30))(eax_2)
