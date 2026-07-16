/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_tracked_allocation_mark @ 0x431cb0 */
/* selector: set_tracked_allocation_mark */

// Windows RShellMemoryBookmark(): saves the current tracked-allocation stack depth as the active unwind mark for a later `free_tracked_allocations_to_mark` call.
void __cdecl set_tracked_allocation_mark()
{
  g_tracked_allocation_stack.bookmark_depth = g_tracked_allocation_stack.depth;
}
