/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_array_with_constructor @ 0x401000 */
/* selector: initialize_array_with_constructor */

// Walks `count` entries from `base` using the supplied byte stride and calls the provided constructor/helper on each slot; shared by game-runtime, enemy-manager, and parcel-bucket pool setup.
void __stdcall initialize_array_with_constructor(
        void *base,
        int32_t stride,
        int32_t count,
        void *(__thiscall *constructor)(void *slot))
{
  int32_t v5; // edi

  if ( count - 1 >= 0 )
  {
    v5 = count;
    do
    {
      constructor(base);
      base = (char *)base + stride;
      --v5;
    }
    while ( v5 );
  }
}
