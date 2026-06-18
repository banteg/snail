# load_registered_sound_sample_from_bytes @ 0x449960

Registers one archive-backed sound sample through the BASS sample loader.

- Focused Wibo result: 2026-06-18, 88.89%, 18/18 instructions, prefix 13/18,
  masked operands 4 ok.
- Calls `g_bass_sample_load` with `from_memory = 1`.
- Uses the caller-provided byte count from the archive read.
- Stores the resulting handle in `g_registered_sound_sample_handles[sample_id]`.
- Failure path uses the native `***ERROR:Bass Sample Load Memory Fail\n` string.

Current status: near-match. The only remaining difference is stack cleanup after
the stripped one-argument debug stub: native emits `pop ecx`; this scratch emits
the equivalent `add esp, 0x4`.
