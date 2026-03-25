/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_corner_quad @ 0x41a290 */
/* selector: initialize_backdrop_corner_quad */

// Builds one sliced backdrop quad and offsets the selected edge pair by 0.3 units using the four-entry corner selector table.
void __cdecl sub_41A290(int a1, int *a2, _BYTE *a3)
{
  int v3; // edx
  float *v4; // ecx
  float *v5; // ecx
  int v6; // [esp+10h] [ebp+Ch]

  initialize_backdrop_slice_quad(a2, a3, 0.0);
  v3 = a2[14];
  v4 = (float *)(v3 + 12 * dword_4A3CE0[a1]);
  if ( *v4 >= 0.0 )
    v6 = *v4 != 0.0;
  else
    v6 = -1;
  *v4 = (double)v6 * 0.30000001;
  v5 = (float *)(v3 + 12 * dword_4A3CE0[a1] + 8);
  if ( *v5 >= 0.0 )
    *v5 = (double)(*v5 != 0.0) * 0.30000001;
  else
    *v5 = (double)-1 * 0.30000001;
}

