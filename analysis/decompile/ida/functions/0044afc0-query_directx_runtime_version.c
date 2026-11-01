/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: query_directx_runtime_version @ 0x44afc0 */
/* selector: query_directx_runtime_version */

// Dynamically probes DirectDraw, DirectInput, and Direct3D 8 availability and returns the highest DirectX-style runtime version code reached by the startup capability check.
int query_directx_runtime_version()
{
  void *LibraryA; // eax
  void *v1; // esi
  void *DirectDrawCreate; // eax
  void *v4; // eax
  void *v5; // edi
  void *DirectDrawCreateEx; // eax
  void *v7; // edi
  int v8; // [esp+5Ch] [ebp-88h] BYREF
  int v9; // [esp+60h] [ebp-84h] BYREF
  int v10; // [esp+64h] [ebp-80h] BYREF
  int ppv; // [esp+68h] [ebp-7Ch] BYREF
  int v12; // [esp+6Ch] [ebp-78h] BYREF
  int v13; // [esp+70h] [ebp-74h] BYREF
  int v14; // [esp+74h] [ebp-70h] BYREF
  _DWORD v15[27]; // [esp+78h] [ebp-6Ch] BYREF

  v8 = 0;
  v12 = 0;
  v9 = 0;
  v10 = 0;
  v13 = 0;
  LibraryA = LoadLibraryA((const char *)aDdrawDll);
  v1 = LibraryA;
  if ( LibraryA != nullptr )
  {
    DirectDrawCreate = GetProcAddress(LibraryA, (const char *)aDirectdrawcrea);
    if ( DirectDrawCreate != nullptr )
    {
      if ( ((int (__stdcall *)(_DWORD, int *, _DWORD))DirectDrawCreate)(0, &v8, 0) >= 0 )
      {
        if ( (**(int (__stdcall ***)(int, void *, int *))v8)(v8, &g_iid_idirectdraw2, &v12) >= 0 )
        {
          (*(void (__stdcall **)(int))(*(_DWORD *)v12 + 8))(v12);
          v4 = LoadLibraryA((const char *)aDinputDll);
          v5 = v4;
          if ( v4 != nullptr )
          {
            if ( GetProcAddress(v4, (const char *)aDirectinputcre) != nullptr )
            {
              FreeLibrary(v5);
              memset(v15, 0, sizeof(v15));
              v15[0] = 108;
              v15[1] = 1;
              v15[26] = 512;
              if ( (*(int (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v8 + 80))(v8, 0, 8) >= 0 )
              {
                if ( (*(int (__stdcall **)(int, _DWORD *, int *, _DWORD))(*(_DWORD *)v8 + 24))(v8, v15, &v9, 0) >= 0 )
                {
                  if ( (**(int (__stdcall ***)(int, void *, int *))v9)(v9, &g_iid_idirectdrawsurface3, &v10) >= 0 )
                  {
                    (*(void (__stdcall **)(int))(*(_DWORD *)v10 + 8))(v10);
                    if ( (**(int (__stdcall ***)(int, void *, int *))v9)(v9, &g_iid_idirectdrawsurface4, &v13) >= 0 )
                    {
                      (*(void (__stdcall **)(int))(*(_DWORD *)v13 + 8))(v13);
                      (*(void (__stdcall **)(int))(*(_DWORD *)v9 + 8))(v9);
                      (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
                      ppv = 0;
                      ((void (__stdcall *)(_DWORD))CoInitialize)(0);
                      if ( ((int (__stdcall *)(void *, _DWORD, int, const PresentationAnimationChannel *, int *))CoCreateInstance)(
                             &g_clsid_directmusic,
                             0,
                             1,
                             &g_iid_idirectmusic,
                             &ppv) >= 0 )
                      {
                        (*(void (__stdcall **)(int))(*(_DWORD *)ppv + 8))(ppv);
                        CoUninitialize();
                        DirectDrawCreateEx = GetProcAddress(v1, (const char *)aDirectdrawcrea_0);
                        if ( DirectDrawCreateEx != nullptr )
                        {
                          if ( ((int (__stdcall *)(_DWORD, int *, PresentationAnimationChannel *, _DWORD))DirectDrawCreateEx)(
                                 0,
                                 &v14,
                                 &g_iid_idirectdraw7,
                                 0) >= 0 )
                          {
                            (*(void (__stdcall **)(int))(*(_DWORD *)v14 + 8))(v14);
                            v7 = LoadLibraryA((const char *)aD3d8Dll_0);
                            if ( v7 != nullptr )
                            {
                              if ( LoadLibraryA((const char *)aDpnhpastDll) != nullptr )
                              {
                                FreeLibrary(v1);
                                FreeLibrary(v7);
                                return 2049;
                              }
                              else
                              {
                                FreeLibrary(nullptr);
                                ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTLoadlib_2);
                                return 2048;
                              }
                            }
                            else
                            {
                              FreeLibrary(v1);
                              ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTLoadlib_1);
                              return 1792;
                            }
                          }
                          else
                          {
                            FreeLibrary(v1);
                            ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTDirectd);
                            return 1537;
                          }
                        }
                        else
                        {
                          FreeLibrary(v1);
                          ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTGetproc_1);
                          return 1537;
                        }
                      }
                      else
                      {
                        FreeLibrary(v1);
                        ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTCreateC);
                        return 1536;
                      }
                    }
                    else
                    {
                      (*(void (__stdcall **)(int))(*(_DWORD *)v9 + 8))(v9);
                      (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
                      FreeLibrary(v1);
                      ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTQiDds4);
                      return 1280;
                    }
                  }
                  else
                  {
                    (*(void (__stdcall **)(int))(*(_DWORD *)v9 + 8))(v9);
                    (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
                    FreeLibrary(v1);
                    ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTQiDds3);
                    return 768;
                  }
                }
                else
                {
                  (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
                  FreeLibrary(v1);
                  ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTCreates);
                  return 0;
                }
              }
              else
              {
                (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
                FreeLibrary(v1);
                ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTSetCoop);
                return 0;
              }
            }
            else
            {
              FreeLibrary(v5);
              (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
              FreeLibrary(v1);
              ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTGetproc_0);
              return 512;
            }
          }
          else
          {
            (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
            FreeLibrary(v1);
            ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTLoadlib_0);
            return 512;
          }
        }
        else
        {
          (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
          FreeLibrary(v1);
          ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTQiDdraw);
          return 256;
        }
      }
      else
      {
        FreeLibrary(v1);
        ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTCreateD);
        return 0;
      }
    }
    else
    {
      FreeLibrary(v1);
      ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(aCouldnTGetproc);
      return 0;
    }
  }
  else
  {
    ((void (__stdcall *)(ObjectFaceQuad *))OutputDebugStringA)(OutputString);
    return 0;
  }
}
