# update_cheat

`update_cheat` consumes text-input key presses, normalizes ASCII lowercase to
uppercase, shifts the eight-byte rolling cheat buffer, and enables the native
`NEWTON`, `AUTUMN`, and `SHEEP` flags.

Current result: 67.35%, 46/52 candidate/target instructions, seven clean
masked operands. The recovered behavior is:

- consume `read_pressed_text_input_key_code()`;
- convert `a..z` to uppercase by subtracting `0x20`;
- ignore non-letters;
- shift the eight-byte recent-text buffer at `CheatState +0x08..+0x0f`;
- set flag bits `1`, `2`, and `4` for `NEWTON`, `AUTUMN`, and `SHEEP`.

Residual:

- Native preserves the shift-loop sentinel as `edx = -8 - this`, uses
  `bl` for the copied byte, and keeps `edi` as the loop test temporary. The
  clean pointer-difference source simplifies this to `edx = cursor - this - 8`
  and uses `dl` for the copied byte.
- The final `SHEEP` flag update compiles as `or dword [this], 4`; native uses
  the same load/`or al, 4`/store shape as the earlier two flag updates.
- The IDA-style pointer expression and separated `-8` local were tested; both
  were neutral or regressed register ownership. Keep this as an honest partial
  until there is stronger source-shape evidence.
