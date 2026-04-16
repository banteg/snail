/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_parcels @ 0x443130 */

00443132        int32_t* esi = arg1
00443134        int32_t i_1 = 0x32
0044314d        int32_t result
0044314d        int32_t i
00443139        result = esi[0xe]
0044313e        if (result != 0)
00443144        result = (**esi)()
00443146        esi = &esi[0x23]
0044314c        i = i_1
0044314c        i_1 -= 1
0044314d        do while (i != 1)
00443151        return result
