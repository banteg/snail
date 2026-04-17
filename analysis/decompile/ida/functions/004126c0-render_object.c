/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_object @ 0x4126c0 */
/* selector: render_object */

// Renders one built object through the grouped Direct3D path: refreshes animated vertices, sets world transform and cull mode, binds each texture group, applies the blend preset and tint, submits indexed primitives, and optionally dispatches the toon edge pass. Cross-port Android symbols match this helper to `G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool)`.
int __cdecl sub_4126C0(int a1, const void *a2, int a3, float a4, _DWORD *a5, char a6)
{
  int result; // eax
  _UNKNOWN **v7; // edi
  int v8; // esi
  char v9; // cl
  int v10; // eax
  int v11; // [esp+8h] [ebp-54h]
  int v12; // [esp+Ch] [ebp-50h]
  float *v13; // [esp+10h] [ebp-4Ch]
  _BYTE v14[64]; // [esp+1Ch] [ebp-40h] BYREF
  _UNKNOWN *retaddr; // [esp+5Ch] [ebp+0h] BYREF

  result = *(_DWORD *)(a1 + 16);
  if ( (result & 0x80000) != 0 && (result & 0x40000) == 0 )
  {
    result = *(_DWORD *)(a1 + 44);
    if ( result )
    {
      refresh_object_vertex_buffer((_DWORD *)a1);
      qmemcpy(v14, a2, sizeof(v14));
      v7 = &retaddr;
      (*(void (__stdcall **)(int, int, _BYTE *))(*(_DWORD *)MEMORY[0x502FEC] + 148))(MEMORY[0x502FEC], 256, v14);
      set_cull_mode((*(_DWORD *)(a1 + 16) & 0x100000) == 0);
      v8 = 0;
      if ( *(int *)(a1 + 100) > 0 )
      {
        v7 = (_UNKNOWN **)a5;
        v9 = MEMORY[0x503260];
        do
        {
          if ( v9 )
          {
            if ( v9 != 1 || a6 != 1 || (**(_DWORD **)(*(_DWORD *)(a1 + 208) + 4 * v8) & 0x10000) != 0 )
            {
LABEL_13:
              if ( *(_DWORD *)(*(_DWORD *)(a1 + 208) + 4 * v8) )
              {
                if ( (*(_BYTE *)(a1 + 16) & 8) != 0 )
                  v11 = *(_DWORD *)(a1 + 24);
                else
                  v11 = *(_DWORD *)(*(_DWORD *)(a1 + 208) + 4 * v8);
                bind_texture_ref(v11);
                if ( *(char *)(a1 + 16) >= 0 )
                {
                  (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 252))(
                    MEMORY[0x502FEC],
                    0,
                    24,
                    0);
                }
                else
                {
                  MEMORY[0x5031F8] = a3;
                  MEMORY[0x5031FC] = 1.0 - a4;
                  (*(void (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)MEMORY[0x502FEC] + 148))(
                    MEMORY[0x502FEC],
                    16,
                    MEMORY[0x5031D8]);
                  (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 252))(
                    MEMORY[0x502FEC],
                    0,
                    24,
                    2);
                }
                if ( a5[3] == 1065353216 || (**(_DWORD **)(*(_DWORD *)(a1 + 208) + 4 * v8) & 0x10000) == 0 )
                {
                  (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 0);
                }
                else
                {
                  set_blend_mode(*(_DWORD *)(a1 + 20));
                  v10 = *(_DWORD *)(a1 + 16);
                  if ( (v10 & 0x50) != 0 )
                  {
                    LOBYTE(v10) = v10 & 0xBF;
                    *(_DWORD *)(a1 + 16) = v10;
                    set_object_color((_DWORD *)a1, *a5, a5[1], a5[2], a5[3]);
                  }
                }
                (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 332))(
                  MEMORY[0x502FEC],
                  0,
                  *(_DWORD *)(*(_DWORD *)(a1 + 192) + 8),
                  24);
                (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 304))(MEMORY[0x502FEC], 322);
                (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 340))(
                  MEMORY[0x502FEC],
                  **(_DWORD **)(a1 + 200),
                  0);
                (*(void (__stdcall **)(int, int, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 284))(
                  MEMORY[0x502FEC],
                  4,
                  0,
                  *(_DWORD *)(a1 + 196),
                  *(_DWORD *)(*(_DWORD *)(a1 + 204) + 4 * v8),
                  *(_DWORD *)(*(_DWORD *)(a1 + 212) + 4 * v8));
                v9 = MEMORY[0x503260];
                MEMORY[0x4F7450] += *(_DWORD *)(*(_DWORD *)(a1 + 212) + 4 * v8);
                ++MEMORY[0x503170];
              }
            }
          }
          else if ( a6 != 1 || (**(_DWORD **)(*(_DWORD *)(a1 + 208) + 4 * v8) & 0x10000) == 0 )
          {
            goto LABEL_13;
          }
          ++v8;
        }
        while ( v8 < *(_DWORD *)(a1 + 100) );
      }
      return render_object_toon(a1, (int)v7, v8, a1, (int)a2, v12, v13);
    }
  }
  return result;
}

