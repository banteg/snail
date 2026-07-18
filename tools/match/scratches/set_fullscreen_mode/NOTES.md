# set_fullscreen_mode

Tiny cdecl wrapper at `0x414260`.

The tracked symbol extent needs `END=0x414270`; otherwise the default target
range flows into `direct3d_renderer_set_fullscreen_mode` and incorrectly shows
this wrapper as a 667-byte no-scratch function.

Recovered relationship:

- Loads `g_direct3d_renderer` as the receiver and forwards the fullscreen flag
  to `direct3d_renderer_set_fullscreen_mode`.

The wrapper and member are `void`; callers ignore the live `EAX` left by the
final Win32 call. Correcting the earlier inferred integer return remains exact.

2026-07-18 byte-valued fullscreen ABI:

- The member copies only `[esp+0xc].b` into `BL`; no caller-visible path reads
  the other three bytes of the stack slot. The wrapper merely forwards that
  slot, so its exact five-instruction body cannot distinguish `int` from the
  narrower authored parameter by itself.
- `game_startup_and_main_loop` closes the ambiguity: it loads only
  `g_runtime_config.fullscreen_enabled` into `DL` before pushing the argument.
  The wrapper and renderer member are therefore byte-valued (`char` in matcher
  sources, `uint8_t` in analysis types). Both exact scratches remain 100.00%.
