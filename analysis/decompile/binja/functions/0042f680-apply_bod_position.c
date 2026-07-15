/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_bod_position @ 0x42f680 */

0042f687        int32_t i = 0
0042f689        struct Object* object = bod->object
0042f691        if (object->vertex_count s> 0)
0042f699        int32_t esi_1 = 0
0042f6a6        struct Vec3 out
0042f6a6        struct Vec3* eax = multiply_vector_by_matrix_copy(object->vertices + esi_1, &out, matrix)
0042f6b3        int32_t* ecx_4 = bod->object->vertices + esi_1
0042f6b5        i += 1
0042f6b6        esi_1 += 0xc
0042f6b9        *ecx_4 = eax->x
0042f6be        ecx_4[1] = eax->y
0042f6c4        ecx_4[2] = eax->z
0042f6c7        object = bod->object
0042f6cd        do while (i s< object->vertex_count)
0042f6d6        return object
