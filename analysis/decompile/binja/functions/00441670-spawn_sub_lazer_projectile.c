/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_sub_lazer_projectile @ 0x441670 */

00441678        pool_head->state = 1
00441684        set_matrix_identity(&pool_head->_pad_18[0x20])
00441698        pool_head->world_position.x = origin->x
0044169d        pool_head->world_position.y = origin->y
004416a7        pool_head->world_position.z = origin->z
004416ae        pool_head->velocity.x = direction->x
004416b3        pool_head->velocity.y = direction->y
004416b6        float z = direction->z
004416b9        pool_head->lifetime_driver = 0f
004416c8        pool_head->velocity.z = z
004416cb        void* emitter = pool_head->emitter
004416e2        bool cond:0 = (0x200 & pool_head->_pad_00[4].d) == 0
004416e4        pool_head->lifetime = fconvert.s(fconvert.t(*(emitter + 0x38)) * fconvert.t(0.00555555569f))
004416ea        if (not(cond:0))
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
00441713        void* eax_4 = pool_head->_pad_00[0xc].d
00441718        if (eax_4 != 0)
0044171a        *(eax_4 + 8) = pool_head
00441721        int32_t eax_6 = pool_head->_pad_00[4].d | 0x200
00441725        pool_head->_pad_00[4] = eax_6.b
00441725        pool_head->_pad_00[5] = eax_6:1.b
00441725        pool_head->_pad_00[6] = eax_6:2.b
00441725        pool_head->_pad_00[7] = eax_6:3.b
00441730        return set_matrix_z_direction(&pool_head->_pad_18[0x20], &pool_head->velocity)
