/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_object_to_list @ 0x42fad0 */

0042fadb        if (object_list->count == object_list->capacity)
0042fae2        report_errorf("Too many Objects - Increase ObjectList.Init(MAX) in G0.cpp")
0042faea        int32_t count = object_list->count
0042faf3        object_list->count = count + 1
0042fafb        struct Object* object = &object_list->objects->_pad_00[count * 0xdc]
0042fb00        initialize_object(object)
0042fb09        return object
