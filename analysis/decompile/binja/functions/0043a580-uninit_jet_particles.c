/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_jet_particles @ 0x43a580 */

0043a583        struct JetParticleSlot* particle_slot_cursor = &sub_hover->particle_slots
0043a586        int32_t rows_remaining = 0xf
0043a59e        int32_t i
0043a58b        int32_t columns_remaining = 2
0043a59b        int32_t j
0043a592        kill_sprite(particle_slot_cursor->sprite)
0043a597        particle_slot_cursor = &particle_slot_cursor[1]
0043a59a        j = columns_remaining
0043a59a        columns_remaining -= 1
0043a59b        do while (j != 1)
0043a59d        i = rows_remaining
0043a59d        rows_remaining -= 1
0043a59e        do while (i != 1)
0043a5a3        return
