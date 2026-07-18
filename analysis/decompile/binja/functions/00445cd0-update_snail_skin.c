/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin @ 0x445cd0 */

00445cd7        struct Snail* snail_1 = snail
00445cdb        int32_t ebx = 0
00445cdd        struct Vec3 (* ebp)[0x13] = &snail->snail_hotspots_world
00445cf2        while (true)
00445cf2        struct TransformMatrix* esi_1 = &snail->snail_hotspot_body.transform
00445cfa        struct Vec3 vector
00445cfa        vector.x = (*ebp)[-0x1f9].__offset(0x16cc).228[0].x
00445d01        vector.y = (*ebp)[-0x1f9].__offset(0x16cc).228[0].y
00445d08        vector.z = (*ebp)[-0x1f9].__offset(0x16cc).228[0].z
00445d0c        if (ebx s>= 0xb)
00445d0e        esi_1 = &snail->snail_hotspot_source_body.transform
00445d1e        void matrix
00445d1e        __builtin_memcpy(&matrix, esi_1, 0x40)
00445d24        multiply_vector_by_matrix(&vector, matrix)
00445d31        struct Vec3 (* ecx_1)[0x13] = ebp
00445d33        ebx += 1
00445d34        ebp = &(*ebp)[1]
00445d3a        (ecx_1 - 0x17b0)->snail_hotspots_world[0].x = vector.x
00445d40        (ecx_1 - 0x17b0)->snail_hotspots_world[0].y = vector.y
00445d43        (ecx_1 - 0x17b0)->snail_hotspots_world[0].z = vector.z
00445d46        if (ebx s>= 0x13)
00445d46        break
00445ce5        snail = snail_1
00445d4f        return
