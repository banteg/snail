/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_tracked_allocation_size @ 0x431ab0 */
/* selector: get_tracked_allocation_size */

// Looks up one tracked allocation inside the global allocation stack and returns the guarded byte size recorded for that pointer.
int32_t __thiscall get_tracked_allocation_size(TrackedAllocationStack *stack, void *pointer)
{
  int32_t v2; // eax
  TrackedAllocationRecord *records; // edx

  v2 = 0;
  if ( stack->depth <= 0 )
  {
LABEL_5:
    report_errorf(aCannotFindMemo);
    return 0;
  }
  else
  {
    records = stack->records;
    while ( records->pointer != pointer )
    {
      ++v2;
      ++records;
      if ( v2 >= stack->depth )
        goto LABEL_5;
    }
    return stack->records[v2].guarded_size;
  }
}
