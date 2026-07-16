# find_registered_sound_sample_id_by_name @ 0x432fc0

Small registered-sample table lookup helper between `register_sound_sample` and
`load_level_definition_file`.

- Scans `g_registered_sound_sample_names` at `data_5088b0` using the count at
  `data_5108b0`.
- Each stored sample path/name entry is a 0x80-byte slot written by
  `register_sound_sample`.
- Uses `find_case_insensitive_substring(requested, registered_entry)`, so the
  level `Sample="..."` payload can name a suffix or substring of the stored
  sample path.
- Returns the sample id / table index on match.
- Reports `Cannot Find Sample %s` and returns `0` on miss.
- Focused Wibo result: 2026-06-18, 100% exact, 34/34 candidate/target
  instructions, prefix 34/34, masked operands 6 ok.
- Source shape matters: the native loop is an index-based `for` over
  `g_registered_sound_sample_names[sample_id]`. VC6 lowers that to `esi` as the
  sample id and `edi += 0x80` as the table cursor; pointer-first `do`/`while`
  spellings preserve semantics but rotate the loop and allocate the registers
  backwards.

Static callsite evidence ties the helper to `load_level_definition_file`, where
it resolves per-segment `Sample="..."` message audio.

## 2026-07-16 authored owner closure

iOS and Android retain this ABI as `RShellFindSample(char*)` in `RShell.o`.
Android independently preserves the same 128-byte slot stride, scalar-count loop
bound, error path, and zero-on-miss contract. Its two ABI builds export
`RShellSoundName` at exactly 0x8000 bytes and `RShellSoundCount` at four bytes,
confirming the Windows lookup borrows a 256-by-128 matrix plus a separate scalar
rather than a recovered aggregate struct.
