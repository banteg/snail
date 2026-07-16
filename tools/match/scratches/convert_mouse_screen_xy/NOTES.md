# convert_mouse_screen_xy @ 0x44c100

Exact scratch for the cursor-position to authored-coordinate bridge.

Recovered behavior:

- when windowed and the game cursor is captured, read the OS cursor directly
  into authored x/y and exit;
- otherwise read the OS cursor as a delta from the authored viewport center;
- uncaptured mode multiplies both axes by
  `resolve_uncaptured_cursor_sensitivity_scale(RuntimeConfig::steering_sensitivity[slot])`;
- captured/fullscreen delta mode applies only the screen-to-authored scales;
- failed `GetCursorPos` calls zero both outputs;
- after delta modes, recenter the OS cursor when the active window is the main
  game window.

This scratch uses the shared `MouseCursorState` view, the shared eight-byte
Win32 `Point` owner, and the same imported cursor APIs already used by
`click_mouse_screen`.

Focused Wibo result: 100.00%, 115/115 instructions, full prefix, with all 35
masked operands clean.

2026-06-21 zero-output store pass: writing the failure-path output zeros in
`y` then `x` order improves focused Wibo to 77.06%, still 116/115 instructions
with a 3/115 prefix and 32 clean masked operands. The swap nudges VC6's pointer
register choice in all three GetCursorPos failure blocks while preserving the
same observable zeroed outputs. The remaining residual is still branch distance
and API-call setup register ownership.

2026-06-21 follow-up zero-store audit: target-looking `x` then `y` zero stores,
raw integer zero stores, output pointer aliases, and an IDA-ordered captured
branch all failed to beat the retained `y` then `x` source. The `x` then `y`
forms preserve `eax == 0` locally but drop back to 74.46% overall; putting the
captured branch first reshapes the body to 53.28%. Keep the current
counterintuitive zero order until a broader branch-owner lead appears.

2026-07-11 root mouse-owner pass: the cRMouse-compatible receiver now comes
through `GameRoot::players[0].mouse_cursor` instead of a raw `Game +0x290`
cast. The focused result remains 77.06%, 116/115 instructions, prefix 3/115,
and 32 clean masked operands.

## 2026-07-13 ABI and point-owner closure

- `update_mouse` is the helper's only native caller and ignores its result. The
  target exits with unrelated incidental values in `eax`: the `y` pointer after
  a successful direct read, zero after a failed `GetCursorPos`, and Win32 API
  results along the recentering paths. Those values do not form a coherent
  return contract; the original helper is `void`, not the decompiler-inferred
  `BOOL`.
- Promoting the helper to `void` removes the synthetic `xor eax, eax` needed by
  the former false-return path and restores the native pointer-register choices
  and every downstream branch displacement. The already exact `update_mouse`
  caller remains 100.00% after adopting the shared void declaration.
- Failed cursor reads use the natural chained clear `*y = *x = 0.0f`. Its
  right-associative writes produce the native x-then-y stores without a dummy
  local or volatile lifetime.
- The scratch-local cursor pair is the SDK-compatible eight-byte Win32 `Point`
  record. It now lives in `win32_window_state.h`, has an explicit size proof,
  and is mirrored in both decompiler type headers.
- The `Point` type was previewed, applied, and read back at size `0x8` in the
  live Binary Ninja database. Binary Ninja rejected the live void-prototype
  mutation during verification and rolled it back, so the replay scripts carry
  the recovered ABI without claiming the live prototype changed.

Final focused Wibo is exact: 100.00% (`115/115`, full prefix), with all 35
masked operands resolved and equal. No register hints, volatile state, dummy
control flow, or flag changes are used.

2026-07-16 authored-view ownership: captured and uncaptured conversion now
borrow the canonical logical viewport pair rather than redeclaring two globals.
This preserves the exact 115/115 result and all 35 clean operands.
