# load_registered_sound_sample_from_path @ 0x449920

Registers one filesystem-backed sound sample through the BASS sample loader.

- Focused Wibo result: 2026-06-18, 100.00%, 20/20 instructions, masked
  operands 4 ok.
- Calls `g_bass_sample_load` with `from_memory = 0`.
- Stores the resulting handle in `g_registered_sound_sample_handles[sample_id]`.
- Calls the stripped debug-report stub with `Bass Sample Load Fail %s\n` and the
  source path on load failure.
