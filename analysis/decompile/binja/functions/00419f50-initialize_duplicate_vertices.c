/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_duplicate_vertices @ 0x419f50 */

00419f62        *arg1 = 0
00419f68        void* result = allocate_tracked_memory(arg2 * 0xa, "Duplicate vertices")
00419f70        arg1[1] = result
00419f74        return result
