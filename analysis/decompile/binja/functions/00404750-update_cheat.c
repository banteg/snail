/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cheat @ 0x404750 */

00404753        char* result = read_pressed_text_input_key_code()
0040475e        if (result.b s>= 0x61 && result.b s<= 0x7a)
00404760        result.b -= 0x20
00404768        if (result.b s>= 0x41 && result.b s<= 0x5a)
0040476f        int32_t ebx
0040476f        int32_t var_8_1 = ebx
00404771        char* ecx = arg1 + 0xf
00404776        ebx.b = ecx[0xffffffff]
00404779        *ecx = ebx.b
0040477b        ecx -= 1
00404781        do while (0xfffffff8 - arg1 + ecx s> 0)
0040478a        arg1[2].b = result.b
00404796        if (match_cheat_text(arg1, "NEWTON") != 0)
0040479a        int32_t eax_1
0040479a        eax_1.b = (*arg1).b | 1
0040479c        *arg1 = eax_1
004047ac        if (match_cheat_text(arg1, "AUTUMN") != 0)
004047b0        int32_t eax_3
004047b0        eax_3.b = (*arg1).b | 2
004047b2        *arg1 = eax_3
004047bb        result = match_cheat_text(arg1, "SHEEP")
004047c2        if (result.b != 0)
004047c6        result.b = (*arg1).b | 4
004047c8        *arg1 = result
004047cb        return result
