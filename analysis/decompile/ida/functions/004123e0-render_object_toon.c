/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_object_toon @ 0x4123e0 */
/* selector: render_object_toon */

// Draws one object's optional toon edge pass by selecting visible outline segments against the current camera and submitting them as line primitives. Cross-port Android symbols match this helper to `G0RenderToon(cRObject*, tMatrix*)`.
int __usercall sub_4123E0@<eax>(int a1@<ebp>, int a2@<edi>, int a3@<esi>, int a4, int a5, int a6, float *a7)
{
  int result; // eax
  double v9; // st7
  int v10; // eax
  int v11; // ebp
  int v12; // esi
  int v13; // eax
  int v14; // ecx
  float *v15; // edi
  int v16; // edx
  int v17; // eax
  float *v18; // ecx
  int v19; // edx
  double v20; // st7
  int v21; // eax
  double v22; // st7
  double v23; // st7
  int *v24; // ecx
  int v25; // eax
  int v26; // esi
  int v27; // ecx
  float v28; // [esp+34h] [ebp-C4h]
  float v29; // [esp+38h] [ebp-C0h]
  int v31; // [esp+50h] [ebp-A8h] BYREF
  float v32; // [esp+54h] [ebp-A4h]
  float v33; // [esp+58h] [ebp-A0h]
  int v34; // [esp+5Ch] [ebp-9Ch]
  float v35; // [esp+60h] [ebp-98h]
  float v36; // [esp+64h] [ebp-94h] BYREF
  float v37; // [esp+68h] [ebp-90h]
  float v38; // [esp+6Ch] [ebp-8Ch]
  float v39; // [esp+70h] [ebp-88h]
  float v40; // [esp+74h] [ebp-84h]
  int v41[2]; // [esp+78h] [ebp-80h] BYREF
  int v42[16]; // [esp+80h] [ebp-78h] BYREF
  float v43[14]; // [esp+C0h] [ebp-38h] BYREF

  result = *(_DWORD *)(a4 + 16);
  if ( (result & 0x4000) != 0 )
  {
    v29 = MEMORY[0x5031D0] + 30.0;
    v28 = MEMORY[0x5031CC] + 0.0040000002;
    sub_450314((int)v41, MEMORY[0x5031D4], MEMORY[0x50316C], v28, v29);
    (*(void (__stdcall **)(int, int, int *, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 148))(
      MEMORY[0x502FEC],
      3,
      v41,
      a2,
      a3);
    v32 = *(float *)(MEMORY[0x5031B8] + 48) - a7[12];
    v33 = *(float *)(MEMORY[0x5031B8] + 52) - a7[13];
    v9 = *(float *)(MEMORY[0x5031B8] + 56) - a7[14];
    v37 = v33;
    qmemcpy(v43, a7, 0x40u);
    *(float *)&v34 = v9;
    v36 = v32;
    v38 = *(float *)&v34;
    invert_matrix_in_place(v43);
    rotate_vector_by_matrix(&v36, v43);
    vector_magnitude(&v36);
    (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 340))(
      MEMORY[0x502FEC],
      **(_DWORD **)(a4 + 216),
      0);
    (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 332))(
      MEMORY[0x502FEC],
      0,
      *(_DWORD *)(*(_DWORD *)(a4 + 192) + 8),
      24);
    v10 = *(_DWORD *)(a4 + 112);
    v35 = 0.0;
    if ( v10 > 0 )
    {
      v11 = 0;
      while ( 1 )
      {
        v12 = 0;
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD, int))(***(_DWORD ***)(a4 + 216) + 44))(
          **(_DWORD **)(a4 + 216),
          0,
          2 * *(_DWORD *)(a4 + 44),
          &v31,
          0,
          a1);
        v13 = v11 + *(_DWORD *)(a4 + 116);
        if ( (*(_BYTE *)v13 & 1) != 0 )
          break;
        v14 = *(_DWORD *)(a4 + 96);
        v15 = (float *)(v14 + 12 * *(_DWORD *)(v13 + 12));
        v16 = *(_DWORD *)(v13 + 16);
        v17 = 3 * *(_DWORD *)(v13 + 4);
        v18 = (float *)(v14 + 12 * v16);
        v19 = *(_DWORD *)(a4 + 56);
        v20 = v37 - *(float *)(v19 + 4 * v17);
        v21 = v19 + 4 * v17;
        v33 = v20;
        *(float *)&v34 = v38 - *(float *)(v21 + 4);
        v22 = v39 - *(float *)(v21 + 8);
        *(float *)v41 = v33;
        v41[1] = v34;
        v35 = v22;
        *(float *)v42 = v35;
        v40 = dot_vector((float *)v41, v18);
        v23 = dot_vector((float *)v41, v15);
        if ( v23 * v40 < 0.0099999998 )
        {
          *(_WORD *)LODWORD(v32) = *(_WORD *)(*(_DWORD *)(a4 + 116) + v11 + 4);
          *(_WORD *)(LODWORD(v32) + 2) = *(_WORD *)(*(_DWORD *)(a4 + 116) + v11 + 8);
          goto LABEL_8;
        }
LABEL_9:
        v24 = *(int **)(a4 + 216);
        a1 = *v24;
        (*(void (**)(void))(*(_DWORD *)*v24 + 48))();
        if ( v12 > 0 )
        {
          v25 = get_sprite_texture(93);
          bind_texture_ref(v25);
          v26 = v12 / 2;
          (*(void (__stdcall **)(int, int, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 284))(
            MEMORY[0x502FEC],
            2,
            0,
            *(_DWORD *)(a4 + 196),
            0,
            v26);
          MEMORY[0x4F7450] += v26;
          ++MEMORY[0x503170];
        }
        v27 = *(_DWORD *)(a4 + 112);
        v11 += 36;
        ++LODWORD(v35);
        if ( SLODWORD(v35) >= v27 )
          goto LABEL_12;
      }
      *(_WORD *)LODWORD(v32) = *(_WORD *)(v13 + 4);
      *(_WORD *)(LODWORD(v32) + 2) = *(_WORD *)(*(_DWORD *)(a4 + 116) + v11 + 8);
LABEL_8:
      v12 = 2;
      goto LABEL_9;
    }
LABEL_12:
    sub_450314((int)v42, MEMORY[0x5031D4], MEMORY[0x50316C], MEMORY[0x5031CC], MEMORY[0x5031D0]);
    return (*(int (__stdcall **)(int))(*(_DWORD *)MEMORY[0x502FEC] + 148))(MEMORY[0x502FEC]);
  }
  return result;
}

