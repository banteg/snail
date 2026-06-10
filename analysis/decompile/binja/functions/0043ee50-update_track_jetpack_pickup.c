/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_jetpack_pickup @ 0x43ee50 */

0043ee5f        if (*(pickup->__offset(0x8c).d + 9) != 0)
0043ee5f        return 
0043ee65        int32_t eax_1 = pickup->__offset(0x80).d
0043ee6d        if (eax_1 == 0)
0043ee6d        return 
0043ee74        void* ecx_1
0043ee74        if (eax_1 == 1)
0043eefa        long double x87_r7_1 = fconvert.t(pickup->_pad_70)
0043eefd        long double temp2_1 = fconvert.t(*(pickup->__offset(0x84).d + 0x2980))
0043eefd        x87_r7_1 - temp2_1
0043ef03        void* eax_8
0043ef03        eax_8.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043ef08        if ((eax_8:1.b & 1) != 0)
0043ef0e        int16_t eax_9 = (pickup->_pad_00[4].d).w
0043ef11        pickup->__offset(0x80).d = 0
0043ef1d        ecx_1 = data_4df904 + 0x5a8
0043ef26        if ((eax_9:1.b & 2) == 0)
0043ef2d        report_errorf("List remove")
0043ef3b        kill_sprite(pickup->__offset(0xac).d)
0043ef42        return 
0043ef45        if ((eax_9.b & 0x40) != 0)
0043ef4c        report_errorf("List remove NEXTBOD")
0043ef5a        kill_sprite(pickup->__offset(0xac).d)
0043ef61        return 
0043ef62        void* eax_10
0043ef62        eax_10.b = pickup->_pad_00[0xc]
0043ef62        eax_10:1.b = pickup->_pad_00[0xd]
0043ef62        eax_10:2.b = pickup->_pad_00[0xe]
0043ef62        eax_10:3.b = pickup->_pad_00[0xf]
0043ef67        if (eax_10 != 0)
0043ef69        int32_t edi_1
0043ef69        edi_1.b = pickup->_pad_00[8]
0043ef69        edi_1:1.b = pickup->_pad_00[9]
0043ef69        edi_1:2.b = pickup->_pad_00[0xa]
0043ef69        edi_1:3.b = pickup->_pad_00[0xb]
0043ef6c        *(eax_10 + 8) = edi_1
0043ef6f        void* eax_11
0043ef6f        eax_11.b = pickup->_pad_00[8]
0043ef6f        eax_11:1.b = pickup->_pad_00[9]
0043ef6f        eax_11:2.b = pickup->_pad_00[0xa]
0043ef6f        eax_11:3.b = pickup->_pad_00[0xb]
0043ef74        if (eax_11 == 0)
0043ef7e        label_43ef7e:
0043ef7e        int32_t eax_12
0043ef7e        eax_12.b = pickup->_pad_00[0xc]
0043ef7e        eax_12:1.b = pickup->_pad_00[0xd]
0043ef7e        eax_12:2.b = pickup->_pad_00[0xe]
0043ef7e        eax_12:3.b = pickup->_pad_00[0xf]
0043ef81        *(ecx_1 + 4) = eax_12.b
0043ef81        *(ecx_1 + 5) = eax_12:1.b
0043ef81        *(ecx_1 + 6) = eax_12:2.b
0043ef81        *(ecx_1 + 7) = eax_12:3.b
0043ef81        goto label_43ef84
0043ef76        int32_t edx_1
0043ef76        edx_1.b = pickup->_pad_00[0xc]
0043ef76        edx_1:1.b = pickup->_pad_00[0xd]
0043ef76        edx_1:2.b = pickup->_pad_00[0xe]
0043ef76        edx_1:3.b = pickup->_pad_00[0xf]
0043ef79        *(eax_11 + 0xc) = edx_1
0043ef84        label_43ef84:
0043ef84        int32_t edx_2
0043ef84        edx_2.b = *(ecx_1 + 8)
0043ef84        edx_2:1.b = *(ecx_1 + 9)
0043ef84        edx_2:2.b = *(ecx_1 + 0xa)
0043ef84        edx_2:3.b = *(ecx_1 + 0xb)
0043ef87        pickup->_pad_00[0xc] = edx_2.b
0043ef87        pickup->_pad_00[0xd] = edx_2:1.b
0043ef87        pickup->_pad_00[0xe] = edx_2:2.b
0043ef87        pickup->_pad_00[0xf] = edx_2:3.b
0043ef8a        *(ecx_1 + 8) = pickup.b
0043ef8a        *(ecx_1 + 9) = pickup:1.b
0043ef8a        *(ecx_1 + 0xa) = pickup:2.b
0043ef8a        *(ecx_1 + 0xb) = pickup:3.b
0043ef8d        int32_t eax_13
0043ef8d        eax_13.b = pickup->_pad_00[4]
0043ef8d        eax_13:1.b = pickup->_pad_00[5]
0043ef8d        eax_13:2.b = pickup->_pad_00[6]
0043ef8d        eax_13:3.b = pickup->_pad_00[7]
0043ef90        void* ecx_7 = pickup->__offset(0xac).d
0043ef96        eax_13:1.b &= 0xfd
0043ef99        pickup->_pad_00[4] = eax_13.b
0043ef99        pickup->_pad_00[5] = eax_13:1.b
0043ef99        pickup->_pad_00[6] = eax_13:2.b
0043ef99        pickup->_pad_00[7] = eax_13:3.b
0043ef9c        kill_sprite(ecx_7)
0043ee77        if (eax_1 == 2)
0043ee7d        int16_t eax_5 = (pickup->_pad_00[4].d).w
0043ee80        pickup->__offset(0x80).d = 0
0043ee8c        ecx_1 = data_4df904 + 0x5a8
0043ee95        if ((eax_5:1.b & 2) == 0)
0043ee9c        report_errorf("List remove")
0043eeaa        kill_sprite(pickup->__offset(0xac).d)
0043eeb1        return 
0043eeb4        if ((eax_5.b & 0x40) != 0)
0043eebb        report_errorf("List remove NEXTBOD")
0043eec9        kill_sprite(pickup->__offset(0xac).d)
0043eed0        return 
0043eed1        void* eax_6
0043eed1        eax_6.b = pickup->_pad_00[0xc]
0043eed1        eax_6:1.b = pickup->_pad_00[0xd]
0043eed1        eax_6:2.b = pickup->_pad_00[0xe]
0043eed1        eax_6:3.b = pickup->_pad_00[0xf]
0043eed6        if (eax_6 != 0)
0043eed8        int32_t edi
0043eed8        edi.b = pickup->_pad_00[8]
0043eed8        edi:1.b = pickup->_pad_00[9]
0043eed8        edi:2.b = pickup->_pad_00[0xa]
0043eed8        edi:3.b = pickup->_pad_00[0xb]
0043eedb        *(eax_6 + 8) = edi
0043eede        void* eax_7
0043eede        eax_7.b = pickup->_pad_00[8]
0043eede        eax_7:1.b = pickup->_pad_00[9]
0043eede        eax_7:2.b = pickup->_pad_00[0xa]
0043eede        eax_7:3.b = pickup->_pad_00[0xb]
0043eee3        if (eax_7 == 0)
0043eee3        goto label_43ef7e
0043eee9        int32_t edx
0043eee9        edx.b = pickup->_pad_00[0xc]
0043eee9        edx:1.b = pickup->_pad_00[0xd]
0043eee9        edx:2.b = pickup->_pad_00[0xe]
0043eee9        edx:3.b = pickup->_pad_00[0xf]
0043eeec        *(eax_7 + 0xc) = edx
0043eeef        goto label_43ef84
0043efa3        return
