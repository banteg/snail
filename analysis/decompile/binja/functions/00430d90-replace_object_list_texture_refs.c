/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: replace_object_list_texture_refs @ 0x430d90 */

00430d96        int32_t result = 0
00430d9a        int32_t var_8 = 0
00430da0        if (*arg1 s> 0)
00430dad        int32_t result_1 = 0
00430e05        bool cond:0_1
00430db1        void* eax = result + arg1[2]
00430db9        if (*(eax + 0x2c) != 0)
00430dbe        int32_t i = 0
00430dc2        if (*(eax + 0x54) s> 0)
00430dc4        int32_t edx_1 = 0
00430dc6        int32_t ecx_3 = *(eax + 0x5c)
00430dd1        if (*(edx_1 + ecx_3 + 0xc) == arg3)
00430dd3        *(edx_1 + ecx_3 + 0xc) = arg2
00430dd8        i += 1
00430dd9        edx_1 += 0x30
00430dde        do while (i s< *(eax + 0x54))
00430de3        replace_object_group_texture_refs(eax, arg2, arg3)
00430df6        result = result_1 + 0xdc
00430dfb        cond:0_1 = var_8 + 1 s< *arg1
00430dfd        var_8 += 1
00430e01        result_1 = result
00430e05        do while (cond:0_1)
00430e0e        return result
