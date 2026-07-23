/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_or_reuse_cached_x_mesh @ 0x405cc0 */

00405cca        int32_t cached_slot_index = 0
00405cd1        if (loader->cached_x_mesh_count s> 0)
00405cd3        char* cached_name_cursor = &loader->cached_x_mesh_slots[0].name
00405ce2        if (strings_equal_case_insensitive_path(mesh_name, cached_name_cursor) != 0)
00405d5a        return cached_slot_index
00405ce7        cached_slot_index += 1
00405ce8        cached_name_cursor = &cached_name_cursor[0xbc]
00405cf0        do while (cached_slot_index s< loader->cached_x_mesh_count)
00405d03        rstrcpy_checked_ascii(&loader->cached_x_mesh_slots[loader->cached_x_mesh_count].name, mesh_name)
00405d10        struct Object* new_object = add_object_to_list(&g_object_list)
00405d25        set_bod_object(&loader->cached_x_mesh_slots[loader->cached_x_mesh_count], new_object)
00405d3c        load_x_mesh(loader, mesh_name, loader->cached_x_mesh_slots[cached_slot_index].object, 1)
00405d45        int32_t new_cached_x_mesh_count = loader->cached_x_mesh_count + 1
00405d46        loader->cached_x_mesh_count = new_cached_x_mesh_count
00405d51        return new_cached_x_mesh_count - 1
