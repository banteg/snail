/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: atan2_positive @ 0x44ca10 */
/* selector: atan2_positive */

// Computes a two-argument arctangent with the result wrapped into the positive full-turn range. Android symbols match this helper to `ATan(float, float)`.
double __cdecl sub_44CA10(float a1, float a2)
{
  double v2; // st7
  int v3; // ecx
  double result; // st7

  if ( a1 <= 0.0 )
  {
    a1 = -a1;
    v2 = a2;
    if ( a2 > 0.0 )
    {
      v3 = 3;
      goto LABEL_9;
    }
    v3 = 2;
  }
  else
  {
    v2 = a2;
    if ( a2 > 0.0 )
    {
      v3 = 0;
      goto LABEL_9;
    }
    v3 = 1;
  }
  v2 = -v2;
LABEL_9:
  if ( v2 == 0.0 )
    result = 1.5707964;
  else
    result = atan2(a1 / v2, 1.0);
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      return 3.1415927 - result;
    }
    else if ( v3 == 2 )
    {
      return result + 3.1415927;
    }
    else
    {
      return -result;
    }
  }
  return result;
}

