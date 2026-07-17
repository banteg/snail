/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_vapour @ 0x442500 */

0044250c        struct Object* object = vapour->body.bod.object
0044250f        vapour->half_width = half_width
00442518        int32_t eax_1 = object->facequad_count + 1
00442519        vapour->capacity = eax_1
0044252d        vapour->points = allocate_tracked_memory(eax_1 << 6, "Vapour Trail")
00442535        reset_vapour(vapour, nullptr)
0044253b        return
