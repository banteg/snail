/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_health_pickup @ 0x43ecc0 */

0043ecc6        void* eax
0043ecc6        eax.b = pickup->_pad_40[4]
0043ecc6        eax:1.b = pickup->_pad_40[5]
0043ecc6        eax:2.b = pickup->_pad_40[6]
0043ecc6        eax:3.b = pickup->_pad_40[7]
0043eccc        if (*(eax + 9) != 0)
0043eccc        return 
0043ecd2        uint32_t state = pickup->state
0043ecd7        if (state == 0)
0043ecd7        return 
0043ecde        struct Player* eax_3
0043ecde        void* ecx_1
0043ecde        if (state == 1)
0043ed58        long double x87_r7_1 = fconvert.t(pickup->world_position.z)
0043ed5b        long double temp2_1 = fconvert.t(pickup->owner->interaction_max_z)
0043ed5b        x87_r7_1 - temp2_1
0043ed61        eax_3.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043ed66        if ((eax_3:1.b & 1) != 0)
0043ed6c        int16_t eax_7 = (pickup->_pad_00[4].d).w
0043ed6f        pickup->state = 0
0043ed78        ecx_1 = data_4df904 + 0x5a8
0043ed81        if ((eax_7:1.b & 2) == 0)
0043ed88        report_errorf("List remove")
0043ed93        kill_sprite(pickup->sprite)
0043ed9a        return 
0043ed9d        if ((eax_7.b & 0x40) != 0)
0043eda4        report_errorf("List remove NEXTBOD")
0043edaf        kill_sprite(pickup->sprite)
0043edb6        return 
0043edb7        void* eax_8
0043edb7        eax_8.b = pickup->_pad_00[0xc]
0043edb7        eax_8:1.b = pickup->_pad_00[0xd]
0043edb7        eax_8:2.b = pickup->_pad_00[0xe]
0043edb7        eax_8:3.b = pickup->_pad_00[0xf]
0043edbc        if (eax_8 != 0)
0043edbe        int32_t edi_1
0043edbe        edi_1.b = pickup->_pad_00[8]
0043edbe        edi_1:1.b = pickup->_pad_00[9]
0043edbe        edi_1:2.b = pickup->_pad_00[0xa]
0043edbe        edi_1:3.b = pickup->_pad_00[0xb]
0043edc1        *(eax_8 + 8) = edi_1
0043edc4        void* eax_9
0043edc4        eax_9.b = pickup->_pad_00[8]
0043edc4        eax_9:1.b = pickup->_pad_00[9]
0043edc4        eax_9:2.b = pickup->_pad_00[0xa]
0043edc4        eax_9:3.b = pickup->_pad_00[0xb]
0043edc9        if (eax_9 == 0)
0043edd3        label_43edd3:
0043edd3        int32_t eax_10
0043edd3        eax_10.b = pickup->_pad_00[0xc]
0043edd3        eax_10:1.b = pickup->_pad_00[0xd]
0043edd3        eax_10:2.b = pickup->_pad_00[0xe]
0043edd3        eax_10:3.b = pickup->_pad_00[0xf]
0043edd6        *(ecx_1 + 4) = eax_10.b
0043edd6        *(ecx_1 + 5) = eax_10:1.b
0043edd6        *(ecx_1 + 6) = eax_10:2.b
0043edd6        *(ecx_1 + 7) = eax_10:3.b
0043edd6        goto label_43edd9
0043edcb        int32_t edx_1
0043edcb        edx_1.b = pickup->_pad_00[0xc]
0043edcb        edx_1:1.b = pickup->_pad_00[0xd]
0043edcb        edx_1:2.b = pickup->_pad_00[0xe]
0043edcb        edx_1:3.b = pickup->_pad_00[0xf]
0043edce        *(eax_9 + 0xc) = edx_1
0043edd9        label_43edd9:
0043edd9        int32_t edx_2
0043edd9        edx_2.b = *(ecx_1 + 8)
0043edd9        edx_2:1.b = *(ecx_1 + 9)
0043edd9        edx_2:2.b = *(ecx_1 + 0xa)
0043edd9        edx_2:3.b = *(ecx_1 + 0xb)
0043eddc        pickup->_pad_00[0xc] = edx_2.b
0043eddc        pickup->_pad_00[0xd] = edx_2:1.b
0043eddc        pickup->_pad_00[0xe] = edx_2:2.b
0043eddc        pickup->_pad_00[0xf] = edx_2:3.b
0043eddf        *(ecx_1 + 8) = pickup.b
0043eddf        *(ecx_1 + 9) = pickup:1.b
0043eddf        *(ecx_1 + 0xa) = pickup:2.b
0043eddf        *(ecx_1 + 0xb) = pickup:3.b
0043ede2        int32_t eax_11
0043ede2        eax_11.b = pickup->_pad_00[4]
0043ede2        eax_11:1.b = pickup->_pad_00[5]
0043ede2        eax_11:2.b = pickup->_pad_00[6]
0043ede2        eax_11:3.b = pickup->_pad_00[7]
0043ede5        void* sprite = pickup->sprite
0043ede8        eax_11:1.b &= 0xfd
0043edeb        pickup->_pad_00[4] = eax_11.b
0043edeb        pickup->_pad_00[5] = eax_11:1.b
0043edeb        pickup->_pad_00[6] = eax_11:2.b
0043edeb        pickup->_pad_00[7] = eax_11:3.b
0043edee        kill_sprite(sprite)
0043edf5        return 
0043ece1        if (state == 2)
0043ece7        int16_t eax_4 = (pickup->_pad_00[4].d).w
0043ecea        pickup->state = 0
0043ecf3        ecx_1 = data_4df904 + 0x5a8
0043ecfc        if ((eax_4:1.b & 2) == 0)
0043ed03        report_errorf("List remove")
0043ed0e        kill_sprite(pickup->sprite)
0043ed15        return 
0043ed18        if ((eax_4.b & 0x40) != 0)
0043ed1f        report_errorf("List remove NEXTBOD")
0043ed2a        kill_sprite(pickup->sprite)
0043ed31        return 
0043ed32        void* eax_5
0043ed32        eax_5.b = pickup->_pad_00[0xc]
0043ed32        eax_5:1.b = pickup->_pad_00[0xd]
0043ed32        eax_5:2.b = pickup->_pad_00[0xe]
0043ed32        eax_5:3.b = pickup->_pad_00[0xf]
0043ed37        if (eax_5 != 0)
0043ed39        int32_t edi
0043ed39        edi.b = pickup->_pad_00[8]
0043ed39        edi:1.b = pickup->_pad_00[9]
0043ed39        edi:2.b = pickup->_pad_00[0xa]
0043ed39        edi:3.b = pickup->_pad_00[0xb]
0043ed3c        *(eax_5 + 8) = edi
0043ed3f        void* eax_6
0043ed3f        eax_6.b = pickup->_pad_00[8]
0043ed3f        eax_6:1.b = pickup->_pad_00[9]
0043ed3f        eax_6:2.b = pickup->_pad_00[0xa]
0043ed3f        eax_6:3.b = pickup->_pad_00[0xb]
0043ed44        if (eax_6 == 0)
0043ed44        goto label_43edd3
0043ed4a        int32_t edx
0043ed4a        edx.b = pickup->_pad_00[0xc]
0043ed4a        edx:1.b = pickup->_pad_00[0xd]
0043ed4a        edx:2.b = pickup->_pad_00[0xe]
0043ed4a        edx:3.b = pickup->_pad_00[0xf]
0043ed4d        *(eax_6 + 0xc) = edx
0043ed50        goto label_43edd9
0043edf9        long double x87_r7_3 = fconvert.t(pickup->_pad_70) + fconvert.t(pickup->parity_offset)
0043edfc        long double temp4_1 = fconvert.t(1f)
0043edfc        x87_r7_3 - temp4_1
0043ee02        pickup->parity_offset = fconvert.s(x87_r7_3)
0043ee02        bool c1_1 = unimplemented  {fst dword [esi+0x6c], st0}
0043ee05        eax_3.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0043ee0a        if ((eax_3:1.b & 0x41) == 0)
0043ee12        pickup->parity_offset = fconvert.s(x87_r7_3 - fconvert.t(1f))
0043ee22        struct TrackPickupRuntime* pickup_1 = pickup
0043ee40        *(pickup->sprite + 0x4c) = fconvert.s((sine(fconvert.s(fconvert.t(pickup->parity_offset) * fconvert.t(6.28318548f))) + fconvert.t(1f)) * fconvert.t(0.300000012f) + fconvert.t(pickup->world_position.y))
0043ee45        return
