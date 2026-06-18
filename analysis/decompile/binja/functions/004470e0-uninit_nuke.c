/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_nuke @ 0x4470e0 */

004470e6        if (nuke->state != 1)
004470e6        return 
004470ea        Sprite** sprite_slots = nuke->sprite_slots
004470ed        int32_t i_1 = 0x19
004470fd        int32_t i
004470f4        kill_sprite(*sprite_slots)
004470f9        sprite_slots = &sprite_slots[1]
004470fc        i = i_1
004470fc        i_1 -= 1
004470fd        do while (i != 1)
00447100        nuke->state = 0
00447108        return
