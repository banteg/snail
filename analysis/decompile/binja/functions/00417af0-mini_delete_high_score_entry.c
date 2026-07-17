/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mini_delete_high_score_entry @ 0x417af0 */

00417af1        int32_t row = rank
00417afa        if (row s>= 0xa)
00417afa        return
00417b12        int32_t record_offset_bytes = row * 0x1fac0
00417b15        struct SubSolution* source_cursor = &bank->survival_records[1] + record_offset_bytes
00417b23        struct SubSolution* destination = record_offset_bytes + bank->active_record_bank
00417b25        struct SubSolution* source = source_cursor
00417b27        record_offset_bytes += 0x1fac0
00417b2c        source_cursor = &source_cursor[1]
00417b32        __builtin_memcpy(destination, source, 0x1fac0)
00417b36        *(record_offset_bytes + bank->active_record_bank - 0x1fa80) = row
00417b3d        row += 1
00417b43        do while (record_offset_bytes s< 0x13cb80)
00417b49        return
