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

Direct calls also construct opaque subobjects inside the exact Snail
presentation constructor: weapon channels call it at `+0xc0`, while the
jetpack channel calls it at `+0x80` and `+0xc0`. Those calls prove only trivial
construction, not the historical `IostreamInit` ownership guess.

## 2026-07-27 folded Player-child owners

Two other direct calls have complete, independently recovered receivers. In the
exact Windows `cRSubGame` constructor, `0x40829b` receives
`Player::cameraman +0x200` and `0x4082a6` receives
`Player::follow_state +0x384`. The shared no-op body is therefore also the
folded Windows constructor body for those two owners.

The mobile layouts corroborate the authored identities without supplying
Windows offsets. Android `cRSubGoldy::Init(int)` passes its complete `+0x1e8`
child to `cRCameraman::Init()`. Android and iOS `cRSubGoldy::AI()` both pass
their complete `+0x374` child to `cRPathFollowGoldy::{Init,Traverse}`. Windows
uses wider earlier fields, but the same owner order and method families land at
the exact typed `+0x200/+0x384` fields already proved by its own consumers.

The matcher now invokes the two folded calls through `Cameraman` and
`FollowState` rather than casting either complete child to `RuntimeSlot`.
Array callbacks and opaque presentation children remain neutral; no mobile
offset or unrelated no-op constructor identity is transferred.
