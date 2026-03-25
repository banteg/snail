/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_textured_backdrop_quad @ 0x41a0b0 */
/* selector: initialize_textured_backdrop_quad */

// Builds one shared 4-vertex textured backdrop quad with full-range UVs for the `Objects/Univers*` lane.
int __cdecl sub_41A0B0(int *a1, _BYTE *a2, float a3)
{
  double v3; // st7
  int v4; // eax
  int v5; // esi
  _DWORD *v6; // eax
  double v7; // st7

  request_object_vertices(a1, 4);
  request_object_facequads(a1, 1);
  v3 = a3 + 0.5;
  v4 = a1[14];
  v5 = a1[23];
  *(_DWORD *)(v4 + 4) = 0;
  *(float *)v4 = v3;
  *(float *)(v4 + 24) = v3;
  *(_DWORD *)(v4 + 8) = 1056964608;
  *(_DWORD *)(v4 + 12) = -1090519040;
  *(_DWORD *)(v4 + 16) = 0;
  *(_DWORD *)(v4 + 20) = 1056964608;
  *(_DWORD *)(v4 + 28) = 0;
  *(_DWORD *)(v4 + 32) = -1090519040;
  *(_DWORD *)(v4 + 36) = -1090519040;
  *(_DWORD *)(v4 + 40) = 0;
  *(_DWORD *)(v4 + 44) = -1090519040;
  *(_WORD *)v5 = 0;
  *(_WORD *)(v5 + 2) = 0;
  *(_WORD *)(v5 + 4) = 1;
  *(_WORD *)(v5 + 6) = 3;
  *(_WORD *)(v5 + 8) = 2;
  v6 = (_DWORD *)get_or_create_texture_ref(&dword_4B7790, a2, 0, 0);
  v7 = a3 + 1.0;
  *(_DWORD *)(v5 + 12) = v6;
  *v6 |= 2u;
  *(float *)(v5 + 24) = v7;
  *(float *)(v5 + 32) = v7;
  *(_DWORD *)(v5 + 16) = 0;
  *(_DWORD *)(v5 + 36) = 0;
  *(_DWORD *)(v5 + 40) = 0;
  *(_DWORD *)(v5 + 44) = 0;
  *(_DWORD *)(v5 + 20) = 1065353216;
  *(_DWORD *)(v5 + 28) = 1065353216;
  return 1065353216;
}

