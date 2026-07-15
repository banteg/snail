/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mini_delete_high_score_entry @ 0x417af0 */

00417af1        int32_t rank_1 = rank
00417afa        if (rank_1 s>= 0xa)
00417afa        return
00417b12        int32_t i = rank_1 * 0x1fac0
00417b15        void* ebx_1 = &bank->survival_records[1] + i
00417b23        void* edi_2 = i + bank->active_record_bank
00417b25        void* esi_1 = ebx_1
00417b27        i += 0x1fac0
00417b2c        ebx_1 += 0x1fac0
00417b32        __builtin_memcpy(edi_2, esi_1, 0x1fac0)
00417b36        *(i + bank->active_record_bank - 0x1fa80) = rank_1
00417b3d        rank_1 += 1
00417b43        do while (i s< 0x13cb80)
00417b49        return
