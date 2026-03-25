/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_object_vertices @ 0x42f790 */
/* selector: copy_object_vertices */

int __thiscall sub_42F790(unsigned int *this)
{
  __int64 v1; // rax
  _DWORD *v2; // esi
  _DWORD *v3; // edi

  v1 = *(this + 11);
  if ( (int)v1 > 0 )
  {
    LODWORD(v1) = 0;
    do
    {
      v2 = (_DWORD *)(*(this + 14) + v1);
      v3 = (_DWORD *)(v1 + *(this + 15));
      ++HIDWORD(v1);
      LODWORD(v1) = v1 + 12;
      *v3 = *v2;
      v3[1] = v2[1];
      v3[2] = v2[2];
    }
    while ( SHIDWORD(v1) < (int)*(this + 11) );
  }
  return v1;
}

