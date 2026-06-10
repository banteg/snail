/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_slice_quad @ 0x41a1c0 */
/* selector: initialize_backdrop_slice_quad */

// Builds one shared 4-vertex textured backdrop quad using a horizontal 1/8 UV slice selected by the panel index for the `Objects/World00*` lane.
int __cdecl sub_41A1C0(int *a1, _BYTE *a2, float a3)
{
  int v3; // edx
  int v4; // eax
  double v5; // st7
  int v6; // esi
  _DWORD *v7; // eax
  double v8; // st7

  request_object_vertices(a1, 4);
  request_object_facequads(a1, 1);
  v3 = a1[4];
  v4 = a1[14];
  v5 = a3 + 0.5;
  LOBYTE(v3) = v3 | 0x80;
  a1[4] = v3;
  v6 = a1[23];
  *(float *)v4 = v5;
  *(float *)(v4 + 24) = v5;
  *(_DWORD *)(v4 + 4) = 0;
  *(_DWORD *)(v4 + 8) = 1056964608;
  *(_DWORD *)(v4 + 12) = -1090519040;
  *(_DWORD *)(v4 + 16) = 0;
  *(_DWORD *)(v4 + 20) = 1056964608;
  *(_DWORD *)(v4 + 28) = 0;
  *(_DWORD *)(v4 + 32) = -1090519040;
  *(_DWORD *)(v4 + 36) = -1090519040;
  *(_DWORD *)(v4 + 40) = 0;
  *(_DWORD *)(v4 + 44) = -1090519040;
  *(_WORD *)v6 = 0;
  *(_WORD *)(v6 + 2) = 0;
  *(_WORD *)(v6 + 4) = 1;
  *(_WORD *)(v6 + 6) = 3;
  *(_WORD *)(v6 + 8) = 2;
  v7 = (_DWORD *)get_or_create_texture_ref(&texture_list, a2, 0, 0);
  *(_DWORD *)(v6 + 12) = v7;
  v8 = (a3 + 1.0) * -0.125;
  *v7 |= 2u;
  *(_DWORD *)(v6 + 24) = 0;
  *(_DWORD *)(v6 + 32) = 0;
  *(_DWORD *)(v6 + 36) = 0;
  *(_DWORD *)(v6 + 44) = 0;
  *(float *)(v6 + 16) = v8;
  *(float *)(v6 + 40) = v8;
  *(_DWORD *)(v6 + 20) = 1040187392;
  *(_DWORD *)(v6 + 28) = 1040187392;
  return 1040187392;
}

