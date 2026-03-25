/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_tracked_memory @ 0x431b60 */
/* selector: allocate_tracked_memory */

// Allocates a zeroed guarded heap block, records it in the global tracked-allocation stack, writes the front and back `DE AD BA BE` sentinels, and returns the caller-visible payload pointer.
_BYTE *__cdecl allocate_tracked_memory(int a1, int a2)
{
  unsigned int v2; // ebx
  _BYTE *v3; // esi

  v2 = a1 + 8;
  v3 = (_BYTE *)malloc(a1 + 8);
  if ( !v3 )
    report_errorf(aNotEnoughMemor);
  push_tracked_allocation((int *)&flt_4DFAFC[50033], a2, (int)v3, v2);
  memset(v3, 0, v2);
  *v3 = -34;
  v3[1] = -83;
  v3[2] = -70;
  v3[3] = -66;
  v3[v2 - 4] = -34;
  v3[v2 - 3] = -83;
  v3[v2 - 2] = -70;
  v3[v2 - 1] = -66;
  LODWORD(flt_4DFAFC[50030]) += v2;
  return v3 + 4;
}

