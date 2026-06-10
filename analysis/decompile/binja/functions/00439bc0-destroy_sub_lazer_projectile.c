/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_sub_lazer_projectile @ 0x439bc0 */

00439bc6        int32_t eax = get_track_cell_row_index(arg1)
00439bcb        uint8_t tile_id = arg1->tile_id
00439bdb        if (tile_id == 0x1d || tile_id == 0x1e)
00439be1        void* edx_1 = data_4df904
00439bed        int32_t eax_1 = eax * 0x3d
00439bf0        int32_t ecx_1
00439bf0        ecx_1.b = *(edx_1 + (eax_1 << 2) + 0x6410e0)
00439bfa        void* eax_2 = edx_1 + (eax_1 << 2)
00439c08        if ((ecx_1.b & 8) != 0 && ((*(eax_2 + 0x641194)).w:1.b & 2) != 0)
00439c0a        int16_t ecx_3 = (*(eax_2 + 0x641194)).w
00439c1e        if ((ecx_3:1.b & 2) == 0)
00439c25        report_errorf("List remove")
00439c32        if ((ecx_3.b & 0x40) == 0)
00439c43        void* ecx_4 = *(eax_2 + 0x64119c)
00439c48        if (ecx_4 != 0)
00439c4a        int32_t edi_1 = *(eax_2 + 0x641198)
00439c4d        *(ecx_4 + 8) = edi_1.b
00439c4d        *(ecx_4 + 9) = edi_1:1.b
00439c4d        *(ecx_4 + 0xa) = edi_1:2.b
00439c4d        *(ecx_4 + 0xb) = edi_1:3.b
00439c50        void* ecx_5 = *(eax_2 + 0x641198)
00439c55        if (ecx_5 == 0)
00439c62        *(edx_1 + 0x5ac) = *(eax_2 + 0x64119c)
00439c57        int32_t edi_2 = *(eax_2 + 0x64119c)
00439c5a        *(ecx_5 + 0xc) = edi_2.b
00439c5a        *(ecx_5 + 0xd) = edi_2:1.b
00439c5a        *(ecx_5 + 0xe) = edi_2:2.b
00439c5a        *(ecx_5 + 0xf) = edi_2:3.b
00439c68        *(eax_2 + 0x64119c) = *(edx_1 + 0x5b0)
00439c6b        *(edx_1 + 0x5b0) = eax_2 + 0x641190
00439c6e        *(eax_2 + 0x641194) &= 0xfffffdff
00439c39        report_errorf("List remove NEXTBOD")
00439c71        int16_t eax_4 = (arg1->_pad_00[4].d).w
00439c77        if ((eax_4:1.b & 2) != 0)
00439c81        void* ecx_8 = data_4df904 + 0x5a8
00439c87        if ((eax_4.b & 0x40) == 0)
00439c98        void* eax_5
00439c98        eax_5.b = arg1->_pad_00[0xc]
00439c98        eax_5:1.b = arg1->_pad_00[0xd]
00439c98        eax_5:2.b = arg1->_pad_00[0xe]
00439c98        eax_5:3.b = arg1->_pad_00[0xf]
00439c9d        if (eax_5 != 0)
00439c9f        int32_t edx_4
00439c9f        edx_4.b = arg1->_pad_00[8]
00439c9f        edx_4:1.b = arg1->_pad_00[9]
00439c9f        edx_4:2.b = arg1->_pad_00[0xa]
00439c9f        edx_4:3.b = arg1->_pad_00[0xb]
00439ca2        *(eax_5 + 8) = edx_4
00439ca5        void* eax_6
00439ca5        eax_6.b = arg1->_pad_00[8]
00439ca5        eax_6:1.b = arg1->_pad_00[9]
00439ca5        eax_6:2.b = arg1->_pad_00[0xa]
00439ca5        eax_6:3.b = arg1->_pad_00[0xb]
00439caa        if (eax_6 == 0)
00439cb4        int32_t eax_7
00439cb4        eax_7.b = arg1->_pad_00[0xc]
00439cb4        eax_7:1.b = arg1->_pad_00[0xd]
00439cb4        eax_7:2.b = arg1->_pad_00[0xe]
00439cb4        eax_7:3.b = arg1->_pad_00[0xf]
00439cb7        *(ecx_8 + 4) = eax_7.b
00439cb7        *(ecx_8 + 5) = eax_7:1.b
00439cb7        *(ecx_8 + 6) = eax_7:2.b
00439cb7        *(ecx_8 + 7) = eax_7:3.b
00439cac        int32_t edx_5
00439cac        edx_5.b = arg1->_pad_00[0xc]
00439cac        edx_5:1.b = arg1->_pad_00[0xd]
00439cac        edx_5:2.b = arg1->_pad_00[0xe]
00439cac        edx_5:3.b = arg1->_pad_00[0xf]
00439caf        *(eax_6 + 0xc) = edx_5
00439cba        int32_t edx_6
00439cba        edx_6.b = *(ecx_8 + 8)
00439cba        edx_6:1.b = *(ecx_8 + 9)
00439cba        edx_6:2.b = *(ecx_8 + 0xa)
00439cba        edx_6:3.b = *(ecx_8 + 0xb)
00439cbd        arg1->_pad_00[0xc] = edx_6.b
00439cbd        arg1->_pad_00[0xd] = edx_6:1.b
00439cbd        arg1->_pad_00[0xe] = edx_6:2.b
00439cbd        arg1->_pad_00[0xf] = edx_6:3.b
00439cc0        *(ecx_8 + 8) = arg1.b
00439cc0        *(ecx_8 + 9) = arg1:1.b
00439cc0        *(ecx_8 + 0xa) = arg1:2.b
00439cc0        *(ecx_8 + 0xb) = arg1:3.b
00439cc3        arg1->_pad_00[4].d &= 0xfffffdff
00439c8e        report_errorf("List remove NEXTBOD")
00439cc6        int32_t* esi_1 = &arg1->_pad_00[0x44]
00439cc9        int32_t i_1 = 4
00439d45        void* result
00439d45        int32_t i
00439cce        result = *esi_1
00439cda        if (result != 0 && ((*(result + 4)).w:1.b & 2) != 0)
00439ce2        void* edx_7 = data_4df904 + 0x5a8
00439ce8        int16_t ecx_11 = (*(result + 4)).w
00439cee        if ((ecx_11:1.b & 2) == 0)
00439cf5        result = report_errorf("List remove")
00439d02        if ((ecx_11.b & 0x40) == 0)
00439d13        void* ecx_12 = *(result + 0xc)
00439d18        if (ecx_12 != 0)
00439d1a        int32_t ebp_1 = *(result + 8)
00439d1d        *(ecx_12 + 8) = ebp_1.b
00439d1d        *(ecx_12 + 9) = ebp_1:1.b
00439d1d        *(ecx_12 + 0xa) = ebp_1:2.b
00439d1d        *(ecx_12 + 0xb) = ebp_1:3.b
00439d20        void* ecx_13 = *(result + 8)
00439d25        if (ecx_13 == 0)
00439d32        *(edx_7 + 4) = *(result + 0xc)
00439d27        int32_t ebp_2 = *(result + 0xc)
00439d2a        *(ecx_13 + 0xc) = ebp_2.b
00439d2a        *(ecx_13 + 0xd) = ebp_2:1.b
00439d2a        *(ecx_13 + 0xe) = ebp_2:2.b
00439d2a        *(ecx_13 + 0xf) = ebp_2:3.b
00439d38        *(result + 0xc) = *(edx_7 + 8)
00439d3b        *(edx_7 + 8) = result
00439d3e        *(result + 4) &= 0xfffffdff
00439d09        result = report_errorf("List remove NEXTBOD")
00439d41        esi_1 = &esi_1[1]
00439d44        i = i_1
00439d44        i_1 -= 1
00439d45        do while (i != 1)
00439d4b        return result
