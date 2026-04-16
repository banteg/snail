/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_zero_parcel_bucket_pool @ 0x4438b0 */

004438b2        int32_t esi = 0x53d190
004438b7        int32_t i_1 = 0x800
004438d2        int32_t result
004438d2        int32_t i
004438c6        result = initialize_array_with_constructor(esi, 0x10, 0x20, sub_408600)
004438cb        esi += 0x20c
004438d1        i = i_1
004438d1        i_1 -= 1
004438d2        do while (i != 1)
004438d6        return result
