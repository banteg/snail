/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_parcel @ 0x443730 */

0044373d        struct Parcel* result = allocate_track_parcel_slot(&runtime->parcel_manager)
00443746        if (result == 0)
00443851        return 0
00443757        result->state = PARCEL_STATE_TRACK_ACTIVE
00443762        float x = world_position->x
00443766        result->position.x.b = x.b
00443766        result->position.x:1.b = x:1.b
00443766        result->position.x:2.b = x:2.b
00443766        result->position.x:3.b = x:3.b
0044376d        result->position.y = world_position->y
00443770        int16_t z = (world_position->z).w
00443773        result->position.z.b = z.b
00443773        result->position.z:1.b = z:1.b
0044377c        result->owner_player = &runtime->player
0044378b        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, runtime->player.player_slot, 0x79, 0xffffffff, 0xffffffff)
00443790        result->sprite = eax_1
00443793        enum SpriteFlag flags = eax_1->flags
00443796        flags:1.b |= 8
0044379b        eax_1->flags = flags
004437ab        result->sprite->progress = 0f
004437bb        result->sprite->progress_step = 0f
004437c5        result->sprite->gravity_step = 0f
004437c8        struct tColour color
004437c8        struct tColour* eax_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004437d0        float r = eax_3->r
004437d2        struct tColour* ecx_6 = &result->sprite->color
004437d5        ecx_6->r.b = r.b
004437d5        ecx_6->r:1.b = r:1.b
004437d5        ecx_6->r:2.b = r:2.b
004437d5        ecx_6->r:3.b = r:3.b
004437da        ecx_6->g = eax_3->g
004437dd        int16_t b = (eax_3->b).w
004437e0        ecx_6->b.b = b.b
004437e0        ecx_6->b:1.b = b:1.b
004437e6        ecx_6->a = eax_3->a
004437f1        result->sprite->size_start = 1f
004437f7        result->sprite->size_end = 1f
004437ff        struct Vec3* eax_6 = &result->sprite->position
00443802        eax_6->x = result->position.x
00443807        eax_6->y = result->position.y
0044380d        eax_6->z = result->position.z
0044381c        int16_t x87control
0044381c        if ((ftol(x87control, fconvert.t(world_position->z)) & 1) == 0)
00443832        result->bob_phase = 0.5f
00443839        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
00443847        return result
0044381e        result->bob_phase = 0f
00443821        __builtin_strncpy(&result->bob_phase_step, "!\rR<", 4)
0044382f        return result
