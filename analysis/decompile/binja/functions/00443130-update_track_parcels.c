/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_parcels @ 0x443130 */

00443132        struct ParcelManager* manager_1 = manager
00443134        int32_t i_1 = 0x32
0044314d        int32_t i
0044313e        if (manager_1->slots[0].state != PARCEL_STATE_INACTIVE)
00443144        (*manager_1->slots[0].vtable)()
00443146        manager_1 = &manager_1->slots[1]
0044314c        i = i_1
0044314c        i_1 -= 1
0044314d        do while (i != 1)
00443151        return
