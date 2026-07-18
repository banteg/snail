/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_bod_to_end @ 0x411420 */

0041142a        if (((node->list_flags).w:1.b & 2) != 0)
00411431        report_errorf("List ADDend")
00411439        return
0041143c        struct BodNode* first = list->first
00411441        if (first == 0)
00411443        list->first = node
00411446        node->list_prev = first
0041144c        list->first->list_next = nullptr
00411453        uint32_t list_flags = node->list_flags
00411456        list_flags:1.b |= 2
00411459        node->list_flags = list_flags
0041145c        return
0041145f        struct BodNode* list_next = first->list_next
00411464        while (list_next != 0)
00411466        first = list_next
00411468        list_next = first->list_next
0041146f        first->list_next = node
00411472        node->list_prev = first
00411475        uint32_t list_flags_1 = node->list_flags
00411478        node->list_next = nullptr
0041147f        list_flags_1:1.b |= 2
00411482        node->list_flags = list_flags_1
00411485        return
