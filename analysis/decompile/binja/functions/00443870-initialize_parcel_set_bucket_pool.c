/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_parcel_set_bucket_pool @ 0x443870 */

00443872        struct ParcelBucket* base = &g_parcel_set_buckets
00443877        int32_t i_1 = 0x800
00443892        int32_t i
00443886        initialize_array_with_constructor(base, 0x10, 0x20, noop_runtime_slot_constructor)
0044388b        base = &base[1]
00443891        i = i_1
00443891        i_1 -= 1
00443892        do while (i != 1)
00443896        return
