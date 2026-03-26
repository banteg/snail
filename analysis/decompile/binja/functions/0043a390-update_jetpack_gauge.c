/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_jetpack_gauge @ 0x43a390 */

0043a399        int32_t state = gauge->state
0043a39c        int32_t state_1 = state
0043a39e        if (state != 0)
0043a3a4        int32_t state_2 = state_1
0043a3a4        state_1 -= 1
0043a3a5        if (state_2 == 1)
0043a3b0        float var_8_1 = fconvert.s(fconvert.t(gauge->cycle_phase) + fconvert.t(gauge->progress))
0043a3b4        long double x87_r7_3 = fconvert.t(var_8_1)
0043a3b8        long double temp2_1 = fconvert.t(1f)
0043a3b8        x87_r7_3 - temp2_1
0043a3c2        gauge->progress = var_8_1
0043a3c4        float eax
0043a3c4        eax.w = (x87_r7_3 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp2_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp2_1 ? 1 : 0) << 0xe
0043a3c9        if ((eax:1.b & 0x41) != 0)
0043a3d5        void* warning_anchor = gauge->warning_anchor
0043a3e2        long double x87_r7_4 = float.t(gauge->game->__offset(0x58).d - 5)
0043a3e6        long double temp4_1 = fconvert.t(*(warning_anchor + 0x70))
0043a3e6        x87_r7_4 - temp4_1
0043a3e9        int32_t eax_2
0043a3e9        eax_2.w = (x87_r7_4 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp4_1 ? 1 : 0) << 0xe
0043a3ee        if ((eax_2:1.b & 1) == 0)
0043a3f4        long double x87_r7_5 = fconvert.t(var_8_1)
0043a3f8        long double temp5 = fconvert.t(0.100000001f)
0043a3f8        x87_r7_5 - temp5
0043a3fe        long double x87_r7_6 = fconvert.t(var_8_1)
0043a402        eax_2.w = (x87_r7_5 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp5) ? 1 : 0) << 0xa | (x87_r7_5 == temp5 ? 1 : 0) << 0xe | 0x3800
0043a407        if ((eax_2:1.b & 1) == 0)
0043a41a        long double temp6_1 = fconvert.t(0.939999998f)
0043a41a        x87_r7_6 - temp6_1
0043a420        eax_2.w = (x87_r7_6 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp6_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp6_1 ? 1 : 0) << 0xe
0043a425        if ((eax_2:1.b & 0x41) != 0)
0043a46c        gauge->warning_intensity = 1f
0043a476        void* eax_3 = data_4df904
0043a48d        warning_anchor = *get_track_runtime_cell_at_world_z(eax_3 + 0x74618, eax_3 + 0x42fde4)
0043a492        if ((warning_anchor:1.b & 0x80) != 0)
0043a494        char* var_14_2 = "Auto Shutoff Jetpack\n"
0043a499        gauge->progress = 0x3f70a3d7
0043a437        gauge->warning_intensity = fconvert.s((fconvert.t(1f) - fconvert.t(var_8_1)) * fconvert.t(16.6666679f))
0043a441        long double x87_r7_12 = fconvert.t(var_8_1) - fconvert.t(gauge->cycle_phase)
0043a444        long double temp7_1 = fconvert.t(0.939999998f)
0043a444        x87_r7_12 - temp7_1
0043a44a        eax_2.w = (x87_r7_12 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp7_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp7_1 ? 1 : 0) << 0xe
0043a44f        if ((eax_2:1.b & 0x41) != 0)
0043a45e        set_snail_jetpack(data_4df904 + 0x432700, 0)
0043a465        warning_anchor = uninit_jet_particles(gauge)
0043a40f        gauge->warning_intensity = fconvert.s(x87_r7_6 * fconvert.t(10f))
0043a4b3        void* warning_anchor_1 = warning_anchor
0043a4ce        gauge->warning_intensity = fconvert.s(fconvert.t(1f) - (cosine(fconvert.s(fconvert.t(gauge->warning_intensity) * fconvert.t(3.14159274f))) + fconvert.t(1f)) * fconvert.t(0.5f))
0043a4f0        gauge->wobble_x = fconvert.s(sine(fconvert.s(fconvert.t(gauge->progress) * fconvert.t(25.1327419f))) * fconvert.t(gauge->warning_intensity) * fconvert.t(0.25f))
0043a503        long double x87_r7_27 = sine(fconvert.s(fconvert.t(gauge->progress) * fconvert.t(37.6991119f))) * fconvert.t(0.25f)
0043a50e        float warning_intensity = gauge->warning_intensity
0043a520        float progress = gauge->progress
0043a521        void* var_18 = gauge->warning_anchor + 0x68
0043a524        long double x87_r7_29 = (x87_r7_27 + fconvert.t(1f)) * fconvert.t(gauge->warning_intensity)
0043a52a        gauge->wobble_alpha = 0f
0043a52d        gauge->_pad_204[8] = warning_intensity.b
0043a52d        gauge->_pad_204[9] = warning_intensity:1.b
0043a52d        gauge->_pad_204[0xa] = warning_intensity:2.b
0043a52d        gauge->_pad_204[0xb] = warning_intensity:3.b
0043a533        gauge->wobble_y = fconvert.s(x87_r7_29)
0043a540        return warning_intensity
0043a543        end_jetpack_hover(gauge)
0043a548        long double x87_r7_30 = fconvert.t(gauge->progress)
0043a54a        long double temp3_1 = fconvert.t(0.939999998f)
0043a54a        x87_r7_30 - temp3_1
0043a550        state_1.w = (x87_r7_30 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_30, temp3_1) ? 1 : 0) << 0xa | (x87_r7_30 == temp3_1 ? 1 : 0) << 0xe
0043a555        if ((state_1:1.b & 0x41) != 0)
0043a563        state_1 = set_snail_jetpack(data_4df904 + 0x432700, 0)
0043a568        gauge->state = 0
0043a56b        gauge->wobble_alpha = 0f
0043a56e        gauge->wobble_y = 0f
0043a571        gauge->wobble_x = 0f
0043a579        return state_1
