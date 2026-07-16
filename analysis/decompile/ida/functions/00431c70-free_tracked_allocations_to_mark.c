/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: free_tracked_allocations_to_mark @ 0x431c70 */
/* selector: free_tracked_allocations_to_mark */

// Frees tracked allocations back down to the current saved stack mark, as used by the main loop to unwind one temporary allocation scope.
void __cdecl free_tracked_allocations_to_mark()
{
  int32_t i; // eax

  for ( i = g_tracked_allocation_stack.depth;
        g_tracked_allocation_stack.depth > g_tracked_allocation_stack.bookmark_depth;
        i = g_tracked_allocation_stack.depth )
  {
    free_tracked_memory((void *)(*(&g_tracked_allocation_stack.depth + 3 * i) + 4));
  }
}
