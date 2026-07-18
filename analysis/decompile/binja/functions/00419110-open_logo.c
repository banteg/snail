/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: open_logo @ 0x419110 */

0041911c        int32_t* esi = chkstk(0x4084) + 0x2403c
00419122        int32_t i_1 = 0x20
0041915c        int32_t i
00419135        set_bod_object(&esi[-9], add_object_to_list(&g_object_list))
00419142        load_object_definition("Objects/Font3D", *esi)
00419147        void* eax_3 = *esi
0041914c        esi = &esi[0x24]
00419158        i = i_1
00419158        i_1 -= 1
00419159        *(eax_3 + 0x10) |= 4
0041915c        do while (i != 1)
00419175        EnumeratedEntryName names[0x80]
00419175        enumerate_matching_archive_or_fs_entries("Intro", "*.tga", &__return_addr, &names)
0041917a        int32_t result = __return_addr
00419181        int32_t esi_1 = 0
00419185        if (result s> 0)
00419187        EnumeratedEntryName (* edi)[0x80] = &names
0041918e        EnumeratedEntryName (* var_c_4)[0x80] = edi
00419199        void texture_path
00419199        sprintf(&texture_path, "Intro/%s")
004191af        struct TextureRef* eax_4 = get_or_create_texture_ref(&g_texture_refs, &texture_path, nullptr, 0)
004191b4        enum TextureRefFlags flags = eax_4->flags
004191b6        edi = &(*edi)[1]
004191bc        flags:1.b |= 4
004191bf        esi_1 += 1
004191c0        eax_4->flags = flags
004191c2        result = __return_addr
004191c8        do while (esi_1 s< result)
004191d2        return result
