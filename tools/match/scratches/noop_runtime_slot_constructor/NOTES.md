# Exact match

`noop_runtime_slot_constructor` @ 0x408600 is the shared no-op thiscall member
constructor callback used by `initialize_array_with_constructor` for POD-like
runtime slot arrays.

The target body is just `mov eax, ecx; ret`. This confirms the callback returns
the input `this` pointer and performs no slot initialization. The scratch is
spelled as a member while keeping the slot type neutral because callers use the
same callback for several distinct array shapes. Keep this distinct from the
parcel bucket callsites: those buckets merely reuse the shared constructor
callback.
