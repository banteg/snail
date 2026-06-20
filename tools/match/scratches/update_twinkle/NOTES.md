# `update_twinkle` notes

- Twinkle records are 0x30 bytes, matching `update_twinkle_manager`.
- The owner layout is scratch-local and only names observed offsets:
  `input_flags` at +0x1a0, position at +0x238/+0x23c, size at
  +0x248/+0x24c.
- The function is modeled as `void`; native exits leave state-dependent scratch
  registers in `eax`.
- 2026-06-20 ABI cleanup: the `Twinkle` record now lives in
  `include/twinkle.h` with the exact 0x30 layout, `void update_twinkle()`, and
  the member `draw_twinkle()` call shape needed by this scratch. Focused matcher
  stayed exact at 181/181 instructions with 48 clean masked operands.
