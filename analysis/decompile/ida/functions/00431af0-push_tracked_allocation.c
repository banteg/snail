/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: push_tracked_allocation @ 0x431af0 */
/* selector: push_tracked_allocation */

// Appends one `(size, pointer)` record to the global tracked-allocation stack used by the guarded resource allocator.
void __thiscall push_tracked_allocation(
        TrackedAllocationStack *stack,
        char *label,
        void *pointer,
        int32_t guarded_size)
{
  int32_t v4; // eax

  stack->records[stack->depth].guarded_size = guarded_size;
  stack->records[stack->depth].pointer = pointer;
  v4 = stack->depth + 1;
  stack->depth = v4;
  if ( v4 > 15000 )
    report_errorf(aMemoryStackFul);
}
