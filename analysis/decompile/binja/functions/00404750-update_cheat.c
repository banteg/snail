/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cheat @ 0x404750 */

00404753        char eax = read_pressed_text_input_key_code()
0040475e        if (eax s>= 0x61 && eax s<= 0x7a)
00404760        eax -= 0x20
00404768        if (eax s< 0x41 || eax s> 0x5a)
00404768        return
0040476f        int32_t ebx
0040476f        int32_t var_8_1 = ebx
00404771        char* recent_text_cursor = &cheat->recent_text.bytes[7]
00404779        *recent_text_cursor = recent_text_cursor[0xffffffff]
0040477b        recent_text_cursor -= 1
00404781        do while (0xfffffff8 - cheat + recent_text_cursor s> 0)
0040478a        cheat->recent_text.bytes.b = eax
00404796        if (match_cheat_text(cheat, "NEWTON") != 0)
00404798        uint32_t flags = cheat->flags
0040479a        flags.b |= 1
0040479c        cheat->flags = flags
004047ac        if (match_cheat_text(cheat, "AUTUMN") != 0)
004047ae        uint32_t flags_1 = cheat->flags
004047b0        flags_1.b |= 2
004047b2        cheat->flags = flags_1
004047c2        if (match_cheat_text(cheat, "SHEEP") == 0)
004047c2        return
004047c4        uint32_t flags_2 = cheat->flags
004047c6        flags_2.b |= 4
004047c8        cheat->flags = flags_2
004047cb        return
