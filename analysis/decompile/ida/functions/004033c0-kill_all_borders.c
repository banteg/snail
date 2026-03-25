/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_all_borders @ 0x4033c0 */
/* selector: kill_all_borders */

int __thiscall sub_4033C0(int *this)
{
  int *v1; // ecx
  int v2; // edx
  int result; // eax

  v1 = this + 521;
  v2 = 150;
  do
  {
    result = *v1;
    if ( *v1 )
    {
      if ( (result & 0x10000400) == 0 )
      {
        LOBYTE(result) = result & 1;
        BYTE1(result) |= 2u;
        *v1 = result;
      }
    }
    v1 += 457;
    --v2;
  }
  while ( v2 );
  return result;
}

