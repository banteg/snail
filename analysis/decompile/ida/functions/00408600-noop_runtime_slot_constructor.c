/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: noop_runtime_slot_constructor @ 0x408600 */
/* selector: noop_runtime_slot_constructor */

// No-op thiscall constructor callback (`mov eax, ecx; ret`) shared by POD-like runtime slot arrays, parcel buckets, and opaque Snail presentation-channel subobjects. The body proves trivial construction only; it does not establish an iostream owner.
void *__thiscall noop_runtime_slot_constructor(void *slot)
{
  return slot;
}
