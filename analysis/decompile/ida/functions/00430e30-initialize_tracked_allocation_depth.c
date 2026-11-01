/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_tracked_allocation_depth @ 0x430e30 */
/* selector: initialize_tracked_allocation_depth */

// Initializes the shared tracked-allocation stack depth to zero before archive and shell startup begin using the guarded allocation helpers.
void initialize_tracked_allocation_depth()
{
  g_tracked_allocation_stack.depth = 0;
}
