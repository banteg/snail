/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_voice_manager @ 0x4492a0 */

004492a5        void* esi = arg1
004492a7        int32_t i_1 = 0x10
004492b7        int32_t result
004492b7        int32_t i
004492ae        result = update_voice_set(esi)
004492b3        esi += 0x18
004492b6        i = i_1
004492b6        i_1 -= 1
004492b7        do while (i != 1)
004492c7        *(arg1 + 0x180) = fconvert.s(fconvert.t(*(arg1 + 0x180)) + fconvert.t(0.0166666675f))
004492ce        return result
