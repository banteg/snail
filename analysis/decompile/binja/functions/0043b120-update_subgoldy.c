/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgoldy @ 0x43b120 */

0043b125        struct Player* player_1 = player
0043b128        int32_t __saved_edi
0043b128        int32_t* esp = &__saved_edi
0043b129        void* eax = player_1->_pad_3c0[0x48].d
0043b12f        player.b = *(eax + 9)
0043b134        if (player.b == 0)
0043b18a        if (player_1->follow_state.active != 1)
0043b1e1        void* eax_5 = player_1->__offset(0x29a8).d
0043b1fb        *(eax_5 + 0x80) = fconvert.s(fneg(fconvert.t(*(eax_5 + 0x80))) * fconvert.t(0.100000001f) + fconvert.t(*(eax_5 + 0x80)))
0043b18c        struct PathTemplate* template_record = player_1->follow_state.template_record
0043b198        int32_t eax_3 = player_1->follow_state.sample_index + 3
0043b19b        uint32_t segment_count = template_record->segment_count
0043b1a0        if (eax_3 s>= segment_count)
0043b1a2        eax_3 = segment_count - 1
0043b1ac        void* edx_1 = player_1->__offset(0x29a8).d
0043b1d9        *(edx_1 + 0x80) = fconvert.s((fconvert.t((&template_record->primary_samples->_pad_a4)[eax_3 * 0x2a]) * fconvert.t(-3f) - fconvert.t(*(edx_1 + 0x80))) * fconvert.t(0.100000001f) + fconvert.t(*(edx_1 + 0x80)))
0043b209        update_squidge(&player_1->_pad_00[0x4344])
0043b216        *(player_1->__offset(0x29a8).d + 0x84) = player_1->__offset(0x4344).d
0043b228        *(player_1->__offset(0x29a8).d + 0x88) = player_1->__offset(0x4350).d
0043b239        if (*(player_1->_pad_3c0[0x48].d + 0x40) == 0)
0043b23d        show_subgoldy_lives(player_1)
0043b242        int32_t eax_8 = player_1->_pad_3c0[0x4c].d
0043b248        eax = eax_8
0043b24b        if (eax_8 != 0)
0043b256        void* temp2_1 = eax
0043b256        eax -= 2
0043b258        if (temp2_1 != 2)
0043b25e        void* eax_9 = player_1->_pad_3c0[0x48].d
0043b26b        int32_t ecx_11
0043b26b        if (*(eax_9 + 0xff25dc) s> 0x14)
0043b26d        ecx_11.b = *(eax_9 + 0xa854)
0043b275        if (ecx_11.b == 0)
0043b277        *(eax_9 + 0xa854) = 1
0043b27e        void* const eax_10 = player_1->_pad_3c0[0x48].d
0043b289        ecx_11.b = *(eax_10 + 0xff25d0)
0043b291        void* ecx_13
0043b291        if (ecx_11.b != 0)
0043b297        ecx_13 = *(eax_10 + 0xff25d4)
0043b29d        eax_10 = *(eax_10 + 0xff25dc)
0043b2b2        struct Player* player_2
0043b2b2        void* eax_12
0043b2b2        struct Vec3* player_7
0043b2b2        long double st0_1
0043b2b2        int16_t top_1
0043b2b2        if (ecx_11.b == 0 || eax_10 s>= *(ecx_13 + 0x6c) || player_1->_pad_74[0xac].d == 2)
0043b360        eax_10.b = player_1->_pad_3c0[0]
0043b368        if (eax_10.b == 0)
0043b38a        label_43b38a:
0043b38a        eax_10.b = player_1->_pad_74[0x264]
0043b392        if (eax_10.b == 0)
0043b402        player_2 = (&data_4df950)[player_1->__offset(0x2970).d]
0043b403        resolve_uncaptured_cursor_sensitivity_scale(player_2)
0043b41c        long double x87_r7_21 = fconvert.t(*(player_1->_pad_430[0xc].d + 0x28)) - fconvert.t(player_1->_pad_430[0x2310].d) + fconvert.t(player_1->_pad_430[0x230c].d)
0043b422        long double temp3_1 = fconvert.t(0f)
0043b422        x87_r7_21 - temp3_1
0043b428        player_1->_pad_430[0x230c].d = fconvert.s(x87_r7_21)
0043b428        bool c1_1 = unimplemented  {fst dword [ebp+0x273c], st0}
0043b42e        void* eax_15
0043b42e        eax_15.w = (x87_r7_21 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_21, temp3_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0043b433        if ((eax_15:1.b & 1) == 0)
0043b43f        long double temp5_1 = fconvert.t(639f)
0043b43f        x87_r7_21 - temp5_1
0043b445        eax_15.w = (x87_r7_21 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp5_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp5_1 ? 1 : 0) << 0xe | 0x3800
0043b44a        if ((eax_15:1.b & 0x41) == 0)
0043b44e        x87_r7_21 = fconvert.t(639f)
0043b437        x87_r7_21 = fconvert.t(0f)
0043b454        player_1->_pad_430[0x230c].d = fconvert.s(x87_r7_21)
0043b460        int32_t edx_9 = *(player_1->_pad_430[0xc].d + 0x28)
0043b463        player_1->_pad_430[0x2310] = edx_9.b
0043b463        player_1->_pad_430[0x2311] = edx_9:1.b
0043b463        player_1->_pad_430[0x2312] = edx_9:2.b
0043b463        player_1->_pad_430[0x2313] = edx_9:3.b
0043b472        if (player_1->__offset(0x2970).d == 1)
0043b47d        player_1->_pad_430[0x230c].d = fconvert.s(fconvert.t(*(player_1->_pad_430[0xc].d + 0x28)))
0043b394        long double x87_r7_11 = fconvert.t(player_1->__offset(0x29cc).d)
0043b39c        long double x87_r7_13 = fconvert.t(player_1->_pad_430[0x230c].d) - (x87_r7_11 + x87_r7_11)
0043b3a2        player_1->_pad_430[0x230c].d = fconvert.s(x87_r7_13)
0043b3a8        player_1->_pad_430[0x2310].d = fconvert.s(x87_r7_13)
0043b3ae        long double x87_r7_14 = fconvert.t(player_1->_pad_430[0x230c].d)
0043b3b4        long double temp4_1 = fconvert.t(0f)
0043b3b4        x87_r7_14 - temp4_1
0043b3ba        eax_10.w = (x87_r7_14 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp4_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp4_1 ? 1 : 0) << 0xe
0043b3bf        long double x87_r7_15
0043b3bf        if ((eax_10:1.b & 1) == 0)
0043b3cc        long double x87_r7_16 = fconvert.t(player_1->_pad_430[0x230c].d)
0043b3d2        long double temp6_1 = fconvert.t(639f)
0043b3d2        x87_r7_16 - temp6_1
0043b3d8        eax_10.w = (x87_r7_16 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp6_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp6_1 ? 1 : 0) << 0xe
0043b3dd        if ((eax_10:1.b & 0x41) != 0)
0043b3ea        x87_r7_15 = fconvert.t(player_1->_pad_430[0x230c].d)
0043b3df        x87_r7_15 = fconvert.t(639f)
0043b3c1        x87_r7_15 = fconvert.t(0f)
0043b47d        player_1->_pad_430[0x230c].d = fconvert.s(x87_r7_15)
0043b36a        eax_10.b = player_1->_pad_430[0x10]
0043b372        if (eax_10.b == 0)
0043b372        goto label_43b38a
0043b379        player_1->_pad_430[0x230c] = 0
0043b379        player_1->_pad_430[0x230d] = 0
0043b379        player_1->_pad_430[0x230e] = 0xa0
0043b379        player_1->_pad_430[0x230f] = 0x43
0043b37f        player_1->_pad_430[0x2310] = 0
0043b37f        player_1->_pad_430[0x2311] = 0
0043b37f        player_1->_pad_430[0x2312] = 0xa0
0043b37f        player_1->_pad_430[0x2313] = 0x43
0043b483        eax_10.b = player_1->_pad_430[0x10]
0043b48b        if (eax_10.b == 0)
0043b499        long double x87_r7_26 = (fconvert.t(320f) - fconvert.t(player_1->_pad_430[0x230c].d)) * fconvert.t(0.0125000002f)
0043b49f        long double temp7_1 = fconvert.t(-3.70000005f)
0043b49f        x87_r7_26 - temp7_1
0043b4a5        eax_10.w = (x87_r7_26 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp7_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0043b4aa        if ((eax_10:1.b & 1) == 0)
0043b4b6        long double temp8_1 = fconvert.t(3.70000005f)
0043b4b6        x87_r7_26 - temp8_1
0043b4bc        eax_10.w = (x87_r7_26 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp8_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp8_1 ? 1 : 0) << 0xe | 0x3800
0043b4c1        if ((eax_10:1.b & 0x41) == 0)
0043b4c5        x87_r7_26 = fconvert.t(3.70000005f)
0043b4ae        x87_r7_26 = fconvert.t(-3.70000005f)
0043b4d1        if (player_1->_pad_74[0xac].d != 2)
0043b4ec        player_1->position.x = fconvert.s(fconvert.t(*(player_1->_pad_3c0[0x48].d + 0x38)) * fconvert.t(0.200000003f) * (x87_r7_26 - fconvert.t(player_1->position.x)) + fconvert.t(player_1->position.x))
0043b4f3        float x_3 = player_1->position.x
0043b4f6        player_7 = &player_1->position
0043b4f9        player_2 = 0x41800000
0043b504        int16_t eax_16
0043b504        int80_t st0_3
0043b504        st0_3, eax_16 = convert_math_type32_to_16(x_3, 16f)
0043b50d        long double st0_4 = convert_math_type16_to_32(eax_16, player_2)
0043b512        float var_40_1 = fconvert.s(st0_4)
0043b51f        player_7->x = fconvert.s(st0_4)
0043b521        void* esi_2 = player_1->_pad_3c0[0x48].d
0043b528        int16_t eax_18
0043b528        int80_t st0_5
0043b528        st0_5, eax_18 = convert_math_type32_to_16(var_40_1, 16f)
0043b536        int32_t ecx_24 = *(esi_2 + 0xff25dc) * 3
0043b539        player_2 = 0x42000000
0043b53e        *(esi_2 + (ecx_24 << 1) + 0xfd2b80) = eax_18
0043b546        void* edx_10 = player_1->_pad_3c0[0x48].d
0043b556        void* ecx_28
0043b556        long double x87_r4_1
0043b556        if (*(edx_10 + 0xff25dc) != 0)
0043b5a5        int32_t var_58_4 = ecx_24
0043b5a9        int16_t eax_24
0043b5a9        int80_t st0_7
0043b5a9        st0_7, eax_24 = convert_math_type32_to_16(fconvert.s(fconvert.t(player_1->position.z) - fconvert.t(data_643194)), player_2)
0043b5c2        *(edx_10 + (*(edx_10 + 0xff25dc) + 0x2a31eb) * 6) = eax_24
0043b5c6        ecx_28 = player_1->_pad_3c0[0x48].d
0043b5da        int32_t eax_26
0043b5da        eax_26.w = *(ecx_28 + (*(ecx_28 + 0xff25dc) + 0x2a31eb) * 6)
0043b5df        st0_1 = convert_math_type16_to_32(eax_26.w, 32f)
0043b5e4        x87_r4_1 = st0_1 + fconvert.t(data_643194)
0043b55c        int16_t eax_21
0043b55c        int80_t st0_6
0043b55c        st0_6, eax_21 = convert_math_type32_to_16(player_1->position.z, player_2)
0043b575        *(edx_10 + (*(edx_10 + 0xff25dc) + 0x2a31eb) * 6) = eax_21
0043b579        ecx_28 = player_1->_pad_3c0[0x48].d
0043b58d        int32_t eax_23
0043b58d        eax_23.w = *(ecx_28 + (*(ecx_28 + 0xff25dc) + 0x2a31eb) * 6)
0043b592        st0_1 = convert_math_type16_to_32(eax_23.w, 32f)
0043b592        x87_r4_1 = st0_1
0043b5ed        data_643194 = fconvert.s(x87_r4_1)
0043b5ed        top_1 = 0xfffd
0043b5f3        void* eax_27 = player_1->_pad_3c0[0x48].d
0043b5f9        ecx_28.b = *(eax_27 + 0xa854)
0043b601        if (ecx_28.b != 0)
0043b60c        if ((*(player_1->_pad_430[0xc].d + 4) & 0x4000) != 0)
0043b614        void* edx_13 = *(eax_27 + 0xff25dc) * 3
0043b617        *(eax_27 + (edx_13 << 1) + 0xfd2b84) |= 1
0043b62f        if ((*(player_1->_pad_430[0xc].d + 0xc) & 0x4000) != 0)
0043b631        void* eax_30 = player_1->_pad_3c0[0x48].d
0043b63d        ecx_28 = *(eax_30 + 0xff25dc) * 3
0043b640        *(eax_30 + (ecx_28 << 1) + 0xfd2b84) |= 2
0043b64f        void* eax_32 = player_1->_pad_430[0xc].d
0043b65d        if ((*(eax_32 + 0xc) & 0x4000) == 0 && (*(eax_32 + 4) & 0x4000) == 0)
0043b665        *(player_1->_pad_3c0[0x48].d + 0xa854) = 1
0043b66c        eax_12 = player_1->_pad_3c0[0x48].d
0043b672        ecx_28.b = *(eax_12 + 0xa854)
0043b67a        if (ecx_28.b != 0)
0043b682        int32_t ecx_34 = *(eax_12 + 0xff25dc) * 3
0043b685        *(eax_12 + (ecx_34 << 1) + 0xfd2b84) |= 4
0043b2bb        player_2 = 0x41800000
0043b2c0        player_7 = &player_1->position
0043b2c3        eax_10.w = *(ecx_13 + eax_10 * 6 + 0x70)
0043b2c9        st0_1 = convert_math_type16_to_32(eax_10.w, player_2)
0043b2ce        player_7->x = fconvert.s(st0_1)
0043b2ce        top_1 = 0
0043b2d0        void* eax_11 = player_1->_pad_3c0[0x48].d
0043b2ed        if ((*(*(eax_11 + 0xff25d4) + *(eax_11 + 0xff25dc) * 6 + 0x74) & 4) == 0)
0043b2f8        *(eax_11 + 0xa854) = 0
0043b2ef        *(eax_11 + 0xa854) = 1
0043b2ff        eax_12 = player_1->_pad_3c0[0x48].d
0043b319        if ((*(*(eax_12 + 0xff25d4) + *(eax_12 + 0xff25dc) * 6 + 0x74) & 8) != 0)
0043b324        *(data_4df904 + 0x1b8) = 0x1a
0043b334        *(data_4df904 + 0x1bc) = 0xa
0043b344        *(data_4df904 + 0x30c) = 1
0043b34b        void* eax_14 = data_4df904
0043b353        begin_frontend_fade_in(eax_14 + 0x24)
0043b35f        return eax_14
0043b694        unimplemented  {fld st0, dword [ebx]}
0043b696        long double temp9_1 = fconvert.t(-4f)
0043b696        unimplemented  {fcomp st0, dword [0x497420]} f- temp9_1
0043b696        bool c0_7 = unimplemented  {fcomp st0, dword [0x497420]} f< temp9_1
0043b696        bool c2_7 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp9_1)
0043b696        bool c3_7 = unimplemented  {fcomp st0, dword [0x497420]} f== temp9_1
0043b696        unimplemented  {fcomp st0, dword [0x497420]}
0043b69c        eax_12.w = (c0_7 ? 1 : 0) << 8 | (c2_7 ? 1 : 0) << 0xa | (c3_7 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b6a1        if ((eax_12:1.b & 1) != 0)
0043b6a3        player_7->x = 0xc0800000
0043b6a9        player_1->_pad_3c0[0x50] = 0
0043b6a9        player_1->_pad_3c0[0x51] = 0
0043b6a9        player_1->_pad_3c0[0x52] = 0
0043b6a9        player_1->_pad_3c0[0x53] = 0
0043b6b3        unimplemented  {fld st0, dword [ebx]}
0043b6b5        long double temp10_1 = fconvert.t(4f)
0043b6b5        unimplemented  {fcomp st0, dword [0x497210]} f- temp10_1
0043b6b5        bool c0_8 = unimplemented  {fcomp st0, dword [0x497210]} f< temp10_1
0043b6b5        bool c2_8 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp10_1)
0043b6b5        bool c3_8 = unimplemented  {fcomp st0, dword [0x497210]} f== temp10_1
0043b6b5        unimplemented  {fcomp st0, dword [0x497210]}
0043b6bb        eax_12.w = (c0_8 ? 1 : 0) << 8 | (c2_8 ? 1 : 0) << 0xa | (c3_8 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b6c0        if ((eax_12:1.b & 0x41) == 0)
0043b6c2        player_7->x = 0x40800000
0043b6c8        player_1->_pad_3c0[0x50] = 0
0043b6c8        player_1->_pad_3c0[0x51] = 0
0043b6c8        player_1->_pad_3c0[0x52] = 0
0043b6c8        player_1->_pad_3c0[0x53] = 0
0043b6d2        eax_12.b = player_1->_pad_74[0x10]
0043b6da        if (eax_12.b != 0)
0043b6de        update_subgoldy_resurrect(player_1)
0043b6e3        struct Game* game = player_1->_pad_3c0[0x48].d
0043b6e9        player_2 = player_7
0043b6ea        struct TrackRowCell* eax_33 = get_track_grid_cell_at_world_position(game, player_2)
0043b6ef        void* edi = player_1->_pad_3c0[0x48].d
0043b706        int32_t eax_35 = get_track_cell_row_index(eax_33) * 0x3d
0043b710        int32_t* eax_36 = *(edi + (eax_35 << 2) + 0x5ccbb8)
0043b734        if (eax_36 s> 0 && eax_36 != player_1->_pad_74[0x174].d && eax_36 s< *(edi + 0xa874) + 1)
0043b73a        player_1->_pad_74[0x174] = eax_36.b
0043b73a        player_1->_pad_74[0x175] = eax_36:1.b
0043b73a        player_1->_pad_74[0x176] = eax_36:2.b
0043b73a        player_1->_pad_74[0x177] = eax_36:3.b
0043b75b        int32_t ecx_39
0043b75b        ecx_39.b = player_1->_pad_3c0[0x48 + 0xa670].d[*(edi + (eax_35 << 2) + 0x5ccbb8) * 0x1088].b
0043b764        if (ecx_39.b != 0)
0043b76a        player_1->_pad_74[0x178] = 2
0043b76a        player_1->_pad_74[0x179] = 0
0043b76a        player_1->_pad_74[0x17a] = 0
0043b76a        player_1->_pad_74[0x17b] = 0
0043b78f        int32_t eax_39 = *(edi + (eax_35 << 2) + 0x5ccbb8) * 0x4220 + player_1->_pad_3c0[0x48].d + 0xa670
0043b796        player_1->_pad_74[0x188] = eax_39.b
0043b796        player_1->_pad_74[0x189] = eax_39:1.b
0043b796        player_1->_pad_74[0x18a] = eax_39:2.b
0043b796        player_1->_pad_74[0x18b] = eax_39:3.b
0043b79c        player_1->_pad_74[0x17c] = 0
0043b79c        player_1->_pad_74[0x17d] = 0
0043b79c        player_1->_pad_74[0x17e] = 0
0043b79c        player_1->_pad_74[0x17f] = 0
0043b7a6        player_1->_pad_74[0x180] = 0
0043b7a6        player_1->_pad_74[0x181] = 0
0043b7a6        player_1->_pad_74[0x182] = 0xf0
0043b7a6        player_1->_pad_74[0x183] = 0x41
0043b7cb        int32_t eax_41 = *(*(edi + (eax_35 << 2) + 0x5ccbb8) * 0x4220 + player_1->_pad_3c0[0x48].d + 0xa870)
0043b7d2        player_1->_pad_74[0x184] = eax_41.b
0043b7d2        player_1->_pad_74[0x185] = eax_41:1.b
0043b7d2        player_1->_pad_74[0x186] = eax_41:2.b
0043b7d2        player_1->_pad_74[0x187] = eax_41:3.b
0043b7d8        eax_41.b = player_1->_pad_74[0xd8]
0043b7e0        if (eax_41.b == 0)
0043b7e2        player_1->_pad_74[0xd8] = 1
0043b7e9        player_2 = 0xffffffff
0043b7eb        unimplemented  {fld st0, dword [ebx]}
0043b7ed        long double temp15_1 = fconvert.t(0f)
0043b7ed        unimplemented  {fcomp st0, dword [0x497234]} f- temp15_1
0043b7ed        bool c0_9 = unimplemented  {fcomp st0, dword [0x497234]} f< temp15_1
0043b7ed        bool c2_9 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp15_1)
0043b7ed        bool c3_9 = unimplemented  {fcomp st0, dword [0x497234]} f== temp15_1
0043b7ed        unimplemented  {fcomp st0, dword [0x497234]}
0043b7fb        eax_41.w = (c0_9 ? 1 : 0) << 8 | (c2_9 ? 1 : 0) << 0xa | (c3_9 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b800        int32_t var_5c_2
0043b800        if ((eax_41:1.b & 0x41) != 0)
0043b806        var_5c_2 = 3
0043b802        var_5c_2 = 4
0043b80a        dispatch_cutscene_animation(&player_1->_pad_00[0x2984], var_5c_2, 1, player_2)
0043b80f        player_2 = 0xffffffff
0043b817        dispatch_cutscene_animation(&player_1->_pad_00[0x2984], 1, 0, player_2)
0043b837        struct Player* player_4 = *(*(edi + (eax_35 << 2) + 0x5ccbb8) * 0x4220 + player_1->_pad_3c0[0x48].d + 0xa874)
0043b841        if (player_4 != 0xffffffff)
0043b843        player_2 = player_4
0043b84d        play_voice_manager(0x751498, 0xd, 2, player_2)
0043b858        player_2 = 1
0043b866        enqueue_tip_message(data_4df904 + 0x12e6f58, &player_1->_pad_74[0x178], player_2)
0043b86b        eax_36.b = player_1->attachment_exit_pending
0043b873        if (eax_36.b == 0)
0043b879        eax_36.b = eax_33->__offset(0x3c).b
0043b882        if (eax_36.b == 0x1d || eax_36.b == 0x1e)
0043b884        eax_36.b = player_1->follow_state.active
0043b88c        if (eax_36.b == 0)
0043b892        player_2 = player_1
0043b89b        begin_track_attachment_follow_state(&player_1->follow_state, eax_33, player_7, player_2)
0043b8aa        if (player_1->follow_state.template_record[0xe] == 0x18)
0043b8ac        player_2 = 0xffffffff
0043b8b7        play_voice_manager(0x751498, 0xc, 0, player_2)
0043b8bc        eax_36.b = player_1->_pad_74[0x264]
0043b8c4        int16_t top_13
0043b8c4        if (eax_36.b == 0)
0043b91b        unimplemented  {fild st0, dword [ecx+0x50]}
0043b91e        long double temp11_1 = fconvert.t(player_1->position.z)
0043b91e        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp11_1
0043b91e        bool c0_12 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp11_1
0043b91e        bool c2_12 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp11_1)
0043b91e        bool c3_12 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp11_1
0043b91e        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043b921        eax_36.w = (c0_12 ? 1 : 0) << 8 | (c2_12 ? 1 : 0) << 0xa | (c3_12 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b926        if ((eax_36:1.b & 0x41) == 0)
0043b928        unimplemented  {fld st0, dword [ecx+0x38]}
0043b92b        unimplemented  {fld st0, st0}
0043b92d        unimplemented  {fmul st0, st1}
0043b92f        unimplemented  {fmul st0, dword [0x4973bc]}
0043b935        unimplemented  {fadd dword [ebp+0x418]}
0043b93b        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b93b        unimplemented  {fstp dword [ebp+0x418], st0}
0043b941        unimplemented  {fstp st0, st0}
0043b941        unimplemented  {fstp st0, st0}
0043b943        unimplemented  {fld st0, dword [ebp+0x418]}
0043b949        long double temp13_1 = fconvert.t(1f)
0043b949        unimplemented  {fcomp st0, dword [0x497220]} f- temp13_1
0043b949        bool c0_13 = unimplemented  {fcomp st0, dword [0x497220]} f< temp13_1
0043b949        bool c2_13 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp13_1)
0043b949        bool c3_13 = unimplemented  {fcomp st0, dword [0x497220]} f== temp13_1
0043b949        unimplemented  {fcomp st0, dword [0x497220]}
0043b949        top_13 = top_1
0043b94f        eax_36.w = (c0_13 ? 1 : 0) << 8 | (c2_13 ? 1 : 0) << 0xa | (c3_13 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043b954        if ((eax_36:1.b & 0x41) == 0)
0043b956        player_1->_pad_3c0[0x58] = 0
0043b956        player_1->_pad_3c0[0x59] = 0
0043b956        player_1->_pad_3c0[0x5a] = 0x80
0043b956        player_1->_pad_3c0[0x5b] = 0x3f
0043b967        if (player_1->_pad_74[0xac].d == 2)
0043b967        goto label_43b969
0043b8c6        unimplemented  {fld st0, dword [ebp+0x418]}
0043b8cc        long double temp12_1 = fconvert.t(0f)
0043b8cc        unimplemented  {fcomp st0, dword [0x497234]} f- temp12_1
0043b8cc        bool c0_10 = unimplemented  {fcomp st0, dword [0x497234]} f< temp12_1
0043b8cc        bool c2_10 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp12_1)
0043b8cc        bool c3_10 = unimplemented  {fcomp st0, dword [0x497234]} f== temp12_1
0043b8cc        unimplemented  {fcomp st0, dword [0x497234]}
0043b8d2        eax_36.w = (c0_10 ? 1 : 0) << 8 | (c2_10 ? 1 : 0) << 0xa | (c3_10 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b8d7        if ((eax_36:1.b & 1) != 0)
0043b8df        unimplemented  {fld st0, dword [ecx+0x38]}
0043b8e2        unimplemented  {fld st0, st0}
0043b8e4        unimplemented  {fmul st0, st1}
0043b8e6        unimplemented  {fmul st0, dword [0x4973bc]}
0043b8ec        unimplemented  {fmul st0, dword [0x49744c]}
0043b8f2        unimplemented  {fadd dword [ebp+0x418]}
0043b8f8        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b8f8        unimplemented  {fstp dword [ebp+0x418], st0}
0043b8fe        unimplemented  {fstp st0, st0}
0043b8fe        unimplemented  {fstp st0, st0}
0043b900        unimplemented  {fld st0, dword [ebp+0x418]}
0043b906        long double temp14_1 = fconvert.t(0f)
0043b906        unimplemented  {fcomp st0, dword [0x497234]} f- temp14_1
0043b906        bool c0_11 = unimplemented  {fcomp st0, dword [0x497234]} f< temp14_1
0043b906        bool c2_11 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp14_1)
0043b906        bool c3_11 = unimplemented  {fcomp st0, dword [0x497234]} f== temp14_1
0043b906        unimplemented  {fcomp st0, dword [0x497234]}
0043b906        top_13 = top_1
0043b90c        eax_36.w = (c0_11 ? 1 : 0) << 8 | (c2_11 ? 1 : 0) << 0xa | (c3_11 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043b911        if ((eax_36:1.b & 0x41) == 0)
0043b969        label_43b969:
0043b969        player_1->_pad_3c0[0x58] = 0
0043b969        player_1->_pad_3c0[0x59] = 0
0043b969        player_1->_pad_3c0[0x5a] = 0
0043b969        player_1->_pad_3c0[0x5b] = 0
0043b973        eax_36.b = player_1->follow_state.active
0043b981        if (eax_36.b != 1)
0043bac4        unimplemented  {fld st0, dword [ebp+0x410]}
0043baca        unimplemented  {fadd dword [ebx]}
0043bacc        player_7->x = fconvert.s(unimplemented  {fstp dword [ebx], st0})
0043bacc        unimplemented  {fstp dword [ebx], st0}
0043bace        unimplemented  {fld st0, dword [ebp+0x414]}
0043bad4        unimplemented  {fadd dword [ebx+0x4]}
0043bad7        player_7->y = fconvert.s(unimplemented  {fstp dword [ebx+0x4], st0})
0043bad7        unimplemented  {fstp dword [ebx+0x4], st0}
0043bada        unimplemented  {fld st0, dword [ebp+0x418]}
0043bae0        unimplemented  {fadd dword [ebx+0x8]}
0043bae3        player_7->z = fconvert.s(unimplemented  {fstp dword [ebx+0x8], st0})
0043bae3        unimplemented  {fstp dword [ebx+0x8], st0}
0043bae6        unimplemented  {fld st0, dword [ebx]}
0043bae8        long double temp16_1 = fconvert.t(-4f)
0043bae8        unimplemented  {fcomp st0, dword [0x497420]} f- temp16_1
0043bae8        bool c0_16 = unimplemented  {fcomp st0, dword [0x497420]} f< temp16_1
0043bae8        bool c2_16 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp16_1)
0043bae8        bool c3_16 = unimplemented  {fcomp st0, dword [0x497420]} f== temp16_1
0043bae8        unimplemented  {fcomp st0, dword [0x497420]}
0043baee        eax_36.w = (c0_16 ? 1 : 0) << 8 | (c2_16 ? 1 : 0) << 0xa | (c3_16 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043baf3        if ((eax_36:1.b & 1) != 0)
0043baf5        player_7->x = 0xc0800000
0043bafb        player_1->_pad_3c0[0x50] = 0
0043bafb        player_1->_pad_3c0[0x51] = 0
0043bafb        player_1->_pad_3c0[0x52] = 0
0043bafb        player_1->_pad_3c0[0x53] = 0
0043bb05        unimplemented  {fld st0, dword [ebx]}
0043bb07        long double temp17_1 = fconvert.t(4f)
0043bb07        unimplemented  {fcomp st0, dword [0x497210]} f- temp17_1
0043bb07        bool c0_17 = unimplemented  {fcomp st0, dword [0x497210]} f< temp17_1
0043bb07        bool c2_17 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp17_1)
0043bb07        bool c3_17 = unimplemented  {fcomp st0, dword [0x497210]} f== temp17_1
0043bb07        unimplemented  {fcomp st0, dword [0x497210]}
0043bb0d        eax_36.w = (c0_17 ? 1 : 0) << 8 | (c2_17 ? 1 : 0) << 0xa | (c3_17 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043bb12        if ((eax_36:1.b & 0x41) == 0)
0043bb14        player_7->x = 0x40800000
0043bb1a        player_1->_pad_3c0[0x50] = 0
0043bb1a        player_1->_pad_3c0[0x51] = 0
0043bb1a        player_1->_pad_3c0[0x52] = 0
0043bb1a        player_1->_pad_3c0[0x53] = 0
0043bb24        eax_36.b = player_1->_pad_430[0x10]
0043bb2c        if (eax_36.b == 0)
0043bb32        struct Game* game_1 = player_1->_pad_3c0[0x48].d
0043bb38        player_2 = player_7
0043bb42        if (get_track_grid_cell_at_world_position(game_1, player_2)->__offset(0x3c).b == 0xf)
0043bb9a        label_43bb9a:
0043bb9a        player_1->_pad_3c0[0x48]
0043bba0        unimplemented  {fld st0, dword [eax+0x38]}
0043bba3        unimplemented  {fld st0, st0}
0043bba5        unimplemented  {fmul st0, st1}
0043bba7        unimplemented  {fmul st0, dword [0x4973bc]}
0043bbad        unimplemented  {fadd st0, st0}
0043bbaf        unimplemented  {fadd dword [ebp+0x418]}
0043bbb5        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bbb5        unimplemented  {fstp dword [ebp+0x418], st0}
0043bbc1        unimplemented  {fstp st0, st0}
0043bbc1        unimplemented  {fstp st0, st0}
0043bbc3        unimplemented  {fild st0, dword [ecx+0x50]}
0043bbc6        long double temp20_1 = fconvert.t(player_1->position.z)
0043bbc6        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp20_1
0043bbc6        bool c0_18 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp20_1
0043bbc6        bool c2_18 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp20_1)
0043bbc6        bool c3_18 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp20_1
0043bbc6        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043bbc9        eax_36.w = (c0_18 ? 1 : 0) << 8 | (c2_18 ? 1 : 0) << 0xa | (c3_18 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043bbce        if ((eax_36:1.b & 0x41) != 0)
0043bbd0        unimplemented  {fld st0, dword [ebp+0x70]}
0043bbd3        long double temp23_1 = fconvert.t(player_1->_pad_430[0x2308].d)
0043bbd3        unimplemented  {fcomp st0, dword [ebp+0x2738]} f- temp23_1
0043bbd3        bool c0_19 = unimplemented  {fcomp st0, dword [ebp+0x2738]} f< temp23_1
0043bbd3        bool c2_19 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x2738]}, temp23_1)
0043bbd3        bool c3_19 = unimplemented  {fcomp st0, dword [ebp+0x2738]} f== temp23_1
0043bbd3        unimplemented  {fcomp st0, dword [ebp+0x2738]}
0043bbd9        eax_36.w = (c0_19 ? 1 : 0) << 8 | (c2_19 ? 1 : 0) << 0xa | (c3_19 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043bbde        if ((eax_36:1.b & 0x41) == 0)
0043bbe0        unimplemented  {fld st0, dword [ebp+0x70]}
0043bbe3        unimplemented  {fadd dword [0x497220]}
0043bbe9        player_1->_pad_430[0x2308].d = fconvert.s(unimplemented  {fstp dword [ebp+0x2738], st0})
0043bbe9        unimplemented  {fstp dword [ebp+0x2738], st0}
0043bb44        struct Game* game_2 = player_1->_pad_3c0[0x48].d
0043bb4a        player_2 = player_7
0043bb54        if (get_track_grid_cell_at_world_position(game_2, player_2)->__offset(0x3c).b == 0x10)
0043bb54        goto label_43bb9a
0043bb56        struct Game* game_3 = player_1->_pad_3c0[0x48].d
0043bb5c        player_2 = player_7
0043bb66        if (get_track_grid_cell_at_world_position(game_3, player_2)->__offset(0x3c).b == 0x12)
0043bb66        goto label_43bb9a
0043bb68        struct Game* game_4 = player_1->_pad_3c0[0x48].d
0043bb6e        player_2 = player_7
0043bb78        if (get_track_grid_cell_at_world_position(game_4, player_2)[0xf].b == 0x13)
0043bb78        goto label_43bb9a
0043bb81        if (player_1->_pad_3c0[4].d == 2)
0043bb83        struct Game* game_5 = player_1->_pad_3c0[0x48].d
0043bb89        player_2 = player_7
0043bb98        if (is_slide_cache_tile_family(get_track_grid_cell_at_world_position(game_5, player_2)).b != 0)
0043bb98        goto label_43bb9a
0043bbf6        if (player_1->_pad_430[0x232c].d == 1)
0043bbfe        unimplemented  {fld st0, dword [edx+0x38]}
0043bc01        unimplemented  {fld st0, st0}
0043bc03        unimplemented  {fmul st0, st1}
0043bc05        unimplemented  {fmul st0, dword [0x4973bc]}
0043bc0b        unimplemented  {fadd st0, st0}
0043bc0d        unimplemented  {fadd dword [ebp+0x418]}
0043bc13        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bc13        unimplemented  {fstp dword [ebp+0x418], st0}
0043bc19        unimplemented  {fstp st0, st0}
0043bc19        unimplemented  {fstp st0, st0}
0043bc1b        eax_36.b = player_1->_pad_74[0x170]
0043bc23        if (eax_36.b == 0)
0043bc25        player_1->_pad_3c0[0x48]
0043bc2b        unimplemented  {fld st0, dword [eax+0x38]}
0043bc2e        unimplemented  {fmul st0, dword [0x4975d0]}
0043bc34        unimplemented  {fsubr st0, dword [0x497220]}
0043bc3a        unimplemented  {fmul st0, dword [ebp+0x418]}
0043bc40        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bc40        unimplemented  {fstp dword [ebp+0x418], st0}
0043bc4c        unimplemented  {fld st0, dword [ecx+0x38]}
0043bc4f        unimplemented  {fmul st0, dword [0x4975d0]}
0043bc55        unimplemented  {fsubr st0, dword [0x497220]}
0043bc5b        unimplemented  {fmul st0, dword [ebp+0x414]}
0043bc61        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043bc61        unimplemented  {fstp dword [ebp+0x414], st0}
0043bc6d        unimplemented  {fld st0, dword [edx+0x38]}
0043bc70        unimplemented  {fmul st0, dword [0x497258]}
0043bc76        unimplemented  {fsubr st0, dword [0x497220]}
0043bc7c        unimplemented  {fmul st0, dword [ebp+0x410]}
0043bc82        player_1->_pad_3c0[0x50].d = fconvert.s(unimplemented  {fstp dword [ebp+0x410], st0})
0043bc82        unimplemented  {fstp dword [ebp+0x410], st0}
0043bc82        int16_t top_66 = top_13
0043bc88        eax_36.b = player_1->_pad_3c0[0x5c]
0043bc90        int32_t cell_1
0043bc90        if (eax_36.b == 0)
0043bcc1        struct Game* game_6 = player_1->_pad_3c0[0x48].d
0043bcc7        player_2 = player_7
0043bcc8        int16_t x87control_1
0043bcc8        cell_1, x87control_1 = get_track_grid_cell_at_world_position(game_6, player_2)
0043bccd        struct TrackRowCell* cell = cell_1
0043bccf        cell_1.b = player_1->attachment_exit_pending
0043bcd7        if (cell_1.b != 0)
0043bd07        if (((*(player_1->_pad_3c0[0x48].d + get_track_cell_row_index(cell) * 0xf4 + 0x5ccac8)).w:1.b & 1) == 0 && player_1->_pad_430[0x232c].d == 0)
0043bd09        int32_t eax_53
0043bd09        eax_53.b = player_1->_pad_74[0x264]
0043bd11        if (eax_53.b == 0)
0043bd13        unimplemented  {fld st0, dword [edi+0x38]}
0043bd16        unimplemented  {fmul st0, dword [0x497270]}
0043bd1c        unimplemented  {fsubr st0, dword [0x497220]}
0043bd22        unimplemented  {fmul st0, dword [ebp+0x418]}
0043bd28        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bd28        unimplemented  {fstp dword [ebp+0x418], st0}
0043bd30        int32_t eax_54 = get_track_cell_row_index(cell)
0043bd4c        if ((*(player_1->_pad_3c0[0x48].d + eax_54 * 0xf4 + 0x5ccac8) & 0x40) != 0)
0043bd52        unimplemented  {fld st0, dword [ebp+0x410]}
0043bd58        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd60        float var_3c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043bd60        unimplemented  {fstp dword [esp+0x14], st0}
0043bd64        unimplemented  {fld st0, dword [ebp+0x414]}
0043bd6a        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd70        float var_38_1 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043bd70        unimplemented  {fstp dword [esp+0x18], st0}
0043bd74        unimplemented  {fld st0, dword [ebp+0x418]}
0043bd7a        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd80        float var_34_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043bd80        unimplemented  {fstp dword [esp+0x1c], st0}
0043bd84        int32_t eax_55 = get_track_cell_row_index(cell)
0043bda3        player_2 = *(player_1->_pad_3c0[0x48].d + eax_55 * 0xf4 + 0x5ccb6c)
0043bdb9        int32_t* player_8 = player_7
0043bdbe        float eax_59 = *player_8
0043bdc4        float eax_60 = player_8[1]
0043bdc7        float ecx_77 = player_8[2]
0043bdd2        int32_t eax_61 = get_track_cell_row_index(cell)
0043bdf0        cell_1, x87control_1 = try_enter_track_attachment_from_swept_motion(*(*(player_1->_pad_3c0[0x48].d + eax_61 * 0xf4 + 0x5ccb6c) + 0x38), eax_59, eax_60, ecx_77, var_3c_1, var_38_1, var_34_1, player_2)
0043bdf5        cell_1.b = player_1->attachment_exit_pending
0043bdfd        if (cell_1.b != 0)
0043be05        int32_t eax_63 = get_track_cell_row_index(cell)
0043be21        if ((*(player_1->_pad_3c0[0x48].d + eax_63 * 0xf4 + 0x5ccac8) & 0x80) != 0)
0043be27        unimplemented  {fld st0, dword [ebp+0x410]}
0043be2d        unimplemented  {fmul st0, dword [0x4975c8]}
0043be35        float var_3c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043be35        unimplemented  {fstp dword [esp+0x14], st0}
0043be39        unimplemented  {fld st0, dword [ebp+0x414]}
0043be3f        unimplemented  {fmul st0, dword [0x4975c8]}
0043be45        float var_38_2 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043be45        unimplemented  {fstp dword [esp+0x18], st0}
0043be49        unimplemented  {fld st0, dword [ebp+0x418]}
0043be4f        unimplemented  {fmul st0, dword [0x4975c8]}
0043be55        float var_34_2 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043be55        unimplemented  {fstp dword [esp+0x1c], st0}
0043be59        int32_t eax_64 = get_track_cell_row_index(cell)
0043be78        player_2 = *(player_1->_pad_3c0[0x48].d + eax_64 * 0xf4 + 0x5ccb70)
0043be93        float x = player_7->x
0043be99        float y_1 = player_7->y
0043be9c        float z_1 = player_7->z
0043bea7        int32_t eax_68 = get_track_cell_row_index(cell)
0043bec5        cell_1, x87control_1 = try_enter_track_attachment_from_swept_motion(*(*(player_1->_pad_3c0[0x48].d + eax_68 * 0xf4 + 0x5ccb70) + 0x38), x, y_1, z_1, var_3c_2, var_38_2, var_34_2, player_2)
0043beca        cell_1.b = player_1->follow_state.active
0043bed2        if (cell_1.b == 0)
0043bed8        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bedb        long double temp30_1 = fconvert.t(0.49000001f)
0043bedb        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp30_1
0043bedb        bool c0_20 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp30_1
0043bedb        bool c2_20 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp30_1)
0043bedb        bool c3_20 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp30_1
0043bedb        unimplemented  {fcomp st0, dword [0x4973e8]}
0043bedb        int16_t top_82 = top_66
0043bee6        cell_1.w = (c0_20 ? 1 : 0) << 8 | (c2_20 ? 1 : 0) << 0xa | (c3_20 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043beeb        if ((cell_1:1.b & 1) != 0)
0043bef1        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bef4        long double temp32_1 = fconvert.t(-0.163333341f)
0043bef4        unimplemented  {fcomp st0, dword [0x4975c4]} f- temp32_1
0043bef4        bool c0_21 = unimplemented  {fcomp st0, dword [0x4975c4]} f< temp32_1
0043bef4        bool c2_21 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975c4]}, temp32_1)
0043bef4        bool c3_21 = unimplemented  {fcomp st0, dword [0x4975c4]} f== temp32_1
0043bef4        unimplemented  {fcomp st0, dword [0x4975c4]}
0043befa        cell_1.w = (c0_21 ? 1 : 0) << 8 | (c2_21 ? 1 : 0) << 0xa | (c3_21 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043beff        if ((cell_1:1.b & 0x41) == 0 && is_open_neighbor_tile_family(cell).b == 0 && cell->__offset(0x3c).b != 0x16)
0043bf15        set_matrix_rotation_identity(&player_1->_pad_00[0x38])
0043bf1a        player_1->_pad_74[0x170] = 0
0043bf21        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf27        long double temp44_1 = fconvert.t(-0.0299999993f)
0043bf27        unimplemented  {fcomp st0, dword [0x4975c0]} f- temp44_1
0043bf27        bool c0_22 = unimplemented  {fcomp st0, dword [0x4975c0]} f< temp44_1
0043bf27        bool c2_22 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975c0]}, temp44_1)
0043bf27        bool c3_22 = unimplemented  {fcomp st0, dword [0x4975c0]} f== temp44_1
0043bf27        unimplemented  {fcomp st0, dword [0x4975c0]}
0043bf2d        cell_1.w = (c0_22 ? 1 : 0) << 8 | (c2_22 ? 1 : 0) << 0xa | (c3_22 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bf32        if ((cell_1:1.b & 1) != 0)
0043bf34        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf3a        unimplemented  {fsub st0, dword [0x497548]}
0043bf40        player_2 = &player_1->_pad_00[0x38]
0043bf47        player_2 = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043bf47        unimplemented  {fstp dword [esp], st0}
0043bf4a        start_squidge_y(&player_1->_pad_00[0x4344], player_2)
0043bf4f        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf55        long double temp49_1 = fconvert.t(0f)
0043bf55        unimplemented  {fcomp st0, dword [0x497234]} f- temp49_1
0043bf55        bool c0_23 = unimplemented  {fcomp st0, dword [0x497234]} f< temp49_1
0043bf55        bool c2_23 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp49_1)
0043bf55        bool c3_23 = unimplemented  {fcomp st0, dword [0x497234]} f== temp49_1
0043bf55        unimplemented  {fcomp st0, dword [0x497234]}
0043bf55        top_82 = top_82
0043bf5b        cell_1.w = (c0_23 ? 1 : 0) << 8 | (c2_23 ? 1 : 0) << 0xa | (c3_23 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bf60        if ((cell_1:1.b & 0x41) != 0)
0043bf62        player_1->position.y = 0.49000001f
0043bf65        player_1->_pad_3c0[0x54] = 0
0043bf65        player_1->_pad_3c0[0x55] = 0
0043bf65        player_1->_pad_3c0[0x56] = 0
0043bf65        player_1->_pad_3c0[0x57] = 0
0043bf6f        player_1->attachment_exit_pending = 0
0043bf76        cell_1.b = cell->__offset(0x3c).b
0043bf7f        if (cell_1.b == 0 || cell_1.b == 0x23)
0043bf85        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bf88        long double temp35_1 = fconvert.t(0.49000001f)
0043bf88        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp35_1
0043bf88        bool c0_24 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp35_1
0043bf88        bool c2_24 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp35_1)
0043bf88        bool c3_24 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp35_1
0043bf88        unimplemented  {fcomp st0, dword [0x4973e8]}
0043bf8e        cell_1.w = (c0_24 ? 1 : 0) << 8 | (c2_24 ? 1 : 0) << 0xa | (c3_24 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bf93        if ((cell_1:1.b & 1) != 0)
0043bf95        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf9b        long double temp40_1 = fconvert.t(0f)
0043bf9b        unimplemented  {fcomp st0, dword [0x497234]} f- temp40_1
0043bf9b        bool c0_25 = unimplemented  {fcomp st0, dword [0x497234]} f< temp40_1
0043bf9b        bool c2_25 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp40_1)
0043bf9b        bool c3_25 = unimplemented  {fcomp st0, dword [0x497234]} f== temp40_1
0043bf9b        unimplemented  {fcomp st0, dword [0x497234]}
0043bfa1        cell_1.w = (c0_25 ? 1 : 0) << 8 | (c2_25 ? 1 : 0) << 0xa | (c3_25 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bfa6        if ((cell_1:1.b & 0x41) != 0)
0043bfa8        unimplemented  {fld st0, dword [ebp+0x70]}
0043bfb0        int32_t var_40_3 = __ftol(x87control_1, st0_1)
0043bfb4        int32_t eax_70
0043bfb4        eax_70.b = cell->__offset(0x3d).b
0043bfb7        unimplemented  {fild st0, dword [esp+0x10]}
0043bfbd        unimplemented  {fsubr st0, dword [ebp+0x70]}
0043bfc0        int16_t top_93
0043bfc0        if ((eax_70.b & 2) != 0)
0043bfca        top_93 = top_82 - 2
0043bfca        unimplemented  {fld st0, dword [0x497250]}
0043bfc2        top_93 = top_82 - 2
0043bfc2        unimplemented  {fld st0, dword [0x497220]}
0043bfd2        float var_40_4 = 0f
0043bfda        if ((eax_70.b & 1) != 0)
0043bfdc        var_40_4 = 0.200000003f
0043bfe4        unimplemented  {fld st0, st1}
0043bfe6        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043bfe6        bool c0_26 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043bfe6        bool c2_26 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043bfe6        bool c3_26 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043bfe6        unimplemented  {fcomp st0, st1}
0043bfe8        eax_70.w = (c0_26 ? 1 : 0) << 8 | (c2_26 ? 1 : 0) << 0xa | (c3_26 ? 1 : 0) << 0xe | (top_93 & 7) << 0xb
0043bfed        unimplemented  {fstp st0, st0}
0043bfed        unimplemented  {fstp st0, st0}
0043bfef        if ((eax_70:1.b & 1) == 0)
0043c00f        unimplemented  {fstp st0, st0}
0043c00f        unimplemented  {fstp st0, st0}
0043c00f        top_82 = top_93 + 2
0043bff1        long double temp56_1 = fconvert.t(var_40_4)
0043bff1        unimplemented  {fcomp st0, dword [esp+0x10]} f- temp56_1
0043bff1        bool c0_27 = unimplemented  {fcomp st0, dword [esp+0x10]} f< temp56_1
0043bff1        bool c2_27 = is_unordered.t(unimplemented  {fcomp st0, dword [esp+0x10]}, temp56_1)
0043bff1        bool c3_27 = unimplemented  {fcomp st0, dword [esp+0x10]} f== temp56_1
0043bff1        unimplemented  {fcomp st0, dword [esp+0x10]}
0043bff1        top_82 = top_93 + 2
0043bff5        eax_70.w = (c0_27 ? 1 : 0) << 8 | (c2_27 ? 1 : 0) << 0xa | (c3_27 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bffa        if ((eax_70:1.b & 0x41) == 0)
0043bffc        eax_70.b = player_1->attachment_exit_pending
0043c004        if (eax_70.b == 0)
0043c008        initialize_subgoldy_fall_state(player_1)
0043c011        struct Game* game_7 = player_1->_pad_3c0[0x48].d
0043c01b        if (game_7->__offset(0x40).d == 3)
0043c01d        player_2 = player_7
0043c01e        get_track_grid_cell_at_world_position(game_7, player_2)
0043c038        if (((*(player_1->_pad_3c0[0x48].d + 0x4c)).w:1.b & 4) == 0 || (data_4b2f40 & 2) != 0)
0043c03a        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c03d        long double temp48_1 = fconvert.t(0.49000001f)
0043c03d        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp48_1
0043c03d        bool c0_28 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp48_1
0043c03d        bool c2_28 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp48_1)
0043c03d        bool c3_28 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp48_1
0043c03d        unimplemented  {fcomp st0, dword [0x4973e8]}
0043c043        cell_1.w = (c0_28 ? 1 : 0) << 8 | (c2_28 ? 1 : 0) << 0xa | (c3_28 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043c048        if ((cell_1:1.b & 1) != 0)
0043c050        player_2 = player_1->_pad_3c0[0x54].d
0043c057        start_squidge_y(&player_1->_pad_00[0x4344], player_2)
0043c05c        player_1->_pad_74[0x170] = 0
0043c063        player_1->_pad_3c0[0x54] = 0
0043c063        player_1->_pad_3c0[0x55] = 0
0043c063        player_1->_pad_3c0[0x56] = 0
0043c063        player_1->_pad_3c0[0x57] = 0
0043c06d        player_1->attachment_exit_pending = 0
0043c074        player_1->position.y = 0.49000001f
0043c077        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c07a        long double temp51_1 = fconvert.t(-7f)
0043c07a        unimplemented  {fcomp st0, dword [0x4975bc]} f- temp51_1
0043c07a        bool c0_29 = unimplemented  {fcomp st0, dword [0x4975bc]} f< temp51_1
0043c07a        bool c2_29 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975bc]}, temp51_1)
0043c07a        bool c3_29 = unimplemented  {fcomp st0, dword [0x4975bc]} f== temp51_1
0043c07a        unimplemented  {fcomp st0, dword [0x4975bc]}
0043c07a        top_66 = top_82
0043c080        cell_1.w = (c0_29 ? 1 : 0) << 8 | (c2_29 ? 1 : 0) << 0xa | (c3_29 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c085        if ((cell_1:1.b & 1) != 0)
0043c087        cell_1.b = player_1->_pad_74[0x10]
0043c08f        if (cell_1.b == 0)
0043c093        initialize_subgoldy_death(player_1)
0043bc92        player_1->_pad_3c0[0x48]
0043bc98        unimplemented  {fld st0, dword [eax+0x38]}
0043bc9b        unimplemented  {fld st0, st0}
0043bc9d        unimplemented  {fmul st0, st1}
0043bc9f        unimplemented  {fmul st0, dword [0x4973bc]}
0043bca5        unimplemented  {fadd st0, st0}
0043bca7        unimplemented  {fadd dword [ebp+0x418]}
0043bcad        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bcad        unimplemented  {fstp dword [ebp+0x418], st0}
0043bcb3        player_1->attachment_exit_pending = 0
0043bcba        unimplemented  {fstp st0, st0}
0043bcba        unimplemented  {fstp st0, st0}
0043c098        unimplemented  {fld st0, dword [ebp+0x1dc]}
0043c09e        long double temp29_1 = fconvert.t(0f)
0043c09e        unimplemented  {fcomp st0, dword [0x497234]} f- temp29_1
0043c09e        bool c0_30 = unimplemented  {fcomp st0, dword [0x497234]} f< temp29_1
0043c09e        bool c2_30 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp29_1)
0043c09e        bool c3_30 = unimplemented  {fcomp st0, dword [0x497234]} f== temp29_1
0043c09e        unimplemented  {fcomp st0, dword [0x497234]}
0043c0a4        cell_1.w = (c0_30 ? 1 : 0) << 8 | (c2_30 ? 1 : 0) << 0xa | (c3_30 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c0a9        if ((cell_1:1.b & 0x40) == 0)
0043c0ab        unimplemented  {fld st0, dword [ebp+0x1e0]}
0043c0b1        unimplemented  {fadd dword [ebp+0x1dc]}
0043c0b7        player_1->_pad_74[0x168].d = fconvert.s(unimplemented  {fst dword [ebp+0x1dc], st0})
0043c0bd        long double temp31_1 = fconvert.t(1f)
0043c0bd        unimplemented  {fcomp st0, dword [0x497220]} f- temp31_1
0043c0bd        bool c0_31 = unimplemented  {fcomp st0, dword [0x497220]} f< temp31_1
0043c0bd        bool c2_31 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp31_1)
0043c0bd        bool c3_31 = unimplemented  {fcomp st0, dword [0x497220]} f== temp31_1
0043c0bd        unimplemented  {fcomp st0, dword [0x497220]}
0043c0c3        cell_1.w = (c0_31 ? 1 : 0) << 8 | (c2_31 ? 1 : 0) << 0xa | (c3_31 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c0c8        if ((cell_1:1.b & 0x41) == 0)
0043c0ca        player_1->_pad_74[0x168] = 0
0043c0ca        player_1->_pad_74[0x169] = 0
0043c0ca        player_1->_pad_74[0x16a] = 0
0043c0ca        player_1->_pad_74[0x16b] = 0
0043c0d4        cell_1.b = player_1->attachment_exit_pending
0043c0dc        if (cell_1.b != 0)
0043c35b        player_2 = player_7
0043c35c        unimplemented  {fld st0, dword [eax+0x38]}
0043c35f        unimplemented  {fld st0, st0}
0043c361        unimplemented  {fmul st0, st1}
0043c363        unimplemented  {fmul st0, dword [0x4975cc]}
0043c369        unimplemented  {fadd dword [ebp+0x414]}
0043c36f        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c36f        unimplemented  {fstp dword [ebp+0x414], st0}
0043c37b        unimplemented  {fstp st0, st0}
0043c37b        unimplemented  {fstp st0, st0}
0043c37b        top_13 = top_66
0043c388        if (get_track_grid_cell_at_world_position(player_1->_pad_3c0[0x48].d, player_2)->__offset(0x3c).b == 0x16)
0043c38a        unimplemented  {fld st0, dword [esi+0x14]}
0043c38d        unimplemented  {fadd dword [0x4973e8]}
0043c393        long double temp36_1 = fconvert.t(player_1->position.y)
0043c393        unimplemented  {fcomp st0, dword [ebp+0x6c]} f- temp36_1
0043c393        bool c0_38 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f< temp36_1
0043c393        bool c2_38 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x6c]}, temp36_1)
0043c393        bool c3_38 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f== temp36_1
0043c393        unimplemented  {fcomp st0, dword [ebp+0x6c]}
0043c396        struct TrackRowCell* eax_73
0043c396        eax_73.w = (c0_38 ? 1 : 0) << 8 | (c2_38 ? 1 : 0) << 0xa | (c3_38 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c39b        if ((eax_73:1.b & 0x41) == 0)
0043c39d        unimplemented  {fld st0, dword [esi+0x14]}
0043c3a0        unimplemented  {fsub st0, dword [0x4973e8]}
0043c3a6        long double temp41_1 = fconvert.t(player_1->position.y)
0043c3a6        unimplemented  {fcomp st0, dword [ebp+0x6c]} f- temp41_1
0043c3a6        bool c0_39 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f< temp41_1
0043c3a6        bool c2_39 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x6c]}, temp41_1)
0043c3a6        bool c3_39 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f== temp41_1
0043c3a6        unimplemented  {fcomp st0, dword [ebp+0x6c]}
0043c3a9        eax_73.w = (c0_39 ? 1 : 0) << 8 | (c2_39 ? 1 : 0) << 0xa | (c3_39 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c3ae        if ((eax_73:1.b & 1) != 0)
0043c3b6        player_2 = player_1->_pad_3c0[0x54].d
0043c3bd        start_squidge_y(&player_1->_pad_00[0x4344], player_2)
0043c3c8        player_2 = 0x29
0043c3cf        unimplemented  {fld st0, dword [edx+0x38]}
0043c3d2        unimplemented  {fmul st0, dword [0x4973d8]}
0043c3d8        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c3d8        unimplemented  {fstp dword [ebp+0x414], st0}
0043c3de        unimplemented  {fld st0, dword [esi+0x14]}
0043c3e1        unimplemented  {fadd dword [0x4973e8]}
0043c3e7        player_1->position.y = fconvert.s(unimplemented  {fstp dword [ebp+0x6c], st0})
0043c3e7        unimplemented  {fstp dword [ebp+0x6c], st0}
0043c3ea        player_1->attachment_exit_pending = 0
0043c3f1        player_1->_pad_74[0x170] = 1
0043c3f8        play_sound_effect(player_2)
0043c0e2        struct Game* game_8 = player_1->_pad_3c0[0x48].d
0043c0e8        player_2 = player_7
0043c0e9        struct TrackRowCell* eax_71
0043c0e9        st0_1, eax_71 = sample_track_floor_height_at_position(game_8, player_2)
0043c0e9        unimplemented  {call 0x43d4d0}
0043c0ee        unimplemented  {fadd dword [0x4973e8]}
0043c0f4        long double temp33_1 = fconvert.t(player_1->position.y)
0043c0f4        unimplemented  {fcom st0, dword [ebp+0x6c]} f- temp33_1
0043c0f4        bool c0_32 = unimplemented  {fcom st0, dword [ebp+0x6c]} f< temp33_1
0043c0f4        bool c2_32 = is_unordered.t(unimplemented  {fcom st0, dword [ebp+0x6c]}, temp33_1)
0043c0f4        bool c3_32 = unimplemented  {fcom st0, dword [ebp+0x6c]} f== temp33_1
0043c0f7        eax_71.w = (c0_32 ? 1 : 0) << 8 | (c2_32 ? 1 : 0) << 0xa | (c3_32 ? 1 : 0) << 0xe | ((top_66 - 1) & 7) << 0xb
0043c0fc        int16_t top_105
0043c0fc        if ((eax_71:1.b & 0x41) != 0)
0043c301        unimplemented  {fstp st0, st0}
0043c301        unimplemented  {fstp st0, st0}
0043c303        unimplemented  {fld st0, dword [edx+0x38]}
0043c306        unimplemented  {fld st0, st0}
0043c308        unimplemented  {fmul st0, st1}
0043c30a        unimplemented  {fmul st0, dword [0x4975cc]}
0043c310        unimplemented  {fadd dword [ebp+0x414]}
0043c316        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c316        unimplemented  {fstp dword [ebp+0x414], st0}
0043c31c        unimplemented  {fstp st0, st0}
0043c31c        unimplemented  {fstp st0, st0}
0043c31c        top_105 = top_66
0043c102        unimplemented  {fld st0, dword [ebp+0x414]}
0043c108        long double temp37_1 = fconvert.t(0f)
0043c108        unimplemented  {fcomp st0, dword [0x497234]} f- temp37_1
0043c108        bool c0_33 = unimplemented  {fcomp st0, dword [0x497234]} f< temp37_1
0043c108        bool c2_33 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp37_1)
0043c108        bool c3_33 = unimplemented  {fcomp st0, dword [0x497234]} f== temp37_1
0043c108        unimplemented  {fcomp st0, dword [0x497234]}
0043c10e        eax_71.w = (c0_33 ? 1 : 0) << 8 | (c2_33 ? 1 : 0) << 0xa | (c3_33 ? 1 : 0) << 0xe | ((top_66 - 1) & 7) << 0xb
0043c113        if ((eax_71:1.b & 0x41) == 0)
0043c11a        unimplemented  {fstp st0, st0}
0043c11a        unimplemented  {fstp st0, st0}
0043c11a        top_105 = top_66
0043c115        player_1->position.y = fconvert.s(unimplemented  {fstp dword [ebp+0x6c], st0})
0043c115        unimplemented  {fstp dword [ebp+0x6c], st0}
0043c115        top_105 = top_66
0043c11c        struct Game* game_9 = player_1->_pad_3c0[0x48].d
0043c122        player_2 = player_7
0043c12c        if (get_track_grid_cell_at_world_position(game_9, player_2)->__offset(0x3c).b == 8)
0043c2ea        label_43c2ea:
0043c2ea        unimplemented  {fld st0, dword [ecx+0x38]}
0043c2ed        unimplemented  {fmul st0, dword [0x4973d8]}
0043c2f3        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c2f3        unimplemented  {fstp dword [ebp+0x414], st0}
0043c132        struct Game* game_10 = player_1->_pad_3c0[0x48].d
0043c138        player_2 = player_7
0043c142        if (get_track_grid_cell_at_world_position(game_10, player_2)->__offset(0x3c).b == 9)
0043c142        goto label_43c2ea
0043c148        struct Game* game_11 = player_1->_pad_3c0[0x48].d
0043c14e        player_2 = player_7
0043c158        if (get_track_grid_cell_at_world_position(game_11, player_2)->__offset(0x3c).b == 0xa)
0043c158        goto label_43c2ea
0043c15e        struct Game* game_12 = player_1->_pad_3c0[0x48].d
0043c164        player_2 = player_7
0043c16e        if (get_track_grid_cell_at_world_position(game_12, player_2)->__offset(0x3c).b == 0xb)
0043c16e        goto label_43c2ea
0043c174        struct Game* game_13 = player_1->_pad_3c0[0x48].d
0043c17a        player_2 = player_7
0043c184        if (get_track_grid_cell_at_world_position(game_13, player_2)->__offset(0x3c).b == 0xc)
0043c184        goto label_43c2ea
0043c18a        struct Game* game_14 = player_1->_pad_3c0[0x48].d
0043c190        player_2 = player_7
0043c19a        if (get_track_grid_cell_at_world_position(game_14, player_2)->__offset(0x3c).b == 0xd)
0043c19a        goto label_43c2ea
0043c1a0        struct Game* game_15 = player_1->_pad_3c0[0x48].d
0043c1a6        player_2 = player_7
0043c1b0        if (get_track_grid_cell_at_world_position(game_15, player_2)->__offset(0x3c).b == 2)
0043c271        label_43c271:
0043c271        unimplemented  {fld st0, dword [ebp+0x1dc]}
0043c277        long double temp58_1 = fconvert.t(0f)
0043c277        unimplemented  {fcomp st0, dword [0x497234]} f- temp58_1
0043c277        bool c0_34 = unimplemented  {fcomp st0, dword [0x497234]} f< temp58_1
0043c277        bool c2_34 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp58_1)
0043c277        bool c3_34 = unimplemented  {fcomp st0, dword [0x497234]} f== temp58_1
0043c277        unimplemented  {fcomp st0, dword [0x497234]}
0043c27d        struct TrackRowCell* eax_72
0043c27d        eax_72.w = (c0_34 ? 1 : 0) << 8 | (c2_34 ? 1 : 0) << 0xa | (c3_34 ? 1 : 0) << 0xe | (top_105 & 7) << 0xb
0043c282        if ((eax_72:1.b & 0x40) != 0)
0043c284        int32_t edx_35 = player_1->_pad_74[0x16c].d
0043c28a        player_1->_pad_74[0x168] = edx_35.b
0043c28a        player_1->_pad_74[0x169] = edx_35:1.b
0043c28a        player_1->_pad_74[0x16a] = edx_35:2.b
0043c28a        player_1->_pad_74[0x16b] = edx_35:3.b
0043c290        player_1->_pad_3c0[0x48]
0043c296        unimplemented  {fld st0, dword [eax+0x38]}
0043c299        unimplemented  {fmul st0, dword [0x497270]}
0043c29f        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c29f        unimplemented  {fstp dword [ebp+0x414], st0}
0043c2a5        eax_71.b = player_1->_pad_74[0x264]
0043c2ad        if (eax_71.b == 0)
0043c2af        unimplemented  {fld st0, dword [ebx]}
0043c2b1        long double temp62_1 = fconvert.t(0f)
0043c2b1        unimplemented  {fcomp st0, dword [0x497234]} f- temp62_1
0043c2b1        bool c0_35 = unimplemented  {fcomp st0, dword [0x497234]} f< temp62_1
0043c2b1        bool c2_35 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp62_1)
0043c2b1        bool c3_35 = unimplemented  {fcomp st0, dword [0x497234]} f== temp62_1
0043c2b1        unimplemented  {fcomp st0, dword [0x497234]}
0043c2b7        player_2 = 0xffffffff
0043c2c1        eax_71.w = (c0_35 ? 1 : 0) << 8 | (c2_35 ? 1 : 0) << 0xa | (c3_35 ? 1 : 0) << 0xe | (top_105 & 7) << 0xb
0043c2c6        int32_t var_5c_7
0043c2c6        if ((eax_71:1.b & 0x41) != 0)
0043c2cc        var_5c_7 = 3
0043c2c8        var_5c_7 = 4
0043c2d0        dispatch_cutscene_animation(&player_1->_pad_00[0x2984], var_5c_7, 1, player_2)
0043c2d5        player_2 = 0xffffffff
0043c2dd        dispatch_cutscene_animation(&player_1->_pad_00[0x2984], 1, 0, player_2)
0043c1b6        struct Game* game_16 = player_1->_pad_3c0[0x48].d
0043c1bc        player_2 = player_7
0043c1c6        if (get_track_grid_cell_at_world_position(game_16, player_2)->__offset(0x3c).b == 3)
0043c1c6        goto label_43c271
0043c1cc        struct Game* game_17 = player_1->_pad_3c0[0x48].d
0043c1d2        player_2 = player_7
0043c1dc        if (get_track_grid_cell_at_world_position(game_17, player_2)->__offset(0x3c).b == 4)
0043c1dc        goto label_43c271
0043c1e2        struct Game* game_18 = player_1->_pad_3c0[0x48].d
0043c1e8        player_2 = player_7
0043c1f2        if (get_track_grid_cell_at_world_position(game_18, player_2)->__offset(0x3c).b == 5)
0043c1f2        goto label_43c271
0043c1f4        struct Game* game_19 = player_1->_pad_3c0[0x48].d
0043c1fa        player_2 = player_7
0043c204        if (get_track_grid_cell_at_world_position(game_19, player_2)->__offset(0x3c).b == 6)
0043c204        goto label_43c271
0043c206        struct Game* game_20 = player_1->_pad_3c0[0x48].d
0043c20c        player_2 = player_7
0043c216        if (get_track_grid_cell_at_world_position(game_20, player_2)->__offset(0x3c).b == 7)
0043c216        goto label_43c271
0043c218        struct Game* game_21 = player_1->_pad_3c0[0x48].d
0043c21e        player_2 = player_7
0043c229        if (get_track_grid_cell_at_world_position(game_21, player_2)->__offset(0x3c).b != 0)
0043c22f        struct Game* game_22 = player_1->_pad_3c0[0x48].d
0043c235        player_2 = player_7
0043c23f        if (get_track_grid_cell_at_world_position(game_22, player_2)->__offset(0x3c).b != 0x23)
0043c245        struct Game* game_23 = player_1->_pad_3c0[0x48].d
0043c24b        player_2 = player_7
0043c255        if (get_track_grid_cell_at_world_position(game_23, player_2)->__offset(0x3c).b != 0x16)
0043c25b        player_1->_pad_74[0x170] = 0
0043c262        player_1->_pad_3c0[0x54] = 0
0043c262        player_1->_pad_3c0[0x55] = 0
0043c262        player_1->_pad_3c0[0x56] = 0
0043c262        player_1->_pad_3c0[0x57] = 0
0043c31e        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c321        long double temp42_1 = fconvert.t(0f)
0043c321        unimplemented  {fcomp st0, dword [0x497234]} f- temp42_1
0043c321        bool c0_36 = unimplemented  {fcomp st0, dword [0x497234]} f< temp42_1
0043c321        bool c2_36 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp42_1)
0043c321        bool c3_36 = unimplemented  {fcomp st0, dword [0x497234]} f== temp42_1
0043c321        unimplemented  {fcomp st0, dword [0x497234]}
0043c321        top_13 = top_105
0043c327        eax_71.w = (c0_36 ? 1 : 0) << 8 | (c2_36 ? 1 : 0) << 0xa | (c3_36 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c32c        if ((eax_71:1.b & 1) != 0)
0043c332        unimplemented  {fld st0, dword [ebp+0x414]}
0043c338        long double temp45_1 = fconvert.t(0f)
0043c338        unimplemented  {fcomp st0, dword [0x497234]} f- temp45_1
0043c338        bool c0_37 = unimplemented  {fcomp st0, dword [0x497234]} f< temp45_1
0043c338        bool c2_37 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp45_1)
0043c338        bool c3_37 = unimplemented  {fcomp st0, dword [0x497234]} f== temp45_1
0043c338        unimplemented  {fcomp st0, dword [0x497234]}
0043c33e        eax_71.w = (c0_37 ? 1 : 0) << 8 | (c2_37 ? 1 : 0) << 0xa | (c3_37 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c343        if ((eax_71:1.b & 0x41) != 0)
0043c34b        initialize_subgoldy_fall_state(player_1)
0043b987        float path_factor = player_1->_pad_3c0[0x58].d
0043b993        player_2 = &player_1->_pad_3c0[0x50]
0043b9a6        switch (update_track_attachment_follow_state(&player_1->follow_state, path_factor, player_7, player_2))
0043b9cc        case 0
0043b9cc        if (player_1->follow_state.template_record->kind != PATH_TEMPLATE_KIND_DETOUR)
0043b9d4        unimplemented  {fld st0, dword [ecx+0x38]}
0043b9d7        unimplemented  {fld st0, st0}
0043b9d9        unimplemented  {fmul st0, st1}
0043b9db        unimplemented  {fmul st0, dword [0x4973bc]}
0043b9e1        unimplemented  {fadd st0, st0}
0043b9e3        unimplemented  {fadd dword [ebp+0x418]}
0043b9e9        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b9e9        unimplemented  {fstp dword [ebp+0x418], st0}
0043b9ef        unimplemented  {fstp st0, st0}
0043b9ef        unimplemented  {fstp st0, st0}
0043b9cc        goto label_43b9f1
0043b9b0        case 1, 3
0043b9b0        if (player_1->follow_state.active == 1)
0043b9b8        initialize_subgoldy_fall_state(player_1)
0043b9f1        case 2
0043b9f1        label_43b9f1:
0043b9f1        unimplemented  {fld st0, dword [ebx]}
0043b9f3        unimplemented  {fadd dword [esi]}
0043b9f5        player_7->x = fconvert.s(unimplemented  {fstp dword [ebx], st0})
0043b9f5        unimplemented  {fstp dword [ebx], st0}
0043b9f7        unimplemented  {fld st0, dword [esi+0x4]}
0043b9fa        unimplemented  {fadd dword [ebx+0x4]}
0043b9fd        player_7->y = fconvert.s(unimplemented  {fstp dword [ebx+0x4], st0})
0043b9fd        unimplemented  {fstp dword [ebx+0x4], st0}
0043ba00        unimplemented  {fld st0, dword [esi+0x8]}
0043ba03        unimplemented  {fadd dword [ebx+0x8]}
0043ba06        player_7->z = fconvert.s(unimplemented  {fstp dword [ebx+0x8], st0})
0043ba06        unimplemented  {fstp dword [ebx+0x8], st0}
0043ba0f        unimplemented  {fld st0, dword [edx+0x38]}
0043ba12        unimplemented  {fmul st0, dword [0x4975d0]}
0043ba18        unimplemented  {fsubr st0, dword [0x497220]}
0043ba1e        unimplemented  {fmul st0, dword [ebp+0x418]}
0043ba24        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043ba24        unimplemented  {fstp dword [ebp+0x418], st0}
0043ba30        unimplemented  {fld st0, dword [eax+0x38]}
0043ba33        unimplemented  {fmul st0, dword [0x4975d0]}
0043ba39        unimplemented  {fsubr st0, dword [0x497220]}
0043ba3f        unimplemented  {fmul st0, dword [ebp+0x414]}
0043ba45        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ba45        unimplemented  {fstp dword [ebp+0x414], st0}
0043ba51        unimplemented  {fld st0, dword [ecx+0x38]}
0043ba54        unimplemented  {fmul st0, dword [0x497258]}
0043ba5a        unimplemented  {fsubr st0, dword [0x497220]}
0043ba60        unimplemented  {fmul st0, dword [esi]}
0043ba62        player_1->_pad_3c0[0x50].d = fconvert.s(unimplemented  {fstp dword [esi], st0})
0043ba62        unimplemented  {fstp dword [esi], st0}
0043ba6a        unimplemented  {fld st0, dword [edx+0x38]}
0043ba6d        unimplemented  {fld st0, st0}
0043ba6f        unimplemented  {fmul st0, st1}
0043ba71        unimplemented  {fmul st0, dword [0x4975cc]}
0043ba77        unimplemented  {fadd dword [ebp+0x414]}
0043ba7d        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ba7d        unimplemented  {fstp dword [ebp+0x414], st0}
0043ba83        unimplemented  {fstp st0, st0}
0043ba83        unimplemented  {fstp st0, st0}
0043ba85        unimplemented  {fld st0, dword [ebx]}
0043ba87        long double temp18_1 = fconvert.t(-4f)
0043ba87        unimplemented  {fcomp st0, dword [0x497420]} f- temp18_1
0043ba87        bool c0_14 = unimplemented  {fcomp st0, dword [0x497420]} f< temp18_1
0043ba87        bool c2_14 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp18_1)
0043ba87        bool c3_14 = unimplemented  {fcomp st0, dword [0x497420]} f== temp18_1
0043ba87        unimplemented  {fcomp st0, dword [0x497420]}
0043ba92        int16_t top_38
0043ba92        if ((((c0_14 ? 1 : 0) << 8 | (c2_14 ? 1 : 0) << 0xa | (c3_14 ? 1 : 0) << 0xe | (top_38 & 7) << 0xb):1.b & 1) != 0)
0043ba94        player_7->x = 0xc0800000
0043ba9a        player_1->_pad_3c0[0x50] = 0
0043ba9a        player_1->_pad_3c0[0x51] = 0
0043ba9a        player_1->_pad_3c0[0x52] = 0
0043ba9a        player_1->_pad_3c0[0x53] = 0
0043baa0        unimplemented  {fld st0, dword [ebx]}
0043baa2        long double temp19_1 = fconvert.t(4f)
0043baa2        unimplemented  {fcomp st0, dword [0x497210]} f- temp19_1
0043baa2        bool c0_15 = unimplemented  {fcomp st0, dword [0x497210]} f< temp19_1
0043baa2        bool c2_15 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp19_1)
0043baa2        bool c3_15 = unimplemented  {fcomp st0, dword [0x497210]} f== temp19_1
0043baa2        unimplemented  {fcomp st0, dword [0x497210]}
0043baa2        top_13 = top_38
0043baad        if ((((c0_15 ? 1 : 0) << 8 | (c2_15 ? 1 : 0) << 0xa | (c3_15 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) == 0)
0043bab3        player_7->x = 0x40800000
0043bab9        player_1->_pad_3c0[0x50] = 0
0043bab9        player_1->_pad_3c0[0x51] = 0
0043bab9        player_1->_pad_3c0[0x52] = 0
0043bab9        player_1->_pad_3c0[0x53] = 0
0043c403        update_warning(&player_1->_pad_3c0[0x34])
0043c408        struct TrackRowCell* eax_74
0043c408        eax_74.b = player_1->_pad_3c0[0x5c]
0043c410        float x_5
0043c410        if (eax_74.b != 0)
0043c510        label_43c510:
0043c510        player_1->_pad_74[0x2b4] = 0
0043c510        player_1->_pad_74[0x2b5] = 0
0043c510        player_1->_pad_74[0x2b6] = 0
0043c510        player_1->_pad_74[0x2b7] = 0
0043c416        eax_74.b = player_1->follow_state.active
0043c41e        if (eax_74.b != 0)
0043c41e        goto label_43c510
0043c424        unimplemented  {fld st0, dword [ebx+0x8]}
0043c427        unimplemented  {fadd dword [0x4973e8]}
0043c42d        float x_1 = player_7->x
0043c42f        float y_2 = player_7->y
0043c432        float x_4 = x_1
0043c438        float y_3 = y_2
0043c43e        float var_34_3 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043c43e        unimplemented  {fstp dword [esp+0x1c], st0}
0043c446        x_5 = x_1
0043c44e        float var_28_1 = var_34_3
0043c452        struct Game* game_24 = player_1->_pad_3c0[0x48].d
0043c458        player_2 = &x_5
0043c459        float y_4 = y_2
0043c45d        int16_t x87control_2
0043c45d        eax_74, x87control_2 = get_track_grid_cell_at_world_position(game_24, player_2)
0043c466        if (eax_74->__offset(0x3c).b != 0xe)
0043c466        goto label_43c510
0043c46c        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c46f        long double temp22_1 = fconvert.t(6.5f)
0043c46f        unimplemented  {fcomp st0, dword [0x4975b8]} f- temp22_1
0043c46f        bool c0_40 = unimplemented  {fcomp st0, dword [0x4975b8]} f< temp22_1
0043c46f        bool c2_40 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975b8]}, temp22_1)
0043c46f        bool c3_40 = unimplemented  {fcomp st0, dword [0x4975b8]} f== temp22_1
0043c46f        unimplemented  {fcomp st0, dword [0x4975b8]}
0043c475        eax_74.w = (c0_40 ? 1 : 0) << 8 | (c2_40 ? 1 : 0) << 0xa | (c3_40 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c47a        if ((eax_74:1.b & 1) == 0)
0043c47a        goto label_43c510
0043c482        player_1->_pad_3c0[0x58] = 0
0043c482        player_1->_pad_3c0[0x59] = 0
0043c482        player_1->_pad_3c0[0x5a] = 0
0043c482        player_1->_pad_3c0[0x5b] = 0
0043c488        unimplemented  {fld st0, dword [ebp+0x70]}
0043c48b        unimplemented  {fadd dword [0x4973e8]}
0043c496        int32_t var_40_5 = __ftol(x87control_2, st0_1)
0043c49a        unimplemented  {fild st0, dword [esp+0x10]}
0043c49e        unimplemented  {fsub st0, dword [0x497228]}
0043c4a4        player_1->position.z = fconvert.s(unimplemented  {fstp dword [ebp+0x70], st0})
0043c4a4        unimplemented  {fstp dword [ebp+0x70], st0}
0043c4a7        unimplemented  {fld st0, dword [ebp+0x4350]}
0043c4ad        long double temp26_1 = fconvert.t(0f)
0043c4ad        unimplemented  {fcomp st0, dword [0x497234]} f- temp26_1
0043c4ad        bool c0_41 = unimplemented  {fcomp st0, dword [0x497234]} f< temp26_1
0043c4ad        bool c2_41 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp26_1)
0043c4ad        bool c3_41 = unimplemented  {fcomp st0, dword [0x497234]} f== temp26_1
0043c4ad        unimplemented  {fcomp st0, dword [0x497234]}
0043c4b3        int32_t eax_76
0043c4b3        eax_76.w = (c0_41 ? 1 : 0) << 8 | (c2_41 ? 1 : 0) << 0xa | (c3_41 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c4b8        if ((eax_76:1.b & 0x40) != 0)
0043c4ba        player_2 = 0x2f
0043c4c1        play_sound_effect(player_2)
0043c4c6        player_2 = 0xbea8f5c3
0043c4d1        start_squidge_z(&player_1->_pad_00[0x4344], player_2)
0043c4d6        unimplemented  {fld st0, dword [ebp+0x32c]}
0043c4dc        unimplemented  {fadd dword [ebp+0x328]}
0043c4e2        player_1->_pad_74[0x2b4].d = fconvert.s(unimplemented  {fst dword [ebp+0x328], st0})
0043c4e8        long double temp28_1 = fconvert.t(1f)
0043c4e8        unimplemented  {fcomp st0, dword [0x497220]} f- temp28_1
0043c4e8        bool c0_42 = unimplemented  {fcomp st0, dword [0x497220]} f< temp28_1
0043c4e8        bool c2_42 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp28_1)
0043c4e8        bool c3_42 = unimplemented  {fcomp st0, dword [0x497220]} f== temp28_1
0043c4e8        unimplemented  {fcomp st0, dword [0x497220]}
0043c4ee        eax_74.w = (c0_42 ? 1 : 0) << 8 | (c2_42 ? 1 : 0) << 0xa | (c3_42 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c4f3        if ((eax_74:1.b & 0x41) == 0)
0043c4f5        player_1->_pad_74[0x2b4] = 0
0043c4f5        player_1->_pad_74[0x2b5] = 0
0043c4f5        player_1->_pad_74[0x2b6] = 0
0043c4f5        player_1->_pad_74[0x2b7] = 0
0043c4fb        eax_74.b = player_1->attachment_exit_pending
0043c503        if (eax_74.b == 0)
0043c507        initialize_subgoldy_fall_state(player_1)
0043c51c        if (player_1->_pad_74[0x2dc].d == 0)
0043c522        struct Game* game_25 = player_1->_pad_3c0[0x48].d
0043c528        player_2 = player_7
0043c532        if (get_track_grid_cell_at_world_position(game_25, player_2)->__offset(0x3c).b == 2)
0043c5d0        label_43c5d0:
0043c5d0        eax_74.b = player_1->attachment_exit_pending
0043c5d8        if (eax_74.b == 0)
0043c5de        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c5e1        long double temp27_1 = fconvert.t(0.980000019f)
0043c5e1        unimplemented  {fcomp st0, dword [0x49756c]} f- temp27_1
0043c5e1        bool c0_43 = unimplemented  {fcomp st0, dword [0x49756c]} f< temp27_1
0043c5e1        bool c2_43 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49756c]}, temp27_1)
0043c5e1        bool c3_43 = unimplemented  {fcomp st0, dword [0x49756c]} f== temp27_1
0043c5e1        unimplemented  {fcomp st0, dword [0x49756c]}
0043c5e7        eax_74.w = (c0_43 ? 1 : 0) << 8 | (c2_43 ? 1 : 0) << 0xa | (c3_43 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c5ec        if ((eax_74:1.b & 0x41) != 0)
0043c5f8        player_2 = player_7
0043c5f9        unimplemented  {fld st0, dword [eax+0x38]}
0043c5fc        unimplemented  {fmul st0, dword [0x4975b4]}
0043c602        player_1->_pad_74[0x2e8].d = fconvert.s(unimplemented  {fstp dword [ebp+0x35c], st0})
0043c602        unimplemented  {fstp dword [ebp+0x35c], st0}
0043c617        if (get_track_grid_cell_at_world_position(player_1->_pad_3c0[0x48].d, player_2)->__offset(0x3c).b == 2)
0043c665        label_43c665:
0043c665        player_1->_pad_74[0x2dc] = 1
0043c665        player_1->_pad_74[0x2dd] = 0
0043c665        player_1->_pad_74[0x2de] = 0
0043c665        player_1->_pad_74[0x2df] = 0
0043c66f        player_1->_pad_74[0x2e0] = 0
0043c66f        player_1->_pad_74[0x2e1] = 0
0043c66f        player_1->_pad_74[0x2e2] = 0x80
0043c66f        player_1->_pad_74[0x2e3] = 0x3f
0043c619        struct Game* game_34 = player_1->_pad_3c0[0x48].d
0043c61f        player_2 = player_7
0043c629        if (get_track_grid_cell_at_world_position(game_34, player_2)->__offset(0x3c).b == 5)
0043c629        goto label_43c665
0043c62b        struct Game* game_35 = player_1->_pad_3c0[0x48].d
0043c631        player_2 = player_7
0043c63b        if (get_track_grid_cell_at_world_position(game_35, player_2)->__offset(0x3c).b == 8)
0043c63b        goto label_43c665
0043c63d        struct Game* game_36 = player_1->_pad_3c0[0x48].d
0043c643        player_2 = player_7
0043c64d        if (get_track_grid_cell_at_world_position(game_36, player_2)->__offset(0x3c).b == 0xb)
0043c64d        goto label_43c665
0043c64f        player_1->_pad_74[0x2dc] = 2
0043c64f        player_1->_pad_74[0x2dd] = 0
0043c64f        player_1->_pad_74[0x2de] = 0
0043c64f        player_1->_pad_74[0x2df] = 0
0043c659        player_1->_pad_74[0x2e0] = 0
0043c659        player_1->_pad_74[0x2e1] = 0
0043c659        player_1->_pad_74[0x2e2] = 0x80
0043c659        player_1->_pad_74[0x2e3] = 0xbf
0043c538        struct Game* game_26 = player_1->_pad_3c0[0x48].d
0043c53e        player_2 = player_7
0043c548        if (get_track_grid_cell_at_world_position(game_26, player_2)->__offset(0x3c).b == 4)
0043c548        goto label_43c5d0
0043c54e        struct Game* game_27 = player_1->_pad_3c0[0x48].d
0043c554        player_2 = player_7
0043c55e        if (get_track_grid_cell_at_world_position(game_27, player_2)->__offset(0x3c).b == 5)
0043c55e        goto label_43c5d0
0043c560        struct Game* game_28 = player_1->_pad_3c0[0x48].d
0043c566        player_2 = player_7
0043c570        if (get_track_grid_cell_at_world_position(game_28, player_2)->__offset(0x3c).b == 7)
0043c570        goto label_43c5d0
0043c572        struct Game* game_29 = player_1->_pad_3c0[0x48].d
0043c578        player_2 = player_7
0043c582        if (get_track_grid_cell_at_world_position(game_29, player_2)->__offset(0x3c).b == 0xa)
0043c582        goto label_43c5d0
0043c584        struct Game* game_30 = player_1->_pad_3c0[0x48].d
0043c58a        player_2 = player_7
0043c594        if (get_track_grid_cell_at_world_position(game_30, player_2)->__offset(0x3c).b == 8)
0043c594        goto label_43c5d0
0043c596        struct Game* game_31 = player_1->_pad_3c0[0x48].d
0043c59c        player_2 = player_7
0043c5a6        if (get_track_grid_cell_at_world_position(game_31, player_2)->__offset(0x3c).b == 0xa)
0043c5a6        goto label_43c5d0
0043c5a8        struct Game* game_32 = player_1->_pad_3c0[0x48].d
0043c5ae        player_2 = player_7
0043c5b8        if (get_track_grid_cell_at_world_position(game_32, player_2)->__offset(0x3c).b == 0xb)
0043c5b8        goto label_43c5d0
0043c5ba        struct Game* game_33 = player_1->_pad_3c0[0x48].d
0043c5c0        player_2 = player_7
0043c5ca        if (get_track_grid_cell_at_world_position(game_33, player_2)->__offset(0x3c).b == 0xd)
0043c5ca        goto label_43c5d0
0043c679        unimplemented  {fld st0, dword [ebp+0x1d4]}
0043c67f        long double temp21_1 = fconvert.t(0f)
0043c67f        unimplemented  {fcomp st0, dword [0x497234]} f- temp21_1
0043c67f        bool c0_44 = unimplemented  {fcomp st0, dword [0x497234]} f< temp21_1
0043c67f        bool c2_44 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp21_1)
0043c67f        bool c3_44 = unimplemented  {fcomp st0, dword [0x497234]} f== temp21_1
0043c67f        unimplemented  {fcomp st0, dword [0x497234]}
0043c685        eax_74.w = (c0_44 ? 1 : 0) << 8 | (c2_44 ? 1 : 0) << 0xa | (c3_44 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c68a        if ((eax_74:1.b & 0x40) == 0)
0043c68c        unimplemented  {fld st0, dword [ebp+0x1d8]}
0043c692        unimplemented  {fadd dword [ebp+0x1d4]}
0043c698        player_1->_pad_74[0x160].d = fconvert.s(unimplemented  {fst dword [ebp+0x1d4], st0})
0043c69e        long double temp25_1 = fconvert.t(1f)
0043c69e        unimplemented  {fcomp st0, dword [0x497220]} f- temp25_1
0043c69e        bool c0_45 = unimplemented  {fcomp st0, dword [0x497220]} f< temp25_1
0043c69e        bool c2_45 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp25_1)
0043c69e        bool c3_45 = unimplemented  {fcomp st0, dword [0x497220]} f== temp25_1
0043c69e        unimplemented  {fcomp st0, dword [0x497220]}
0043c6a4        eax_74.w = (c0_45 ? 1 : 0) << 8 | (c2_45 ? 1 : 0) << 0xa | (c3_45 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c6a9        if ((eax_74:1.b & 0x41) == 0)
0043c6ab        player_1->_pad_74[0x160] = 0
0043c6ab        player_1->_pad_74[0x161] = 0
0043c6ab        player_1->_pad_74[0x162] = 0
0043c6ab        player_1->_pad_74[0x163] = 0
0043c6b1        struct Player* player_5 = player_1->_pad_3c0[0x48].d
0043c6b7        unimplemented  {fild st0, dword [ecx+0x58]}
0043c6ba        float var_40_6 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043c6ba        unimplemented  {fstp dword [esp+0x10], st0}
0043c6be        unimplemented  {fld st0, dword [ebp+0x70]}
0043c6c1        long double temp24_1 = fconvert.t(var_40_6)
0043c6c1        unimplemented  {fcomp st0, dword [esp+0x10]} f- temp24_1
0043c6c1        bool c0_46 = unimplemented  {fcomp st0, dword [esp+0x10]} f< temp24_1
0043c6c1        bool c2_46 = is_unordered.t(unimplemented  {fcomp st0, dword [esp+0x10]}, temp24_1)
0043c6c1        bool c3_46 = unimplemented  {fcomp st0, dword [esp+0x10]} f== temp24_1
0043c6c1        unimplemented  {fcomp st0, dword [esp+0x10]}
0043c6c1        int16_t top_142 = top_13
0043c6c5        eax_74.w = (c0_46 ? 1 : 0) << 8 | (c2_46 ? 1 : 0) << 0xa | (c3_46 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c6ca        if ((eax_74:1.b & 1) != 0)
0043ca46        label_43ca46:
0043ca46        eax_74.b = player_1->_pad_3c0[0x5c]
0043ca4e        if (eax_74.b == 0)
0043ca50        eax_74.b = player_1->_pad_74[0x264]
0043ca58        if (eax_74.b == 0)
0043ca5a        unimplemented  {fld st0, dword [ecx+0x38]}
0043ca5d        unimplemented  {fmul st0, dword [0x4975b0]}
0043ca63        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca69        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043ca69        bool c0_56 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043ca69        bool c2_56 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043ca69        bool c3_56 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043ca69        unimplemented  {fcomp st0, st1}
0043ca69        int16_t top_170 = top_142 - 1
0043ca6b        eax_74.w = (c0_56 ? 1 : 0) << 8 | (c2_56 ? 1 : 0) << 0xa | (c3_56 ? 1 : 0) << 0xe | (top_170 & 7) << 0xb
0043ca70        if ((eax_74:1.b & 1) == 0)
0043ca72        unimplemented  {fstp st0, st0}
0043ca72        unimplemented  {fstp st0, st0}
0043ca74        unimplemented  {fld st0, dword [ecx+0x38]}
0043ca77        unimplemented  {fmul st0, dword [0x497228]}
0043ca7d        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca83        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043ca83        bool c0_57 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043ca83        bool c2_57 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043ca83        bool c3_57 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043ca83        unimplemented  {fcomp st0, st1}
0043ca85        eax_74.w = (c0_57 ? 1 : 0) << 8 | (c2_57 ? 1 : 0) << 0xa | (c3_57 ? 1 : 0) << 0xe | (top_170 & 7) << 0xb
0043ca8a        if ((eax_74:1.b & 0x41) != 0)
0043ca8c        unimplemented  {fstp st0, st0}
0043ca8c        unimplemented  {fstp st0, st0}
0043ca8e        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca94        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043ca94        unimplemented  {fstp dword [ebp+0x418], st0}
0043c6d0        eax_74.b = player_1->attachment_exit_pending
0043c6d8        if (eax_74.b != 0)
0043c6d8        goto label_43ca46
0043c6de        eax_74.b = player_1->_pad_430[0x10]
0043c6e6        if (eax_74.b == 0)
0043c6f0        if (player_5->_pad_00[0x40].d == 4)
0043c6f2        unimplemented  {fld st0, dword [ebp+0x70]}
0043c6f5        unimplemented  {fsub st0, dword [esp+0x10]}
0043c6f9        player_2 = player_5
0043c700        unimplemented  {fdiv st0, dword [ebp+0x418]}
0043c706        unimplemented  {fsubr st0, dword [0x497220]}
0043c70c        unimplemented  {fmul st0, dword [0x4972c8]}
0043c712        player_2 = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043c712        unimplemented  {fstp dword [esp], st0}
0043c715        advance_timer_counters(&player_1->_pad_74[0x274], player_2)
0043c720        player_1->_pad_430[0x14] = 0
0043c720        player_1->_pad_430[0x15] = 0
0043c720        player_1->_pad_430[0x16] = 0
0043c720        player_1->_pad_430[0x17] = 0
0043c726        player_1->_pad_430[0x18] = 0x89
0043c726        player_1->_pad_430[0x19] = 0x88
0043c726        player_1->_pad_430[0x1a] = 0x88
0043c726        player_1->_pad_430[0x1b] = 0x3c
0043c730        player_1->_pad_430[0x1e] = 0
0043c737        unimplemented  {fld st0, dword [ecx+0x38]}
0043c73a        unimplemented  {fmul st0, dword [0x4975b0]}
0043c740        unimplemented  {fld st0, dword [ebp+0x418]}
0043c746        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043c746        bool c0_47 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043c746        bool c2_47 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043c746        bool c3_47 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043c746        unimplemented  {fcomp st0, st1}
0043c746        int16_t top_146 = top_142 - 1
0043c748        eax_74.w = (c0_47 ? 1 : 0) << 8 | (c2_47 ? 1 : 0) << 0xa | (c3_47 ? 1 : 0) << 0xe | (top_146 & 7) << 0xb
0043c74d        if ((eax_74:1.b & 1) == 0)
0043c74f        unimplemented  {fstp st0, st0}
0043c74f        unimplemented  {fstp st0, st0}
0043c751        unimplemented  {fld st0, dword [ecx+0x38]}
0043c754        unimplemented  {fmul st0, dword [0x497228]}
0043c75a        unimplemented  {fld st0, dword [ebp+0x418]}
0043c760        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043c760        bool c0_48 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043c760        bool c2_48 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043c760        bool c3_48 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043c760        unimplemented  {fcomp st0, st1}
0043c762        eax_74.w = (c0_48 ? 1 : 0) << 8 | (c2_48 ? 1 : 0) << 0xa | (c3_48 ? 1 : 0) << 0xe | (top_146 & 7) << 0xb
0043c767        if ((eax_74:1.b & 0x41) != 0)
0043c769        unimplemented  {fstp st0, st0}
0043c769        unimplemented  {fstp st0, st0}
0043c76b        unimplemented  {fld st0, dword [ebp+0x418]}
0043c771        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043c771        unimplemented  {fstp dword [ebp+0x418], st0}
0043c771        top_142 = top_146 + 1
0043c77c        reset_voice_manager(0x751498)
0043c787        end_jetpack_hover(&player_1->_pad_430[0x2320])
0043c791        player_2 = nullptr
0043c797        player_1->__offset(0x42e8).d = 5
0043c79d        play_sound_effect(player_2)
0043c7a2        player_1->_pad_3c0[0x5c] = 0
0043c7b0        player_1->_pad_430[0x10] = 1
0043c7bd        unimplemented  {fild st0, dword [ecx+0x58]}
0043c7c0        unimplemented  {fadd dword [0x4973cc]}
0043c7c6        long double temp34_1 = fconvert.t(player_1->position.z)
0043c7c6        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp34_1
0043c7c6        bool c0_49 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp34_1
0043c7c6        bool c2_49 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp34_1)
0043c7c6        bool c3_49 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp34_1
0043c7c6        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043c7c9        eax_74.w = (c0_49 ? 1 : 0) << 8 | (c2_49 ? 1 : 0) << 0xa | (c3_49 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c7ce        if ((eax_74:1.b & 1) != 0)
0043c7d0        unimplemented  {fld st0, dword [ecx+0x38]}
0043c7d3        unimplemented  {fld st0, st0}
0043c7d5        unimplemented  {fmulp st1, st0}
0043c7d5        unimplemented  {fmulp st1, st0}
0043c7d7        unimplemented  {fmul st0, dword [0x4973bc]}
0043c7dd        unimplemented  {fadd st0, st0}
0043c7df        unimplemented  {fsubr st0, dword [ebp+0x418]}
0043c7e5        player_1->_pad_3c0[0x58].d = fconvert.s(unimplemented  {fst dword [ebp+0x418], st0})
0043c7eb        long double temp39_1 = fconvert.t(0f)
0043c7eb        unimplemented  {fcomp st0, dword [0x497234]} f- temp39_1
0043c7eb        bool c0_50 = unimplemented  {fcomp st0, dword [0x497234]} f< temp39_1
0043c7eb        bool c2_50 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp39_1)
0043c7eb        bool c3_50 = unimplemented  {fcomp st0, dword [0x497234]} f== temp39_1
0043c7eb        unimplemented  {fcomp st0, dword [0x497234]}
0043c7f1        eax_74.w = (c0_50 ? 1 : 0) << 8 | (c2_50 ? 1 : 0) << 0xa | (c3_50 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c7f6        if ((eax_74:1.b & 1) != 0)
0043c7f8        player_1->_pad_3c0[0x58] = 0
0043c7f8        player_1->_pad_3c0[0x59] = 0
0043c7f8        player_1->_pad_3c0[0x5a] = 0
0043c7f8        player_1->_pad_3c0[0x5b] = 0
0043c7fe        unimplemented  {fld st0, dword [ebp+0x2748]}
0043c804        unimplemented  {fadd dword [ebp+0x2744]}
0043c80a        player_1->_pad_430[0x2314].d = fconvert.s(unimplemented  {fst dword [ebp+0x2744], st0})
0043c810        long double temp38_1 = fconvert.t(1f)
0043c810        unimplemented  {fcomp st0, dword [0x497220]} f- temp38_1
0043c810        bool c0_51 = unimplemented  {fcomp st0, dword [0x497220]} f< temp38_1
0043c810        bool c2_51 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp38_1)
0043c810        bool c3_51 = unimplemented  {fcomp st0, dword [0x497220]} f== temp38_1
0043c810        unimplemented  {fcomp st0, dword [0x497220]}
0043c816        eax_74.w = (c0_51 ? 1 : 0) << 8 | (c2_51 ? 1 : 0) << 0xa | (c3_51 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c81b        if ((eax_74:1.b & 0x41) == 0)
0043c81d        player_1->_pad_430[0x2314] = 0
0043c81d        player_1->_pad_430[0x2315] = 0
0043c81d        player_1->_pad_430[0x2316] = 0
0043c81d        player_1->_pad_430[0x2317] = 0
0043c823        unimplemented  {fld st0, dword [ebp+0x444]}
0043c829        unimplemented  {fadd dword [ebp+0x448]}
0043c835        player_1->_pad_430[0x14].d = fconvert.s(unimplemented  {fstp dword [ebp+0x444], st0})
0043c835        unimplemented  {fstp dword [ebp+0x444], st0}
0043c83b        *(player_1->_pad_3c0[0x48].d + 0x1270fc8) = 2
0043c845        unimplemented  {fld st0, dword [ebp+0x444]}
0043c84b        long double temp43_1 = fconvert.t(2f)
0043c84b        unimplemented  {fcomp st0, dword [0x4974a4]} f- temp43_1
0043c84b        bool c0_52 = unimplemented  {fcomp st0, dword [0x4974a4]} f< temp43_1
0043c84b        bool c2_52 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4974a4]}, temp43_1)
0043c84b        bool c3_52 = unimplemented  {fcomp st0, dword [0x4974a4]} f== temp43_1
0043c84b        unimplemented  {fcomp st0, dword [0x4974a4]}
0043c851        eax_74.w = (c0_52 ? 1 : 0) << 8 | (c2_52 ? 1 : 0) << 0xa | (c3_52 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c856        if ((eax_74:1.b & 0x41) == 0)
0043c858        eax_74.b = player_1->_pad_430[0x1e]
0043c860        if (eax_74.b == 0)
0043c862        player_2 = 0xffffffff
0043c86d        player_1->_pad_430[0x1e] = 1
0043c874        play_voice_manager(0x751498, 8, 2, player_2)
0043c879        unimplemented  {fld st0, dword [ebp+0x444]}
0043c87f        long double temp47_1 = fconvert.t(2f)
0043c87f        unimplemented  {fcomp st0, dword [0x4974a4]} f- temp47_1
0043c87f        bool c0_53 = unimplemented  {fcomp st0, dword [0x4974a4]} f< temp47_1
0043c87f        bool c2_53 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4974a4]}, temp47_1)
0043c87f        bool c3_53 = unimplemented  {fcomp st0, dword [0x4974a4]} f== temp47_1
0043c87f        unimplemented  {fcomp st0, dword [0x4974a4]}
0043c885        eax_74.w = (c0_53 ? 1 : 0) << 8 | (c2_53 ? 1 : 0) << 0xa | (c3_53 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c88a        if ((eax_74:1.b & 0x41) == 0)
0043c88c        eax_74 = player_1->_pad_3c0[0x48].d
0043c892        int32_t ecx_121 = eax_74->__offset(0x40).d
0043c89c        if (ecx_121 == 0 || ecx_121 == 1)
0043c8b8        if (eax_74->__offset(0x12727f0).b == 1 && (*(player_1->_pad_430[0xc].d + 5) & 0x40) != 0)
0043c8ba        player_1->_pad_430[0x14] = 0x33
0043c8ba        player_1->_pad_430[0x15] = 0x33
0043c8ba        player_1->_pad_430[0x16] = 0xa3
0043c8ba        player_1->_pad_430[0x17] = 0x40
0043c8c6        if (eax_74->__offset(0x12727ec).d == 5)
0043c8c8        player_1->_pad_430[0x14] = 0x33
0043c8c8        player_1->_pad_430[0x15] = 0x33
0043c8c8        player_1->_pad_430[0x16] = 0xa3
0043c8c8        player_1->_pad_430[0x17] = 0x40
0043c8ce        unimplemented  {fld st0, dword [ebp+0x444]}
0043c8d4        long double temp50_1 = fconvert.t(5f)
0043c8d4        unimplemented  {fcomp st0, dword [0x497288]} f- temp50_1
0043c8d4        bool c0_54 = unimplemented  {fcomp st0, dword [0x497288]} f< temp50_1
0043c8d4        bool c2_54 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497288]}, temp50_1)
0043c8d4        bool c3_54 = unimplemented  {fcomp st0, dword [0x497288]} f== temp50_1
0043c8d4        unimplemented  {fcomp st0, dword [0x497288]}
0043c8da        eax_74.w = (c0_54 ? 1 : 0) << 8 | (c2_54 ? 1 : 0) << 0xa | (c3_54 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c8df        if ((eax_74:1.b & 0x41) == 0)
0043c8e1        void* ecx_122 = player_1->_pad_3c0[0x48].d
0043c8e7        eax_74 = *(ecx_122 + 0x40)
0043c8f9        if ((eax_74 == 0 || eax_74 == 1) && *(ecx_122 + 0x12727ec) != 5)
0043c8fb        unimplemented  {fld st0, dword [ebp+0x444]}
0043c901        unimplemented  {fsub st0, dword [ebp+0x448]}
0043c907        player_1->_pad_430[0x14].d = fconvert.s(unimplemented  {fstp dword [ebp+0x444], st0})
0043c907        unimplemented  {fstp dword [ebp+0x444], st0}
0043c90d        unimplemented  {fld st0, dword [ebp+0x444]}
0043c913        long double temp54_1 = fconvert.t(5f)
0043c913        unimplemented  {fcomp st0, dword [0x497288]} f- temp54_1
0043c913        bool c0_55 = unimplemented  {fcomp st0, dword [0x497288]} f< temp54_1
0043c913        bool c2_55 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497288]}, temp54_1)
0043c913        bool c3_55 = unimplemented  {fcomp st0, dword [0x497288]} f== temp54_1
0043c913        unimplemented  {fcomp st0, dword [0x497288]}
0043c919        eax_74.w = (c0_55 ? 1 : 0) << 8 | (c2_55 ? 1 : 0) << 0xa | (c3_55 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c91e        if ((eax_74:1.b & 0x41) == 0)
0043c924        void* eax_77 = data_4df904
0043c92c        int32_t eax_78 = *(eax_77 + 0x24)
0043c931        if (eax_78 == 0)
0043c933        player_2 = nullptr
0043c934        begin_frontend_fade_out(eax_77 + 0x24, player_2)
0043c941        if (eax_78 == 4)
0043c947        void* eax_79 = player_1->_pad_3c0[0x48].d
0043c953        if (*(eax_79 + 0x12727ec) != 0)
0043c95b        flush_row_event_display(eax_79 + 0x12727d8)
0043c960        void* ecx_125 = player_1->_pad_3c0[0x48].d
0043c969        void* eax_83
0043c969        if (*(ecx_125 + 0x40) != 0)
0043c9c6        player_2 = 1
0043c9c8        eax_83 = complete_subgame(ecx_125, player_2.b)
0043c97d        if (*(ecx_125 + 0x44) == *(data_4df904 + 0x12d4644) - 1)
0043c97f        player_2 = 1
0043c981        void* eax_82 = complete_subgame(ecx_125, player_2.b)
0043c98c        *(data_4df904 + 0x1bc) = 0x1d
0043c99c        *(data_4df904 + 0x1b8) = 0x1a
0043c9ad        return eax_82
0043c9ae        player_2 = nullptr
0043c9af        complete_subgame(ecx_125, player_2.b)
0043c9b4        eax_83 = player_1->_pad_3c0[0x48].d
0043c9ba        *(eax_83 + 0x1270fc8) = 1
0043c9cd        void* ebp = player_1->_pad_3c0[0x48].d
0043c9d7        if (*(ebp + 0x40) == 7)
0043c9df        *(data_4df904 + 0x1b8) = 0x1a
0043c9ef        *(data_4df904 + 0x1bc) = 2
0043ca00        return eax_83
0043ca01        eax_83.b = *(ebp + 0xff25d1)
0043ca09        void* eax_84 = data_4df904
0043ca14        *(eax_84 + 0x1bc) = *(eax_84 + 0x1b8)
0043ca1a        void* edx_43 = data_4df904
0043ca20        if (eax_83.b == 0)
0043ca34        *(edx_43 + 0x1b8) = 0x1b
0043ca45        return eax_84
0043ca22        *(edx_43 + 0x1b8) = 0x1a
0043ca33        return eax_84
0043ca9c        float x_2 = player_7->x
0043caa5        float y = player_7->y
0043caac        float z = player_7->z
0043cab0        float eax_86
0043cab0        eax_86.b = player_1->follow_state.active
0043cab8        if (eax_86.b == 1)
0043cac4        player_7->x = player_1->follow_state.output_position.x
0043cac9        player_7->y = player_1->follow_state.output_position.y
0043cacf        player_7->z = player_1->follow_state.output_position.z
0043cad8        update_jetpack_gauge(&player_1->_pad_430[0x2320])
0043cae5        if (player_1->_pad_430[0x10] != 0)
0043cae7        int32_t eax_90 = data_4df904
0043cafd        __builtin_memcpy(eax_90 + 0x2cc, eax_90 + 0x15c, 0x40)
0043cb06        unimplemented  {fld st0, dword [eax+0x300]}
0043cb0c        unimplemented  {fsub st0, dword [0x497220]}
0043cb12        *(data_4df904 + 0x300) = fconvert.s(unimplemented  {fstp dword [eax+0x300], st0})
0043cb12        unimplemented  {fstp dword [eax+0x300], st0}
0043cb1e        update_damage_gauge(&player_1->_pad_3c0[4])
0043cb29        update_progress_bar()
0043cb36        unimplemented  {fld st0, dword [ebp+0x276c]}
0043cb40        unimplemented  {fld st0, st0}
0043cb42        player_1->cached_camera_target_world.x = player_7->x
0043cb4a        player_1->cached_camera_target_world.y = player_7->y
0043cb4d        player_1->cached_camera_target_world.z = player_7->z
0043cb50        unimplemented  {fmul st0, dword [ebp+0x58]}
0043cb53        float var_18_1 = fconvert.s(unimplemented  {fstp dword [esp+0x38], st0})
0043cb53        unimplemented  {fstp dword [esp+0x38], st0}
0043cb57        unimplemented  {fld st0, st0}
0043cb59        unimplemented  {fmul st0, dword [ebp+0x5c]}
0043cb5c        float var_14_1 = fconvert.s(unimplemented  {fstp dword [esp+0x3c], st0})
0043cb5c        unimplemented  {fstp dword [esp+0x3c], st0}
0043cb60        unimplemented  {fmul st0, dword [ebp+0x60]}
0043cb63        unimplemented  {fld st0, dword [ebp+0x2768]}
0043cb69        unimplemented  {fld st0, st0}
0043cb6b        unimplemented  {fmul st0, dword [ebp+0x48]}
0043cb6e        float var_3c_3 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043cb6e        unimplemented  {fstp dword [esp+0x14], st0}
0043cb72        unimplemented  {fld st0, st0}
0043cb74        unimplemented  {fmul st0, dword [ebp+0x4c]}
0043cb77        float var_38_3 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043cb77        unimplemented  {fstp dword [esp+0x18], st0}
0043cb7b        unimplemented  {fmul st0, dword [ebp+0x50]}
0043cb7e        unimplemented  {fld st0, dword [ebp+0x2764]}
0043cb84        unimplemented  {fld st0, st0}
0043cb86        unimplemented  {fmul st0, dword [ebp+0x38]}
0043cb89        x_5 = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043cb89        unimplemented  {fstp dword [esp+0x20], st0}
0043cb8d        unimplemented  {fld st0, st0}
0043cb8f        unimplemented  {fmul st0, dword [ebp+0x3c]}
0043cb92        float var_2c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
0043cb92        unimplemented  {fstp dword [esp+0x24], st0}
0043cb96        unimplemented  {fmul st0, dword [ebp+0x40]}
0043cb99        unimplemented  {fld st0, dword [esp+0x20]}
0043cb9d        unimplemented  {fadd dword [esp+0x14]}
0043cba1        float var_24_1 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
0043cba1        unimplemented  {fstp dword [esp+0x2c], st0}
0043cba5        unimplemented  {fld st0, dword [esp+0x24]}
0043cba9        unimplemented  {fadd dword [esp+0x18]}
0043cbad        float var_20_1 = fconvert.s(unimplemented  {fstp dword [esp+0x30], st0})
0043cbad        unimplemented  {fstp dword [esp+0x30], st0}
0043cbb1        unimplemented  {faddp st1, st0}
0043cbb1        unimplemented  {faddp st1, st0}
0043cbb3        unimplemented  {fld st0, dword [esp+0x2c]}
0043cbb7        unimplemented  {fadd dword [esp+0x38]}
0043cbbb        x_5 = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043cbbb        unimplemented  {fstp dword [esp+0x20], st0}
0043cbbf        unimplemented  {fld st0, dword [esp+0x30]}
0043cbc3        unimplemented  {fadd dword [esp+0x3c]}
0043cbc7        float var_2c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
0043cbc7        unimplemented  {fstp dword [esp+0x24], st0}
0043cbcb        unimplemented  {faddp st1, st0}
0043cbcb        unimplemented  {faddp st1, st0}
0043cbcd        unimplemented  {fld st0, dword [esp+0x20]}
0043cbd1        unimplemented  {fadd dword [eax]}
0043cbd3        player_1->cached_camera_target_world.x = fconvert.s(unimplemented  {fstp dword [eax], st0})
0043cbd3        unimplemented  {fstp dword [eax], st0}
0043cbd5        unimplemented  {fld st0, dword [esp+0x24]}
0043cbd9        unimplemented  {fadd dword [eax+0x4]}
0043cbdc        player_1->cached_camera_target_world.y = fconvert.s(unimplemented  {fstp dword [eax+0x4], st0})
0043cbdc        unimplemented  {fstp dword [eax+0x4], st0}
0043cbdf        unimplemented  {fadd dword [eax+0x8]}
0043cbe2        player_1->cached_camera_target_world.z = fconvert.s(unimplemented  {fstp dword [eax+0x8], st0})
0043cbe2        unimplemented  {fstp dword [eax+0x8], st0}
0043cbe5        float eax_93 = player_1->_pad_3c0[0x1c].d
0043cbed        if (eax_93 s> 0)
0043cbf0        player_1->_pad_3c0[0x1c] = (eax_93 i- 1).b
0043cbf0        player_1->_pad_3c0[0x1d] = (eax_93 i- 1):1.b
0043cbf0        player_1->_pad_3c0[0x1e] = (eax_93 i- 1):2.b
0043cbf0        player_1->_pad_3c0[0x1f] = (eax_93 i- 1):3.b
0043cbfd        if (player_1->follow_state.active == 1)
0043cc03        player_7->x = x_2
0043cc0b        unimplemented  {fld st0, dword [ecx+0x38]}
0043cc0e        unimplemented  {fmul st0, dword [0x4975b4]}
0043cc14        player_1->_pad_74[0x2e8].d = fconvert.s(unimplemented  {fst dword [ebp+0x35c], st0})
0043cc20        int16_t top_207
0043cc20        int16_t top_191
0043cc20        if (player_1->_pad_74[0x2dc].d == 0)
0043cc49        unimplemented  {fstp st0, st0}
0043cc49        unimplemented  {fstp st0, st0}
0043cc49        top_207 = top_191 + 4
0043cc22        unimplemented  {fadd dword [ebp+0x358]}
0043cc28        player_1->_pad_74[0x2e4].d = fconvert.s(unimplemented  {fst dword [ebp+0x358], st0})
0043cc2e        long double temp46_1 = fconvert.t(1f)
0043cc2e        unimplemented  {fcomp st0, dword [0x497220]} f- temp46_1
0043cc2e        bool c0_58 = unimplemented  {fcomp st0, dword [0x497220]} f< temp46_1
0043cc2e        bool c2_58 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp46_1)
0043cc2e        bool c3_58 = unimplemented  {fcomp st0, dword [0x497220]} f== temp46_1
0043cc2e        unimplemented  {fcomp st0, dword [0x497220]}
0043cc2e        top_207 = top_191 + 4
0043cc34        eax_93.w = (c0_58 ? 1 : 0) << 8 | (c2_58 ? 1 : 0) << 0xa | (c3_58 ? 1 : 0) << 0xe | (top_207 & 7) << 0xb
0043cc39        if ((eax_93:1.b & 0x41) == 0)
0043cc3b        player_1->_pad_74[0x2e4] = 0
0043cc3b        player_1->_pad_74[0x2e5] = 0
0043cc3b        player_1->_pad_74[0x2e6] = 0
0043cc3b        player_1->_pad_74[0x2e7] = 0
0043cc41        player_1->_pad_74[0x2dc] = 0
0043cc41        player_1->_pad_74[0x2dd] = 0
0043cc41        player_1->_pad_74[0x2de] = 0
0043cc41        player_1->_pad_74[0x2df] = 0
0043cc51        if (player_1->_pad_74[0x2ec].d != 0)
0043cc53        unimplemented  {fld st0, dword [ebp+0x36c]}
0043cc59        unimplemented  {fadd dword [ebp+0x368]}
0043cc5f        player_1->_pad_74[0x2f4].d = fconvert.s(unimplemented  {fst dword [ebp+0x368], st0})
0043cc65        long double temp53_1 = fconvert.t(1f)
0043cc65        unimplemented  {fcomp st0, dword [0x497220]} f- temp53_1
0043cc65        bool c0_59 = unimplemented  {fcomp st0, dword [0x497220]} f< temp53_1
0043cc65        bool c2_59 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp53_1)
0043cc65        bool c3_59 = unimplemented  {fcomp st0, dword [0x497220]} f== temp53_1
0043cc65        unimplemented  {fcomp st0, dword [0x497220]}
0043cc6b        eax_93.w = (c0_59 ? 1 : 0) << 8 | (c2_59 ? 1 : 0) << 0xa | (c3_59 ? 1 : 0) << 0xe | (top_207 & 7) << 0xb
0043cc70        if ((eax_93:1.b & 0x41) == 0)
0043cc72        player_1->_pad_74[0x2f4] = 0
0043cc72        player_1->_pad_74[0x2f5] = 0
0043cc72        player_1->_pad_74[0x2f6] = 0
0043cc72        player_1->_pad_74[0x2f7] = 0
0043cc78        player_1->_pad_74[0x2ec] = 0
0043cc78        player_1->_pad_74[0x2ed] = 0
0043cc78        player_1->_pad_74[0x2ee] = 0
0043cc78        player_1->_pad_74[0x2ef] = 0
0043cc84        unimplemented  {fld st0, dword [edx+0x38]}
0043cc87        unimplemented  {fmul st0, dword [0x4975ac]}
0043cc8d        player_1->_pad_74[0x304].d = fconvert.s(unimplemented  {fst dword [ebp+0x378], st0})
0043cc93        unimplemented  {fld st0, dword [ebp+0x374]}
0043cc99        long double temp52_1 = fconvert.t(0f)
0043cc99        unimplemented  {fcomp st0, dword [0x497234]} f- temp52_1
0043cc99        bool c0_60 = unimplemented  {fcomp st0, dword [0x497234]} f< temp52_1
0043cc99        bool c2_60 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp52_1)
0043cc99        bool c3_60 = unimplemented  {fcomp st0, dword [0x497234]} f== temp52_1
0043cc99        unimplemented  {fcomp st0, dword [0x497234]}
0043cc9f        eax_93.w = (c0_60 ? 1 : 0) << 8 | (c2_60 ? 1 : 0) << 0xa | (c3_60 ? 1 : 0) << 0xe | ((top_207 - 1) & 7) << 0xb
0043cca4        int16_t top_212
0043cca4        if ((eax_93:1.b & 0x41) != 0)
0043ccdf        unimplemented  {fstp st0, st0}
0043ccdf        unimplemented  {fstp st0, st0}
0043ccdf        top_212 = top_207
0043cca6        unimplemented  {fadd dword [ebp+0x374]}
0043ccac        player_1->_pad_74[0x300].d = fconvert.s(unimplemented  {fst dword [ebp+0x374], st0})
0043ccb2        long double temp55_1 = fconvert.t(1f)
0043ccb2        unimplemented  {fcomp st0, dword [0x497220]} f- temp55_1
0043ccb2        bool c0_61 = unimplemented  {fcomp st0, dword [0x497220]} f< temp55_1
0043ccb2        bool c2_61 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp55_1)
0043ccb2        bool c3_61 = unimplemented  {fcomp st0, dword [0x497220]} f== temp55_1
0043ccb2        unimplemented  {fcomp st0, dword [0x497220]}
0043ccb2        top_212 = top_207
0043ccb8        eax_93.w = (c0_61 ? 1 : 0) << 8 | (c2_61 ? 1 : 0) << 0xa | (c3_61 ? 1 : 0) << 0xe | (top_212 & 7) << 0xb
0043ccbd        if ((eax_93:1.b & 0x41) != 0)
0043ccd8        update_nuke(&player_1->_pad_74[0xdc])
0043ccc5        player_1->_pad_74[0x300] = 0
0043ccc5        player_1->_pad_74[0x301] = 0
0043ccc5        player_1->_pad_74[0x302] = 0
0043ccc5        player_1->_pad_74[0x303] = 0
0043cccb        uninit_nuke(&player_1->_pad_74[0xdc])
0043cce1        struct Player* player_6 = player_1->_pad_3c0[0x48].d
0043cceb        if (player_6->_pad_00[0x40].d == 4)
0043cd07        void* eax_97 = &player_6->_pad_00[player_6->_pad_00[0x44].d * 0x1fac0]
0043cd10        if (*(eax_97 + 0x944150) == 1)
0043cd16        int32_t edx_52
0043cd16        edx_52.b = player_6->__offset(0xff25d0).b
0043cd1e        if (edx_52.b == 0)
0043cd24        int32_t ecx_137 = player_6->__offset(0xff25dc).d
0043cd2a        int32_t edx_53 = *(eax_97 + 0x9441bc)
0043cd32        if (ecx_137 s>= edx_53)
0043cd34        ecx_137 = edx_53
0043cd36        int32_t edx_54 = player_1->_pad_74[0x290].d
0043cd3e        int32_t edi_8
0043cd3e        int32_t temp66_1
0043cd3e        if (edx_54 != 0)
0043cd46        edi_8 = *(eax_97 + 0x944174) - edx_54
0043cd48        temp66_1 = ecx_137
0043cd48        ecx_137 += edi_8
0043cd4a        int16_t top_213
0043cd4a        if (edx_54 != 0 && temp66_1 != neg.d(edi_8))
0043cd66        player_2 = 0x42000000
0043cd6b        eax_97.w = *(eax_97 + ecx_137 * 6 + 0x9441c2)
0043cd74        top_213 = top_212 - 1
0043cd74        unimplemented  {call 0x44c8b0}
0043cd79        unimplemented  {fadd dword [0x643190]}
0043cd4c        ecx_137.w = *(eax_97 + 0x9441c2)
0043cd53        player_2 = 0x42000000
0043cd59        top_213 = top_212 - 1
0043cd59        unimplemented  {call 0x44c8b0}
0043cd82        data_643190 = fconvert.s(unimplemented  {fstp dword [0x643190], st0})
0043cd82        unimplemented  {fstp dword [0x643190], st0}
0043cd8e        int16_t eax_98
0043cd8e        eax_98.b = *(player_1->_pad_3c0[0x48].d + 0xff25d0)
0043cd96        if (eax_98.b != 0)
0043cd9b        data_643190 = player_1->position.z
0043cda1        unimplemented  {fld st0, dword [ebp+0x70]}
0043cda4        unimplemented  {fadd dword [0x497448]}
0043cdaa        unimplemented  {fld st0, dword [0x643190]}
0043cdb0        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043cdb0        bool c0_62 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043cdb0        bool c2_62 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043cdb0        bool c3_62 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043cdb0        unimplemented  {fcomp st0, st1}
0043cdb7        struct Player* player_3
0043cdb7        if ((((c0_62 ? 1 : 0) << 8 | (c2_62 ? 1 : 0) << 0xa | (c3_62 ? 1 : 0) << 0xe | (top_213 & 7) << 0xb):1.b & 1) == 0)
0043cdc6        player_3 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043cdc6        unimplemented  {fstp dword [esp+0x10], st0}
0043cdc6        top_212 = top_213 + 1
0043cdbe        unimplemented  {fstp st0, st0}
0043cdbe        unimplemented  {fstp st0, st0}
0043cdbe        top_212 = top_213 + 1
0043cdc0        player_3 = data_643190
0043cdce        player_2 = player_3
0043cdd1        player_6 = mark_current_track_pair_with_payload(player_1, player_2)
0043cddc        void* eax_100 = data_4df904
0043cde1        player_2 = player_6
0043cde2        unimplemented  {fild st0, dword [edx+0x54]}
0043cdeb        unimplemented  {fdivr st0, dword [ebp+0x70]}
0043cdee        player_2 = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043cdee        unimplemented  {fstp dword [esp], st0}
0043cdf1        set_backdrop_progress_fraction(eax_100 + 0x4ec10, player_2)
0043cdf1        esp = &__saved_edi
0043cdfc        unimplemented  {fild st0, dword [ecx+0x58]}
0043cdff        unimplemented  {fsub st0, dword [0x4972c0]}
0043ce05        unimplemented  {fld st0, dword [ebp+0x70]}
0043ce08        unimplemented  {fsub st0, dword [0x49720c]}
0043ce0e        float var_40_7 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043ce0e        unimplemented  {fstp dword [esp+0x10], st0}
0043ce0e        int16_t top_222 = top_212 - 1
0043ce12        long double temp57_1 = fconvert.t(var_40_7)
0043ce12        unimplemented  {fcom st0, dword [esp+0x10]} f- temp57_1
0043ce12        bool c0_63 = unimplemented  {fcom st0, dword [esp+0x10]} f< temp57_1
0043ce12        bool c2_63 = is_unordered.t(unimplemented  {fcom st0, dword [esp+0x10]}, temp57_1)
0043ce12        bool c3_63 = unimplemented  {fcom st0, dword [esp+0x10]} f== temp57_1
0043ce1b        if ((((c0_63 ? 1 : 0) << 8 | (c2_63 ? 1 : 0) << 0xa | (c3_63 ? 1 : 0) << 0xe | (top_222 & 7) << 0xb):1.b & 1) == 0)
0043ce1d        unimplemented  {fstp st0, st0}
0043ce1d        unimplemented  {fstp st0, st0}
0043ce1f        unimplemented  {fld st0, dword [esp+0x10]}
0043ce23        int32_t eax_102 = player_1->_pad_430[0x232c].d
0043ce29        player_1->__offset(0x2980).d = fconvert.s(unimplemented  {fstp dword [ebp+0x2980], st0})
0043ce29        unimplemented  {fstp dword [ebp+0x2980], st0}
0043ce29        int16_t top_224 = top_222 + 1
0043ce32        if (eax_102 == 1)
0043ce34        unimplemented  {fld st0, dword [ebp+0x6c]}
0043ce37        long double temp59_1 = fconvert.t(1f)
0043ce37        unimplemented  {fcomp st0, dword [0x497220]} f- temp59_1
0043ce37        bool c0_64 = unimplemented  {fcomp st0, dword [0x497220]} f< temp59_1
0043ce37        bool c2_64 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp59_1)
0043ce37        bool c3_64 = unimplemented  {fcomp st0, dword [0x497220]} f== temp59_1
0043ce37        unimplemented  {fcomp st0, dword [0x497220]}
0043ce3d        eax_102.w = (c0_64 ? 1 : 0) << 8 | (c2_64 ? 1 : 0) << 0xa | (c3_64 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043ce42        if ((eax_102:1.b & 1) != 0)
0043ce44        unimplemented  {fld st0, dword [ebp+0x414]}
0043ce4a        unimplemented  {fmul st0, dword [0x49726c]}
0043ce50        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fst dword [ebp+0x414], st0})
0043ce5c        unimplemented  {fld st0, dword [edx+0x38]}
0043ce5f        unimplemented  {fld st0, st0}
0043ce61        unimplemented  {fmul st0, st1}
0043ce63        unimplemented  {fmul st0, dword [0x4975cc]}
0043ce69        unimplemented  {fsubr st0, st2}
0043ce6b        player_1->_pad_3c0[0x54].d = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ce6b        unimplemented  {fstp dword [ebp+0x414], st0}
0043ce71        unimplemented  {fstp st0, st0}
0043ce71        unimplemented  {fstp st0, st0}
0043ce73        unimplemented  {fstp st0, st0}
0043ce73        unimplemented  {fstp st0, st0}
0043ce75        player_1->attachment_exit_pending = 0
0043ce7c        eax_102.b = player_1->attachment_exit_pending
0043ce84        if (eax_102.b != 0)
0043ce8a        unimplemented  {fld st0, dword [ebp+0x438]}
0043ce90        unimplemented  {fadd dword [ebp+0x434]}
0043ce96        player_1->_pad_430[4].d = fconvert.s(unimplemented  {fst dword [ebp+0x434], st0})
0043ce9c        long double temp61_1 = fconvert.t(0.699999988f)
0043ce9c        unimplemented  {fcomp st0, dword [0x497200]} f- temp61_1
0043ce9c        bool c0_65 = unimplemented  {fcomp st0, dword [0x497200]} f< temp61_1
0043ce9c        bool c2_65 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497200]}, temp61_1)
0043ce9c        bool c3_65 = unimplemented  {fcomp st0, dword [0x497200]} f== temp61_1
0043ce9c        unimplemented  {fcomp st0, dword [0x497200]}
0043cea2        eax_102.w = (c0_65 ? 1 : 0) << 8 | (c2_65 ? 1 : 0) << 0xa | (c3_65 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cea7        if ((eax_102:1.b & 0x41) == 0)
0043cea9        eax_102.b = player_1->_pad_430[0x1c]
0043ceb1        if (eax_102.b == 0)
0043ceb3        player_2 = 0xffffffff
0043cebd        play_voice_manager(0x751498, 3, 0, player_2)
0043cebd        esp = &__saved_edi
0043cec2        eax_102.b = player_1->_pad_74[0x264]
0043cec8        player_1->_pad_430[0x1c] = 1
0043ced1        if (eax_102.b == 0)
0043ced3        unimplemented  {fld st0, dword [ebp+0x6c]}
0043ced6        long double temp68_1 = fconvert.t(-6f)
0043ced6        unimplemented  {fcomp st0, dword [0x4975a8]} f- temp68_1
0043ced6        bool c0_66 = unimplemented  {fcomp st0, dword [0x4975a8]} f< temp68_1
0043ced6        bool c2_66 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975a8]}, temp68_1)
0043ced6        bool c3_66 = unimplemented  {fcomp st0, dword [0x4975a8]} f== temp68_1
0043ced6        unimplemented  {fcomp st0, dword [0x4975a8]}
0043cedc        eax_102.w = (c0_66 ? 1 : 0) << 8 | (c2_66 ? 1 : 0) << 0xa | (c3_66 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cee1        if ((eax_102:1.b & 1) != 0)
0043cee3        player_2 = 0xffffffff
0043ceef        dispatch_cutscene_animation(&player_1->_pad_00[0x2984], 5, 1, player_2)
0043ceef        esp = &__saved_edi
0043cef4        unimplemented  {fld st0, dword [ebp+0x6c]}
0043cef7        long double temp65_1 = fconvert.t(-7f)
0043cef7        unimplemented  {fcomp st0, dword [0x4975bc]} f- temp65_1
0043cef7        bool c0_67 = unimplemented  {fcomp st0, dword [0x4975bc]} f< temp65_1
0043cef7        bool c2_67 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975bc]}, temp65_1)
0043cef7        bool c3_67 = unimplemented  {fcomp st0, dword [0x4975bc]} f== temp65_1
0043cef7        unimplemented  {fcomp st0, dword [0x4975bc]}
0043cef7        top_224 = top_224
0043cefd        eax_102.w = (c0_67 ? 1 : 0) << 8 | (c2_67 ? 1 : 0) << 0xa | (c3_67 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cf02        if ((eax_102:1.b & 1) != 0)
0043cf04        eax_102.b = player_1->_pad_430[0x1d]
0043cf0c        if (eax_102.b == 0)
0043cf0e        player_2 = 0xffffffff
0043cf19        play_voice_manager(0x751498, 1, 2, player_2)
0043cf19        esp = &__saved_edi
0043cf1e        player_1->_pad_430[0x1d] = 1
0043cf25        player_1->_pad_430[0x1c] = 1
0043cf2c        unimplemented  {fld st0, dword [ebp+0x330]}
0043cf32        long double temp60_1 = fconvert.t(0f)
0043cf32        unimplemented  {fcomp st0, dword [0x497234]} f- temp60_1
0043cf32        bool c0_68 = unimplemented  {fcomp st0, dword [0x497234]} f< temp60_1
0043cf32        bool c2_68 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp60_1)
0043cf32        bool c3_68 = unimplemented  {fcomp st0, dword [0x497234]} f== temp60_1
0043cf32        unimplemented  {fcomp st0, dword [0x497234]}
0043cf38        eax_102.w = (c0_68 ? 1 : 0) << 8 | (c2_68 ? 1 : 0) << 0xa | (c3_68 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cf3d        if ((eax_102:1.b & 0x41) == 0)
0043cf3f        unimplemented  {fld st0, dword [ebp+0x334]}
0043cf45        unimplemented  {fadd dword [ebp+0x330]}
0043cf4b        player_1->_pad_74[0x2bc].d = fconvert.s(unimplemented  {fst dword [ebp+0x330], st0})
0043cf51        long double temp64_1 = fconvert.t(1f)
0043cf51        unimplemented  {fcomp st0, dword [0x497220]} f- temp64_1
0043cf51        bool c0_69 = unimplemented  {fcomp st0, dword [0x497220]} f< temp64_1
0043cf51        bool c2_69 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp64_1)
0043cf51        bool c3_69 = unimplemented  {fcomp st0, dword [0x497220]} f== temp64_1
0043cf51        unimplemented  {fcomp st0, dword [0x497220]}
0043cf57        eax_102.w = (c0_69 ? 1 : 0) << 8 | (c2_69 ? 1 : 0) << 0xa | (c3_69 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cf5c        if ((eax_102:1.b & 0x41) == 0)
0043cf5e        player_2 = 0xffffffff
0043cf69        play_voice_manager(0x751498, 7, 2, player_2)
0043cf69        esp = &__saved_edi
0043cf6e        player_1->_pad_74[0x2bc] = 0
0043cf6e        player_1->_pad_74[0x2bd] = 0
0043cf6e        player_1->_pad_74[0x2be] = 0
0043cf6e        player_1->_pad_74[0x2bf] = 0
0043cf7a        unimplemented  {fld st0, dword [eax+0x38]}
0043cf7d        unimplemented  {fmul st0, dword [0x4975b0]}
0043cf83        unimplemented  {fld st0, dword [eax+0x38]}
0043cf86        unimplemented  {fmul st0, dword [0x497228]}
0043cf8c        unimplemented  {fsub st0, st1}
0043cf8e        unimplemented  {fmul st0, dword [0x497258]}
0043cf94        unimplemented  {fadd st0, st1}
0043cf96        long double temp63_1 = fconvert.t(player_1->_pad_3c0[0x58].d)
0043cf96        unimplemented  {fcomp st0, dword [ebp+0x418]} f- temp63_1
0043cf96        bool c0_70 = unimplemented  {fcomp st0, dword [ebp+0x418]} f< temp63_1
0043cf96        bool c2_70 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x418]}, temp63_1)
0043cf96        bool c3_70 = unimplemented  {fcomp st0, dword [ebp+0x418]} f== temp63_1
0043cf96        unimplemented  {fcomp st0, dword [ebp+0x418]}
0043cfa1        int16_t top_241
0043cfa1        if ((((c0_70 ? 1 : 0) << 8 | (c2_70 ? 1 : 0) << 0xa | (c3_70 ? 1 : 0) << 0xe | ((top_224 - 1) & 7) << 0xb):1.b & 0x41) != 0)
0043cffa        unimplemented  {fstp st0, st0}
0043cffa        unimplemented  {fstp st0, st0}
0043cffa        top_241 = top_224
0043cffc        player_1->__offset(0x435c).d = 0
0043cfa3        long double temp67_1 = fconvert.t(player_1->_pad_3c0[0x58].d)
0043cfa3        unimplemented  {fcomp st0, dword [ebp+0x418]} f- temp67_1
0043cfa3        bool c0_71 = unimplemented  {fcomp st0, dword [ebp+0x418]} f< temp67_1
0043cfa3        bool c2_71 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x418]}, temp67_1)
0043cfa3        bool c3_71 = unimplemented  {fcomp st0, dword [ebp+0x418]} f== temp67_1
0043cfa3        unimplemented  {fcomp st0, dword [ebp+0x418]}
0043cfa3        top_241 = top_224
0043cfae        if ((((c0_71 ? 1 : 0) << 8 | (c2_71 ? 1 : 0) << 0xa | (c3_71 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb):1.b & 1) == 0)
0043cffc        player_1->__offset(0x435c).d = 0
0043cfb0        int16_t eax_103
0043cfb0        eax_103.b = player_1->attachment_exit_pending
0043cfc1        if (eax_103.b != 0 || player_1->_pad_74[0xac].d == 2)
0043cffc        player_1->__offset(0x435c).d = 0
0043cfc3        unimplemented  {fld st0, dword [ebp+0x4360]}
0043cfc9        unimplemented  {fadd dword [ebp+0x435c]}
0043cfcf        player_1->__offset(0x435c).d = fconvert.s(unimplemented  {fst dword [ebp+0x435c], st0})
0043cfd5        long double temp69_1 = fconvert.t(1f)
0043cfd5        unimplemented  {fcomp st0, dword [0x497220]} f- temp69_1
0043cfd5        bool c0_72 = unimplemented  {fcomp st0, dword [0x497220]} f< temp69_1
0043cfd5        bool c2_72 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp69_1)
0043cfd5        bool c3_72 = unimplemented  {fcomp st0, dword [0x497220]} f== temp69_1
0043cfd5        unimplemented  {fcomp st0, dword [0x497220]}
0043cfe0        if ((((c0_72 ? 1 : 0) << 8 | (c2_72 ? 1 : 0) << 0xa | (c3_72 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb):1.b & 0x41) == 0)
0043cfe2        player_2 = 0xffffffff
0043cfed        player_1->__offset(0x435c).d = 0
0043cff3        play_voice_manager(0x751498, 6, 1, player_2)
0043cff3        esp = &__saved_edi
0043d004        handle_subgoldy_collisions(player_1)
0043d00f        update_anim_manager(&player_1->_pad_00[0x2a88])
0043d01a        update_anim_manager(&player_1->_pad_00[0x3c6c])
0043d025        update_anim_manager(&player_1->_pad_00[0x30d8])
0043d030        update_anim_manager(&player_1->_pad_00[0x34b4])
0043d03b        update_anim_manager(&player_1->_pad_00[0x3890])
0043d04c        update_track_parcels(player_1->_pad_3c0[0x48].d + 0x125e480)
0043d057        initialize_cutscene(&player_1->_pad_00[0x2984])
0043d05e        update_player_movement_flags(player_1)
0043d06f        if (*(data_4df904 + 0x1066bf4) s< 0xa)
0043d071        int32_t ecx_153 = player_1->_pad_430[0x2304].d
0043d077        player_1->_pad_430[0x2300] = ecx_153.b
0043d077        player_1->_pad_430[0x2301] = ecx_153:1.b
0043d077        player_1->_pad_430[0x2302] = ecx_153:2.b
0043d077        player_1->_pad_430[0x2303] = ecx_153:3.b
0043d07d        void* ecx_154 = player_1->_pad_3c0[0x48].d
0043d08a        if ((*(ecx_154 + 0x4c) & &__dos_header) != 0)
0043d090        void* eax_104
0043d090        eax_104.b = player_1->_pad_430[0x10]
0043d098        if (eax_104.b == 0)
0043d09e        eax_104.b = player_1->_pad_74[0x264]
0043d0a6        if (eax_104.b == 0)
0043d0ac        int32_t eax_105 = player_1->_pad_74[0xac].d
0043d0b9        if (eax_105 == 0 || eax_105 == 4)
0043d0bf        unimplemented  {fld st0, dword [ebp+0x2730]}
0043d0c5        long double temp70_1 = fconvert.t(0f)
0043d0c5        unimplemented  {fcomp st0, dword [0x497234]} f- temp70_1
0043d0c5        bool c0_73 = unimplemented  {fcomp st0, dword [0x497234]} f< temp70_1
0043d0c5        bool c2_73 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp70_1)
0043d0c5        bool c3_73 = unimplemented  {fcomp st0, dword [0x497234]} f== temp70_1
0043d0c5        unimplemented  {fcomp st0, dword [0x497234]}
0043d0cb        eax_105.w = (c0_73 ? 1 : 0) << 8 | (c2_73 ? 1 : 0) << 0xa | (c3_73 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb
0043d0d0        if ((eax_105:1.b & 0x41) != 0)
0043d100        eax_105.b = *(ecx_154 + 0xa854)
0043d108        if (eax_105.b != 0)
0043d10e        char edx_57 = *(ecx_154 + 0xff25d0)
0043d116        if (edx_57 == 0)
0043d138        label_43d138:
0043d13f        if ((*(player_1->_pad_430[0xc].d + 4) & 0x4000) != 0)
0043d13f        goto label_43d143
0043d166        if (edx_57 != 0)
0043d166        goto label_43d168
0043d18b        label_43d18b:
0043d18e        if (((*(player_1->_pad_430[0xc].d + 0xc)).w:1.b & 0x40) != 0)
0043d18e        goto label_43d190
0043d12c        struct Player* entry_movement_source
0043d12c        if ((*(*(ecx_154 + 0xff25d4) + *(ecx_154 + 0xff25dc) * 6 + 0x74) & 1) != 0)
0043d143        label_43d143:
0043d143        play_movement_state_sound(player_1)
0043d148        player_2 = player_1
0043d148        esp = &player_2
0043d14b        update_movement_flag_emitters(player_2, entry_movement_source)
0043d150        unimplemented  {fld st0, dword [ebp+0x2734]}
0043d156        unimplemented  {fadd dword [0x4973d8]}
0043d15c        player_1->_pad_430[0x2300].d = fconvert.s(unimplemented  {fstp dword [ebp+0x2730], st0})
0043d15c        unimplemented  {fstp dword [ebp+0x2730], st0}
0043d130        if (edx_57 == 0)
0043d130        goto label_43d138
0043d168        label_43d168:
0043d17c        if ((*(*(ecx_154 + 0xff25d4) + *(ecx_154 + 0xff25dc) * 6 + 0x74) & 2) != 0)
0043d190        label_43d190:
0043d190        int32_t eax_112 = player_1->_pad_430[0x2304].d
0043d198        player_1->_pad_430[0x2300] = eax_112.b
0043d198        player_1->_pad_430[0x2301] = eax_112:1.b
0043d198        player_1->_pad_430[0x2302] = eax_112:2.b
0043d198        player_1->_pad_430[0x2303] = eax_112:3.b
0043d19e        play_movement_state_sound(player_1)
0043d1a3        player_2 = player_1
0043d1a3        esp = &player_2
0043d1a6        update_movement_flag_emitters(player_2, entry_movement_source)
0043d180        if (edx_57 == 0)
0043d180        goto label_43d18b
0043d0d2        unimplemented  {fld st0, dword [ebp+0x2734]}
0043d0d8        unimplemented  {fadd dword [ebp+0x2730]}
0043d0de        player_1->_pad_430[0x2300].d = fconvert.s(unimplemented  {fst dword [ebp+0x2730], st0})
0043d0e4        long double temp71_1 = fconvert.t(1f)
0043d0e4        unimplemented  {fcomp st0, dword [0x497220]} f- temp71_1
0043d0e4        bool c0_74 = unimplemented  {fcomp st0, dword [0x497220]} f< temp71_1
0043d0e4        bool c2_74 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp71_1)
0043d0e4        bool c3_74 = unimplemented  {fcomp st0, dword [0x497220]} f== temp71_1
0043d0e4        unimplemented  {fcomp st0, dword [0x497220]}
0043d0ea        eax_105.w = (c0_74 ? 1 : 0) << 8 | (c2_74 ? 1 : 0) << 0xa | (c3_74 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb
0043d0ef        if ((eax_105:1.b & 0x41) == 0)
0043d0f5        player_1->_pad_430[0x2300] = 0
0043d0f5        player_1->_pad_430[0x2301] = 0
0043d0f5        player_1->_pad_430[0x2302] = 0
0043d0f5        player_1->_pad_430[0x2303] = 0
0043d1b7        update_row_event_display(player_1->_pad_3c0[0x48].d + 0x12727d8)
0043d1bc        void* eax_113 = player_1->_pad_3c0[0x48].d
0043d1c9        *(eax_113 + 0xfd2b7c) += 1
0043d1cf        void* eax_114 = player_1->_pad_3c0[0x48].d
0043d1dc        *(eax_114 + 0xff25dc) += 1
0043d1e2        void* eax_115 = player_1->_pad_3c0[0x48].d
0043d1f2        if (*(eax_115 + 0xff25dc) == 0x5208)
0043d1fa        show_times_up_message(eax_115 + 0x1272828)
0043d20b        eax = update_times_up(player_1->_pad_3c0[0x48].d + 0x1272828)
0043b143        if (*(data_4df904 + 0x1b8) != 9)
0043b14f        update_damage_gauge(&player_1->_pad_3c0[4])
0043b15a        update_progress_bar()
0043b165        update_warning(&player_1->_pad_3c0[0x34])
0043b182        return update_row_event_display(player_1->_pad_3c0[0x48].d + 0x12727d8)
0043d210        *esp
0043d210        esp[1]
0043d211        esp[2]
0043d212        esp[3]
0043d217        return eax
