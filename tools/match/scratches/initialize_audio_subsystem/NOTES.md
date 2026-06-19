# `initialize_audio_subsystem` recovery notes

Target: `initialize_audio_subsystem @ 0x407a10` (`cdecl`).

The retained source models the hidden BASS window bootstrap:

- fills a stack `WNDCLASSA` with `sub_4079e0` as the window procedure;
- registers the `"BASS"` class;
- creates the hidden window with the shared blank text buffer;
- initializes `g_audio_backend` using the hidden window handle;
- applies saved sample and stream volume configuration.

The manifest range currently runs through the helper at `0x407b00`, so
`scratch.conf` pins `END=0x407af6` to measure only this function body. With
that endpoint, the body is instruction-exact: 73 target instructions and 73
candidate instructions.

Remaining masked-audit noise is symbol naming, not code shape:
`data_4dfad8` is still normalized on the target side as
`g_mouse_wheel_delta+0x8`, and the hidden window handle / cleanup helper are
raw image references in the target. The scratch keeps semantic names instead
of adding aliases purely for the matcher.
