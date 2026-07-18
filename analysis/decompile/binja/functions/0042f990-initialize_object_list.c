/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_object_list @ 0x42f990 */

0042f991        int32_t esi = capacity
0042f9a0        object_list->count = 0
0042f9a6        object_list->capacity = esi
0042f9bb        object_list->objects = allocate_tracked_memory(esi * 0xdc, "Object List")
0042f9c0        if (esi s<= 0)
0042f9c0        return
0042f9c3        void* ebx_1 = nullptr
0042f9d8        int32_t i
0042f9cc        initialize_object(ebx_1 + object_list->objects)
0042f9d1        ebx_1 += 0xdc
0042f9d7        i = esi
0042f9d7        esi -= 1
0042f9d8        do while (i != 1)
0042f9dd        return
