/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_track_parcel_slot @ 0x443190 */

00443190        int32_t i = 0
00443192        uint32_t* edx = &slots->state
00443198        if ((edx - 0x38)->state == 0)
004431c5        return &slots[i]
0044319a        i += 1
0044319b        edx = &edx[0x23]
004431a4        do while (i s< 0x32)
004431ab        report_errorf("Too Many Parcels increase RPARCEL_MAXIMUM")
004431b5        return 0
