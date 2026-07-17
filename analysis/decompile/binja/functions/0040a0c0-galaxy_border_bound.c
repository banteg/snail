/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: galaxy_border_bound @ 0x40a0c0 */

0040a0cc        long double x87_r7_1
0040a0cc        if (widget->text_alignment != 2)
0040a14f        long double x87_r7_8 = fconvert.t(widget->layout_left)
0040a155        long double temp1_1 = fconvert.t(*min_x)
0040a155        x87_r7_8 - temp1_1
0040a15c        if ((((x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0040a15e        float eax_4
0040a15e        eax_4.b = widget->layout_left.b
0040a15e        eax_4:1.b = widget->layout_left:1.b
0040a15e        eax_4:2.b = widget->layout_left:2.b
0040a15e        eax_4:3.b = widget->layout_left:3.b
0040a164        *min_x = eax_4
0040a16c        x87_r7_1 = fconvert.t(widget->layout_width) + fconvert.t(widget->layout_left)
0040a178        long double temp3_1 = fconvert.t(*max_x)
0040a178        x87_r7_1 - temp3_1
0040a17f        if ((((x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0040a181        *max_x = fconvert.s(x87_r7_1)
0040a0d8        x87_r7_1 = fconvert.t(*max_x) - fconvert.t(*min_x)
0040a0da        long double temp2_1 = fconvert.t(widget->layout_width)
0040a0da        x87_r7_1 - temp2_1
0040a0e5        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0040a0f3        x87_r7_1 = fconvert.t(*min_x) - (fconvert.t(widget->layout_width) - x87_r7_1) * fconvert.t(0.5f)
0040a0f5        *min_x = fconvert.s(x87_r7_1)
0040a10b        *min_x = fconvert.s((fconvert.t(widget->layout_width) - (fconvert.t(*max_x) - x87_r7_1)) * fconvert.t(0.5f) + x87_r7_1)
0040a114        long double x87_r7_5 = fconvert.t(widget->layout_top)
0040a11a        long double temp4 = fconvert.t(*min_y)
0040a11a        x87_r7_5 - temp4
0040a121        if ((((x87_r7_5 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp4) ? 1 : 0) << 0xa | (x87_r7_5 == temp4 ? 1 : 0) << 0xe):1.b & 1) != 0)
0040a123        float eax_2
0040a123        eax_2.b = widget->layout_top.b
0040a123        eax_2:1.b = widget->layout_top:1.b
0040a123        eax_2:2.b = widget->layout_top:2.b
0040a123        eax_2:3.b = widget->layout_top:3.b
0040a129        *min_y = eax_2
0040a131        long double x87_r7_7 = fconvert.t(widget->layout_height) + fconvert.t(widget->layout_top)
0040a13d        long double temp5 = fconvert.t(*max_y)
0040a13d        x87_r7_7 - temp5
0040a144        if ((((x87_r7_7 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp5) ? 1 : 0) << 0xa | (x87_r7_7 == temp5 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0040a187        return
0040a146        *max_y = fconvert.s(x87_r7_7)
0040a148        return
