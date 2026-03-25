/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_add_text_number @ 0x401030 */
/* selector: border_add_text_number */

char __thiscall sub_401030(_BYTE *this, int a2)
{
  unsigned int v2; // eax
  _BYTE *i; // ecx
  int v4; // ebx
  char v5; // al
  int v6; // esi
  int v7; // eax
  char j; // [esp+4h] [ebp+4h]

  LOBYTE(v2) = *(this + 716);
  for ( i = this + 716; (_BYTE)v2; ++i )
    LOBYTE(v2) = i[1];
  v4 = a2;
  if ( a2 )
  {
    v5 = 0;
    v6 = 10000000;
    for ( j = 0; ; v5 = j )
    {
      if ( v5 && (v6 == 100 || v6 == 100000) )
        *i++ = 44;
      if ( v4 >= v6 || v5 )
        break;
LABEL_21:
      v4 %= v6;
      v2 = (unsigned int)((unsigned __int64)(1717986919LL * v6) >> 32) >> 31;
      v6 /= 10;
      if ( !v6 )
      {
        *i = 0;
        return v2;
      }
    }
    if ( v6 == 1 )
    {
      LOBYTE(v7) = v4;
    }
    else
    {
      v7 = v4 / v6;
      if ( !(v4 / v6) )
      {
        if ( !j )
          goto LABEL_21;
        *i = 48;
        goto LABEL_20;
      }
      j = 1;
    }
    *i = v7 + 48;
LABEL_20:
    ++i;
    goto LABEL_21;
  }
  *i = 48;
  i[1] = 0;
  return v2;
}

