/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: query_directx_runtime_version @ 0x44afc0 */

0044afc7        int32_t ebp
0044afc7        int32_t var_90 = ebp
0044afc8        int32_t esi
0044afc8        int32_t var_94 = esi
0044afc9        int32_t edi
0044afc9        int32_t var_98 = edi
0044afd2        char* var_9c = "DDRAW.DLL"
0044afd7        int32_t* var_88 = nullptr
0044afdb        int32_t var_78 = 0
0044afdf        int32_t* var_84 = nullptr
0044afe3        int32_t* var_80 = nullptr
0044afe7        int32_t* var_74 = nullptr
0044afeb        int32_t eax = LoadLibraryA(var_9c)
0044aff1        if (eax == 0)
0044aff8        OutputDebugStringA("Couldn't LoadLibrary DDraw\r\n")
0044b00a        return 0
0044b017        int32_t eax_2 = GetProcAddress(eax, "DirectDrawCreate")
0044b01b        if (eax_2 == 0)
0044b01e        FreeLibrary(eax)
0044b029        OutputDebugStringA("Couldn't GetProcAddress DirectDrawCreate\r\n")
0044b03b        return 0
0044b047        if (eax_2(0, &var_88, 0) s< 0)
0044b04a        FreeLibrary(eax)
0044b055        OutputDebugStringA("Couldn't create DDraw\r\n")
0044b067        return 0
0044b068        int32_t* eax_6 = var_84
0044b07d        if ((**eax_6)(eax_6, 0x49b100, &var_74) s< 0)
0044b07f        int32_t* eax_8 = var_84
0044b086        (*(*eax_8 + 8))(eax_8)
0044b08a        FreeLibrary(eax)
0044b095        OutputDebugStringA("Couldn't QI DDraw2\r\n")
0044b0aa        return 0x100
0044b0ab        int32_t* eax_10 = var_74
0044b0b2        (*(*eax_10 + 8))(eax_10)
0044b0ba        int32_t eax_11 = LoadLibraryA("DINPUT.DLL")
0044b0c0        if (eax_11 == 0)
0044b0c2        int32_t* eax_12 = var_84
0044b0c9        (*(*eax_12 + 8))(eax_12)
0044b0cd        FreeLibrary(eax)
0044b0d8        OutputDebugStringA("Couldn't LoadLibrary DInput\r\n")
0044b0ed        return 0x200
0044b0f9        if (GetProcAddress(eax_11, "DirectInputCreateA") == 0)
0044b101        FreeLibrary(eax_11)
0044b103        int32_t* eax_15 = var_88
0044b10a        (*(*eax_15 + 8))(eax_15)
0044b10e        FreeLibrary(eax)
0044b115        OutputDebugStringA("Couldn't GetProcAddress DInputCreate\r\n")
0044b12a        return 0x200
0044b131        FreeLibrary(eax_11)
0044b13e        int32_t var_9c_12 = 8
0044b140        int32_t var_6c
0044b140        __builtin_memset(&var_6c, 0, 0x6c)
0044b142        int32_t* eax_17 = var_88
0044b146        var_6c = 0x6c
0044b14e        int32_t var_68 = 1
0044b156        int32_t var_4 = 0x200
0044b168        bool cond1 = (*(*eax_17 + 0x50))(eax_17, 0, var_9c_12) s>= 0
0044b16a        int32_t* eax_19 = var_88
0044b16e        if (not(cond1))
0044b173        (*(*eax_19 + 8))(eax_19)
0044b177        FreeLibrary(eax)
0044b17e        OutputDebugStringA("Couldn't Set coop level\r\n")
0044b190        return 0
0044b1a4        if ((*(*eax_19 + 0x18))(eax_19, &var_6c, &var_84, 0) s< 0)
0044b1a6        int32_t* eax_22 = var_88
0044b1ad        (*(*eax_22 + 8))(eax_22)
0044b1b1        FreeLibrary(eax)
0044b1b8        OutputDebugStringA("Couldn't CreateSurface\r\n")
0044b1ca        return 0
0044b1cb        int32_t* eax_24 = var_84
0044b1e0        if ((**eax_24)(eax_24, 0x49b0e0, &var_80) s< 0)
0044b1e2        int32_t* eax_26 = var_84
0044b1e9        (*(*eax_26 + 8))(eax_26)
0044b1ec        int32_t* eax_27 = var_84
0044b1f3        (*(*eax_27 + 8))(eax_27)
0044b1f7        FreeLibrary(eax)
0044b1fe        OutputDebugStringA("Couldn't QI DDS3\r\n")
0044b213        return 0x300
0044b214        int32_t* eax_29 = var_80
0044b21b        (*(*eax_29 + 8))(eax_29)
0044b21e        int32_t* eax_30 = var_84
0044b233        if ((**eax_30)(eax_30, 0x49b0d0, &var_74) s< 0)
0044b235        int32_t* eax_32 = var_84
0044b23c        (*(*eax_32 + 8))(eax_32)
0044b23f        int32_t* eax_33 = var_84
0044b246        (*(*eax_33 + 8))(eax_33)
0044b24a        FreeLibrary(eax)
0044b251        OutputDebugStringA("Couldn't QI DDS4\r\n")
0044b266        return 0x500
0044b267        int32_t* eax_35 = var_74
0044b26e        (*(*eax_35 + 8))(eax_35)
0044b271        int32_t* eax_36 = var_84
0044b278        (*(*eax_36 + 8))(eax_36)
0044b27b        int32_t* eax_37 = var_88
0044b282        (*(*eax_37 + 8))(eax_37)
0044b285        int32_t pvReserved = 0
0044b286        int32_t* ppv = nullptr
0044b28a        CoInitialize(pvReserved)
0044b2aa        if (CoCreateInstance(&data_49b000, 0, CLSCTX_INPROC_SERVER, &data_49aff0, &ppv) s< 0)
0044b2ad        FreeLibrary(eax)
0044b2b4        OutputDebugStringA("Couldn't create CLSID_DirectMusic\r\n")
0044b2c9        return 0x600
0044b2ca        int32_t* ppv_1 = ppv
0044b2d1        (*(*ppv_1 + 8))(ppv_1)
0044b2d4        CoUninitialize()
0044b2e0        int32_t eax_40 = GetProcAddress(eax, "DirectDrawCreateEx")
0044b2e8        if (eax_40 == 0)
0044b2eb        FreeLibrary(eax)
0044b2f2        OutputDebugStringA("Couldn't GetProcAddress DirectDrawCreateEx\r\n")
0044b307        return 0x601
0044b318        int32_t* var_70
0044b318        if (eax_40(0, &var_70, 0x49b0f0, 0) s< 0)
0044b31b        FreeLibrary(eax)
0044b322        OutputDebugStringA("Couldn't DirectDrawCreateEx\r\n")
0044b337        return 0x601
0044b338        int32_t* eax_44 = var_70
0044b33f        (*(*eax_44 + 8))(eax_44)
0044b347        int32_t eax_45 = LoadLibraryA("D3D8.DLL")
0044b351        if (eax_45 == 0)
0044b354        FreeLibrary(eax)
0044b35b        OutputDebugStringA("Couldn't LoadLibrary D3D8.DLL\r\n")
0044b370        return 0x700
0044b37e        if (LoadLibraryA("dpnhpast.dll") != 0)
0044b39f        FreeLibrary(eax)
0044b3a2        FreeLibrary(eax_45)
0044b3b3        return 0x801
0044b381        FreeLibrary(0)
0044b388        OutputDebugStringA("Couldn't LoadLibrary dpnhpast.dll\r\n")
0044b39d        return 0x800
