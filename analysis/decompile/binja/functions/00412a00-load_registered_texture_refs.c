/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_texture_refs @ 0x412a00 */

00412a18        g_d3d_texture_slots = allocate_tracked_memory(g_texture_refs.count << 2, "DirectX Texture name list")
00412a22        int32_t i = 0
00412a29        g_estimated_texture_vram_bytes = 0
00412a2f        if (g_texture_refs.count s> 0)
00412a36        int32_t var_c_1 = arg1
00412a38        load_registered_texture_ref(i)
00412a45        i += 1
00412a48        do while (i s< g_texture_refs.count)
00412a4b        g_estimated_texture_vram_bytes
00412a6b        return 0
