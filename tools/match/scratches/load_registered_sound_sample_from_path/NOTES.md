# load_registered_sound_sample_from_path @ 0x449920

Registers one filesystem-backed sound sample through the BASS sample loader.

- Focused Wibo result: 2026-06-18, 100.00%, 20/20 instructions, masked
  operands 4 ok.
- Calls `g_bass_sample_load` with `from_memory = 0`.
- Stores the resulting handle in `g_registered_sound_sample_handles[sample_id]`.
- Calls the stripped debug-report stub with `Bass Sample Load Fail %s\n` and the
  source path on load failure.

## 2026-07-16 handle-table owner closure

`register_sound_sample` supplies the `RSHELL_SOUND_MAX`-bounded id to both
sample loaders, and every playback/stop consumer indexes the same handle base.
The resulting owner is exactly `int[256]` (0x400 bytes) at `0x7537e0`. The next
word at `0x753be0` has no code or data references and remains unclaimed; the
independent `BASS_ChannelStop` pointer begins at `0x753be4`. This rejects IDA's
old inferred `int[257]` type without inventing ownership for the padding word.
