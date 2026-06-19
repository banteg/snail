# `initialize_audio_subsystem` recovery notes

Target: `initialize_audio_subsystem @ 0x407a10` (`cdecl`).

The retained source models the hidden BASS window bootstrap:

- fills a stack `WNDCLASSA` with `bass_audio_window_proc` (`sub_4079e0`) as the
  window procedure;
- registers the `"BASS"` class;
- creates the hidden window with the shared blank text buffer;
- initializes `g_audio_backend` using the hidden window handle;
- applies saved sample and stream volume configuration.

The manifest range currently runs through the helper at `0x407b00`, so
`scratch.conf` pins `END=0x407af6` to measure only this function body. With
that endpoint, the body is instruction-exact: 73 target instructions and 73
candidate instructions.

The reference manifest now names the real startup/window references used here:
`g_application_instance` (`data_4dfad8`), `g_bass_window` (`data_4dfaf8`),
`bass_audio_window_proc` (`sub_4079e0`), and
`shutdown_bass_audio_window` (`sub_407b00`). The masked operand audit is clean:
23 resolved operands, no unresolved operands, and no mismatches.
