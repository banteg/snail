/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: save_config_file @ 0x42f540 */

0042f551        struct File* stream = fopen(file_name, "wb")
0042f55d        if (stream == 0)
0042f578        char buffer[0x200]
0042f578        return getcwd(&buffer, 0x200)
0042f58c        fwrite(bytes, 1, byte_count, stream)
0042f5a1        return fclose(stream)
