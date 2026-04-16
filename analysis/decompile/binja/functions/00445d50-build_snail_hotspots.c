/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_snail_hotspots @ 0x445d50 */

00445d50        struct PlayerPresentationController* presentation_1 = presentation
00445d53        void* ebp = presentation->_pad_1644[0x2c].d
00445d5f        char (** i)[0x16] = &data_4a4aa0
00445d64        float* esi = &presentation->snail_hotspots_local[0].z
00445d71        (esi - 0x16d4)->snail_hotspots_local[0].z = 0f
00445d73        (esi - 0x16d4)->snail_hotspots_local[0].y = 0f
00445d76        (esi - 0x16d4)->snail_hotspots_local[0].x = 0
00445d7e        struct TextureRef* j = get_or_create_texture_ref(&data_4b7790, *i, 0, 0)
00445d83        int32_t edx_1 = *(ebp + 0x54)
00445d86        int32_t ecx = 0
00445d8a        if (edx_1 s<= 0)
00445da0        label_445da0:
00445da0        char (* var_18_1)[0x16] = *i
00445da6        report_errorf("Cannot find HotPoint Texture %s")
00445d8f        int32_t* edi_2 = *(ebp + 0x5c) + 0xc
00445d94        while (*edi_2 != j)
00445d96        ecx += 1
00445d97        edi_2 = &edi_2[0xc]
00445d9c        if (ecx s>= edx_1)
00445d9c        goto label_445da0
00445dbb        int32_t eax_2
00445dbb        eax_2.w = *(ecx * 0x30 + *(ebp + 0x5c) + 2)
00445dc0        int32_t ecx_2 = *(ebp + 0x38)
00445dc6        int32_t eax_3 = eax_2 * 3
00445dcc        void* eax_4 = ecx_2 + (eax_3 << 2)
00445dcf        (esi - 0x16d4)->snail_hotspots_local[0].x = fconvert.s(fconvert.t((esi - 0x16d4)->snail_hotspots_local[0].x) + fconvert.t(*(ecx_2 + (eax_3 << 2))))
00445dd8        (esi - 0x16d4)->snail_hotspots_local[0].y = fconvert.s(fconvert.t(*(eax_4 + 4)) + fconvert.t((esi - 0x16d4)->snail_hotspots_local[0].y))
00445de0        (esi - 0x16d4)->snail_hotspots_local[0].z = fconvert.s(fconvert.t(*(eax_4 + 8)) + fconvert.t((esi - 0x16d4)->snail_hotspots_local[0].z))
00445dea        (esi - 0x16d4)->snail_hotspots_local[0].x = (esi - 0x16d4)->snail_hotspots_local[0].x
00445ded        (esi - 0x16d4)->snail_hotspots_local[0].y = (esi - 0x16d4)->snail_hotspots_local[0].y
00445df0        (esi - 0x16d4)->snail_hotspots_local[0].z = (esi - 0x16d4)->snail_hotspots_local[0].z
00445df2        i = &i[1]
00445df5        esi = &esi[3]
00445dfe        do while (i s< "X/CameraIntroTalk")
00445e18        presentation->snail_hotspots_local[0x12].y = fconvert.s(fconvert.t(presentation->snail_hotspots_local[0x12].y) + fconvert.t(0.300000012f))
00445e1f        return
