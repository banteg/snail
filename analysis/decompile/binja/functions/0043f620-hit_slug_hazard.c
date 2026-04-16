/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hit_slug_hazard @ 0x43f620 */

0043f627        int32_t ecx = arg1->_pad_b4[0x14].d
0043f62d        int32_t ecx_1 = ecx - arg2
0043f62f        arg1->_pad_b4[0x14] = ecx_1.b
0043f62f        arg1->_pad_b4[0x15] = ecx_1:1.b
0043f62f        arg1->_pad_b4[0x16] = ecx_1:2.b
0043f62f        arg1->_pad_b4[0x17] = ecx_1:3.b
0043f635        if (ecx - arg2 s>= 0)
0043f64c        arg1->_pad_b4[0x18] = 1
0043f67b        int16_t x87control
0043f67b        return play_slug_voice(arg1, 0x24 - __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-9.15527344e-05f)))
0043f639        arg1->_pad_b4[0x14] = 0
0043f639        arg1->_pad_b4[0x15] = 0
0043f639        arg1->_pad_b4[0x16] = 0
0043f639        arg1->_pad_b4[0x17] = 0
0043f649        return kill_slug_hazard(arg1)
