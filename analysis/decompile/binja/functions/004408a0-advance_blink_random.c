/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_blink_random @ 0x4408a0 */

004408ae        int32_t temp1 = mods.dp.d(sx.q(runtime->blink_random_index + 1), 0x18)
004408b1        runtime->blink_random_index = temp1
004408be        return (fconvert.t(runtime->blink_random_samples[temp1])).q
