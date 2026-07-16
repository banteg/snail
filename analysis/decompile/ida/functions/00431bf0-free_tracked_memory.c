/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: free_tracked_memory @ 0x431bf0 */
/* selector: free_tracked_memory */

// Windows RShellMemoryFree(void*): validates a guarded tracked allocation, removes its size from the global memory tally, frees the backing block, and drops the pointer from the tracked-allocation stack.
void __cdecl free_tracked_memory(void *pointer)
{
  char *v1; // esi
  int32_t tracked_allocation_size; // eax

  v1 = (char *)pointer - 4;
  tracked_allocation_size = get_tracked_allocation_size(&g_tracked_allocation_stack, (char *)pointer - 4);
  g_tracked_allocation_total_bytes -= tracked_allocation_size;
  if ( *((char *)pointer - 4) != -34
    || v1[1] != -83
    || v1[2] != -70
    || v1[3] != -66
    || v1[tracked_allocation_size - 4] != -34
    || v1[tracked_allocation_size - 3] != -83
    || v1[tracked_allocation_size - 2] != -70
    || v1[tracked_allocation_size - 1] != -66 )
  {
    report_errorf(aMemoryCorrupti);
  }
  free(v1);
  pop_tracked_allocation(&g_tracked_allocation_stack, v1);
}
