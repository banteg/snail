/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_tracked_allocation_size @ 0x431ab0 */
/* selector: get_tracked_allocation_size */

// Looks up one tracked allocation inside the global allocation stack and returns the guarded byte size recorded for that pointer.
int __thiscall sub_431AB0(int *this, int a2)
{
  int v2; // eax
  _DWORD *v3; // edx

  v2 = 0;
  if ( *this <= 0 )
  {
LABEL_5:
    report_errorf(aCannotFindMemo);
    return 0;
  }
  else
  {
    v3 = this + 3;
    while ( *v3 != a2 )
    {
      ++v2;
      v3 += 3;
      if ( v2 >= *this )
        goto LABEL_5;
    }
    return *(this + 3 * v2 + 4);
  }
}

