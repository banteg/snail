/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_vapour_point @ 0x442560 */

00442564        int32_t point_count = trail->point_count
0044256a        int32_t capacity = trail->capacity
00442572        int32_t arg_4
00442572        if (point_count s< capacity)
00442588        __builtin_memcpy(&trail->points[point_count], arg_4, 0x40)
00442593        trail->point_count += 1
00442599        return
0044259d        int32_t i = 0
004425a2        if (capacity - 1 s> 0)
004425a4        void* edx_1 = nullptr
004425a6        struct TransformMatrix* points = trail->points
004425ac        i += 1
004425ad        void* esi_2 = edx_1 + points + 0x40
004425b1        void* edi_2 = edx_1 + points
004425b9        edx_1 += 0x40
004425bc        __builtin_memcpy(edi_2, esi_2, 0x40)
004425c7        do while (i s< trail->capacity - 1)
004425e6        __builtin_memcpy(&trail->points[trail->point_count - 1], arg_4, 0x40)
004425ea        return
