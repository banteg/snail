# Exact match

`initialize_array_with_constructor` @ 0x401000 is the shared constructor-loop
helper used by runtime pools and parcel bucket pools. It walks `count` slots
from `base`, advances by byte `stride`, and invokes the supplied thiscall
constructor callback on each slot.

The scratch intentionally models the callback as a single-inheritance MSVC
member-function pointer. That is the same ABI shape used by existing matched
runtime-pool callsites.

The exact count guard is `if (--count < 0) return;`, which lets VC6 branch on
the flags from `dec eax`. Spelling the loop as `count > 0` emitted a separate
`test eax, eax` and missed the native prologue.

2026-06-20 ABI note: the `RuntimeSlot` callback declaration now lives in
`tools/match/include/runtime_slot.h` and returns `RuntimeSlot*`. This keeps the
exact helper body unchanged while aligning the callers with the no-op
constructor's proven `return this` shape.
