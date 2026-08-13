# Exact match

`initialize_click_start_controller_runtime` @ 0x408670 constructs the
exact 0xac-byte authored `cRClickStart` and installs callback
table `data_497348`.
Reading that table in Binary Ninja shows its first entry is
`update_click_start`, so this is the runtime constructor for the controller,
not the later gameplay setup helper `initialize_click_start` @ 0x442170.

Android and iOS retain the cRClickStart vtable and `Init`/`AI` siblings. The
Windows constructor is exact at 7/7 instructions with two clean masked
operands; its typed return is the constructed `cRClickStart*`.

## 2026-07-17 analysis ownership closure

The shared Binary Ninja replay now preserves this exact constructor ABI and
the `initialize_click_start` / `update_click_start` lifecycle ABIs together.
That retires the decompiler-only `ClickStartController` and
`ClickStartPlayer` views in favor of the exact 0xac-byte `ClickStart` and its
borrowed `Player* owner_player`. The constructor remains 7/7 exact; no matcher
source or operand mask changed.

## 2026-08-09 primary cRClickStart ownership

The matcher now emits the exact constructor as `cRClickStart::cRClickStart()`
with `??0cRClickStart@@QAE@XZ`. Live Windows xrefs give the constructor one
caller at `0x408290`, where the child is constructed inline at
`cRSubGoldy +0xa0`; its installed table at `0x497348` points to the exact
`cRClickStart::AI()` leaf. `ClickStart` remains only a matcher compatibility
typedef.
The constructor stays exact at 7/7 instructions with both operands clean.

## 2026-08-13 canonical analysis owner

Both decompilers now retire the generic `ClickStart` shell after exact 0xac-byte
layout equivalence. The focused replay guards the `Player +0xa0` embed between
`ghost_sprite_b` and `row_event_cutscene_started` before applying the canonical
constructor ABI; matcher source and operands remain unchanged.
