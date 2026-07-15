/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_twinkle @ 0x404080 */

0040408a        long double x87_r7_1 = fconvert.t(twinkle->angle) + fconvert.t(twinkle->angle_step)
0040408d        long double temp0 = fconvert.t(6.28318548f)
0040408d        x87_r7_1 - temp0
00404093        twinkle->angle = fconvert.s(x87_r7_1)
00404093        bool c1 = unknown  {fst dword [esi+0x18], st0}
0040409b        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
004040a8        long double temp1_1 = fconvert.t(0f)
004040a8        x87_r7_1 - temp1_1
004040b3        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004040bb        twinkle->angle = fconvert.s(x87_r7_1 + fconvert.t(6.28318548f))
004040a3        twinkle->angle = fconvert.s(x87_r7_1 - fconvert.t(6.28318548f))
004040c2        int32_t state = twinkle->state
004040c5        if (state == 1)
004041a4        int16_t widget_flags = (twinkle->owner_widget->widget_flags).w
004041b5        if ((widget_flags.b & 2) != 0 && (widget_flags:1.b & 0x80) == 0)
004041be        long double x87_r7_22 = fconvert.t(twinkle->delay_progress) + fconvert.t(twinkle->delay_step)
004041c1        twinkle->delay_progress = fconvert.s(x87_r7_22)
004041c4        long double temp6_1 = fconvert.t(1f)
004041c4        x87_r7_22 - temp6_1
004041cf        if ((((x87_r7_22 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp6_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004041d7        twinkle->state = 2
004041dd        twinkle->alpha = 0f
004041e0        __builtin_strncpy(&twinkle->target_alpha, "fff?", 4)
00404200        twinkle->angle = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f))
00404216        long double x87_r7_28 = (float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f)
0040421c        long double temp9_1 = fconvert.t(0f)
0040421c        x87_r7_28 - temp9_1
00404227        int32_t var_8_4
00404227        if ((((x87_r7_28 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp9_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp9_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00404240        var_8_4 = 0
0040424a        long double x87_r7_31 = (float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f)
00404250        long double temp11_1 = fconvert.t(0f)
00404250        x87_r7_31 - temp11_1
0040425b        if ((((x87_r7_31 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp11_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0040425d        var_8_4 = 1
00404229        var_8_4 = 0xffffffff
00404265        int32_t eax_15 = next_math_random_value()
0040426e        twinkle->delay_progress = 0f
00404275        struct FrontendWidget* owner_widget = twinkle->owner_widget
00404278        twinkle->delay_step = 1f
004042a7        twinkle->angle_step = fconvert.s(fconvert.t(1f) / (((float.t(eax_15) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f) + fconvert.t(5f)) * fconvert.t(60f)) * float.t(var_8_4) * fconvert.t(6.28318548f))
004042b3        long double x87_r7_40 = float.t(next_math_random_value())
004042dd        struct FrontendWidget* owner_widget_1 = twinkle->owner_widget
004042e2        twinkle->x = fconvert.s(x87_r7_40 * fconvert.t(owner_widget->layout_width) * fconvert.t(0.800000012f) * fconvert.t(3.05175781e-05f) + fconvert.t(owner_widget->layout_left) + fconvert.t(owner_widget->layout_width) * fconvert.t(0.100000001f))
0040431a        twinkle->y = fconvert.s(float.t(next_math_random_value()) * fconvert.t(owner_widget_1->layout_height) * fconvert.t(0.800000012f) * fconvert.t(3.05175781e-05f) + fconvert.t(owner_widget_1->layout_height) * fconvert.t(0.100000001f) + fconvert.t(owner_widget_1->layout_top))
0040433c        twinkle->size = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000732421875f) + fconvert.t(25f))
004040cc        if (state == 2)
00404162        long double x87_r7_19 = (fconvert.t(twinkle->target_alpha) - fconvert.t(twinkle->alpha)) * fconvert.t(0.100000001f) + fconvert.t(twinkle->alpha)
00404165        twinkle->alpha = fconvert.s(x87_r7_19)
00404168        long double x87_r7_20 = fconvert.t(twinkle->target_alpha) - x87_r7_19
0040416b        long double temp4 = fconvert.t(0f)
0040416b        x87_r7_20 - temp4
00404176        if ((((x87_r7_20 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp4) ? 1 : 0) << 0xa | (x87_r7_20 == temp4 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00404178        x87_r7_20 = fneg(x87_r7_20)
0040417a        long double temp7 = fconvert.t(0.00999999978f)
0040417a        x87_r7_20 - temp7
00404185        if ((((x87_r7_20 < temp7 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp7) ? 1 : 0) << 0xa | (x87_r7_20 == temp7 ? 1 : 0) << 0xe):1.b & 1) != 0)
00404187        twinkle->target_alpha = 0f
0040418e        twinkle->state = 4
00404196        draw_twinkle(twinkle)
004041a0        return
004040d5        if (state == 4)
004040ec        twinkle->alpha = fconvert.s((fconvert.t(twinkle->target_alpha) - fconvert.t(twinkle->alpha)) * fconvert.t(0.100000001f) + fconvert.t(twinkle->alpha))
004040ef        draw_twinkle(twinkle)
004040f7        long double x87_r7_10 = fconvert.t(twinkle->target_alpha) - fconvert.t(twinkle->alpha)
004040fa        long double temp8_1 = fconvert.t(0f)
004040fa        x87_r7_10 - temp8_1
00404105        if ((((x87_r7_10 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp8_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp8_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00404107        x87_r7_10 = fneg(x87_r7_10)
00404109        long double temp10_1 = fconvert.t(0.00999999978f)
00404109        x87_r7_10 - temp10_1
00404114        if ((((x87_r7_10 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp10_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp10_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0040411c        twinkle->state = 1
00404122        twinkle->alpha = 0f
00404125        twinkle->delay_progress = 0f
0040414e        twinkle->delay_step = fconvert.s(fconvert.t(1f) / ((float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f) + fconvert.t(0.00999999978f)) * fconvert.t(60f)))
00404344        return
