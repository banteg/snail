/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy_fall_state @ 0x43af60 */

0043af6a        if (player->__offset(0x384).b == 0)
0043af8c        player->__offset(0x430).d = 0
0043af92        player->__offset(0x42c).d = 0
0043af78        player->__offset(0x430).d = *(player->__offset(0x388).d + 0x98)
0043af84        player->__offset(0x42c).d = player->__offset(0x3a0).d
0043af98        int32_t edx_4 = player->__offset(0x70).d
0043af9b        player->__offset(0x384).b = 0
0043afa1        player->__offset(0x41d).b = 1
0043afa8        player->__offset(0x424).d = edx_4
0043afae        player->__offset(0x434).d = 0
0043afb4        player->__offset(0x44c).b = 0
0043afba        player->__offset(0x44d).b = 0
0043afc0        return 0
