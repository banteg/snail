/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_font3d_objects @ 0x44ae10 */
/* selector: initialize_font3d_objects */

// Builds the per-font `Objects/Font3D` bod instances, applies the atlas UV layout for each glyph slot, and scales each object to the registered font metrics.
int __cdecl sub_44AE10(float a1)
{
  int result; // eax
  int v2; // ebx
  float *v3; // ebp
  int **v4; // esi
  int v5; // edi
  _DWORD *v6; // eax
  int *v7; // eax
  int v8; // ecx
  int v9; // [esp+4h] [ebp-8h]
  int v10; // [esp+8h] [ebp-4h]
  float v11; // [esp+10h] [ebp+4h]

  result = SLOWORD(a1);
  v9 = 0;
  v2 = 2088 * SLOWORD(a1);
  if ( unk_7772F8[v2 / 4u] > 0 )
  {
    v3 = &unk_7770E8;
    v4 = (int **)&unk_77550C;
    v10 = 522 * SLOWORD(a1);
    v5 = 2088 * SLOWORD(a1) + 7828740;
    do
    {
      v11 = *(float *)(v5 + 512) / *(float *)(v2 + 7830276);
      v6 = add_object_to_list(unk_4B7648);
      set_bod_object(v4 - 9, (int)v6);
      load_object_definition(aObjectsFont3d, *v4);
      *(v4 - 2) = nullptr;
      *(v4 - 1) = nullptr;
      *(float *)((*v4)[23] + 12) = *(&unk_7772FC + *(_DWORD *)(v5 + 1024) + v10);
      *(_DWORD *)((*v4)[23] + 16) = *(_DWORD *)(v5 - 512);
      *(float *)((*v4)[23] + 20) = 1.0 - *(float *)(v2 + 7830280);
      *(_DWORD *)((*v4)[23] + 24) = *(_DWORD *)v5;
      *(float *)((*v4)[23] + 28) = 1.0 - *(float *)(v2 + 7830280);
      *(_DWORD *)((*v4)[23] + 32) = *(_DWORD *)v5;
      *(float *)((*v4)[23] + 36) = 1.0 - *(float *)(v2 + 7830284);
      *(_DWORD *)((*v4)[23] + 40) = *(_DWORD *)(v5 - 512);
      *(float *)((*v4)[23] + 44) = 1.0 - *(float *)(v2 + 7830284);
      *(float *)(*v4)[14] = v11 * *(float *)(*v4)[14];
      *(float *)((*v4)[14] + 12) = v11 * *(float *)((*v4)[14] + 12);
      *(float *)((*v4)[14] + 24) = v11 * *(float *)((*v4)[14] + 24);
      *(float *)((*v4)[14] + 36) = v11 * *(float *)((*v4)[14] + 36);
      (*v4)[5] = 1;
      v7 = *v4;
      v4 += 14;
      v5 += 4;
      ++v3;
      v7[4] |= 0x10u;
      v8 = unk_7772F8[v2 / 4u];
      *(v3 - 1) = v11;
      result = ++v9;
    }
    while ( v9 < v8 );
  }
  return result;
}

