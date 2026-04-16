/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_font3d_objects @ 0x44ae10 */

0044ae13        int32_t result = sx.d(arg1)
0044ae20        int32_t result_1 = 0
0044ae2b        int32_t ebx_1 = result * 0x828
0044ae36        if (*(ebx_1 + 0x7772f8) s> 0)
0044ae46        void* ebp_1 = &data_7770e8
0044ae4e        int32_t* esi_1 = &data_77550c
0044ae53        int32_t eax_1 = result * 0x20a
0044ae59        int32_t* edi_1 = (eax_1 << 2) + &data_777504
0044afa5        int32_t ecx_16
0044ae71        arg1.d = fconvert.s(fconvert.t(edi_1[0x80]) / fconvert.t(*(ebx_1 + &data_777b04)))
0044ae7e        set_bod_object(&esi_1[-9], add_object_to_list(0x4b7648))
0044ae8b        load_object_definition("Objects/Font3D", *esi_1)
0044ae96        esi_1[-2] = 0
0044ae99        esi_1[-1] = 0
0044aeb9        *(*(*esi_1 + 0x5c) + 0xc) = *(((eax_1 + edi_1[0x100]) << 2) + &data_7772fc)
0044aec7        *(*(*esi_1 + 0x5c) + 0x10) = edi_1[-0x80]
0044aed5        *(*(*esi_1 + 0x5c) + 0x14) = fconvert.s(fconvert.t(1f) - fconvert.t(*(ebx_1 + 0x777b08)))
0044aee5        *(*(*esi_1 + 0x5c) + 0x18) = *edi_1
0044aef3        *(*(*esi_1 + 0x5c) + 0x1c) = fconvert.s(fconvert.t(1f) - fconvert.t(*(ebx_1 + 0x777b08)))
0044af03        *(*(*esi_1 + 0x5c) + 0x20) = *edi_1
0044af11        *(*(*esi_1 + 0x5c) + 0x24) = fconvert.s(fconvert.t(1f) - fconvert.t(*(ebx_1 + 0x777b0c)))
0044af25        *(*(*esi_1 + 0x5c) + 0x28) = edi_1[-0x80]
0044af33        *(*(*esi_1 + 0x5c) + 0x2c) = fconvert.s(fconvert.t(1f) - fconvert.t(*(ebx_1 + 0x777b0c)))
0044af3c        float* eax_13 = *(*esi_1 + 0x38)
0044af41        *eax_13 = fconvert.s(fconvert.t(arg1.d) * fconvert.t(*eax_13))
0044af49        void* eax_14 = *(*esi_1 + 0x38)
0044af4f        *(eax_14 + 0xc) = fconvert.s(fconvert.t(arg1.d) * fconvert.t(*(eax_14 + 0xc)))
0044af58        void* eax_16 = *(*esi_1 + 0x38)
0044af5e        *(eax_16 + 0x18) = fconvert.s(fconvert.t(arg1.d) * fconvert.t(*(eax_16 + 0x18)))
0044af67        void* eax_17 = *(*esi_1 + 0x38)
0044af6d        *(eax_17 + 0x24) = fconvert.s(fconvert.t(arg1.d) * fconvert.t(*(eax_17 + 0x24)))
0044af72        *(*esi_1 + 0x14) = 1
0044af79        void* eax_18 = *esi_1
0044af7b        esi_1 = &esi_1[0xe]
0044af7e        edi_1 = &edi_1[1]
0044af81        ebp_1 += 4
0044af8a        *(eax_18 + 0x10) |= 0x10
0044af91        ecx_16 = *(ebx_1 + 0x7772f8)
0044af97        *(ebp_1 - 4) = arg1.d
0044af9e        result = result_1 + 1
0044afa1        result_1 = result
0044afa5        do while (result s< ecx_16)
0044afb2        return result
