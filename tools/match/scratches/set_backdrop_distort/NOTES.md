# set_backdrop_distort @ 0x410c40

Current scratch: 50.70% (73 target insns, 69 candidate insns), clean masks.

Seeds the 8x8 backdrop distortion grid from the parsed landscape `Distort:`
scalar.

Recovered layout:

- `Backdrop::distort_cells[64]` starts at `+0x58`.
- each `BackdropDistortCell` has stride `0x18`.
- the helper writes `phase +0x00`, `phase_step +0x04`, `x_offset +0x08`, and
  `y_offset +0x0c`.
- `update_backdrop` writes the derived per-frame `current_x_offset +0x10` and
  `current_y_offset +0x14` terms from sine/cosine, and `render_backdrop`
  consumes those values as warped quad corner offsets.
- border cells (`row == 0`, `row == 7`, `column == 0`, or `column == 7`) are
  hard-zeroed.

Open source-shape issue: the clean float-stride spelling still lets VC6
strength-reduce the inner loop into a moving pointer cursor. Native keeps the
row index in `edi`, column in `esi`, zero in `edx`, and recomputes the
`(row + column) * 0x18` address inside the zero/random branches. Do not close
this with volatile or dummy helper calls; resume from a loop-shape or idiom
probe.

2026-06-21 direct-index retry: removing the `result`/`cell` pointer locals and
repeating the full indexed store expression is codegen-neutral at 50.70%. VC6
still strength-reduces to the moving pointer cursor, so direct source indexing
alone does not recover the native recomputed branch addresses.
