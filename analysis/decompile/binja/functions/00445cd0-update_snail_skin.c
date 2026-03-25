/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin @ 0x445cd0 */

00445cd7        void* var_10 = arg1
00445cdb        int32_t ebx = 0
00445cdd        int32_t* ebp = arg1 + 0x17b0
00445cf2        int32_t result
00445cf2        while (true)
00445cf2        void* esi_1 = arg1 + 0x1684
00445cfa        int32_t var_c = ebp[-0x39]
00445cfe        result = ebp[-0x38]
00445d05        int32_t eax_2 = ebp[-0x37]
00445d0c        if (ebx s>= 0xb)
00445d0e        esi_1 = arg1 + 0x1604
00445d1e        void var_60
00445d1e        __builtin_memcpy(&var_60, esi_1, 0x40)
00445d24        multiply_vector_by_matrix(&var_c)
00445d31        int32_t* ecx_1 = ebp
00445d33        ebx += 1
00445d34        ebp = &ebp[3]
00445d3a        *ecx_1 = var_c
00445d40        ecx_1[1] = result
00445d43        ecx_1[2] = eax_2
00445d46        if (ebx s>= 0x13)
00445d46        break
00445ce5        arg1 = var_10
00445d4f        return result
