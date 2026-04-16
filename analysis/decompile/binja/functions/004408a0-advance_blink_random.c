/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_blink_random @ 0x4408a0 */

004408ae        int32_t temp1 = mods.dp.d(sx.q(*(arg1 + 0x3bb700) + 1), 0x18)
004408b1        *(arg1 + 0x3bb700) = temp1
004408be        return fconvert.t(*(arg1 + (temp1 << 2) + 0x3bb704))
