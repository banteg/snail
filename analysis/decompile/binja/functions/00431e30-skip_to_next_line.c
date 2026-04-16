/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: skip_to_next_line @ 0x431e30 */

00431e34        char* result = *arg1
00431e39        while (*result != 0)
00431e3b        result = *arg1
00431e40        if (*result == 0xa)
00431e40        break
00431e42        result = &result[1]
00431e43        *arg1 = result
00431e4a        *arg1 += 1
00431e4c        return result
