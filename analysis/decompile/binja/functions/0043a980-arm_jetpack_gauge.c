/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: arm_jetpack_gauge @ 0x43a980 */

0043a988        if (gauge->state != 0)
0043a9b6        return 0
0043a98a        gauge->state = 1
0043a991        gauge->progress = 0
0043a993        gauge->wobble_alpha = 0f
0043a996        gauge->wobble_y = 0f
0043a999        gauge->wobble_x = 0f
0043a9a9        set_snail_jetpack(data_4df904 + 0x432700, 1)
0043a9b0        return initialize_jet_particles(gauge)
