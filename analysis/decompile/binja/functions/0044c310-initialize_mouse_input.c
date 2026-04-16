/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_mouse_input @ 0x44c310 */

0044c32d        data_777d58 = fconvert.s(fconvert.t(data_4df85c) * fconvert.t(0.5f))
0044c339        long double x87_r7_2 = fconvert.t(data_4b7760) * fconvert.t(0.5f)
0044c341        data_777d70 = 1
0044c348        data_777d60 = fconvert.s(x87_r7_2)
0044c355        HRESULT result = DirectInput8Create(GetModuleHandleA(nullptr), 0x800, 0x49b0c0, &data_777d98, 0)
0044c35c        if (result s>= 0)
0044c35e        int32_t* eax_1 = data_777d98
0044c372        result = (*(*eax_1 + 0xc))(eax_1, 0x49b020, &data_777d9c, 0)
0044c377        if (result s>= 0)
0044c379        int32_t* eax_2 = data_777d9c
0044c386        result = (*(*eax_2 + 0x2c))(eax_2, 0x49b70c)
0044c38b        if (result s>= 0)
0044c38d        int32_t* eax_3 = data_777d9c
0044c39c        (*(*eax_3 + 0x34))(eax_3, arg1, 4)
0044c39f        int32_t* eax_4 = data_777d9c
0044c3a7        (*(*eax_4 + 0x1c))(eax_4)
0044c3aa        return 0
0044c3ac        return result
