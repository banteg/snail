/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_movement_flag_emitters @ 0x43a300 */

0043a307        uint32_t movement_flags = player->movement_flags
0043a312        int32_t ebx_1
0043a312        if ((movement_flags.b & 0x69) != 0)
0043a32a        ebx_1 = 1
0043a32f        label_43a32f:
0043a32f        int32_t i = 0
0043a331        void* entry_ecx
0043a331        int32_t* edi_1 = entry_ecx + 0x450
0043a337        movement_flags = edi_1[0x91]
0043a33f        if (movement_flags == 0)
0043a346        movement_flags = create_golb(edi_1, entry_ecx, ebx_1, i)
0043a34b        int32_t temp1_1 = ebx_1
0043a34b        ebx_1 -= 1
0043a34c        if (temp1_1 == 1)
0043a34c        break
0043a34e        i += 1
0043a34f        edi_1 = &edi_1[0xba]
0043a358        do while (i s< 0xc)
0043a316        if ((movement_flags.b & 0x12) != 0)
0043a323        ebx_1 = 2
0043a328        goto label_43a32f
0043a31a        if ((movement_flags.b & 4) != 0)
0043a31c        ebx_1 = 3
0043a321        goto label_43a32f
0043a35e        return movement_flags
