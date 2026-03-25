/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_stream_length_preserve_position @ 0x405170 */

00405178        void* eax = sub_48b4bc(arg1)
00405184        sub_48b430(arg1, nullptr, FILE_END)
0040518a        void* result = sub_48b4bc(arg1)
00405195        sub_48b430(arg1, eax, FILE_BEGIN)
004051a2        return result
