/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: activate_all_borders @ 0x403300 */
/* selector: activate_all_borders */

int *__thiscall sub_403300(int *this)
{
  int *result; // eax
  int v2; // edx
  int v3; // ecx
  int v4; // ecx

  result = this + 521;
  v2 = 150;
  do
  {
    v3 = *result;
    if ( *result >= 0 )
    {
      BYTE1(v3) &= ~0x80u;
      *result = v3;
    }
    v4 = *result;
    result += 457;
    --v2;
    *(result - 457) = v4 & 0x7FFFFFFF;
    *(result - 426) = *(result - 428);
    *(result - 425) = *(result - 428);
    *(result - 430) = 0;
  }
  while ( v2 );
  return result;
}

