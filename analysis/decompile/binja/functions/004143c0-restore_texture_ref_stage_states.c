/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: restore_texture_ref_stage_states @ 0x4143c0 */

004143c7        int32_t i = 0
004143cd        if (g_texture_refs s<= 0)
004143cd        return
004143d4        int32_t* edi_1 = &data_4b7798
004143df        struct Direct3DDevice8* device = renderer->device
004143ee        device->vtbl->SetTexture(device, 0, *(g_d3d_texture_slots + (i << 2)))
004143f4        int32_t* eax = g_direct3d_renderer.device
00414402        (*(*eax + 0xfc))(eax, 0, 0x10, 3)
00414408        int32_t* eax_1 = g_direct3d_renderer.device
00414416        (*(*eax_1 + 0xfc))(eax_1, 0, 0x11, 3)
00414422        if ((*edi_1 & 0x10000) != 0)
00414424        int32_t* eax_2 = g_direct3d_renderer.device
00414432        (*(*eax_2 + 0xfc))(eax_2, 0, 1, 4)
00414438        int32_t* eax_3 = g_direct3d_renderer.device
00414446        (*(*eax_3 + 0xfc))(eax_3, 0, 2, 2)
0041444c        int32_t* eax_4 = g_direct3d_renderer.device
0041445a        (*(*eax_4 + 0xfc))(eax_4, 0, 3, 0)
00414460        int32_t* eax_5 = g_direct3d_renderer.device
0041446e        (*(*eax_5 + 0xfc))(eax_5, 0, 4, 4)
00414474        int32_t* eax_6 = g_direct3d_renderer.device
00414482        (*(*eax_6 + 0xfc))(eax_6, 0, 5, 2)
00414488        int32_t* eax_7 = g_direct3d_renderer.device
00414496        (*(*eax_7 + 0xfc))(eax_7, 0, 6, 0)
004144a1        int32_t* eax_9 = g_direct3d_renderer.device
004144a6        int32_t ecx_5 = *eax_9
004144a8        int32_t var_10_2
004144a8        int32_t* eax_10
004144a8        int32_t edx_7
004144a8        if (((*edi_1).w:1.b & 0x10) == 0)
004144c9        (*(ecx_5 + 0xfc))(eax_9, 0, 0xd, 3)
004144cf        eax_10 = g_direct3d_renderer.device
004144d4        var_10_2 = 3
004144d6        edx_7 = *eax_10
004144b1        (*(ecx_5 + 0xfc))(eax_9, 0, 0xd, 1)
004144b7        eax_10 = g_direct3d_renderer.device
004144bc        var_10_2 = 1
004144be        edx_7 = *eax_10
004144dd        (*(edx_7 + 0xfc))(eax_10, 0, 0xe, var_10_2)
004144e8        i += 1
004144e9        edi_1 = &edi_1[0x29]
004144f1        do while (i s< g_texture_refs)
004144fa        return
