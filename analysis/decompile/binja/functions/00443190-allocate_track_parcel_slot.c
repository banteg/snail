/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_track_parcel_slot @ 0x443190 */

00443190        int32_t i = 0
00443192        enum ParcelState* edx = &manager->slots[0].state
00443198        if ((edx - 0x38)->slots[0].state == PARCEL_STATE_INACTIVE)
004431c5        return &manager->slots[i]
0044319a        i += 1
0044319b        edx = &edx[0x23]
004431a4        do while (i s< 0x32)
004431ab        report_errorf("Too Many Parcels increase RPARCEL_MAXIMUM")
004431b5        return 0
