/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: free_tracked_memory @ 0x431bf0 */
/* selector: free_tracked_memory */

// Validates a guarded tracked allocation, removes its size from the global memory tally, frees the backing block, and drops the pointer from the tracked-allocation stack.
int __cdecl sub_431BF0(int a1)
{
  _BYTE *v1; // esi
  int v2; // eax

  v1 = (_BYTE *)(a1 - 4);
  v2 = get_tracked_allocation_size((int *)&MEMORY[0x5108C0], a1 - 4);
  MEMORY[0x5108B4] -= v2;
  if ( *(_BYTE *)(a1 - 4) != 0xDE
    || v1[1] != 0xAD
    || v1[2] != 0xBA
    || v1[3] != 0xBE
    || v1[v2 - 4] != 0xDE
    || v1[v2 - 3] != 0xAD
    || v1[v2 - 2] != 0xBA
    || v1[v2 - 1] != 0xBE )
  {
    report_errorf(aMemoryCorrupti);
  }
  free(v1);
  return pop_tracked_allocation((int *)&MEMORY[0x5108C0], (int)v1);
}

