/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_parcel @ 0x443730 */

0044373d        struct TrackParcelRuntime* result = allocate_track_parcel_slot(&game->parcel_pool)
00443746        if (result == 0)
00443851        return 0
00443757        result->state = 1
00443762        float x = world_position->x
00443766        result->world_position.x.b = x.b
00443766        result->world_position.x:1.b = x:1.b
00443766        result->world_position.x:2.b = x:2.b
00443766        result->world_position.x:3.b = x:3.b
0044376a        float y = world_position->y
0044376d        result->world_position.y.b = y.b
0044376d        result->world_position.y:1.b = y:1.b
0044376d        result->world_position.y:2.b = y:2.b
0044376d        result->world_position.y:3.b = y:3.b
00443770        float z = world_position->z
00443773        result->world_position.z.b = z.b
00443773        result->world_position.z:1.b = z:1.b
00443773        result->world_position.z:2.b = z:2.b
00443773        result->world_position.z:3.b = z:3.b
0044377c        result->owner = &game->__offset(0x3bb764).d
0044378b        int32_t* eax_1 = allocate_sprite(&data_790f30, game->__offset(0x3bbae4).d, 0x79, 0xffffffff, 0xffffffff)
00443790        result->sprite = eax_1
00443796        int32_t ecx_3
00443796        ecx_3:1.b = eax_1[1]:1.b | 8
0044379b        eax_1[1] = ecx_3
004437ab        *(result->sprite + 0x68) = 0
004437bb        *(result->sprite + 0x6c) = 0
004437c5        *(result->sprite + 0x78) = 0
004437c8        struct Color4f color
004437c8        struct Color4f* eax_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004437d0        float r = eax_3->r
004437d2        char* ecx_7 = result->sprite + 0x2c
004437d5        *ecx_7 = r.b
004437d5        ecx_7[1] = r:1.b
004437d5        ecx_7[2] = r:2.b
004437d5        ecx_7[3] = r:3.b
004437d7        float g = eax_3->g
004437da        ecx_7[4] = g.b
004437da        ecx_7[5] = g:1.b
004437da        ecx_7[6] = g:2.b
004437da        ecx_7[7] = g:3.b
004437dd        float b = eax_3->b
004437e0        ecx_7[8] = b.b
004437e0        ecx_7[9] = b:1.b
004437e0        ecx_7[0xa] = b:2.b
004437e0        ecx_7[0xb] = b:3.b
004437e3        float a = eax_3->a
004437e6        ecx_7[0xc] = a.b
004437e6        ecx_7[0xd] = a:1.b
004437e6        ecx_7[0xe] = a:2.b
004437e6        ecx_7[0xf] = a:3.b
004437f1        *(result->sprite + 0x60) = 0x3f800000
004437f7        *(result->sprite + 0x64) = 0x3f800000
004437ff        float* eax_5 = result->sprite + 0x48
00443802        *eax_5 = result->world_position.x
00443807        eax_5[1] = result->world_position.y
0044380d        eax_5[2] = result->world_position.z
0044381c        int16_t x87control
0044381c        if ((__ftol(x87control, fconvert.t(world_position->z)) & 1) == 0)
00443832        result->bob_phase = 0.5f
00443839        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
00443847        return result
0044381e        result->bob_phase = 0f
00443821        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
0044382f        return result
