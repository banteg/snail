/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_from_path @ 0x42f490 */

0042f4a5        struct File* eax = fopen(file_name, "rb")
0042f4b1        if (eax == 0)
0042f4bd        char buffer_1[0x200]
0042f4bd        getcwd(&buffer_1, 0x200)
0042f4cd        printf("WARNING:Cannot find file : %s (from %s)\n", file_name, &buffer_1)
0042f4df        return 0
0042f4e0        int32_t byte_count_1 = byte_count
0042f4e9        if (byte_count_1 == 0)
0042f4f4        byte_count_1 = get_stream_length_preserve_position(eax)
0042f4f7        void* bytes = buffer
0042f500        if (bytes == 0)
0042f50b        bytes = malloc(byte_count_1)
0042f512        fread(bytes, 1, byte_count_1, eax)
0042f518        fclose(eax)
0042f529        if (out_size != 0)
0042f52b        *out_size = byte_count_1
0042f538        return bytes
