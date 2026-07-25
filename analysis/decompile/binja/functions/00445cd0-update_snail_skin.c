/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin @ 0x445cd0 */

00445cd7        struct Snail* snail_1 = snail
00445cdb        int32_t hotspot_index = 0
00445cdd        struct Vec3* hotspot_world_cursor = &snail->snail_hotspots_world
00445cf2        while (true)
00445cf2        struct TransformMatrix* hotspot_transform = &snail->snail_hotspot_body.transform
00445cfa        struct Vec3 vector
00445cfa        vector.x = (hotspot_world_cursor - 0xe4)->x
00445d01        vector.y = (hotspot_world_cursor - 0xe4)->y
00445d08        vector.z = (hotspot_world_cursor - 0xe4)->z
00445d0c        if (hotspot_index s>= 0xb)
00445d0e        hotspot_transform = &snail->snail_hotspot_source_body.transform
00445d1e        void matrix
00445d1e        __builtin_memcpy(&matrix, hotspot_transform, 0x40)
00445d24        multiply_vector_by_matrix(&vector, matrix)
00445d2d        float y = vector.y
00445d31        struct Vec3* hotspot_world_slot = hotspot_world_cursor
00445d33        hotspot_index += 1
00445d34        hotspot_world_cursor = &hotspot_world_cursor[1]
00445d3a        hotspot_world_slot->x = vector.x
00445d3c        float z = vector.z
00445d40        hotspot_world_slot->y = y
00445d43        hotspot_world_slot->z = z
00445d46        if (hotspot_index s>= 0x13)
00445d46        break
00445ce5        snail = snail_1
00445d4f        return
