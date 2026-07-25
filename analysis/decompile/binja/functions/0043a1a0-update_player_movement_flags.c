/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_player_movement_flags @ 0x43a1a0 */

0043a1a3        int32_t shooting_tier = player->shooting_tier
0043a1a9        player->shoot_flags = 0
0043a1b6        if (shooting_tier u> 8)
0043a288        player->shoot_flags = 0x81
0043a292        player->shoot_cooldown_step = 0.0666666701f
0043a1bc        switch (shooting_tier)
0043a1c3        case 0
0043a1c3        player->shoot_flags = 1
0043a1cd        player->shoot_cooldown_step = 0.0740740746f
0043a1dc        case 1
0043a1dc        player->shoot_flags = 2
0043a1e6        player->shoot_cooldown_step = 0.0740740746f
0043a1f5        case 2
0043a1f5        player->shoot_flags = 4
0043a1ff        player->shoot_cooldown_step = 0.0740740746f
0043a20e        case 3
0043a20e        player->shoot_flags = 8
0043a218        player->shoot_cooldown_step = 0.111111104f
0043a224        case 4
0043a224        player->shoot_flags = 0x10
0043a22e        player->shoot_cooldown_step = 0.111111104f
0043a23a        case 5
0043a23a        player->shoot_flags = 0x20
0043a292        player->shoot_cooldown_step = 0.0666666701f
0043a246        case 6
0043a246        player->shoot_flags = 0x40
0043a250        player->shoot_cooldown_step = 0.13333334f
0043a25c        case 7
0043a25c        player->shoot_flags = 0xc0
0043a266        player->shoot_cooldown_step = 0.13333334f
0043a272        case 8
0043a272        player->shoot_flags = 0x90
0043a27c        player->shoot_cooldown_step = 0.111111104f
0043a29c        uint32_t shoot_flags = player->shoot_flags
0043a2aa        if (shoot_flags == player->previous_shoot_flags)
0043a2cc        player->previous_shoot_flags = player->shoot_flags
0043a2d3        return
0043a2b3        set_snail_weapon(&player->presentation, shoot_flags)
0043a2be        player->previous_shoot_flags = player->shoot_flags
0043a2c5        return
