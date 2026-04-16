/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_parcel_set_bucket_pool @ 0x443870 */

00443872        int32_t esi = 0x6487e8
00443877        int32_t i_1 = 0x800
00443892        int32_t result
00443892        int32_t i
00443886        result = initialize_array_with_constructor(esi, 0x10, 0x20, sub_408600)
0044388b        esi += 0x20c
00443891        i = i_1
00443891        i_1 -= 1
00443892        do while (i != 1)
00443896        return result
