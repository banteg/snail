/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_object_color @ 0x4141d0 */
/* selector: set_object_color */

// Packs one object RGBA tint and, when grouped vertex buffers exist, rewrites the per-vertex diffuse colour lane so the next object draw uses that colour. Cross-port Android symbols match this helper's role to `G0SetColour(tColourSmall*)`.
ColorBGRA8 *set_object_color(_DWORD *a1, ...)
{
  ColorBGRA8 *result; // eax
  int v2; // eax
  int v3; // ecx
  ColorBGRA8 v4; // [esp+14h] [ebp-8h] BYREF
  int v5; // [esp+18h] [ebp-4h] BYREF
  Color4f v6; // [esp+24h] [ebp+8h] BYREF

  Iostream_init::Iostream_init((#93 *)&v4);
  result = pack_color_rgba_u8(&v4, &v6);
  if ( (a1[4] & 0x80000) != 0 )
  {
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD))(**(_DWORD **)(a1[48] + 8) + 44))(
      *(_DWORD *)(a1[48] + 8),
      0,
      24 * LODWORD(flt_4DFAFC[36272]),
      &v5,
      0);
    v2 = 0;
    if ( (int)a1[49] > 0 )
    {
      v3 = 0;
      do
      {
        ++v2;
        *(ColorBGRA8 *)(v3 + v5 + 12) = v4;
        v3 += 24;
      }
      while ( v2 < a1[49] );
    }
    return (ColorBGRA8 *)(*(_BYTE *(__stdcall **)(_DWORD))(**(_DWORD **)(a1[48] + 8) + 48))(*(_DWORD *)(a1[48] + 8));
  }
  return result;
}

