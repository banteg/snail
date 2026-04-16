/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy @ 0x43a9c0 */

0043a9c4        int32_t ebx
0043a9c4        int32_t var_4 = ebx
0043a9c5        int32_t ebp
0043a9c5        int32_t var_8 = ebp
0043a9c6        int32_t esi
0043a9c6        int32_t var_c = esi
0043a9cb        int32_t edi
0043a9cb        int32_t var_10 = edi
0043a9cc        *(arg3 + 0x380) = arg4
0043a9de        *(arg3 + 0x408) = data_4df904 + 0x74618
0043a9e4        *(arg3 + 0x370) = 0
0043a9ea        *(arg3 + 0x1e8) = 0
0043a9f0        *(arg3 + 0x2d8) = 0
0043a9f6        *(arg3 + 0x154) = arg3
0043a9fc        *(arg3 + 0x150) = 0
0043aa02        *(arg3 + 0x14c) = 0
0043aa08        *(arg3 + 0x8c) = 0
0043aa0e        *(arg3 + 0x444) = 0
0043aa14        *(arg3 + 0x338) = 0
0043aa1a        *(arg3 + 0x33c) = 0xffffffff
0043aa24        *(arg3 + 0x1e4) = 0
0043aa2a        *(arg3 + 0x42b8) = 0
0043aa36        *(*(arg3 + 0x408) + 0x12727ec) = 0
0043aa3c        *(arg3 + 0x3c68) = 0
0043aa42        *(arg3 + 0x30d4) = 0
0043aa48        *(arg3 + 0x34b0) = 0
0043aa4e        *(arg3 + 0x388c) = 0
0043aa54        *(arg3 + 0x2dc) = 0
0043aa5a        *(arg3 + 0x2e0) = 0
0043aa60        *(arg3 + 0x29a8)
0043aa6c        sub_41aa30()
0043aa71        *(arg3 + 0x2980) = 0xc1980000
0043aa7b        *(arg3 + 0x1cc) = 0
0043aa86        *(arg3 + 0x42b0) = 0
0043aa8c        *(arg3 + 0x42b4) = 0x3c888889
0043aa92        *(arg3 + 0x435c) = 0
0043aa9e        *(arg3 + 0x4360) = 0x3c888889
0043aaa4        initialize_score_stats()
0043aaaf        initialize_invincible_shell(arg3 + 0x4218)
0043aabe        *(arg3 + 0x334) = 0x3d638e38
0043aac4        *(arg3 + 0x330) = 0x3d638e38
0043aaca        *(arg3 + 0x434) = 0
0043aad0        *(arg3 + 0x438) = 0x3c888889
0043aadf        if ((*(*(arg3 + 0x29a8) + 0x10) & 0x200000) == 0)
0043ab31        initialize_anim_manager(arg3 + 0x2a88)
0043ab36        *(arg3 + 0x2a88) = 0
0043aaed        int32_t eax_1
0043aaed        eax_1:1.b = (*(arg3 + 0x2988)):1.b | 8
0043aaf2        *(arg3 + 0x2988) = eax_1
0043aaf8        *(arg3 + 0x29fc) = arg3 + 0x2a88
0043aafe        initialize_anim_manager(arg3 + 0x2a88)
0043ab09        *(arg3 + 0x2a88) = 1
0043ab15        *(arg3 + 0x2ac8) = arg3 + 0x2984
0043ab1b        *(arg3 + 0x2acc) = arg3 + 0x2ad0
0043ab21        *(arg3 + 0x2ac4) = 0
0043ab41        if ((*(*(arg3 + 0x3b88) + 0x10) & 0x200000) == 0)
0043ab9c        initialize_anim_manager(arg3 + 0x3c6c)
0043aba1        *(arg3 + 0x3c6c) = 0
0043ab52        int32_t ecx_10
0043ab52        ecx_10:1.b = (*(arg3 + 0x3b68) & 0xffffffdf):1.b | 8
0043ab55        *(arg3 + 0x3b68) = ecx_10
0043ab5b        *(arg3 + 0x3c68) = 0
0043ab63        *(arg3 + 0x3bdc) = arg3 + 0x3c6c
0043ab69        initialize_anim_manager(arg3 + 0x3c6c)
0043ab74        *(arg3 + 0x3c6c) = 1
0043ab80        *(arg3 + 0x3cac) = arg3 + 0x3b64
0043ab86        *(arg3 + 0x3cb0) = arg3 + 0x3cb4
0043ab8c        *(arg3 + 0x3ca8) = 0
0043abac        if ((*(*(arg3 + 0x2ff4) + 0x10) & 0x200000) == 0)
0043ac07        initialize_anim_manager(arg3 + 0x30d8)
0043ac0c        *(arg3 + 0x30d8) = 0
0043abbf        int32_t edx_4
0043abbf        edx_4:1.b = (*(arg3 + 0x2fd4) & 0xffffffdf):1.b | 8
0043abc2        *(arg3 + 0x2fd4) = edx_4
0043abc8        *(arg3 + 0x30d4) = 0
0043abce        *(arg3 + 0x3048) = arg3 + 0x30d8
0043abd4        initialize_anim_manager(arg3 + 0x30d8)
0043abdf        *(arg3 + 0x30d8) = 1
0043abeb        *(arg3 + 0x3118) = arg3 + 0x2fd0
0043abf1        *(arg3 + 0x311c) = arg3 + 0x3120
0043abf7        *(arg3 + 0x3114) = 0
0043ac17        if ((*(*(arg3 + 0x33d0) + 0x10) & 0x200000) == 0)
0043ac71        initialize_anim_manager(arg3 + 0x34b4)
0043ac76        *(arg3 + 0x34b4) = 0
0043ac25        int32_t eax_5
0043ac25        eax_5.b = (*(arg3 + 0x33b0)).b & 0xdf
0043ac27        eax_5:1.b |= 8
0043ac2a        *(arg3 + 0x33b0) = eax_5
0043ac30        *(arg3 + 0x34b0) = 0
0043ac38        *(arg3 + 0x3424) = arg3 + 0x34b4
0043ac3e        initialize_anim_manager(arg3 + 0x34b4)
0043ac49        *(arg3 + 0x34b4) = 1
0043ac55        *(arg3 + 0x34f4) = arg3 + 0x33ac
0043ac5b        *(arg3 + 0x34f8) = arg3 + 0x34fc
0043ac61        *(arg3 + 0x34f0) = 0
0043ac81        if ((*(*(arg3 + 0x37ac) + 0x10) & 0x200000) == 0)
0043acdc        initialize_anim_manager(arg3 + 0x3890)
0043ace1        *(arg3 + 0x3890) = 0
0043ac92        int32_t ecx_21
0043ac92        ecx_21:1.b = (*(arg3 + 0x378c) & 0xffffffdf):1.b | 8
0043ac95        *(arg3 + 0x378c) = ecx_21
0043ac9b        *(arg3 + 0x388c) = 0
0043aca3        *(arg3 + 0x3800) = arg3 + 0x3890
0043aca9        initialize_anim_manager(arg3 + 0x3890)
0043acb4        *(arg3 + 0x3890) = 1
0043acc0        *(arg3 + 0x38d0) = arg3 + 0x3788
0043acc6        *(arg3 + 0x38d4) = arg3 + 0x38d8
0043accc        *(arg3 + 0x38cc) = 0
0043ace9        initialize_snail_skin(arg3 + 0x42bc)
0043acf4        initialize_cutscene_ai(arg3 + 0x42dc)
0043ad05        if (*(*(arg3 + 0x408) + 0xff25d0) == 0)
0043ad07        *(arg3 + 0x42e8) = 1
0043ad17        *(arg3 + 0x2a84) = arg3
0043ad1d        set_matrix_identity(arg3 + 0x29bc)
0043ad28        set_matrix_identity(arg3 + 0x2a44)
0043ad33        set_matrix_identity(arg3 + 0x2a04)
0043ad3f        *(arg3 + 0x4338) = 0
0043ad45        initialize_click_start(arg3 + 0xa0, arg3)
0043ad50        initialize_cameraman(arg3 + 0x200)
0043ad5e        initialize_subgoldy_ghost(arg3, *(arg3 + 0x380))
0043ad6a        *(arg3 + 0x1d8) = 0x3d4ede62
0043ad70        *(arg3 + 0x1e0) = 0x3d4ede62
0043ad7e        *(arg3 + 0x68) = 0
0043ad81        *(arg3 + 0x6c) = 0
0043ad84        *(arg3 + 0x2964) = 0
0043ad86        *(arg3 + 0x70) = 0x40800000
0043ad8d        int32_t ecx_33 = *(arg3 + 0x70)
0043ad90        *(arg3 + 0x37c) = 0
0043ad96        *(arg3 + 0x2968) = 0
0043ad99        *(arg3 + 0x328) = 0
0043ad9f        *(arg3 + 0x32c) = 0x3c888889
0043ada9        *(arg3 + 0x1d4) = 0
0043adaf        *(arg3 + 0x1dc) = 0
0043adb5        *(arg3 + 0x3f40) = 0
0043adbb        *(arg3 + 0x3f44) = 0x3bbc5264
0043adc5        *(arg3 + 0x3f48) = 0
0043adcb        *(arg3 + 0x3f4c) = 0x3bde0163
0043add5        *(arg3 + 0x84) = 0
0043addb        *(arg3 + 0x296c) = ecx_33
0043adde        *(arg3 + 0x418) = 0
0043ade4        *(arg3 + 0x414) = 0
0043adea        *(arg3 + 0x410) = 0
0043adf9        int32_t eax_10 = data_4df904
0043adfe        int32_t eax_11
0043adfe        if (*(arg3 + 0x380) != 1)
0043ae14        if (eax_10 == 0xffffff4c)
0043ae1d        eax_11 = 0
0043ae16        eax_11 = eax_10 + 0xec
0043ae05        if (eax_10 == 0xffffffbc)
0043ae1d        eax_11 = 0
0043ae07        eax_11 = eax_10 + 0x7c
0043ae25        *(arg3 + 0x43c) = eax_11
0043ae2b        *(arg3 + 0x2730) = 0
0043ae31        *(arg3 + 0x440) = 0
0043ae37        *(arg3 + 0x2738) = 0
0043ae3d        initialize_damage_gauge(arg3 + 0x3c4)
0043ae4d        *(arg3 + 0x384) = 0
0043ae53        struct TransformMatrix* transform = arg3 + 0x614
0043ae59        int32_t i_1 = 0xc
0043ae7e        int32_t i
0043ae60        transform->__offset(0x80).d = 0
0043ae66        set_matrix_identity(transform)
0043ae71        transform->__offset(0xac).d = *(arg3 + 0x408)
0043ae77        transform += 0x2e8
0043ae7d        i = i_1
0043ae7d        i_1 -= 1
0043ae7e        do while (i != 1)
0043ae8c        int32_t var_14_2 = *(arg3 + 0x380)
0043ae93        *(arg3 + 4) |= 0x20
0043ae96        *(arg3 + 0x2744) = 0
0043ae9c        __builtin_strncpy(arg3 + 0x2748, "VUU>", 8)
0043aeac        initialize_jetpack_gauge(arg3 + 0x2750)
0043aeb1        __builtin_memset(arg3 + 0x350, 0, 0x20)
0043aee1        *(arg3 + 0x374) = 0
0043aee7        *(arg3 + 0x378) = 0
0043aeed        *(arg3 + 0x41d) = 0
0043aef3        *(arg3 + 0x41c) = 0
0043aef9        *(arg3 + 0x404) = 0
0043af08        *(*(arg3 + 0x408) + 1) = 1
0043af0d        return 0
