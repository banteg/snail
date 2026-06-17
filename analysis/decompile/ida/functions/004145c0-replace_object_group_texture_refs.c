/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: replace_object_group_texture_refs @ 0x4145c0 */
/* selector: replace_object_group_texture_refs */

// Rewrites one built object's grouped-render texture-ref table from an old texture reference to a replacement after grouped buffers have been built.
void __cdecl sub_4145C0(_DWORD *a1, int a2, int a3)
{
  int i; // ecx
  int v4; // eax
  int v5; // ebx
  _DWORD *v6; // eax

  if ( (a1[4] & 0x80000) != 0 )
  {
    for ( i = 0; i < a1[25]; ++i )
    {
      v4 = a1[52];
      v5 = *(_DWORD *)(v4 + 4 * i);
      v6 = (_DWORD *)(v4 + 4 * i);
      if ( v5 == a3 )
        *v6 = a2;
    }
  }
}

