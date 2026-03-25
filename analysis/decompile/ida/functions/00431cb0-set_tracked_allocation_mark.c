/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_tracked_allocation_mark @ 0x431cb0 */
/* selector: set_tracked_allocation_mark */

// Saves the current tracked-allocation stack depth as the active unwind mark for a later `free_tracked_allocations_to_mark` call.
int sub_431CB0()
{
  MEMORY[0x5108C4] = MEMORY[0x5108C0];
  return MEMORY[0x5108C0];
}

