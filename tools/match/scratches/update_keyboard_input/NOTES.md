# update_keyboard_input @ 0x44b870

Polls the keyboard DirectInput device, builds the slot-0 button mask and axes,
and clears both keyboard buffers on lost/unacquired device errors.

The source uses `if (GetDeviceState(...) < 0) { reacquire } else { map keys }`
because native lays out the reacquire block before the key-mapping block and
jumps forward on successful polling.

2026-07-16 caller-side ABI proof: the main loop pushes `g_main_window` before
this cdecl call and releases it in the shared three-poller stack cleanup. The
body does not consume the argument, so the exact implementation could not prove
the signature alone; adopting the proven `HWND` parameter leaves it 100.00%.

2026-07-16 state-owner closure: the poller now borrows the canonical keyboard
device and the fixed previous/current 256-key pair. Copy, clear, and
`GetDeviceState` sizes all derive from that owner. Focused output remains exact
at 199/199 instructions with all 34 operands clean.

2026-07-27 mobile owner confirmation: Android and iOS retain the authored
`KeyboardAI()` global and the same process-owned current/previous 256-byte
tables. Their platform bodies inject or clear mobile key events instead of
polling DirectInput, so the crosswalk transfers the owner and table lifetime
without changing the proven Windows ABI. The Windows flag immediates
`0x400000` and `0x800000` collide with mapped image addresses; guarded BN/IDA
numeric-operand overrides preserve them as unresolved `InputButtonFlag` bits
instead of inventing PE-header or sprite-manager ownership.
