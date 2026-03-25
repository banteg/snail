/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_array_with_constructor @ 0x401000 */
/* selector: initialize_array_with_constructor */

// Walks `count` entries from `base` using the supplied byte stride and calls the provided constructor/helper on each slot; shared by game-runtime, enemy-manager, and parcel-bucket pool setup.
int __stdcall sub_401000(int a1, int a2, int a3, int (__thiscall *a4)(int))
{
  int result; // eax
  int v6; // edi

  result = a3 - 1;
  if ( a3 - 1 >= 0 )
  {
    v6 = a3;
    do
    {
      result = a4(a1);
      a1 += a2;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

