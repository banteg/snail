# Exact match

`initialize_click_start_controller_runtime` @ 0x408670 constructs the
exact 0xac-byte authored `ClickStart` (`cRClickStart`) and installs callback
table `data_497348`.
Reading that table in Binary Ninja shows its first entry is
`update_click_start`, so this is the runtime constructor for the controller,
not the later gameplay setup helper `initialize_click_start` @ 0x442170.

Android and iOS retain the cRClickStart vtable and `Init`/`AI` siblings. The
Windows constructor is exact at 7/7 instructions with two clean masked
operands; its typed return is the constructed `ClickStart*`.

## 2026-07-17 analysis ownership closure

The shared Binary Ninja replay now preserves this exact constructor ABI and
the `initialize_click_start` / `update_click_start` lifecycle ABIs together.
That retires the decompiler-only `ClickStartController` and
`ClickStartPlayer` views in favor of the exact 0xac-byte `ClickStart` and its
borrowed `Player* owner_player`. The constructor remains 7/7 exact; no matcher
source or operand mask changed.
