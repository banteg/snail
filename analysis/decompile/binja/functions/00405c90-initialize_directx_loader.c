/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_directx_loader @ 0x405c90 */

00405c9a        loader->cached_x_mesh_count = 0
00405caf        loader->animation_bytes = load_file_bytes("X/_Animation.txt", nullptr)
00405cb6        initialize_duplicate_vertices(&loader->duplicate_vertices, 0x7d0)
00405cbc        return
