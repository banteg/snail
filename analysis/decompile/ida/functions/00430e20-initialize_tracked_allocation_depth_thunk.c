/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_tracked_allocation_depth_thunk @ 0x430e20 */
/* selector: initialize_tracked_allocation_depth_thunk */

// CRT constructor-table thunk that tail-forwards to the adjacent initializer for the tracked-allocation stack depth.
// attributes: thunk
void initialize_tracked_allocation_depth_thunk()
{
  initialize_tracked_allocation_depth();
}
