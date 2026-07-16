/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_pressed_text_input_key_code @ 0x432440 */

00432443        char result = 0
0043244f        if (is_key_pressed_edge(0x1e) != 0)
00432451        result = 0x61
0043245f        if (is_key_pressed_edge(0x30) != 0)
00432461        result = 0x62
0043246f        if (is_key_pressed_edge(0x2e) != 0)
00432471        result = 0x63
0043247f        if (is_key_pressed_edge(0x20) != 0)
00432481        result = 0x64
0043248f        if (is_key_pressed_edge(0x12) != 0)
00432491        result = 0x65
0043249f        if (is_key_pressed_edge(0x21) != 0)
004324a1        result = 0x66
004324af        if (is_key_pressed_edge(0x22) != 0)
004324b1        result = 0x67
004324bf        if (is_key_pressed_edge(0x23) != 0)
004324c1        result = 0x68
004324cf        if (is_key_pressed_edge(0x17) != 0)
004324d1        result = 0x69
004324df        if (is_key_pressed_edge(0x24) != 0)
004324e1        result = 0x6a
004324ef        if (is_key_pressed_edge(0x25) != 0)
004324f1        result = 0x6b
004324ff        if (is_key_pressed_edge(0x26) != 0)
00432501        result = 0x6c
0043250f        if (is_key_pressed_edge(0x32) != 0)
00432511        result = 0x6d
0043251f        if (is_key_pressed_edge(0x31) != 0)
00432521        result = 0x6e
0043252f        if (is_key_pressed_edge(0x18) != 0)
00432531        result = 0x6f
0043253f        if (is_key_pressed_edge(0x19) != 0)
00432541        result = 0x70
0043254f        if (is_key_pressed_edge(0x10) != 0)
00432551        result = 0x71
0043255f        if (is_key_pressed_edge(0x13) != 0)
00432561        result = 0x72
0043256f        if (is_key_pressed_edge(0x1f) != 0)
00432571        result = 0x73
0043257f        if (is_key_pressed_edge(0x14) != 0)
00432581        result = 0x74
0043258f        if (is_key_pressed_edge(0x16) != 0)
00432591        result = 0x75
0043259f        if (is_key_pressed_edge(0x2f) != 0)
004325a1        result = 0x76
004325af        if (is_key_pressed_edge(0x11) != 0)
004325b1        result = 0x77
004325bf        if (is_key_pressed_edge(0x2d) != 0)
004325c1        result = 0x78
004325cf        if (is_key_pressed_edge(0x15) != 0)
004325d1        result = 0x79
004325df        if (is_key_pressed_edge(0x2c) != 0)
004325e1        result = 0x7a
004325eb        label_4325eb:
004325eb        char eax_26 = is_key_down(0x2a)
004325f5        char eax_27
004325f5        if (eax_26 == 0)
004325f9        eax_27 = is_key_down(0x36)
00432603        if (eax_26 != 0 || eax_27 != 0)
00432605        result -= 0x20
004325e7        if (result != 0)
004325e7        goto label_4325eb
00432614        if (is_key_pressed_edge(0x39) != 0)
00432616        result = 0x20
00432624        if (is_key_pressed_edge(0xb) != 0)
00432626        result = 0x30
00432634        if (is_key_pressed_edge(2) != 0)
00432636        result = 0x31
00432644        if (is_key_pressed_edge(3) != 0)
00432646        result = 0x32
00432654        if (is_key_pressed_edge(4) != 0)
00432656        result = 0x33
00432664        if (is_key_pressed_edge(5) != 0)
00432666        result = 0x34
00432674        if (is_key_pressed_edge(6) != 0)
00432676        result = 0x35
00432684        if (is_key_pressed_edge(7) != 0)
00432686        result = 0x36
00432694        if (is_key_pressed_edge(8) != 0)
00432696        result = 0x37
004326a4        if (is_key_pressed_edge(9) != 0)
004326a6        result = 0x38
004326b4        if (is_key_pressed_edge(0xa) != 0)
004326b6        result = 0x39
004326c4        if (is_key_pressed_edge(0x34) != 0)
004326c6        result = 0x2e
004326d4        if (is_key_pressed_edge(0x33) != 0)
004326d6        result = 0x2c
004326e4        if (is_key_pressed_edge(0x28) != 0)
004326e6        result = 0x27
004326f4        if (is_key_pressed_edge(0x2b) != 0)
004326f6        result = 0x5c
00432704        if (is_key_pressed_edge(0xe) != 0)
00432706        result = 1
00432717        if (is_key_pressed_edge(0xd3) != 0)
00432719        result = 2
0043272a        if (is_key_pressed_edge(0xcb) != 0)
0043272c        result = 3
0043273d        if (is_key_pressed_edge(0xcd) != 0)
0043273f        result = 4
00432750        if (is_key_pressed_edge(0xc8) != 0)
00432752        result = 7
00432763        if (is_key_pressed_edge(0xd0) != 0)
00432765        result = 8
00432776        if (is_key_pressed_edge(0xcf) != 0)
00432778        result = 9
00432789        if (is_key_pressed_edge(0xc7) != 0)
0043278b        result = 0xa
00432799        if (is_key_pressed_edge(1) != 0)
0043279b        result = 0xb
004327a9        if (is_key_pressed_edge(0x3b) != 0)
004327ab        result = 0xc
004327b9        if (is_key_pressed_edge(0x1c) == 0)
004327d2        return result
004327ce        return (is_key_down(0x1d) != 0) + 5
