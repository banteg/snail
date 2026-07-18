/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_all_objects @ 0x42f9e0 */

0042f9e4        int32_t i = 0
0042f9e9        if (object_list->count s<= 0)
0042f9e9        return
0042f9f0        int32_t edi_1 = 0
0042f9f4        int32_t eax_2 = i & 0x80000003
0042f9f4        bool cond:0_1 = eax_2 != 0
0042f9f9        if (eax_2 s< 0)
0042f9ff        cond:0_1 = ((eax_2 - 1) | 0xfffffffc) != 0xffffffff
0042fa00        if (not(cond:0_1))
0042fa07        update_loading_screen(&g_loading_bar)
0042fa0f        struct Object* object = &object_list->objects->_pad_00[edi_1]
0042fa16        if (object->vertex_count != 0)
0042fa18        calc_object_bounding_box(object)
0042fa23        sort_object_faces_by_texture_group(&object_list->objects->_pad_00[edi_1])
0042fa30        calc_object_texture_groups(&object_list->objects->_pad_00[edi_1])
0042fa35        struct Object* objects = object_list->objects
0042fa42        if (((*(&objects->flags + edi_1)).w:1.b & 0x40) != 0)
0042fa44        calc_object_facequad_normals(&objects->_pad_00[edi_1])
0042fa4e        calc_object_edges(&object_list->objects->_pad_00[edi_1])
0042fa59        build_object_texture_group_buffers(&object_list->objects->_pad_00[edi_1])
0042fa63        i += 1
0042fa64        edi_1 += 0xdc
0042fa6c        do while (i s< object_list->count)
0042fa71        return
