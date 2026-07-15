/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: bind_texture_ref @ 0x414500 */

0041450c        if (texture == g_current_texture_ref)
0041450c        return
00414512        int32_t* eax = g_direct3d_renderer.device
00414518        int32_t d3d_texture_slots_1 = g_d3d_texture_slots
0041451e        g_current_texture_ref = texture
00414533        int32_t eax_1 = (*(*eax + 0xf4))(eax, 0, *(d3d_texture_slots_1 + (texture->slot_index << 2)))
00414543        g_texture_bind_call_count += 1
00414549        if (eax_1 != 0)
00414554        report_errorf("SetTexture Failed %s", &texture->name)
0041455d        return
00414563        int32_t* eax_3 = g_direct3d_renderer.device
00414568        int32_t ecx_2 = *eax_3
0041456a        if (((texture->flags).w:1.b & 0x10) != 0)
00414573        (*(ecx_2 + 0xfc))(eax_3, 0, 0xd, 1)
00414579        int32_t* eax_4 = g_direct3d_renderer.device
00414587        (*(*eax_4 + 0xfc))(eax_4, 0, 0xe, 1)
0041458e        return
00414596        (*(ecx_2 + 0xfc))(eax_3, 0, 0xd, 3)
0041459c        int32_t* eax_5 = g_direct3d_renderer.device
004145aa        (*(*eax_5 + 0xfc))(eax_5, 0, 0xe, 3)
004145b1        return
