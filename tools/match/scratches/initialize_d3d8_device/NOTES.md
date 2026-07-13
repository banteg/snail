# `initialize_d3d8_device` recovery notes

Target: `initialize_d3d8_device @ 0x411730` (`thiscall`, `ret 0x4`).

The gameplay manifest's gap after this function reaches the next mapped
gameplay entry at `0x4119d0`, but BN shows `reset_direct3d_render_state` starts
at `0x4118b0` after six alignment NOPs. The scratch therefore sets
`END=0x4118aa`, the byte after the initializer's `ret 4`, and leaves the reset
helper as a real call target instead of measuring it as part of the initializer.

## Recovered behavior

- Calls the `Direct3DCreate8` import thunk with SDK version `0xdc` and stores
  the Direct3D object at renderer `+0xbb90`.
- On a null Direct3D object, calls `abort_startup_with_3d_error` and clears the
  initialized byte.
- Calls `GetAdapterDisplayMode(0, &mode)` and returns the abort result on
  failure after clearing the initialized byte.
- Builds the `D3DPresentParameters` block at `+0xbb98`, including:
  - display format from the fourth `D3DDisplayMode` field;
  - requested width/height from `+0xbca4/+0xbca8`;
  - multisample/depth-stencil fields from `+0xbcbc/+0xbcb8`;
  - main window handle from `g_main_window`;
  - fullscreen presentation interval from the function argument.
- Attempts `CreateDevice` with hardware vertex processing (`0x40`), then falls
  back to software vertex processing (`0x20`), reporting the selected path
  through the stripped debug-report helper.
- Calls `reset_direct3d_render_state`, then `query_direct3d_device_caps`, and
  sets the initialized byte.

2026-07-13 ownership pass: both renderer lifecycle calls are now typed as
`void`. Their apparent integer returns were merely the last callee's `EAX`
left live at `ret`; the sole bootstrap caller ignores `initialize_d3d8_device`
and it likewise ignores `query_direct3d_device_caps`. The corrected signatures
remain byte-identical.

## Current match

Focused matcher result: 86.79%, 106 candidate instructions versus 106 target
instructions, 38-instruction prefix, and 9 clean masked operands. There are no
unresolved or mismatched operands.

The first remaining mismatch is source scheduling around the presentation
parameter stores:

```text
target[38]    mov [esi+0xbbb4], eax
candidate[38] mov [esi+0xbbbc], ecx
```

The retained source keeps the clear field assignments. A trial with explicit
temporaries for `one`, depth format, window, width, height, and multisample
regressed to 64.76% by making VC6 allocate `ebx` as a live `one` value instead
of preserving it as the native zero register.

2026-06-21 present-store order pass: a bounded adjacent-swap sweep over the
independent `D3DPresentParameters` stores found that filling the device window
before the back-buffer format, then spelling height/width/multisample, recovers
the native call register ownership and improves focused Wibo from 86.79% to
97.17% with 106/106 instructions and 12 clean masked operands. Pure field-order
permutations cannot recover the final dimension/multisample scheduling: the
best tied spellings leave only one store-order region around the
width/height/multisample loads. Local `device_window` and dimension temporaries
were either codegen-neutral at 97.17% or regressed, so the retained change is
the minimal source-order spelling.

2026-06-21 full store-order sweep: exhaustively permuting the five independent
window/format/width/height/multisample assignments found one proof-grade source
order: `device_window`, `back_buffer_width`, `back_buffer_height`,
`back_buffer_format`, then `multisample_type`. This recovers the native
presentation-parameter store schedule and moves the scratch to `100.00%`,
`106/106`, with the same 12 clean masked operands.

## Added reference

`0x47bdf4` is now named `Direct3DCreate8`, the Direct3D 8 import thunk used by
the initializer.
