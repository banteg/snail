/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: explode_slug_hazard @ 0x43f680 */

0043f689        int32_t result_1 = 0x46
0043f89e        int32_t result
0043f89e        bool cond:0_1
0043f698        int32_t var_3c_1 = next_math_random_value()
0043f69c        unimplemented  {fild st0, dword [esp+0x14]}
0043f6a0        unimplemented  {fmul st0, dword [0x49753c]}
0043f6a6        unimplemented  {fadd dword [0x497270]}
0043f6ac        float var_3c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043f6ac        unimplemented  {fstp dword [esp+0x14], st0}
0043f6b5        int32_t var_40_1 = next_math_random_value()
0043f6bb        unimplemented  {fild st0, dword [esp+0x14]}
0043f6cd        unimplemented  {fmul st0, dword [0x497278]}
0043f6d3        unimplemented  {fmul st0, dword [0x497624]}
0043f6d9        unimplemented  {fadd dword [0x49744c]}
0043f6df        float var_40_2 = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043f6df        unimplemented  {fstp dword [esp+0x20], st0}
0043f6e3        int32_t* eax_3 = allocate_sprite(&g_sprite_manager, 1, 0x81, 0xffffffff, 0xffffffff)
0043f6e8        unimplemented  {fld st0, dword [esp+0x10]}
0043f6ee        unimplemented  {fadd st0, st0}
0043f6f0        int32_t edx_1 = eax_3[1]
0043f6f3        eax_3[0x1a] = 0
0043f6fc        eax_3[1] = edx_1 | 0x802
0043f6ff        eax_3[0x22] = fconvert.s(unimplemented  {fstp dword [esi+0x88], st0})
0043f6ff        unimplemented  {fstp dword [esi+0x88], st0}
0043f70a        int32_t var_34_1 = next_math_random_value()
0043f714        unimplemented  {fild st0, dword [esp+0x1c]}
0043f718        unimplemented  {fmul st0, dword [0x497620]}
0043f71e        unimplemented  {fadd dword [0x4973d4]}
0043f724        unimplemented  {fmul st0, dword [0x497298]}
0043f72a        unimplemented  {fdivr st0, dword [0x497220]}
0043f730        unimplemented  {fmul st0, dword [eax+0x38]}
0043f733        eax_3[0x1c] = 0
0043f736        eax_3[0x1d] = 0
0043f739        eax_3[0x1b] = fconvert.s(unimplemented  {fstp dword [esi+0x6c], st0})
0043f739        unimplemented  {fstp dword [esi+0x6c], st0}
0043f741        int32_t var_34_2 = next_math_random_value()
0043f745        int32_t var_54_1 = 0x1fff
0043f746        unimplemented  {fild st0, dword [esp+0x20]}
0043f74d        unimplemented  {fmul st0, dword [0x49761c]}
0043f753        unimplemented  {fadd dword [0x497200]}
0043f759        float intensity = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043f759        unimplemented  {fstp dword [esp], st0}
0043f75c        set_color_grayscale(&eax_3[0xb], intensity)
0043f761        unimplemented  {fld st0, dword [esp+0x10]}
0043f765        unimplemented  {fmul st0, dword [0x4973d8]}
0043f76b        eax_3[0x18] = fconvert.s(unimplemented  {fstp dword [esi+0x60], st0})
0043f76b        unimplemented  {fstp dword [esi+0x60], st0}
0043f76e        unimplemented  {fld st0, dword [esp+0x10]}
0043f772        unimplemented  {fmul st0, dword [0x497618]}
0043f778        eax_3[0x19] = fconvert.s(unimplemented  {fstp dword [esi+0x64], st0})
0043f778        unimplemented  {fstp dword [esi+0x64], st0}
0043f781        unimplemented  {fld st0, dword [ecx+0x38]}
0043f784        unimplemented  {fld st0, st0}
0043f786        unimplemented  {fmul st0, st1}
0043f788        unimplemented  {fmul st0, dword [0x4975cc]}
0043f78e        unimplemented  {fmul st0, dword [0x497614]}
0043f794        eax_3[0x1e] = fconvert.s(unimplemented  {fstp dword [esi+0x78], st0})
0043f794        unimplemented  {fstp dword [esi+0x78], st0}
0043f797        unimplemented  {fstp st0, st0}
0043f797        unimplemented  {fstp st0, st0}
0043f79e        int32_t var_34_3 = next_math_random_value()
0043f7a2        unimplemented  {fild st0, dword [esp+0x1c]}
0043f7a6        unimplemented  {fsub st0, dword [0x497294]}
0043f7ac        unimplemented  {fmul st0, dword [esp+0x14]}
0043f7b0        unimplemented  {fmul st0, dword [0x49728c]}
0043f7b6        float var_18_1 = fconvert.s(unimplemented  {fstp dword [esp+0x38], st0})
0043f7b6        unimplemented  {fstp dword [esp+0x38], st0}
0043f7bf        int32_t var_34_4 = next_math_random_value()
0043f7c9        unimplemented  {fild st0, dword [esp+0x1c]}
0043f7cd        unimplemented  {fld st0, dword [esp+0x14]}
0043f7d1        unimplemented  {fadd dword [0x4973d8]}
0043f7d7        unimplemented  {fmulp st1, st0}
0043f7d7        unimplemented  {fmulp st1, st0}
0043f7d9        unimplemented  {fmul st0, dword [0x497278]}
0043f7df        float var_14_1 = fconvert.s(unimplemented  {fstp dword [esp+0x3c], st0})
0043f7df        unimplemented  {fstp dword [esp+0x3c], st0}
0043f7e8        int32_t var_34_5 = next_math_random_value()
0043f7ec        unimplemented  {fild st0, dword [esp+0x1c]}
0043f7f0        unimplemented  {fmul st0, dword [esp+0x14]}
0043f7f4        unimplemented  {fmul st0, dword [0x497278]}
0043f7fa        unimplemented  {fadd dword [ebx+0x3bbb7c]}
0043f800        unimplemented  {fld st0, dword [ebx+0x38]}
0043f803        unimplemented  {fld st0, st0}
0043f805        unimplemented  {fmul st0, dword [esp+0x38]}
0043f80e        float var_30_1 = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043f80e        unimplemented  {fstp dword [esp+0x20], st0}
0043f812        unimplemented  {fld st0, dword [esp+0x3c]}
0043f816        unimplemented  {fmul st0, st1}
0043f81c        eax_3[0x15] = var_30_1
0043f81e        float var_2c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
0043f81e        unimplemented  {fstp dword [esp+0x24], st0}
0043f826        unimplemented  {fxch st0, st1}
0043f826        unimplemented  {fxch st0, st1}
0043f828        unimplemented  {fmul st0, st1}
0043f82a        eax_3[0x16] = var_2c_1
0043f82d        float var_28_1 = fconvert.s(unimplemented  {fstp dword [esp+0x28], st0})
0043f82d        unimplemented  {fstp dword [esp+0x28], st0}
0043f835        unimplemented  {fstp st0, st0}
0043f835        unimplemented  {fstp st0, st0}
0043f837        eax_3[0x17] = var_28_1
0043f83f        int32_t var_34_6 = next_math_random_value()
0043f846        unimplemented  {fild st0, dword [esp+0x1c]}
0043f84a        unimplemented  {fmul st0, dword [0x497610]}
0043f850        unimplemented  {fld st0, st0}
0043f852        unimplemented  {fmul st0, dword [ebx]}
0043f854        float var_c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x44], st0})
0043f854        unimplemented  {fstp dword [esp+0x44], st0}
0043f858        unimplemented  {fld st0, st0}
0043f85a        unimplemented  {fmul st0, dword [ebx+0x4]}
0043f85d        float var_8_1 = fconvert.s(unimplemented  {fstp dword [esp+0x48], st0})
0043f85d        unimplemented  {fstp dword [esp+0x48], st0}
0043f861        unimplemented  {fmul st0, dword [ebx+0x8]}
0043f864        unimplemented  {fld st0, dword [esp+0x44]}
0043f868        unimplemented  {fadd dword [edi+0x68]}
0043f86b        float var_24_1 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
0043f86b        unimplemented  {fstp dword [esp+0x2c], st0}
0043f86f        unimplemented  {fld st0, dword [esp+0x48]}
0043f873        unimplemented  {fadd dword [edi+0x6c]}
0043f87a        float var_20_1 = fconvert.s(unimplemented  {fstp dword [esp+0x30], st0})
0043f87a        unimplemented  {fstp dword [esp+0x30], st0}
0043f882        unimplemented  {fadd dword [edi+0x70]}
0043f885        eax_3[0x12] = var_24_1
0043f887        eax_3[0x13] = var_20_1
0043f88a        float var_1c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x34], st0})
0043f88a        unimplemented  {fstp dword [esp+0x34], st0}
0043f892        eax_3[0x14] = var_1c_1
0043f899        result = result_1 - 1
0043f899        cond:0_1 = result_1 != 1
0043f89a        result_1 = result
0043f89e        do while (cond:0_1)
0043f8ab        return result
