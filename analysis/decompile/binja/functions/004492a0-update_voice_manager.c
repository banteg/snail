/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_voice_manager @ 0x4492a0 */

004492a5        struct VoiceManager* set = manager
004492a7        int32_t i_1 = 0x10
004492b7        int32_t i
004492ae        update_voice_set(set)
004492b3        set = &set->sets[1]
004492b6        i = i_1
004492b6        i_1 -= 1
004492b7        do while (i != 1)
004492c7        manager->global_progress = fconvert.s(fconvert.t(manager->global_progress) + fconvert.t(0.0166666675f))
004492ce        return
