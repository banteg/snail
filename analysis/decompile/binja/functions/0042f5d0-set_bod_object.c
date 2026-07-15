/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_bod_object @ 0x42f5d0 */

0042f5d4        bod->object = object
0042f5d7        uint32_t list_flags = bod->bod.list_flags
0042f5da        list_flags.b |= 2
0042f5dc        bod->bod.list_flags = list_flags
0042f5df        return list_flags
