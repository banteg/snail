/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_snail_weapons @ 0x442e40 */

00442e4e        if (snail->invincible_shell.channel_release_steps_active == 0)
00442e5d        int32_t var_24_1 = 0
00442e74        float var_c_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442e7d        long double x87_r7_5 = random_float_below(1f) + fconvert.t(0.5f)
00442eb1        snail->jetpack_channel.release_step.x = fconvert.s(fconvert.t(var_c_1) * fconvert.t(0.300000012f))
00442ec5        snail->jetpack_channel.release_step.y = fconvert.s(x87_r7_5 * fconvert.t(0.300000012f))
00442ed0        snail->jetpack_channel.release_step.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(snail->owner_player->velocity.z))) * fconvert.t(0.300000012f))
00442edc        int32_t var_2c_1 = 0
00442ef3        float var_1c_3 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442ef7        long double st0_2 = random_float_below(1f)
00442f30        snail->weapon_channels[0].release_step.x = fconvert.s(fconvert.t(var_1c_3) * fconvert.t(0.300000012f))
00442f44        snail->weapon_channels[0].release_step.y = fconvert.s((st0_2 + fconvert.t(0.5f)) * fconvert.t(0.300000012f))
00442f4f        snail->weapon_channels[0].release_step.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(snail->owner_player->velocity.z))) * fconvert.t(0.300000012f))
00442f5b        int32_t var_34_1 = 0
00442f72        float var_1c_5 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442f7b        long double x87_r7_21 = random_float_below(1f) + fconvert.t(0.5f)
00442faf        snail->weapon_channels[2].release_step.x = fconvert.s(fconvert.t(var_1c_5) * fconvert.t(0.300000012f))
00442fc3        snail->weapon_channels[2].release_step.y = fconvert.s(x87_r7_21 * fconvert.t(0.300000012f))
00442fce        snail->weapon_channels[2].release_step.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(snail->owner_player->velocity.z))) * fconvert.t(0.300000012f))
00442fda        int32_t var_3c_1 = 0
00442ff1        float var_1c_7 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442ff5        long double st0_4 = random_float_below(1f)
00442ffa        struct Player* owner_player = snail->owner_player
00443031        snail->weapon_channels[1].release_step.x = fconvert.s(fconvert.t(var_1c_7) * fconvert.t(0.300000012f))
00443045        snail->weapon_channels[1].release_step.y = fconvert.s((st0_4 + fconvert.t(0.5f)) * fconvert.t(0.300000012f))
00443050        snail->weapon_channels[1].release_step.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(owner_player->velocity.z))) * fconvert.t(0.300000012f))
00443059        end_jetpack_hover(&owner_player->sub_hover)
0044305e        snail->invincible_shell.channel_release_steps_active = 1
00443069        return
