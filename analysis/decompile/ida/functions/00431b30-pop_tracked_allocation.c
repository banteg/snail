/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pop_tracked_allocation @ 0x431b30 */
/* selector: pop_tracked_allocation */

// Removes one pointer from the global tracked-allocation stack, preferring the top-of-stack fast path and falling back to a linear search when the free order differs.
int __thiscall sub_431B30(int *this, int a2)
{
  int result; // eax
  int v3; // edx
  _DWORD *v4; // ecx

  result = *this - 1;
  *this = result;
  if ( *(this + 3 * result + 3) != a2 )
  {
    v3 = 0;
    if ( result > 0 )
    {
      v4 = this + 3;
      do
      {
        if ( *v4 == a2 )
          break;
        ++v3;
        v4 += 3;
      }
      while ( v3 < result );
    }
  }
  return result;
}

