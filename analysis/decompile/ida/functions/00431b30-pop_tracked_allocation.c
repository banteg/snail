/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pop_tracked_allocation @ 0x431b30 */
/* selector: pop_tracked_allocation */

// Removes one pointer from the global tracked-allocation stack, preferring the top-of-stack fast path and falling back to a linear search when the free order differs.
int32_t __thiscall pop_tracked_allocation(TrackedAllocationStack *stack, void *pointer)
{
  int32_t result; // eax
  int32_t v3; // edx
  TrackedAllocationRecord *records; // ecx

  result = stack->depth - 1;
  stack->depth = result;
  if ( stack->records[result].pointer != pointer )
  {
    v3 = 0;
    if ( result > 0 )
    {
      records = stack->records;
      do
      {
        if ( records->pointer == pointer )
          break;
        ++v3;
        ++records;
      }
      while ( v3 < result );
    }
  }
  return result;
}
