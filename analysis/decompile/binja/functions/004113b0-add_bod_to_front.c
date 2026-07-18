/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_bod_to_front @ 0x4113b0 */

004113ba        if (((node->list_flags).w:1.b & 2) != 0)
004113c1        report_errorf("List ADD")
004113c9        return
004113cc        struct BodNode* first = list->first
004113d1        if (first == 0)
004113d3        list->first = node
004113d6        node->list_prev = first
004113dc        list->first->list_next = nullptr
004113e3        uint32_t list_flags = node->list_flags
004113e6        list_flags:1.b |= 2
004113e9        node->list_flags = list_flags
004113ec        return
004113ef        first->list_prev = node
004113f2        struct BodNode* first_1 = list->first
004113f9        first_1->list_prev->list_next = first_1
00411400        struct BodNode* list_prev = list->first->list_prev
00411403        list->first = list_prev
00411406        list_prev->list_prev = nullptr
0041140d        uint32_t list_flags_1 = node->list_flags
00411410        list_flags_1:1.b |= 2
00411413        node->list_flags = list_flags_1
00411416        return
