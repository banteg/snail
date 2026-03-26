/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_parcel @ 0x443730 */

0044373d        struct TrackParcelRuntime* result = allocate_track_parcel_slot(game + 0x125e480)
00443746        if (result == 0)
00443851        return 0
00443757        result->state = 1
00443766        result->world_position.x = world_position->x
0044376d        result->world_position.y = world_position->y
00443773        result->world_position.z = world_position->z
0044377c        result->owner = game + 0x3bb764
0044378b        int32_t* eax_2 = allocate_sprite(&data_790f30, game->__offset(0x3bbae4).d, 0x79, 0xffffffff, 0xffffffff)
00443790        result->sprite = eax_2
00443796        int32_t ecx_3
00443796        ecx_3:1.b = eax_2[1]:1.b | 8
0044379b        eax_2[1] = ecx_3
004437ab        *(result->sprite + 0x68) = 0
004437bb        *(result->sprite + 0x6c) = 0
004437c5        *(result->sprite + 0x78) = 0
004437c8        struct Color4f color
004437c8        struct Color4f* eax_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004437d2        float* ecx_7 = result->sprite + 0x2c
004437d5        *ecx_7 = eax_4->r
004437da        ecx_7[1] = eax_4->g
004437e0        ecx_7[2] = eax_4->b
004437e6        ecx_7[3] = eax_4->a
004437f1        *(result->sprite + 0x60) = 0x3f800000
004437f7        *(result->sprite + 0x64) = 0x3f800000
004437ff        int32_t* eax_7 = result->sprite + 0x48
00443802        *eax_7 = result->world_position.x
00443807        eax_7[1] = result->world_position.y
0044380d        eax_7[2] = result->world_position.z
0044381c        int16_t x87control
0044381c        if ((__ftol(x87control, fconvert.t(world_position->z)) & 1) == 0)
00443832        result->bob_phase = 0.5f
00443839        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
00443847        return result
0044381e        result->bob_phase = 0f
00443821        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
0044382f        return result
