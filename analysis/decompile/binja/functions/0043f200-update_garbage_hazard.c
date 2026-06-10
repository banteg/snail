/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_garbage_hazard @ 0x43f200 */

0043f20a        struct Game* result = self->game
0043f213        if (result->_pad_00[9] == 0)
0043f219        result = self->state
0043f222        if (result u> 3)
0043f4de        label_43f4de:
0043f4de        *(self->sprite + 0x7c) = fconvert.s(fconvert.t(self->owner->heading_roll) + fconvert.t(self->sprite_y_offset))
0043f4e1        result = self->owner
0043f4ee        if (result->__offset(0x384).b == 1)
0043f4f0        void* sprite = self->sprite
0043f4ff        *(sprite + 0x7c) = fconvert.s(fconvert.t(result->__offset(0x3a0).d) + fconvert.t(*(sprite + 0x7c)))
0043f228        switch (result)
0043f23a        case 1
0043f23a        char* ecx_1 = self->sprite + 0x48
0043f23d        float x = self->world_position.x
0043f23f        *ecx_1 = x.b
0043f23f        ecx_1[1] = x:1.b
0043f23f        ecx_1[2] = x:2.b
0043f23f        ecx_1[3] = x:3.b
0043f241        float y = self->world_position.y
0043f244        ecx_1[4] = y.b
0043f244        ecx_1[5] = y:1.b
0043f244        ecx_1[6] = y:2.b
0043f244        ecx_1[7] = y:3.b
0043f247        float z = self->world_position.z
0043f24a        ecx_1[8] = z.b
0043f24a        ecx_1[9] = z:1.b
0043f24a        ecx_1[0xa] = z:2.b
0043f24a        ecx_1[0xb] = z:3.b
0043f24d        struct Player* owner = self->owner
0043f253        long double x87_r7_1 = fconvert.t(self->world_position.z)
0043f256        long double temp1_1 = fconvert.t(owner->interaction_max_z)
0043f256        x87_r7_1 - temp1_1
0043f25c        y.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
0043f261        if ((y:1.b & 1) != 0)
0043f270        return destroy_garbage_hazard(self)
0043f271        long double x87_r7_2 = fconvert.t(owner->nuke_effect_progress)
0043f277        long double temp3_1 = fconvert.t(0f)
0043f277        x87_r7_2 - temp3_1
0043f27d        y.w = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
0043f282        if ((y:1.b & 0x41) == 0)
0043f284        long double x87_r7_3 = fconvert.t(self->world_position.x)
0043f286        long double temp6_1 = fconvert.t(0f)
0043f286        x87_r7_3 - temp6_1
0043f291        self->state = 2
0043f297        y.w = (x87_r7_3 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp6_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp6_1 ? 1 : 0) << 0xe
0043f29c        if ((y:1.b & 0x41) != 0)
0043f2aa        self->collision_side = 2
0043f29e        self->collision_side = 1
0043f2b2        add_subgoldy_score(owner, 0, 0)
0043f2cd        sub_415ef0(&self->game->__offset(0x1270fd4).d, &self->world_position.x, self->__offset(0x9c).d, 0, self)
0043f2d2        goto label_43f4de
0043f2d7        case 2
0043f2d7        void* __saved_ebp_2 = &data_4a4e6c
0043f2e1        self->state = 3
0043f2f0        float var_c_1 = fconvert.s(random_signed_float_below(0.100000001f))
0043f2f4        int32_t var_34_2 = 0
0043f305        int32_t var_3c_1 = 0
0043f30b        float var_8_1 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043f30f        long double st0_3 = random_float_below(0.300000012f)
0043f314        struct Game* game = self->game
0043f325        long double x87_r6_1 = fconvert.t(game->subgame_rate)
0043f33c        self->velocity.x = fconvert.s(x87_r6_1 * fconvert.t(var_c_1))
0043f34a        self->velocity.y = fconvert.s(fconvert.t(var_8_1) * x87_r6_1)
0043f355        self->velocity.z = fconvert.s(st0_3 * x87_r6_1)
0043f358        uint32_t collision_side = self->collision_side
0043f363        if (collision_side == 1)
0043f365        long double x87_r7_10 = fconvert.t(self->velocity.x)
0043f367        long double temp4_1 = fconvert.t(0f)
0043f367        x87_r7_10 - temp4_1
0043f36d        long double x87_r7_11 = fconvert.t(self->velocity.x)
0043f36f        collision_side.w = (x87_r7_10 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp4_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0043f374        if ((collision_side:1.b & 1) != 0)
0043f376        x87_r7_11 = fneg(x87_r7_11)
0043f394        self->velocity.x = fconvert.s(x87_r7_11)
0043f37d        if (collision_side == 2)
0043f37f        long double x87_r7_12 = fconvert.t(self->velocity.x)
0043f381        long double temp8_1 = fconvert.t(0f)
0043f381        x87_r7_12 - temp8_1
0043f387        long double x87_r7_13 = fconvert.t(self->velocity.x)
0043f389        collision_side.w = (x87_r7_12 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp8_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp8_1 ? 1 : 0) << 0xe | 0x3800
0043f38e        if ((collision_side:1.b & 1) != 0)
0043f390        x87_r7_13 = fneg(x87_r7_13)
0043f394        self->velocity.x = fconvert.s(fneg(x87_r7_13))
0043f396        long double x87_r7_14 = fconvert.t(self->velocity.x)
0043f398        long double temp7_1 = fconvert.t(0f)
0043f398        x87_r7_14 - temp7_1
0043f39e        collision_side.w = (x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe
0043f3a3        int32_t var_1c_1
0043f3a3        if ((collision_side:1.b & 1) == 0)
0043f3af        long double x87_r7_15 = fconvert.t(self->velocity.x)
0043f3b1        long double temp10_1 = fconvert.t(0f)
0043f3b1        x87_r7_15 - temp10_1
0043f3b7        var_1c_1 = 0
0043f3bb        collision_side.w = (x87_r7_15 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp10_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp10_1 ? 1 : 0) << 0xe
0043f3c0        if ((collision_side:1.b & 0x40) == 0)
0043f3c2        var_1c_1 = 1
0043f3a5        var_1c_1 = 0xffffffff
0043f3d4        long double x87_r7_18 = float.t(var_1c_1) * fconvert.t(0.200000003f) * fconvert.t(game->subgame_rate)
0043f3d7        self->__offset(0xa4).d = 0
0043f3df        self->velocity.x = fconvert.s(x87_r7_18 + fconvert.t(self->velocity.x))
0043f3e4        long double x87_r7_21 = fconvert.t(game->subgame_rate) * fconvert.t(0.00833333377f)
0043f3ea        self->smoke_timer = 0f
0043f3f0        self->__offset(0xa8).d = fconvert.s(x87_r7_21)
0043f3ff        self->smoke_timer_step = fconvert.s(fconvert.t(game->subgame_rate) * fconvert.t(0.277777791f))
0043f3a3        goto label_43f41a
0043f41a        case 3
0043f41a        label_43f41a:
0043f41a        self->world_position.x = fconvert.s(fconvert.t(self->velocity.x) + fconvert.t(self->world_position.x))
0043f422        self->world_position.y = fconvert.s(fconvert.t(self->velocity.y) + fconvert.t(self->world_position.y))
0043f42b        self->world_position.z = fconvert.s(fconvert.t(self->velocity.z) + fconvert.t(self->world_position.z))
0043f436        float* eax_4 = self->sprite + 0x48
0043f439        *eax_4 = self->world_position.x
0043f43e        eax_4[1] = self->world_position.y
0043f445        eax_4[2] = self->world_position.z
0043f44e        long double x87_r7_30 = fconvert.t(self->game->subgame_rate)
0043f461        self->velocity.y = fconvert.s(x87_r7_30 * x87_r7_30 * fconvert.t(-0.00999999978f) + fconvert.t(self->velocity.y))
0043f469        long double x87_r7_32 = fconvert.t(self->world_position.y)
0043f46c        long double temp2_1 = fconvert.t(-10f)
0043f46c        x87_r7_32 - temp2_1
0043f472        struct Game* eax_5
0043f472        eax_5.w = (x87_r7_32 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp2_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp2_1 ? 1 : 0) << 0xe
0043f477        if ((eax_5:1.b & 1) != 0)
0043f270        return destroy_garbage_hazard(self)
0043f47d        struct Player* owner_1 = self->owner
0043f483        long double x87_r7_33 = fconvert.t(self->world_position.z)
0043f486        long double temp5_1 = fconvert.t(owner_1->interaction_max_z)
0043f486        x87_r7_33 - temp5_1
0043f48c        eax_5.w = (x87_r7_33 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp5_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp5_1 ? 1 : 0) << 0xe
0043f491        if ((eax_5:1.b & 1) != 0)
0043f270        return destroy_garbage_hazard(self)
0043f49d        long double x87_r7_35 = fconvert.t(self->smoke_timer_step) + fconvert.t(self->smoke_timer)
0043f4a3        self->smoke_timer = fconvert.s(x87_r7_35)
0043f4a9        long double temp9_1 = fconvert.t(1f)
0043f4a9        x87_r7_35 - temp9_1
0043f4af        eax_5.w = (x87_r7_35 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp9_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp9_1 ? 1 : 0) << 0xe
0043f4b4        if ((eax_5:1.b & 0x41) == 0)
0043f4bb        self->smoke_timer = 0f
0043f4c1        spawn_garbage_smoke_particle(self, &self->world_position.x, &self->velocity, owner_1)
0043f4b4        goto label_43f4de
0043f508        return result
