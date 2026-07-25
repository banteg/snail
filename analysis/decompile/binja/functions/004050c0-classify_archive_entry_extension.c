/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: classify_archive_entry_extension @ 0x4050c0 */

004050c0        uint8_t* path_cursor = path
004050c4        uint8_t* stem_cursor = stem_out
004050c8        uint8_t current_char = *path_cursor
004050cc        if (current_char != 0)
004050d1        while (current_char != 0x2e)
004050d3        path_cursor = &path_cursor[1]
004050d4        *stem_cursor = current_char
004050d6        stem_cursor = &stem_cursor[1]
004050d7        current_char = *path_cursor
004050db        if (current_char == 0)
004050db        break
004050dd        *stem_cursor = 0
004050e4        if (*path_cursor != 0)
004050e6        current_char = path_cursor[1]
004050fa        if (current_char == 0x54 && path_cursor[2] == 0x47 && path_cursor[3] == 0x41)
00405101        return 1
00405110        if (current_char == 0x57 && path_cursor[2] == 0x41 && path_cursor[3] == 0x56)
00405117        return 2
00405127        if (current_char == 0x4d && path_cursor[2] == 0x50 && path_cursor[3] == 0x33)
0040512e        return 3
00405131        return 0
