/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_sprite_texture @ 0x44e0f0 */

0044e0f9        char* eax = arg1
0044e0fe        if (*arg1 != 0x2e)
0044e107        char i
0044e100        i = eax[1]
0044e103        eax = &eax[1]
0044e107        do while (i != 0x2e)
0044e113        if (arg2 s>= 0x3e8)
0044e115        int32_t var_10_1 = 0x3e8
0044e11f        report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h")
0044e134        struct TextureRef* eax_1 = get_or_create_texture_ref(&data_4b7790, arg1, 0, arg3.w)
0044e139        *((arg2 << 2) + &data_78ff90) = eax_1
0044e145        eax_1->__offset(0x0).d |= arg3
0044e147        void* result = *((arg2 << 2) + &data_78ff90)
0044e150        *(result + 0x90) = 0
0044e15a        return result
