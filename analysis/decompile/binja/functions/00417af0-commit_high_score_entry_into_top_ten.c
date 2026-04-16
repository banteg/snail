/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: commit_high_score_entry_into_top_ten @ 0x417af0 */

00417af1        int32_t ebp = arg2
00417afa        if (ebp s>= 0xa)
00417afa        return 
00417b12        int32_t i = ebp * 0x1fac0
00417b15        void* ebx_1 = i + arg1 + 0x17c108
00417b23        int32_t edi_2 = i + *arg1
00417b25        void* esi_1 = ebx_1
00417b27        i += 0x1fac0
00417b2c        ebx_1 += 0x1fac0
00417b32        __builtin_memcpy(edi_2, esi_1, 0x1fac0)
00417b36        *(i + *arg1 - 0x1fa80) = ebp
00417b3d        ebp += 1
00417b43        do while (i s< 0x13cb80)
00417b49        return
