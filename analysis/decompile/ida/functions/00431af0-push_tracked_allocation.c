/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: push_tracked_allocation @ 0x431af0 */
/* selector: push_tracked_allocation */

// Appends one `(size, pointer)` record to the global tracked-allocation stack used by the guarded resource allocator.
int __thiscall sub_431AF0(int *this, int a2, int a3, int a4)
{
  int result; // eax

  *(this + 3 * *this + 4) = a4;
  *(this + 3 * *this + 3) = a3;
  result = *this + 1;
  *this = result;
  if ( result > 15000 )
    return report_errorf(aMemoryStackFul);
  return result;
}

