/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_pressed_text_input_key_code @ 0x432440 */

00432443        int32_t ebx
00432443        ebx.b = 0
0043244f        if (is_key_pressed_edge(0x1e) != 0)
00432451        ebx.b = 0x61
0043245f        if (is_key_pressed_edge(0x30) != 0)
00432461        ebx.b = 0x62
0043246f        if (is_key_pressed_edge(0x2e) != 0)
00432471        ebx.b = 0x63
0043247f        if (is_key_pressed_edge(0x20) != 0)
00432481        ebx.b = 0x64
0043248f        if (is_key_pressed_edge(0x12) != 0)
00432491        ebx.b = 0x65
0043249f        if (is_key_pressed_edge(0x21) != 0)
004324a1        ebx.b = 0x66
004324af        if (is_key_pressed_edge(0x22) != 0)
004324b1        ebx.b = 0x67
004324bf        if (is_key_pressed_edge(0x23) != 0)
004324c1        ebx.b = 0x68
004324cf        if (is_key_pressed_edge(0x17) != 0)
004324d1        ebx.b = 0x69
004324df        if (is_key_pressed_edge(0x24) != 0)
004324e1        ebx.b = 0x6a
004324ef        if (is_key_pressed_edge(0x25) != 0)
004324f1        ebx.b = 0x6b
004324ff        if (is_key_pressed_edge(0x26) != 0)
00432501        ebx.b = 0x6c
0043250f        if (is_key_pressed_edge(0x32) != 0)
00432511        ebx.b = 0x6d
0043251f        if (is_key_pressed_edge(0x31) != 0)
00432521        ebx.b = 0x6e
0043252f        if (is_key_pressed_edge(0x18) != 0)
00432531        ebx.b = 0x6f
0043253f        if (is_key_pressed_edge(0x19) != 0)
00432541        ebx.b = 0x70
0043254f        if (is_key_pressed_edge(0x10) != 0)
00432551        ebx.b = 0x71
0043255f        if (is_key_pressed_edge(0x13) != 0)
00432561        ebx.b = 0x72
0043256f        if (is_key_pressed_edge(0x1f) != 0)
00432571        ebx.b = 0x73
0043257f        if (is_key_pressed_edge(0x14) != 0)
00432581        ebx.b = 0x74
0043258f        if (is_key_pressed_edge(0x16) != 0)
00432591        ebx.b = 0x75
0043259f        if (is_key_pressed_edge(0x2f) != 0)
004325a1        ebx.b = 0x76
004325af        if (is_key_pressed_edge(0x11) != 0)
004325b1        ebx.b = 0x77
004325bf        if (is_key_pressed_edge(0x2d) != 0)
004325c1        ebx.b = 0x78
004325cf        if (is_key_pressed_edge(0x15) != 0)
004325d1        ebx.b = 0x79
004325df        if (is_key_pressed_edge(0x2c) != 0)
004325e1        ebx.b = 0x7a
004325eb        label_4325eb:
004325eb        char eax_26 = is_key_down(0x2a)
004325f5        char eax_27
004325f5        if (eax_26 == 0)
004325f9        eax_27 = is_key_down(0x36)
00432603        if (eax_26 != 0 || eax_27 != 0)
00432605        ebx.b -= 0x20
004325e7        if (ebx.b != 0)
004325e7        goto label_4325eb
00432614        if (is_key_pressed_edge(0x39) != 0)
00432616        ebx.b = 0x20
00432624        if (is_key_pressed_edge(0xb) != 0)
00432626        ebx.b = 0x30
00432634        if (is_key_pressed_edge(2) != 0)
00432636        ebx.b = 0x31
00432644        if (is_key_pressed_edge(3) != 0)
00432646        ebx.b = 0x32
00432654        if (is_key_pressed_edge(4) != 0)
00432656        ebx.b = 0x33
00432664        if (is_key_pressed_edge(5) != 0)
00432666        ebx.b = 0x34
00432674        if (is_key_pressed_edge(6) != 0)
00432676        ebx.b = 0x35
00432684        if (is_key_pressed_edge(7) != 0)
00432686        ebx.b = 0x36
00432694        if (is_key_pressed_edge(8) != 0)
00432696        ebx.b = 0x37
004326a4        if (is_key_pressed_edge(9) != 0)
004326a6        ebx.b = 0x38
004326b4        if (is_key_pressed_edge(0xa) != 0)
004326b6        ebx.b = 0x39
004326c4        if (is_key_pressed_edge(0x34) != 0)
004326c6        ebx.b = 0x2e
004326d4        if (is_key_pressed_edge(0x33) != 0)
004326d6        ebx.b = 0x2c
004326e4        if (is_key_pressed_edge(0x28) != 0)
004326e6        ebx.b = 0x27
004326f4        if (is_key_pressed_edge(0x2b) != 0)
004326f6        ebx.b = 0x5c
00432704        if (is_key_pressed_edge(0xe) != 0)
00432706        ebx.b = 1
00432717        if (is_key_pressed_edge(0xd3) != 0)
00432719        ebx.b = 2
0043272a        if (is_key_pressed_edge(0xcb) != 0)
0043272c        ebx.b = 3
0043273d        if (is_key_pressed_edge(0xcd) != 0)
0043273f        ebx.b = 4
00432750        if (is_key_pressed_edge(0xc8) != 0)
00432752        ebx.b = 7
00432763        if (is_key_pressed_edge(0xd0) != 0)
00432765        ebx.b = 8
00432776        if (is_key_pressed_edge(0xcf) != 0)
00432778        ebx.b = 9
00432789        if (is_key_pressed_edge(0xc7) != 0)
0043278b        ebx.b = 0xa
00432799        if (is_key_pressed_edge(1) != 0)
0043279b        ebx.b = 0xb
004327a9        if (is_key_pressed_edge(0x3b) != 0)
004327ab        ebx.b = 0xc
004327b9        if (is_key_pressed_edge(0x1c) == 0)
004327d2        return ebx.b
004327c7        uint32_t eax_54
004327c7        eax_54.b = is_key_down(0x1d).b != 0
004327ce        return eax_54 + 5
