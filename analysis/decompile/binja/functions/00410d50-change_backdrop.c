/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_backdrop @ 0x410d50 */

00410d50        void* result = arg2
00410d55        int32_t edx = 0
00410d58        int32_t ebx
00410d58        ebx.b = *(result + 0x88)
00410d5e        int32_t esi = *(result + 0x84)
00410d66        if (ebx.b == 0)
00410d8e        if (esi != 0)
00410d90        *(arg1 + 0x39) = 0
00410d93        edx = 1
00410d98        *(arg1 + 0x4c) = 1
00410da1        *(arg1 + 0x40) = *(result + 0x84)
00410daa        label_410daa:
00410daa        *(arg1 + 0x50) = *(result + 0x120)
00410dad        result.b = arg3
00410db1        *(arg1 + 0x54) = result.b
00410d6a        if (esi != 0)
00410d6c        edx = 1
00410d71        *(arg1 + 0x39) = 1
00410d74        *(arg1 + 0x4c) = 1
00410d7d        *(arg1 + 0x40) = *(result + 0x84)
00410d87        *(arg1 + 0x48) = *(result + 0x84) + 1
00410d8a        goto label_410daa
00410db5        *(arg1 + 0x658) = edx
00410dbc        return result
