# `update_input_controller_pointer_region` recovery notes

Target: `update_input_controller_pointer_region @ 0x4321c0` (`cdecl`, 466 bytes, 134 instructions).

The routine installs a screen rectangle for an input slot, updates the OS cursor hide flag, optionally clamps/warps the mouse back into that rectangle, and converts the screen position into the game's 640x480 authored pointer space. It then records the pointer pressure/value, ORs the three pointer button lanes into the slot button word, and clamps authored coordinates to `x=[1,632]`, `y=[1,472]`.

## Source-shape findings

- The slot state is the shared two-entry `InputControllerSlot` owner: slot 1 is
  `0x38` bytes after slot 0, and the native `(slot * 7) << 3` expression is the
  array's byte stride rather than a collection of unrelated lane globals.
- Keeping the clamp as "choose a float, then store it" recovers the native x87
  tail. The simpler source that only stores on out-of-range paths left a
  masked operand mismatch and scored lower.
- Native keeps `slot` in `edi`, mutable `x` in `esi`, and mutable `y` in `ebx`.
  Those roles fall out exactly when the sixth and seventh parameters are
  modified directly rather than copied into shadow locals.

## Rejected trials

- A plain `slot * 14` array-index spelling scored 21.48% and kept the slot live too long.
- Computing an explicit `inside_region` boolean before storing the rectangle regressed to 48.38%; VC6 materialized the boolean and changed the top block.
- `register` hints for the slot and coordinate locals were codegen-neutral and were not retained.

## 2026-06-21 rectangle-store order

Moving the local `x`/`y` copies after the rectangle stores improves focused Wibo
from 53.09% to 57.14%, with the exact prefix moving from 0/134 to 4/134 and the
same 26 clean masked operands. This recovers native's initial left/top/bottom
argument load order before the saved-register block while preserving the
existing clamp and pointer-space conversion semantics.

Follow-up variants that introduced a durable `slot_index`, declared `y` before
`x`, changed the click-call expressions, or nudged the in-range float clamp
stores with `+ 0.0f` were all codegen-neutral at 57.14%. The remaining early
residual is still the saved-register owner rotation for `screen_x`, `screen_y`,
and `slot`.

## 2026-07-13 parameter and slot ownership closure

- The native routine mutates its sixth and seventh parameters directly while
  clamping an out-of-region pointer. The old `screen_x`/`screen_y` parameters
  plus shadow `x`/`y` locals obscured that ownership and caused VC6 to rotate
  all three saved-register roles.
- Naming the mutable parameters `x` and `y` removes the false shadow lifetime
  and recovers the entire native entry, clamp/warp, coordinate-conversion,
  button, and X-clamp sequence. Focused Wibo moves from 57.14% (`139/134`,
  prefix 4) to 98.51% (`134/134`, prefix 131), with all 30 masked operands
  clean.
- Direct `g_input_controller_slots[slot]` field access is codegen-equivalent
  to the former scratch-local lane pointers and makes the recovered 0x38-byte
  owner explicit. A retained pointer to the whole record changed x87 lifetime
  and regressed to 68.16%, so the direct array-member form is retained.
- The only residual is the final in-range Y self-store: native emits
  `fld`/`fstp`, while VC6 emits a bit-preserving integer load/store for the
  equivalent recovered source. A `double` temporary regressed to 94.81%, and
  no-op arithmetic or artificial volatility is not retained.

## 2026-07-14 pointer-region sidecar ownership

The top, bottom, left, and right region arrays now use
`INPUT_CONTROLLER_SLOT_COUNT` rather than four independent literal extents.
Binary Ninja finds exactly two consumers for every array: this routine writes
the selected rectangle, and exact `set_input_controller_pointer_authored_xy`
reads the same slot to reverse-map authored coordinates. Both index the paired
`g_input_controller_slots` owner with that slot, independently proving that
all four arrays are two-entry sidecars rather than unrelated globals.
