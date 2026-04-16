/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_all_objects @ 0x42f9e0 */

0042f9e4        int32_t i = 0
0042f9e9        if (*arg1 s<= 0)
0042f9e9        return 
0042f9f0        int32_t edi_1 = 0
0042f9f4        int32_t eax_2 = i & 0x80000003
0042f9f4        bool cond:0_1 = eax_2 != 0
0042f9f9        if (eax_2 s< 0)
0042f9ff        cond:0_1 = ((eax_2 - 1) | 0xfffffffc) != 0xffffffff
0042fa00        if (not(cond:0_1))
0042fa07        update_loading_screen(0x503290)
0042fa0f        void* ecx_1 = arg1[2] + edi_1
0042fa16        if (*(ecx_1 + 0x2c) != 0)
0042fa18        calc_object_bounding_box(ecx_1)
0042fa23        sort_object_faces_by_texture_group(arg1[2] + edi_1)
0042fa30        calc_object_texture_groups(arg1[2] + edi_1)
0042fa35        void* eax_7 = arg1[2]
0042fa42        if (((*(eax_7 + edi_1 + 0x10)).w:1.b & 0x40) != 0)
0042fa44        calc_object_facequad_normals(eax_7 + edi_1)
0042fa4e        calc_object_edges(arg1[2] + edi_1)
0042fa59        build_object_texture_group_buffers(arg1[2] + edi_1)
0042fa63        i += 1
0042fa64        edi_1 += 0xdc
0042fa6c        do while (i s< *arg1)
0042fa71        return
