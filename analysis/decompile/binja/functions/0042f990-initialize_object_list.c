/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_object_list @ 0x42f990 */

0042f991        int32_t remaining_capacity = capacity
0042f9a0        object_list->count = 0
0042f9a6        object_list->capacity = remaining_capacity
0042f9bb        object_list->objects = allocate_tracked_memory(remaining_capacity * 0xdc, "Object List")
0042f9c0        if (remaining_capacity s<= 0)
0042f9c0        return
0042f9c3        int32_t object_byte_offset = 0
0042f9d8        int32_t i
0042f9cc        initialize_object(&object_list->objects->_pad_00[object_byte_offset])
0042f9d1        object_byte_offset += 0xdc
0042f9d7        i = remaining_capacity
0042f9d7        remaining_capacity -= 1
0042f9d8        do while (i != 1)
0042f9dd        return
