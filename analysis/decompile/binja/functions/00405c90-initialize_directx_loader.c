/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_directx_loader @ 0x405c90 */

00405c9a        arg1[1] = 0
00405caf        *arg1 = load_file_bytes("X/_Animation.txt", nullptr)
00405cbc        return initialize_duplicate_vertices(&arg1[0x1782], 0x7d0)
