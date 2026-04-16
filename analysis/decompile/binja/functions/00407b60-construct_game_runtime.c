/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: construct_game_runtime @ 0x407b60 */

00407b60        int32_t var_4_2 = 0xffffffff
00407b62        int32_t (* var_8)() = sub_496a7b
00407b6d        TEB* fsbase
00407b6d        struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList = fsbase->NtTib.ExceptionList
00407b6e        fsbase->NtTib.ExceptionList = &ExceptionList
00407b75        int32_t ecx
00407b75        int32_t var_10 = ecx
00407b77        int32_t __saved_ebx = 0x12e6ff4
00407b7c        char* __saved_edi = "Size of cRGame %i\n"
00407b86        int32_t var_20 = 0x1272838
00407b8b        char* var_24 = "Size of cRSubGame %i\n"
00407b95        int32_t var_28 = 0xa7f8
00407b9a        char* var_2c = "   Size of cRSegmentCache %i\n"
00407ba4        int32_t var_30 = 0x1c
00407ba6        char* var_34 = "   Size of cRTutorial\t%i\n"
00407bb0        int32_t var_38 = 0x1a5978
00407bb5        char* var_3c = "   Size of cRSubTracks %i\n"
00407bbf        int32_t var_40 = 0xb4
00407bc4        char* var_44 = "   Size of cRSubSpeedUp %i\n"
00407bce        int32_t var_48 = 0x19c
00407bd3        char* var_4c = "   Size of cRJetPack %i\n"
00407bdd        int32_t var_50 = 0x3a0
00407be2        char* var_54 = "   Size of cRSubHealth %i\n"
00407bef        int32_t __saved_ebx_1 = 0x760
00407bf4        char* __saved_edi_1 = "   Size of cRSlug %i\n"
00407bfe        int32_t var_20_1 = 0xdc0
00407c03        char* var_24_1 = "   Size of cRSubLazerManager %i\n"
00407c0d        int32_t var_28_1 = 0x17c0
00407c12        char* var_2c_1 = "   Size of cRSaltManager %i\n"
00407c1c        int32_t var_30_1 = 0x2648
00407c21        char* var_34_1 = "   Size of cRSubGarbage %i\n"
00407c2b        int32_t var_38_1 = 0x3f0
00407c30        char* var_3c_1 = "   Size of cRSubRing %i\n"
00407c3a        int32_t var_40_1 = 0x5fb44
00407c3f        char* var_44_1 = "   Size of cRFringeManager %i\n"
00407c49        int32_t var_48_1 = 0x4364
00407c4e        char* var_4c_1 = "   Size of cRSubGoldy %i\n"
00407c58        int32_t var_50_1 = 0x20d000
00407c5d        char* var_54_1 = "   Size of cRSubLoc %i\n"
00407c6a        int32_t __saved_ebx_2 = 0xbea00
00407c6f        char* __saved_edi_2 = "   Size of cRSubRow %i\n"
00407c79        int32_t var_20_2 = 0x947648
00407c7e        char* var_24_2 = "   Size of cRSubHighScore %i\n"
00407c88        int32_t var_28_2 = 0x1fac0
00407c8d        char* var_2c_2 = "   Size of cRSubSolution %i\n"
00407c97        int32_t var_30_2 = 0x330
00407c9c        char* var_34_2 = "   Size of cRTimeTrial %i\n"
00407ca6        int32_t var_38_2 = 1
00407ca8        char* var_3c_2 = "   Size of cRPathManager %i\n"
00407cb2        int32_t var_40_2 = 0x52b0
00407cb7        char* var_44_2 = "   Size of cRPath %i\n"
00407cc1        int32_t var_48_2 = 0x97a4
00407cc6        char* var_4c_2 = "   Size of cRLandscapeManager %i\n"
00407cd0        int32_t var_50_2 = 0x25cfb4
00407cd5        char* var_54_2 = "   Size of cRSMTracks %i\n"
00407ce2        int32_t __saved_ebx_3 = 0x1b58
00407ce7        char* __saved_edi_3 = "   Size of cRParcelManager %i\n"
00407cf1        int32_t var_20_3 = 0x28
00407cf3        char* var_24_3 = "   Size of cRGUI %i\n"
00407cfd        int32_t var_28_3 = 0x10fa8
00407d02        char* var_2c_3 = "   Size of cRGalaxy %i\n"
00407d0c        int32_t var_30_3 = 0x1804
00407d11        char* var_34_3 = "   Size of cREnemyManager %i\n"
00407d1b        int32_t var_38_3 = 0x50
00407d1d        char* var_3c_3 = "   Size of cRCompletion %i\n"
00407d27        int32_t var_40_3 = 0x10
00407d29        char* var_44_3 = "   Size of cRTimesUp %i\n"
00407d33        int32_t var_48_3 = 0x947648
00407d38        char* var_4c_3 = "Size of cRSubHighScore %i\n"
00407d42        int32_t var_50_3 = 0x38
00407d44        char* var_54_3 = "Size of cRBod %i\n"
00407d51        int32_t __saved_ebx_4 = 0x54
00407d53        char* __saved_edi_4 = "Size of cRSubLoc %i\n"
00407d5d        int32_t var_20_4 = 0x947648
00407d62        char* var_24_4 = "Solutions %i\n"
00407d76        void*** esi = sub_48ba3f(0x12e6ff4)
00407d7b        void*** var_10_1 = esi
00407d81        int32_t var_4 = 0
00407d89        if (esi == 0)
00407f6d        esi = nullptr
00407d99        void*** edi_1 = &esi[0x11]
00407d9c        int32_t i_4 = 2
00407db2        int16_t top
00407db2        int32_t i
00407da3        initialize_bod_base(edi_1)
00407da3        top -= 1
00407da8        *edi_1 = &data_4972f0
00407dae        edi_1 = &edi_1[0x1c]
00407db1        i = i_4
00407db1        i_4 -= 1
00407db2        do while (i != 1)
00407db4        char** edi_2 = &esi[0x49]
00407dba        int32_t i_5 = 2
00407dcd        int32_t i_1
00407dc1        sub_408000(edi_2)
00407dc1        top -= 2
00407dc6        edi_2 = &edi_2[0x7e]
00407dcc        i_1 = i_5
00407dcc        i_5 -= 1
00407dcd        do while (i_1 != 1)
00407dd5        initialize_bod_base(&esi[0x15c])
00407dda        void* edi_3 = &esi[0x16d]
00407de0        int32_t i_6 = 5
00407df0        int32_t i_2
00407de7        sub_44e920(edi_3)
00407dec        edi_3 += 0x28
00407def        i_2 = i_6
00407def        i_6 -= 1
00407df0        do while (i_2 != 1)
00407dfa        initialize_renderable_bod(&esi[0x19f])
00407e05        Concurrency::details::SingleWaitBlock::SingleWaitBlock(&esi[0x1bf])
00407e0a        esi[0x19f] = &data_4972ec
00407e18        initialize_renderable_bod(&esi[0x1f2])
00407e23        Concurrency::details::SingleWaitBlock::SingleWaitBlock(&esi[0x212])
00407e28        esi[0x1f2] = &data_4972ec
00407e36        initialize_renderable_bod(&esi[0x245])
00407e41        Concurrency::details::SingleWaitBlock::SingleWaitBlock(&esi[0x265])
00407e46        esi[0x245] = &data_4972ec
00407e54        initialize_renderable_bod(&esi[0x298])
00407e64        esi[0x298] = "P{@"
00407e72        initialize_bod_base(&esi[0x2d3])
00407e72        int16_t top_9 = top - 9
00407e8d        initialize_array_with_constructor(&esi[0x474], 0x724, 0x96, sub_408410)
00407e92        esi[0x2d3] = &data_4972e8
00407e98        char** edi_9 = &esi[0x11040]
00407e9e        int32_t i_7 = 0x160
00407eae        int32_t i_3
00407ea5        initialize_bod_base(edi_9)
00407ea5        top_9 -= 1
00407eaa        edi_9 = &edi_9[0xe]
00407ead        i_3 = i_7
00407ead        i_7 -= 1
00407eae        do while (i_3 != 1)
00407ec6        initialize_array_with_constructor(&esi[0x12382], 0xbc, 0x80, sub_408470)
00407ed3        initialize_bod_base(&esi[0x13b04])
00407eee        esi[0x13b04] = &data_4972e4
00407efc        initialize_bod_base(&esi[0x13ccf])
00407f07        esi[0x13ccf] = &data_4972e0
00407f0d        initialize_bod_base(&esi[0x13cf2])
00407f28        initialize_array_with_constructor(&esi[0x13d06], 0x90, 0x400, sub_408490)
00407f40        initialize_array_with_constructor(&esi[0x1cd06], 0x90, 0x20, sub_408490)
00407f4b        initialize_runtime_pools_and_path_template_bank(&esi[0x1d186])
00407f58        initialize_bod_base(&esi[0x4b9bd6])
00407f5d        esi[0x4b9bd6] = &data_4972dc
00407f64        *esi = &data_4972d8
00407f6f        int32_t __saved_edi_6 = data_50331c
00407f74        int32_t var_4_1 = 0xffffffff
00407f7c        data_4df904 = esi
00407f8e        int32_t __saved_ebx_5 = __saved_edi_6 * 0x38
00407f8f        int32_t __saved_edi_5 = __saved_edi_6
00407f90        char* var_20_5 = "BodCount=%i  Memory=%i\n"
00407f9a        int32_t ecx_27 = data_4dfadc
00407faf        int32_t var_24_5 = ecx_27 * 0x54
00407fb0        int32_t var_28_4 = ecx_27
00407fb1        char* var_2c_8 = "LocCount=%i Memory=%i\n"
00407fbb        int32_t eax_6 = data_4dfae0
00407fd2        int32_t var_30_4 = eax_6 * 0x15c
00407fd3        int32_t var_34_4 = eax_6
00407fd4        char* var_38_4 = "LocMirrorCount=%i Memory=%i\n"
00407fe5        fsbase->NtTib.ExceptionList = ExceptionList
00407ff0        return 0
