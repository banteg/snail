/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_sub_lazer_projectile @ 0x441670 */

00441678        pool_head->state = 1
00441684        set_matrix_identity(&pool_head->_pad_18[0x20])
00441696        int32_t edx
00441696        edx.b = origin->x.b
00441696        edx:1.b = origin->x:1.b
00441696        edx:2.b = origin->x:2.b
00441696        edx:3.b = origin->x:3.b
00441698        pool_head->world_position.x = edx
0044169a        float edx_1
0044169a        edx_1.b = origin->y.b
0044169a        edx_1:1.b = origin->y:1.b
0044169a        edx_1:2.b = origin->y:2.b
0044169a        edx_1:3.b = origin->y:3.b
0044169d        pool_head->world_position.y = edx_1
004416a4        float ecx_2
004416a4        ecx_2.b = origin->z.b
004416a4        ecx_2:1.b = origin->z:1.b
004416a4        ecx_2:2.b = origin->z:2.b
004416a4        ecx_2:3.b = origin->z:3.b
004416a7        pool_head->world_position.z = ecx_2
004416ae        pool_head->velocity.x = direction->x
004416b3        pool_head->velocity.y = direction->y
004416b6        float z = direction->z
004416b9        pool_head->lifetime_driver = 0f
004416c8        pool_head->velocity.z = z
004416cb        void* emitter = pool_head->emitter
004416d1        int32_t edx_3
004416d1        edx_3.b = pool_head->_pad_00[4]
004416d1        edx_3:1.b = pool_head->_pad_00[5]
004416d1        edx_3:2.b = pool_head->_pad_00[6]
004416d1        edx_3:3.b = pool_head->_pad_00[7]
004416e4        pool_head->lifetime = fconvert.s(fconvert.t(*(emitter + 0x38)) * fconvert.t(0.00555555569f))
004416ea        if ((0x200 & edx_3) != 0)
004416f1        report_errorf("List ADDafter")
00441704        return set_matrix_z_direction(&pool_head->_pad_18[0x20], &pool_head->velocity)
00441707        pool_head->_pad_00[8] = (emitter + 0x355bd4).b
00441707        pool_head->_pad_00[9] = (emitter + 0x355bd4):1.b
00441707        pool_head->_pad_00[0xa] = (emitter + 0x355bd4):2.b
00441707        pool_head->_pad_00[0xb] = (emitter + 0x355bd4):3.b
0044170a        int32_t edx_4 = *(emitter + 0x355be0)
0044170d        pool_head->_pad_00[0xc] = edx_4.b
0044170d        pool_head->_pad_00[0xd] = edx_4:1.b
0044170d        pool_head->_pad_00[0xe] = edx_4:2.b
0044170d        pool_head->_pad_00[0xf] = edx_4:3.b
00441710        *(emitter + 0x355be0) = pool_head
00441713        void* eax_4
00441713        eax_4.b = pool_head->_pad_00[0xc]
00441713        eax_4:1.b = pool_head->_pad_00[0xd]
00441713        eax_4:2.b = pool_head->_pad_00[0xe]
00441713        eax_4:3.b = pool_head->_pad_00[0xf]
00441718        if (eax_4 != 0)
0044171a        *(eax_4 + 8) = pool_head
0044171d        int32_t eax_5
0044171d        eax_5.b = pool_head->_pad_00[4]
0044171d        eax_5:1.b = pool_head->_pad_00[5]
0044171d        eax_5:2.b = pool_head->_pad_00[6]
0044171d        eax_5:3.b = pool_head->_pad_00[7]
00441721        int32_t eax_6 = eax_5 | 0x200
00441725        pool_head->_pad_00[4] = eax_6.b
00441725        pool_head->_pad_00[5] = eax_6:1.b
00441725        pool_head->_pad_00[6] = eax_6:2.b
00441725        pool_head->_pad_00[7] = eax_6:3.b
00441730        return set_matrix_z_direction(&pool_head->_pad_18[0x20], &pool_head->velocity)
