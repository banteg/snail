/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_repeating_text_input_key_code @ 0x4327e0 */

004327e4        int32_t ebx
004327e4        ebx.b = 0
004327e8        char var_4 = 0
004327f6        if (is_key_down(0x1e) != 0)
004327f8        ebx.b = 0x61
004327fa        var_4 = 0x61
0043280a        if (is_key_down(0x30) != 0)
0043280c        ebx.b = 0x62
0043280e        var_4 = 0x62
0043281e        if (is_key_down(0x2e) != 0)
00432820        ebx.b = 0x63
00432822        var_4 = 0x63
00432832        if (is_key_down(0x20) != 0)
00432834        ebx.b = 0x64
00432836        var_4 = 0x64
00432846        if (is_key_down(0x12) != 0)
00432848        ebx.b = 0x65
0043284a        var_4 = 0x65
0043285a        if (is_key_down(0x21) != 0)
0043285c        ebx.b = 0x66
0043285e        var_4 = 0x66
0043286e        if (is_key_down(0x22) != 0)
00432870        ebx.b = 0x67
00432872        var_4 = 0x67
00432882        if (is_key_down(0x23) != 0)
00432884        ebx.b = 0x68
00432886        var_4 = 0x68
00432896        if (is_key_down(0x17) != 0)
00432898        ebx.b = 0x69
0043289a        var_4 = 0x69
004328aa        if (is_key_down(0x24) != 0)
004328ac        ebx.b = 0x6a
004328ae        var_4 = 0x6a
004328be        if (is_key_down(0x25) != 0)
004328c0        ebx.b = 0x6b
004328c2        var_4 = 0x6b
004328d2        if (is_key_down(0x26) != 0)
004328d4        ebx.b = 0x6c
004328d6        var_4 = 0x6c
004328e6        if (is_key_down(0x32) != 0)
004328e8        ebx.b = 0x6d
004328ea        var_4 = 0x6d
004328fa        if (is_key_down(0x31) != 0)
004328fc        ebx.b = 0x6e
004328fe        var_4 = 0x6e
0043290e        if (is_key_down(0x18) != 0)
00432910        ebx.b = 0x6f
00432912        var_4 = 0x6f
00432922        if (is_key_down(0x19) != 0)
00432924        ebx.b = 0x70
00432926        var_4 = 0x70
00432936        if (is_key_down(0x10) != 0)
00432938        ebx.b = 0x71
0043293a        var_4 = 0x71
0043294a        if (is_key_down(0x13) != 0)
0043294c        ebx.b = 0x72
0043294e        var_4 = 0x72
0043295e        if (is_key_down(0x1f) != 0)
00432960        ebx.b = 0x73
00432962        var_4 = 0x73
00432972        if (is_key_down(0x14) != 0)
00432974        ebx.b = 0x74
00432976        var_4 = 0x74
00432986        if (is_key_down(0x16) != 0)
00432988        ebx.b = 0x75
0043298a        var_4 = 0x75
0043299a        if (is_key_down(0x2f) != 0)
0043299c        ebx.b = 0x76
0043299e        var_4 = 0x76
004329ae        if (is_key_down(0x11) != 0)
004329b0        ebx.b = 0x77
004329b2        var_4 = 0x77
004329c2        if (is_key_down(0x2d) != 0)
004329c4        ebx.b = 0x78
004329c6        var_4 = 0x78
004329d6        if (is_key_down(0x15) != 0)
004329d8        ebx.b = 0x79
004329da        var_4 = 0x79
004329ea        if (is_key_down(0x2c) != 0)
004329ec        ebx.b = 0x7a
004329ee        var_4 = 0x7a
004329fa        label_4329fa:
004329fa        char eax_26 = is_key_down(0x2a)
00432a04        char eax_27
00432a04        if (eax_26 == 0)
00432a08        eax_27 = is_key_down(0x36)
00432a12        if (eax_26 != 0 || eax_27 != 0)
00432a14        ebx.b -= 0x20
00432a17        var_4 = ebx.b
004329f6        if (ebx.b != 0)
004329f6        goto label_4329fa
00432a27        if (is_key_down(0x39) != 0)
00432a29        ebx.b = 0x20
00432a2b        var_4 = 0x20
00432a3b        if (is_key_down(0xb) != 0)
00432a3d        ebx.b = 0x30
00432a3f        var_4 = 0x30
00432a4f        if (is_key_down(2) != 0)
00432a51        ebx.b = 0x31
00432a53        var_4 = 0x31
00432a63        if (is_key_down(3) != 0)
00432a65        ebx.b = 0x32
00432a67        var_4 = 0x32
00432a77        if (is_key_down(4) != 0)
00432a79        ebx.b = 0x33
00432a7b        var_4 = 0x33
00432a8b        if (is_key_down(5) != 0)
00432a8d        ebx.b = 0x34
00432a8f        var_4 = 0x34
00432a9f        if (is_key_down(6) != 0)
00432aa1        ebx.b = 0x35
00432aa3        var_4 = 0x35
00432ab3        if (is_key_down(7) != 0)
00432ab5        ebx.b = 0x36
00432ab7        var_4 = 0x36
00432ac7        if (is_key_down(8) != 0)
00432ac9        ebx.b = 0x37
00432acb        var_4 = 0x37
00432adb        if (is_key_down(9) != 0)
00432add        ebx.b = 0x38
00432adf        var_4 = 0x38
00432aef        if (is_key_down(0xa) != 0)
00432af1        ebx.b = 0x39
00432af3        var_4 = 0x39
00432b03        if (is_key_down(0x34) != 0)
00432b05        ebx.b = 0x2e
00432b07        var_4 = 0x2e
00432b17        if (is_key_down(0x33) != 0)
00432b19        ebx.b = 0x2c
00432b1b        var_4 = 0x2c
00432b2b        if (is_key_down(0x28) != 0)
00432b2d        ebx.b = 0x27
00432b2f        var_4 = 0x27
00432b3f        if (is_key_down(0x2b) != 0)
00432b41        ebx.b = 0x5c
00432b43        var_4 = 0x5c
00432b53        if (is_key_down(0xe) != 0)
00432b55        ebx.b = 1
00432b57        var_4 = 1
00432b6a        if (is_key_down(0xd3) != 0)
00432b6c        ebx.b = 2
00432b6e        var_4 = 2
00432b81        if (is_key_down(0xcb) != 0)
00432b83        ebx.b = 3
00432b85        var_4 = 3
00432b98        if (is_key_down(0xcd) != 0)
00432b9a        ebx.b = 4
00432b9c        var_4 = 4
00432baf        if (is_key_down(0xc8) != 0)
00432bb1        ebx.b = 7
00432bb3        var_4 = 7
00432bc6        if (is_key_down(0xd0) != 0)
00432bc8        ebx.b = 8
00432bca        var_4 = 8
00432bdd        if (is_key_down(0xcf) != 0)
00432bdf        ebx.b = 9
00432be1        var_4 = 9
00432bf4        if (is_key_down(0xc7) != 0)
00432bf6        ebx.b = 0xa
00432bf8        var_4 = 0xa
00432c08        if (is_key_down(1) != 0)
00432c0a        ebx.b = 0xb
00432c0c        var_4 = 0xb
00432c1c        if (is_key_down(0x3b) != 0)
00432c1e        ebx.b = 0xc
00432c20        var_4 = 0xc
00432c30        if (is_key_down(0x1c) == 0)
00432c7e        if (ebx.b != 0)
00432c7e        goto label_432c48
00432c80        g_text_input_repeat_accumulator = 0f
00432c8a        g_text_input_last_repeat_code = ebx.b
00432c3e        ebx.b = is_key_down(0x1d) != 0
00432c41        ebx += 5
00432c44        var_4 = ebx.b
00432c48        label_432c48:
00432c48        long double x87_r7_1 = fconvert.t(g_text_input_repeat_accumulator)
00432c4e        long double temp0_1 = fconvert.t(0f)
00432c4e        x87_r7_1 - temp0_1
00432c54        int16_t eax_54 = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
00432c59        if ((eax_54:1.b & 0x40) != 0)
00432c5b        g_text_input_last_repeat_code = ebx.b
00432c61        eax_54.b = ebx.b
00432c63        g_text_input_repeat_step = 0.0333333351f
00432c6d        g_text_input_repeat_accumulator = 0.0333333351f
00432c7b        return eax_54.b
00432cbc        if (ascii_upper_if_lowercase(var_4) != ascii_upper_if_lowercase(g_text_input_last_repeat_code))
00432cf8        g_text_input_last_repeat_code = ebx.b
00432d00        g_text_input_repeat_step = 0.0111111114f
00432d0a        g_text_input_repeat_accumulator = 0.0111111114f
00432d18        return ebx.b
00432cc4        long double x87_r7_3 = fconvert.t(g_text_input_repeat_step) + fconvert.t(g_text_input_repeat_accumulator)
00432cca        g_text_input_repeat_accumulator = fconvert.s(x87_r7_3)
00432cd0        long double temp1_1 = fconvert.t(1f)
00432cd0        x87_r7_3 - temp1_1
00432cd6        int16_t eax_59 = (x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe
00432cdb        if ((eax_59:1.b & 0x41) == 0)
00432cdd        eax_59.b = ebx.b
00432cdf        g_text_input_repeat_step = 0.111111104f
00432ce9        g_text_input_repeat_accumulator = 0.111111104f
00432cf7        return eax_59.b
00432c90        int32_t eax_55
00432c90        eax_55.b = 0
00432c96        return 0
