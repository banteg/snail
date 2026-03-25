/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: free_tracked_allocations_to_mark @ 0x431c70 */
/* selector: free_tracked_allocations_to_mark */

// Frees tracked allocations back down to the current saved stack mark, as used by the main loop to unwind one temporary allocation scope.
int sub_431C70()
{
  int result; // eax

  for ( result = MEMORY[0x5108C0][0]; MEMORY[0x5108C0][0] > MEMORY[0x5108C4]; result = MEMORY[0x5108C0][0] )
    free_tracked_memory(MEMORY[0x5108C0][3 * result] + 4);
  return result;
}

