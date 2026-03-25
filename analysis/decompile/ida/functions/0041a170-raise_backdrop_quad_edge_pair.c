/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: raise_backdrop_quad_edge_pair @ 0x41a170 */
/* selector: raise_backdrop_quad_edge_pair */

// Raises one of the two adjacent backdrop-quad edge pairs by 0.5 units using the small orientation tables consumed by the `Objects/Univers` variants.
float *__cdecl sub_41A170(int a1, int a2)
{
  int v2; // ecx
  float *result; // eax

  v2 = *(_DWORD *)(a2 + 56);
  if ( a1 > 0 || (result = (float *)(v2 + 12 * dword_4A3C40 + 4), *result = *result + 0.5, a1 >= 0) )
  {
    result = (float *)(v2 + 12 * dword_4A3C44 + 4);
    *result = *result + 0.5;
  }
  return result;
}

