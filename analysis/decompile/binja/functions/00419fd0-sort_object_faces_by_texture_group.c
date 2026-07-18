/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sort_object_faces_by_texture_group @ 0x419fd0 */

00419fd5        struct Object* object_1 = object
00419fd9        int32_t ebp = 0
00419fdb        int32_t var_3c = 0
00419fdf        int32_t facequad_count = object_1->facequad_count
00419fe2        struct ObjectFaceQuad* facequads = object_1->facequads
00419fe7        struct ObjectFaceQuad* facequads_1 = facequads
00419feb        if (facequad_count s<= 0)
00419feb        return
00419ff7        int32_t i = ebp + 1
00419fff        int32_t texture_ref = facequads[ebp].texture_ref
0041a007        if (i s< facequad_count)
0041a015        void* edx_5 = &facequads[i]
0041a017        int32_t i_1 = i
0041a01b        void* eax_2 = &facequads[i]
0041a024        if (*(edx_5 + 0xc) == texture_ref)
0041a02c        if (i != i_1)
0041a044        ebp += 1
0041a045        void var_30
0041a045        __builtin_memcpy(&var_30, eax_2, 0x30)
0041a04e        void* edi_4 = eax_2
0041a050        eax_2 += 0x30
0041a053        __builtin_memcpy(edi_4, edx_5, 0x30)
0041a060        __builtin_memcpy(edx_5, &var_30, 0x30)
0041a06c        i_1 += 1
0041a070        object_1 = object
0041a074        var_3c += 1
0041a078        facequads = facequads_1
0041a02e        ebp += 1
0041a02f        eax_2 += 0x30
0041a033        i_1 += 1
0041a07f        i += 1
0041a080        edx_5 += 0x30
0041a085        do while (i s< object_1->facequad_count)
0041a087        facequad_count = object_1->facequad_count
0041a08a        ebp += 1
0041a08d        do while (ebp s< facequad_count)
0041a09a        return
