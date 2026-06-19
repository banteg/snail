# initialize_slalombig_path_template_pair

Honest starter scratch for `initialize_slalombig_path_template_pair @ 0x4221f0`.

Recovered from the IDA/Binja decompiles and the constructor callsite in
`initialize_game_assets_and_world`: the native cleanup is `ret 0x18`, so the
scratch keeps six explicit arguments after `this`.

The implementation initializes the `SLALOMBIG` path-template record, allocates
primary/secondary samples, builds the four straight lead-in and lead-out nodes,
fills the sinusoidal interior slalom body, derives per-sample orientation and
segment deltas, emits the strip mesh, and calls `finalize_path_template`.

Residuals are expected. The scratch uses small semantic helpers for the repeated
sample/orientation/mesh idioms instead of attempting instruction scheduling.
