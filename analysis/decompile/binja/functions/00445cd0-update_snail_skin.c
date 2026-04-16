/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin @ 0x445cd0 */

00445cd7        struct PlayerPresentationController* presentation_1 = presentation
00445cdb        int32_t ebx = 0
00445cdd        struct Vec3 (* ebp)[0x13] = &presentation->snail_hotspots_world
00445cf2        while (true)
00445cf2        struct TransformMatrix* esi_1 = &presentation->snail_hotspot_source_matrix_b
00445cfa        int32_t var_c = *(ebp - 0xe4)
00445cfe        float edx_2 = *(ebp - 0xe0)
00445d05        float x = (*ebp)[-0x12].x
00445d0c        if (ebx s>= 0xb)
00445d0e        esi_1 = &presentation->snail_hotspot_source_matrix_a
00445d1e        void var_60
00445d1e        __builtin_memcpy(&var_60, esi_1, 0x40)
00445d24        multiply_vector_by_matrix(&var_c)
00445d31        struct Vec3 (* ecx_1)[0x13] = ebp
00445d33        ebx += 1
00445d34        ebp = &(*ebp)[1]
00445d3a        (ecx_1 - 0x17b0)->snail_hotspots_world[0].x = var_c
00445d40        (ecx_1 - 0x17b0)->snail_hotspots_world[0].y = edx_2
00445d43        (ecx_1 - 0x17b0)->snail_hotspots_world[0].z = x
00445d46        if (ebx s>= 0x13)
00445d46        break
00445ce5        presentation = presentation_1
00445d4f        return
