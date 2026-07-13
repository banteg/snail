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
