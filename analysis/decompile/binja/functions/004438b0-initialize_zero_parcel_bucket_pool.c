/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_zero_parcel_bucket_pool @ 0x4438b0 */

004438b2        struct ParcelBucket* base = &g_zero_parcel_buckets
004438b7        int32_t i_1 = 0x800
004438d2        int32_t i
004438c6        initialize_array_with_constructor(base, 0x10, 0x20, noop_runtime_slot_constructor)
004438cb        base = &base[1]
004438d1        i = i_1
004438d1        i_1 -= 1
004438d2        do while (i != 1)
004438d6        return
