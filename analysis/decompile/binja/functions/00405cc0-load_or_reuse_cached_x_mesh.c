/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_or_reuse_cached_x_mesh @ 0x405cc0 */

00405cca        int32_t i = 0
00405cd1        if (loader->cached_x_mesh_count s> 0)
00405cd3        char (* ebx_1)[0x80] = &loader->cached_x_mesh_slots[0].name
00405ce2        if (strings_equal_case_insensitive_path(mesh_name, ebx_1) != 0)
00405d5a        return i
00405ce7        i += 1
00405ce8        ebx_1 = &(*ebx_1)[0xbc]
00405cf0        do while (i s< loader->cached_x_mesh_count)
00405d03        rstrcpy_checked_ascii(&loader->cached_x_mesh_slots[loader->cached_x_mesh_count].name, mesh_name)
00405d10        struct Object* object = add_object_to_list(&g_object_list)
00405d25        set_bod_object(&loader->cached_x_mesh_slots[loader->cached_x_mesh_count], object)
00405d3c        load_x_mesh(loader, mesh_name, loader->cached_x_mesh_slots[i].object, 1)
00405d45        int32_t eax_7 = loader->cached_x_mesh_count + 1
00405d46        loader->cached_x_mesh_count = eax_7
00405d51        return eax_7 - 1
