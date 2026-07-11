/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_blink_random @ 0x4408c0 */

004408c0        struct SubgameRuntime* runtime_1 = runtime
004408c3        runtime->blink_random_index = 0
004408cd        float (* esi)[0x18] = &runtime->blink_random_samples
004408d3        int32_t i_1 = 0x18
00440904        int32_t result
00440904        int32_t i
004408d8        result = next_math_random_value()
004408e1        esi = &(*esi)[1]
004408e8        i = i_1
004408e8        i_1 -= 1
00440901        (esi - 0x3bb704)->blink_random_index = fconvert.s(fconvert.t(1f) / ((float.t(result) * fconvert.t(3.05175781e-05f) + fconvert.t(1f)) * fconvert.t(60f)))
00440904        do while (i != 1)
00440909        return result
