/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_stream_length_preserve_position @ 0x405170 */

00405178        void* eax = ftell(file)
00405184        fseek(file, nullptr, FILE_END)
0040518a        void* result = ftell(file)
00405195        fseek(file, eax, FILE_BEGIN)
004051a2        return result
