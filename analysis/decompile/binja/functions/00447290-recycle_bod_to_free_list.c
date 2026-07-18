/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: recycle_bod_to_free_list @ 0x447290 */

00447294        uint16_t list_flags_1 = (node->list_flags).w
0044729a        if ((list_flags_1:1.b & 2) == 0)
004472a1        report_errorf("List remove")
004472a9        return 0
004472af        if ((list_flags_1.b & 0x40) != 0)
004472b6        report_errorf("List remove NEXTBOD")
004472be        return 0
004472c1        struct BodNode* list_next = node->list_next
004472c7        if (list_next != 0)
004472cc        list_next->list_prev = node->list_prev
004472cf        struct BodNode* list_prev = node->list_prev
004472d4        if (list_prev == 0)
004472e1        list->first = node->list_next
004472d9        list_prev->list_next = node->list_next
004472e8        node->list_next = list->free_top
004472eb        list->free_top = node
004472ee        uint32_t list_flags = node->list_flags
004472f1        list_flags:1.b &= 0xfd
004472f4        node->list_flags = list_flags
004472f7        return node
