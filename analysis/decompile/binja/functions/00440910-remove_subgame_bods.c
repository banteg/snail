/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_subgame_bods @ 0x440910 */

00440910        struct Game* game_1 = game
00440919        void* __offset(Game, 0x3bfac8) edi = &game->__offset(0x3bfac8).d
0044091f        void* __offset(Game, 0x5ccad8) esi = &game->__offset(0x5ccad8).d
00440925        int32_t i_6 = 0xc80
004409b3        int32_t i
00440930        if ((((esi - 0x5ccad8)->__offset(0x5ccad0).d).w:1.b & 2) != 0)
00440937        void* ecx = data_4df904 + 0x5a8
0044093d        int16_t eax_3 = ((esi - 0x5ccad8)->__offset(0x5ccad0).d).w
00440943        if ((eax_3:1.b & 2) == 0)
0044094a        report_errorf("List remove")
00440956        if ((eax_3.b & 0x40) == 0)
00440967        void* eax_4 = (esi - 0x5ccad8)->__offset(0x5ccad8).d
0044096b        if (eax_4 != 0)
00440970        *(eax_4 + 8) = (esi - 0x5ccad8)->__offset(0x5ccad4).d
00440973        void* eax_5 = (esi - 0x5ccad8)->__offset(0x5ccad4).d
00440978        if (eax_5 == 0)
00440981        int32_t eax_6 = (esi - 0x5ccad8)->__offset(0x5ccad8).d
00440983        *(ecx + 4) = eax_6.b
00440983        *(ecx + 5) = eax_6:1.b
00440983        *(ecx + 6) = eax_6:2.b
00440983        *(ecx + 7) = eax_6:3.b
0044097c        *(eax_5 + 0xc) = (esi - 0x5ccad8)->__offset(0x5ccad8).d
00440986        int32_t edx_3
00440986        edx_3.b = *(ecx + 8)
00440986        edx_3:1.b = *(ecx + 9)
00440986        edx_3:2.b = *(ecx + 0xa)
00440986        edx_3:3.b = *(ecx + 0xb)
0044098c        (esi - 0x5ccad8)->__offset(0x5ccad8).d = edx_3
0044098e        *(ecx + 8) = (esi - 0xc).b
0044098e        *(ecx + 9) = (esi - 0xc):1.b
0044098e        *(ecx + 0xa) = (esi - 0xc):2.b
0044098e        *(ecx + 0xb) = (esi - 0xc):3.b
00440994        int32_t eax_8
00440994        eax_8:1.b = (esi - 0x5ccad8)->__offset(0x5ccad0).d:1.b & 0xfd
00440997        (esi - 0x5ccad8)->__offset(0x5ccad0).d = eax_8
0044095d        report_errorf("List remove NEXTBOD")
0044099a        int32_t j_1 = 8
004409aa        int32_t j
004409a1        destroy_sub_lazer_projectile(edi)
004409a6        edi += 0x54
004409a9        j = j_1
004409a9        j_1 -= 1
004409aa        do while (j != 1)
004409ac        esi += 0xf4
004409b2        i = i_6
004409b2        i_6 -= 1
004409b3        do while (i != 1)
004409c0        remove_track_render_cache_bods(&game->__offset(0x5c).d)
004409c5        void* __offset(Game, 0x35600c) esi_1 = &game->__offset(0x35600c).d
004409cb        int32_t i_7 = 8
00440a47        int32_t i_1
004409d2        int16_t eax_9 = ((esi_1 - 0x35600c)->__offset(0x356004).d).w
004409d8        if ((eax_9:1.b & 2) != 0)
004409e0        void* ecx_4 = data_4df904 + 0x5a8
004409e9        if ((eax_9:1.b & 2) == 0)
004409f0        report_errorf("List remove")
004409fc        if ((eax_9.b & 0x40) == 0)
00440a0d        void* eax_10 = (esi_1 - 0x35600c)->__offset(0x35600c).d
00440a11        if (eax_10 != 0)
00440a16        *(eax_10 + 8) = (esi_1 - 0x35600c)->__offset(0x356008).d
00440a19        void* eax_11 = (esi_1 - 0x35600c)->__offset(0x356008).d
00440a1e        if (eax_11 == 0)
00440a27        int32_t eax_12 = (esi_1 - 0x35600c)->__offset(0x35600c).d
00440a29        *(ecx_4 + 4) = eax_12.b
00440a29        *(ecx_4 + 5) = eax_12:1.b
00440a29        *(ecx_4 + 6) = eax_12:2.b
00440a29        *(ecx_4 + 7) = eax_12:3.b
00440a22        *(eax_11 + 0xc) = (esi_1 - 0x35600c)->__offset(0x35600c).d
00440a2c        int32_t edx_10
00440a2c        edx_10.b = *(ecx_4 + 8)
00440a2c        edx_10:1.b = *(ecx_4 + 9)
00440a2c        edx_10:2.b = *(ecx_4 + 0xa)
00440a2c        edx_10:3.b = *(ecx_4 + 0xb)
00440a32        (esi_1 - 0x35600c)->__offset(0x35600c).d = edx_10
00440a34        *(ecx_4 + 8) = (esi_1 - 0xc).b
00440a34        *(ecx_4 + 9) = (esi_1 - 0xc):1.b
00440a34        *(ecx_4 + 0xa) = (esi_1 - 0xc):2.b
00440a34        *(ecx_4 + 0xb) = (esi_1 - 0xc):3.b
00440a3a        int32_t eax_14
00440a3a        eax_14:1.b = (esi_1 - 0x35600c)->__offset(0x356004).d:1.b & 0xfd
00440a3d        (esi_1 - 0x35600c)->__offset(0x356004).d = eax_14
00440a03        report_errorf("List remove NEXTBOD")
00440a40        (esi_1 - 0x35600c)->__offset(0x356038).d = 0
00440a43        esi_1 += 0x74
00440a46        i_1 = i_7
00440a46        i_7 -= 1
00440a47        do while (i_1 != 1)
00440a52        if (((game->__offset(0x355db4).d).w:1.b & 2) != 0)
00440a60        void* edx_11 = data_4df904 + 0x5a8
00440a66        int16_t ecx_6 = (game->__offset(0x355db4).d).w
00440a6c        if ((ecx_6:1.b & 2) == 0)
00440a73        report_errorf("List remove")
00440a80        if ((ecx_6.b & 0x40) == 0)
00440a91        void* ecx_7 = game->__offset(0x355dbc).d
00440a96        if (ecx_7 != 0)
00440a98        int32_t esi_2 = game->__offset(0x355db8).d
00440a9b        *(ecx_7 + 8) = esi_2.b
00440a9b        *(ecx_7 + 9) = esi_2:1.b
00440a9b        *(ecx_7 + 0xa) = esi_2:2.b
00440a9b        *(ecx_7 + 0xb) = esi_2:3.b
00440a9e        void* ecx_8 = game->__offset(0x355db8).d
00440aa3        if (ecx_8 == 0)
00440ab0        *(edx_11 + 4) = game->__offset(0x355dbc).d
00440aa5        int32_t esi_3 = game->__offset(0x355dbc).d
00440aa8        *(ecx_8 + 0xc) = esi_3.b
00440aa8        *(ecx_8 + 0xd) = esi_3:1.b
00440aa8        *(ecx_8 + 0xe) = esi_3:2.b
00440aa8        *(ecx_8 + 0xf) = esi_3:3.b
00440ab6        game->__offset(0x355dbc).d = *(edx_11 + 8)
00440ab9        *(edx_11 + 8) = &game->__offset(0x355db0).d
00440abf        int32_t ecx_11
00440abf        ecx_11:1.b = game->__offset(0x355db4).d:1.b & 0xfd
00440ac2        game->__offset(0x355db4).d = ecx_11
00440a87        report_errorf("List remove NEXTBOD")
00440ac5        game->__offset(0x355e30).d = 0
00440ad4        if (((game->__offset(0x355e68).d).w:1.b & 2) != 0)
00440adc        int16_t ecx_12 = (game->__offset(0x355e68).d).w
00440ae8        void* edx_15 = data_4df904 + 0x5a8
00440af1        if ((ecx_12:1.b & 2) == 0)
00440af8        report_errorf("List remove")
00440b05        if ((ecx_12.b & 0x40) == 0)
00440b16        void* ecx_13 = game->__offset(0x355e70).d
00440b1b        if (ecx_13 != 0)
00440b1d        int32_t esi_4 = game->__offset(0x355e6c).d
00440b20        *(ecx_13 + 8) = esi_4.b
00440b20        *(ecx_13 + 9) = esi_4:1.b
00440b20        *(ecx_13 + 0xa) = esi_4:2.b
00440b20        *(ecx_13 + 0xb) = esi_4:3.b
00440b23        void* ecx_14 = game->__offset(0x355e6c).d
00440b28        if (ecx_14 == 0)
00440b35        *(edx_15 + 4) = game->__offset(0x355e70).d
00440b2a        int32_t esi_5 = game->__offset(0x355e70).d
00440b2d        *(ecx_14 + 0xc) = esi_5.b
00440b2d        *(ecx_14 + 0xd) = esi_5:1.b
00440b2d        *(ecx_14 + 0xe) = esi_5:2.b
00440b2d        *(ecx_14 + 0xf) = esi_5:3.b
00440b3b        game->__offset(0x355e70).d = *(edx_15 + 8)
00440b3e        *(edx_15 + 8) = &game->__offset(0x355e64).d
00440b44        int32_t ecx_17
00440b44        ecx_17:1.b = game->__offset(0x355e68).d:1.b & 0xfd
00440b47        game->__offset(0x355e68).d = ecx_17
00440b0c        report_errorf("List remove NEXTBOD")
00440b4a        game->__offset(0x355e9c).d = 0
00440b50        void* __offset(Game, 0x359150) esi_6 = &game->__offset(0x359150).d
00440b56        int32_t i_8 = 0x32
00440bd6        int32_t i_2
00440b61        if ((((esi_6 - 0x359150)->__offset(0x359148).d).w:1.b & 2) != 0)
00440b63        (esi_6 - 0x359150)->__offset(0x3591c8).d = 0
00440b6c        int16_t eax_20 = ((esi_6 - 0x359150)->__offset(0x359148).d).w
00440b72        void* ecx_18 = data_4df904 + 0x5a8
00440b78        if ((eax_20:1.b & 2) == 0)
00440b7f        report_errorf("List remove")
00440b8b        if ((eax_20.b & 0x40) == 0)
00440b9c        void* eax_21 = (esi_6 - 0x359150)->__offset(0x359150).d
00440ba0        if (eax_21 != 0)
00440ba5        *(eax_21 + 8) = (esi_6 - 0x359150)->__offset(0x35914c).d
00440ba8        void* eax_22 = (esi_6 - 0x359150)->__offset(0x35914c).d
00440bad        if (eax_22 == 0)
00440bb6        int32_t eax_23 = (esi_6 - 0x359150)->__offset(0x359150).d
00440bb8        *(ecx_18 + 4) = eax_23.b
00440bb8        *(ecx_18 + 5) = eax_23:1.b
00440bb8        *(ecx_18 + 6) = eax_23:2.b
00440bb8        *(ecx_18 + 7) = eax_23:3.b
00440bb1        *(eax_22 + 0xc) = (esi_6 - 0x359150)->__offset(0x359150).d
00440bbb        int32_t edx_23
00440bbb        edx_23.b = *(ecx_18 + 8)
00440bbb        edx_23:1.b = *(ecx_18 + 9)
00440bbb        edx_23:2.b = *(ecx_18 + 0xa)
00440bbb        edx_23:3.b = *(ecx_18 + 0xb)
00440bc1        (esi_6 - 0x359150)->__offset(0x359150).d = edx_23
00440bc3        *(ecx_18 + 8) = (esi_6 - 0xc).b
00440bc3        *(ecx_18 + 9) = (esi_6 - 0xc):1.b
00440bc3        *(ecx_18 + 0xa) = (esi_6 - 0xc):2.b
00440bc3        *(ecx_18 + 0xb) = (esi_6 - 0xc):3.b
00440bc9        int32_t eax_25
00440bc9        eax_25:1.b = (esi_6 - 0x359150)->__offset(0x359148).d:1.b & 0xfd
00440bcc        (esi_6 - 0x359150)->__offset(0x359148).d = eax_25
00440b92        report_errorf("List remove NEXTBOD")
00440bcf        esi_6 += 0xc4
00440bd5        i_2 = i_8
00440bd5        i_8 -= 1
00440bd6        do while (i_2 != 1)
00440bd8        void* __offset(Game, 0x3563ac) esi_7 = &game->__offset(0x3563ac).d
00440bde        int32_t i_9 = 8
00440c5e        int32_t i_3
00440be9        if ((((esi_7 - 0x3563ac)->__offset(0x3563a4).d).w:1.b & 2) != 0)
00440beb        (esi_7 - 0x3563ac)->__offset(0x356420).d = 0
00440bf4        int16_t eax_27 = ((esi_7 - 0x3563ac)->__offset(0x3563a4).d).w
00440bf7        void* ecx_20 = data_4df904 + 0x5a8
00440c00        if ((eax_27:1.b & 2) == 0)
00440c07        report_errorf("List remove")
00440c13        if ((eax_27.b & 0x40) == 0)
00440c24        void* eax_28 = (esi_7 - 0x3563ac)->__offset(0x3563ac).d
00440c28        if (eax_28 != 0)
00440c2d        *(eax_28 + 8) = (esi_7 - 0x3563ac)->__offset(0x3563a8).d
00440c30        void* eax_29 = (esi_7 - 0x3563ac)->__offset(0x3563a8).d
00440c35        if (eax_29 == 0)
00440c3e        int32_t eax_30 = (esi_7 - 0x3563ac)->__offset(0x3563ac).d
00440c40        *(ecx_20 + 4) = eax_30.b
00440c40        *(ecx_20 + 5) = eax_30:1.b
00440c40        *(ecx_20 + 6) = eax_30:2.b
00440c40        *(ecx_20 + 7) = eax_30:3.b
00440c39        *(eax_29 + 0xc) = (esi_7 - 0x3563ac)->__offset(0x3563ac).d
00440c43        int32_t edx_28
00440c43        edx_28.b = *(ecx_20 + 8)
00440c43        edx_28:1.b = *(ecx_20 + 9)
00440c43        edx_28:2.b = *(ecx_20 + 0xa)
00440c43        edx_28:3.b = *(ecx_20 + 0xb)
00440c49        (esi_7 - 0x3563ac)->__offset(0x3563ac).d = edx_28
00440c4b        *(ecx_20 + 8) = (esi_7 - 0xc).b
00440c4b        *(ecx_20 + 9) = (esi_7 - 0xc):1.b
00440c4b        *(ecx_20 + 0xa) = (esi_7 - 0xc):2.b
00440c4b        *(ecx_20 + 0xb) = (esi_7 - 0xc):3.b
00440c51        int32_t eax_32
00440c51        eax_32:1.b = (esi_7 - 0x3563ac)->__offset(0x3563a4).d:1.b & 0xfd
00440c54        (esi_7 - 0x3563ac)->__offset(0x3563a4).d = eax_32
00440c1a        report_errorf("List remove NEXTBOD")
00440c57        esi_7 += 0xec
00440c5d        i_3 = i_9
00440c5d        i_9 -= 1
00440c5e        do while (i_3 != 1)
00440c60        void* __offset(Game, 0x35b798) esi_8 = &game->__offset(0x35b798).d
00440c66        int32_t i_10 = 2
00440ce3        int32_t i_4
00440c6e        if ((esi_8 - 0x35b798)->__offset(0x35b80c).d != 0)
00440c76        int16_t eax_33 = ((esi_8 - 0x35b798)->__offset(0x35b790).d).w
00440c79        void* ecx_22 = data_4df904 + 0x5a8
00440c82        if ((eax_33:1.b & 2) == 0)
00440c89        report_errorf("List remove")
00440c95        if ((eax_33.b & 0x40) == 0)
00440ca6        void* eax_34 = (esi_8 - 0x35b798)->__offset(0x35b798).d
00440caa        if (eax_34 != 0)
00440caf        *(eax_34 + 8) = (esi_8 - 0x35b798)->__offset(0x35b794).d
00440cb2        void* eax_35 = (esi_8 - 0x35b798)->__offset(0x35b794).d
00440cb7        if (eax_35 == 0)
00440cc0        int32_t eax_36 = (esi_8 - 0x35b798)->__offset(0x35b798).d
00440cc2        *(ecx_22 + 4) = eax_36.b
00440cc2        *(ecx_22 + 5) = eax_36:1.b
00440cc2        *(ecx_22 + 6) = eax_36:2.b
00440cc2        *(ecx_22 + 7) = eax_36:3.b
00440cbb        *(eax_35 + 0xc) = (esi_8 - 0x35b798)->__offset(0x35b798).d
00440cc5        int32_t edx_33
00440cc5        edx_33.b = *(ecx_22 + 8)
00440cc5        edx_33:1.b = *(ecx_22 + 9)
00440cc5        edx_33:2.b = *(ecx_22 + 0xa)
00440cc5        edx_33:3.b = *(ecx_22 + 0xb)
00440ccb        (esi_8 - 0x35b798)->__offset(0x35b798).d = edx_33
00440ccd        *(ecx_22 + 8) = (esi_8 - 0xc).b
00440ccd        *(ecx_22 + 9) = (esi_8 - 0xc):1.b
00440ccd        *(ecx_22 + 0xa) = (esi_8 - 0xc):2.b
00440ccd        *(ecx_22 + 0xb) = (esi_8 - 0xc):3.b
00440cd3        int32_t eax_38
00440cd3        eax_38:1.b = (esi_8 - 0x35b798)->__offset(0x35b790).d:1.b & 0xfd
00440cd6        (esi_8 - 0x35b798)->__offset(0x35b790).d = eax_38
00440c9c        report_errorf("List remove NEXTBOD")
00440cd9        (esi_8 - 0x35b798)->__offset(0x35b80c).d = 0
00440cdc        esi_8 += 0x1f8
00440ce2        i_4 = i_10
00440ce2        i_10 -= 1
00440ce3        do while (i_4 != 1)
00440cee        if (((game->__offset(0x3bb768).d).w:1.b & 2) != 0)
00440cfa        int16_t eax_40 = (game->__offset(0x3bb768).d).w
00440d06        void* ecx_24 = data_4df904 + 0x5a8
00440d0f        if ((eax_40:1.b & 2) == 0)
00440d16        report_errorf("List remove")
00440d22        if ((eax_40.b & 0x40) == 0)
00440d33        void* eax_41 = game->__offset(0x3bb770).d
00440d38        if (eax_41 != 0)
00440d3d        *(eax_41 + 8) = game->__offset(0x3bb76c).d
00440d40        void* eax_42 = game->__offset(0x3bb76c).d
00440d45        if (eax_42 == 0)
00440d4f        int32_t eax_43 = game->__offset(0x3bb770).d
00440d52        *(ecx_24 + 4) = eax_43.b
00440d52        *(ecx_24 + 5) = eax_43:1.b
00440d52        *(ecx_24 + 6) = eax_43:2.b
00440d52        *(ecx_24 + 7) = eax_43:3.b
00440d4a        *(eax_42 + 0xc) = game->__offset(0x3bb770).d
00440d55        int32_t edx_36
00440d55        edx_36.b = *(ecx_24 + 8)
00440d55        edx_36:1.b = *(ecx_24 + 9)
00440d55        edx_36:2.b = *(ecx_24 + 0xa)
00440d55        edx_36:3.b = *(ecx_24 + 0xb)
00440d58        game->__offset(0x3bb770).d = edx_36
00440d5b        *(ecx_24 + 8) = (&game->__offset(0x3bb764).d).b
00440d5b        *(ecx_24 + 9) = (&game->__offset(0x3bb764).d):1.b
00440d5b        *(ecx_24 + 0xa) = (&game->__offset(0x3bb764).d):2.b
00440d5b        *(ecx_24 + 0xb) = (&game->__offset(0x3bb764).d):3.b
00440d61        int32_t eax_44
00440d61        eax_44:1.b = game->__offset(0x3bb768).d:1.b & 0xfd
00440d64        game->__offset(0x3bb768).d = eax_44
00440d29        report_errorf("List remove NEXTBOD")
00440d73        void* edx_37 = data_4df904 + 0x5a8
00440d79        int16_t ecx_26 = (game->__offset(0x3be0ec).d).w
00440d7f        if ((ecx_26:1.b & 2) == 0)
00440d86        report_errorf("List remove")
00440d93        if ((ecx_26.b & 0x40) == 0)
00440da4        void* ecx_27 = game->__offset(0x3be0f4).d
00440da9        if (ecx_27 != 0)
00440dab        int32_t edi_1 = game->__offset(0x3be0f0).d
00440dae        *(ecx_27 + 8) = edi_1.b
00440dae        *(ecx_27 + 9) = edi_1:1.b
00440dae        *(ecx_27 + 0xa) = edi_1:2.b
00440dae        *(ecx_27 + 0xb) = edi_1:3.b
00440db1        void* ecx_28 = game->__offset(0x3be0f0).d
00440db6        if (ecx_28 == 0)
00440dc3        *(edx_37 + 4) = game->__offset(0x3be0f4).d
00440db8        int32_t edi_2 = game->__offset(0x3be0f4).d
00440dbb        *(ecx_28 + 0xc) = edi_2.b
00440dbb        *(ecx_28 + 0xd) = edi_2:1.b
00440dbb        *(ecx_28 + 0xe) = edi_2:2.b
00440dbb        *(ecx_28 + 0xf) = edi_2:3.b
00440dc9        game->__offset(0x3be0f4).d = *(edx_37 + 8)
00440dcc        *(edx_37 + 8) = &game->__offset(0x3be0e8).d
00440dd2        int32_t ecx_31
00440dd2        ecx_31:1.b = game->__offset(0x3be0ec).d:1.b & 0xfd
00440dd5        game->__offset(0x3be0ec).d = ecx_31
00440d9a        report_errorf("List remove NEXTBOD")
00440dde        int16_t ecx_32 = (game->__offset(0x3bf2cc).d).w
00440dea        void* edx_39 = data_4df904 + 0x5a8
00440df3        if ((ecx_32:1.b & 2) == 0)
00440dfa        report_errorf("List remove")
00440e07        if ((ecx_32.b & 0x40) == 0)
00440e18        void* ecx_33 = game->__offset(0x3bf2d4).d
00440e1d        if (ecx_33 != 0)
00440e1f        int32_t edi_3 = game->__offset(0x3bf2d0).d
00440e22        *(ecx_33 + 8) = edi_3.b
00440e22        *(ecx_33 + 9) = edi_3:1.b
00440e22        *(ecx_33 + 0xa) = edi_3:2.b
00440e22        *(ecx_33 + 0xb) = edi_3:3.b
00440e25        void* ecx_34 = game->__offset(0x3bf2d0).d
00440e2a        if (ecx_34 == 0)
00440e37        *(edx_39 + 4) = game->__offset(0x3bf2d4).d
00440e2c        int32_t edi_4 = game->__offset(0x3bf2d4).d
00440e2f        *(ecx_34 + 0xc) = edi_4.b
00440e2f        *(ecx_34 + 0xd) = edi_4:1.b
00440e2f        *(ecx_34 + 0xe) = edi_4:2.b
00440e2f        *(ecx_34 + 0xf) = edi_4:3.b
00440e3d        game->__offset(0x3bf2d4).d = *(edx_39 + 8)
00440e40        *(edx_39 + 8) = &game->__offset(0x3bf2c8).d
00440e46        int32_t ecx_37
00440e46        ecx_37:1.b = game->__offset(0x3bf2cc).d:1.b & 0xfd
00440e49        game->__offset(0x3bf2cc).d = ecx_37
00440e0e        report_errorf("List remove NEXTBOD")
00440e52        int16_t ecx_38 = (game->__offset(0x3be738).d).w
00440e5e        void* edx_41 = data_4df904 + 0x5a8
00440e67        if ((ecx_38:1.b & 2) == 0)
00440e6e        report_errorf("List remove")
00440e7b        if ((ecx_38.b & 0x40) == 0)
00440e8c        void* ecx_39 = game->__offset(0x3be740).d
00440e91        if (ecx_39 != 0)
00440e93        int32_t edi_5 = game->__offset(0x3be73c).d
00440e96        *(ecx_39 + 8) = edi_5.b
00440e96        *(ecx_39 + 9) = edi_5:1.b
00440e96        *(ecx_39 + 0xa) = edi_5:2.b
00440e96        *(ecx_39 + 0xb) = edi_5:3.b
00440e99        void* ecx_40 = game->__offset(0x3be73c).d
00440e9e        if (ecx_40 == 0)
00440eab        *(edx_41 + 4) = game->__offset(0x3be740).d
00440ea0        int32_t edi_6 = game->__offset(0x3be740).d
00440ea3        *(ecx_40 + 0xc) = edi_6.b
00440ea3        *(ecx_40 + 0xd) = edi_6:1.b
00440ea3        *(ecx_40 + 0xe) = edi_6:2.b
00440ea3        *(ecx_40 + 0xf) = edi_6:3.b
00440eb1        game->__offset(0x3be740).d = *(edx_41 + 8)
00440eb4        *(edx_41 + 8) = &game->__offset(0x3be734).d
00440eba        int32_t ecx_43
00440eba        ecx_43:1.b = game->__offset(0x3be738).d:1.b & 0xfd
00440ebd        game->__offset(0x3be738).d = ecx_43
00440e82        report_errorf("List remove NEXTBOD")
00440ed2        recycle_bod_to_free_list(data_4df904 + 0x5a8, &game->__offset(0x3beb10).d)
00440eea        recycle_bod_to_free_list(data_4df904 + 0x5a8, &game->__offset(0x3beeec).d)
00440f02        recycle_bod_to_free_list(data_4df904 + 0x5a8, &game->__offset(0x3bf97c).d)
00440f09        game->__offset(0x3bbb70).d = 0
00440f14        void* __offset(Game, 0x3bbbb4) esi_10 = &game->__offset(0x3bbbb4).d
00440f1a        int32_t i_11 = 0xc
00440f3a        int32_t i_5
00440f2a        if ((esi_10 - 0x3bbbb4)->__offset(0x3bbdf8).d == 1)
00440f2e        kill_golb(esi_10)
00440f33        esi_10 += 0x2e8
00440f39        i_5 = i_11
00440f39        i_11 -= 1
00440f3a        do while (i_5 != 1)
00440f49        if (((game->__offset(0x3bb808).d).w:1.b & 2) != 0)
00440f5d        recycle_bod_to_free_list(data_4df904 + 0x5a8, &game->__offset(0x3bb804).d)
00440f62        game->__offset(0x3bb884).d = 0
00440f71        kill_game_sprites()
00440f7b        return
