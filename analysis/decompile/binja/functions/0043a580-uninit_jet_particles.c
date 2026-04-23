/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_jet_particles @ 0x43a580 */

0043a583        struct JetParticleSlot (* esi)[0x1e] = &gauge->particle_slots
0043a586        int32_t i_1 = 0xf
0043a59e        int32_t i
0043a58b        int32_t j_1 = 2
0043a59b        int32_t j
0043a592        kill_sprite((esi - 0x20)->particle_slots[0].sprite)
0043a597        esi = &(*esi)[1]
0043a59a        j = j_1
0043a59a        j_1 -= 1
0043a59b        do while (j != 1)
0043a59d        i = i_1
0043a59d        i_1 -= 1
0043a59e        do while (i != 1)
0043a5a3        return
