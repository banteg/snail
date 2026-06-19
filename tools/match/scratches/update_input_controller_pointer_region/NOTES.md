# `update_input_controller_pointer_region` recovery notes

Target: `update_input_controller_pointer_region @ 0x4321c0` (`cdecl`, 466 bytes, 134 instructions).

The routine installs a screen rectangle for an input slot, updates the OS cursor hide flag, optionally clamps/warps the mouse back into that rectangle, and converts the screen position into the game's 640x480 authored pointer space. It then records the pointer pressure/value, ORs the three pointer button lanes into the slot button word, and clamps authored coordinates to `x=[1,632]`, `y=[1,472]`.

## Source-shape findings

- The slot state uses the same lane layout as the other input-controller helpers: slot 1 is `0x38` bytes after slot 0, so the scratch computes `(slot * 7) << 3` and accesses the lane globals through byte offsets.
- Keeping the clamp as "choose a float, then store it" recovers the native x87 tail. The simpler source that only stores on out-of-range paths left a masked operand mismatch and scored lower.
- The first native block keeps `slot`, `screen_x`, and `screen_y` in different saved registers from this scratch. The semantics are recovered, but the register-owner swap shifts the early labels and keeps the common prefix at zero.

## Rejected trials

- A plain `slot * 14` array-index spelling scored 21.48% and kept the slot live too long.
- Computing an explicit `inside_region` boolean before storing the rectangle regressed to 48.38%; VC6 materialized the boolean and changed the top block.
- `register` hints for the slot and coordinate locals were codegen-neutral and were not retained.
