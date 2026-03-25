/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: recycle_bod_to_free_list @ 0x447290 */
/* selector: recycle_bod_to_free_list */

// Unlinks one active BOD from its current list membership and moves it back onto the shared free-list head, erroring if the source node is not currently marked as live-list owned.
int __thiscall sub_447290(_DWORD *this, _DWORD *a2)
{
  int result; // eax
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // ecx

  result = (int)a2;
  v3 = a2[1];
  if ( (v3 & 0x200) == 0 )
    return report_errorf(aListRemove);
  if ( (v3 & 0x40) != 0 )
    return report_errorf(aListRemoveNext);
  v4 = a2[3];
  if ( v4 )
    *(_DWORD *)(v4 + 8) = a2[2];
  v5 = a2[2];
  if ( v5 )
    *(_DWORD *)(v5 + 12) = a2[3];
  else
    *(this + 1) = a2[3];
  a2[3] = *(this + 2);
  *(this + 2) = a2;
  v6 = a2[1];
  BYTE1(v6) &= ~2u;
  a2[1] = v6;
  return result;
}

