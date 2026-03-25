/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_nuke @ 0x4470e0 */

004470e6        if (*arg1 != 1)
004470e6        return 
004470ea        int32_t* esi_1 = &arg1[6]
004470ed        int32_t i_1 = 0x19
004470fd        int32_t i
004470f4        kill_sprite(*esi_1)
004470f9        esi_1 = &esi_1[1]
004470fc        i = i_1
004470fc        i_1 -= 1
004470fd        do while (i != 1)
00447100        *arg1 = 0
00447108        return
