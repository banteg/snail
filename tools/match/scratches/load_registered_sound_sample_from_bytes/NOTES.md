# load_registered_sound_sample_from_bytes @ 0x449960

Registers one archive-backed sound sample through the BASS sample loader.

- Focused Wibo result: 2026-06-18, 88.89%, 18/18 instructions, prefix 13/18,
  masked operands 4 ok.
- Proof result: 2026-06-20, 100.00%, 18/18 instructions, prefix 18/18,
  masked operands 4 ok.
- Calls `g_bass_sample_load` with `from_memory = 1`.
- Uses the caller-provided byte count from the archive read.
- Stores the resulting handle in `g_registered_sound_sample_handles[sample_id]`.
- Failure path uses the native `***ERROR:Bass Sample Load Memory Fail\n` string.

Current status: proof-grade match. The backend method is a `void` surface:
callers ignore the result, and native leaves `eax` as the incidental result of
`g_bass_sample_load` or the stripped debug report call. Treating the method as
`int` forced the failure arm to be a returned expression and made VC6 clean the
single debug argument with `add esp, 0x4`; the original-looking `void` method
with a side-effect-only debug report emits the native `pop ecx`.

2026-06-20 audio-loader family check: the exact path sibling uses the same
`debug_report_stub(char*, ...)` surface and direct failure return. Mirroring that
source shape in the byte loader preserved the 88.89% object and confirmed the
residual is the one-argument cleanup selection, not failure-branch semantics.

2026-06-20 audio-family audit: declaring the one-argument failure call as
`debug_report_stub(char*)` is codegen-neutral at 88.89% and still emits
`add esp, 0x4`. The exact path sibling remains the stronger surface evidence
for keeping the shared variadic debug-report declaration; the cleanup mismatch
had to come from the bytes method's own return surface.

2026-06-20 proof retry: spelling the failure branch as
`if (sample_handle == 0) return debug_report_stub(...)` and as a conditional
return is codegen-neutral at 88.89%. Spelling it as a side-effect call while
keeping the method `int` regresses to 65.00% because VC6 saves the sample handle
in `esi` for the final return. Changing only the bytes backend method to
`void`, then using the side-effect debug report, matches 100.00%; the caller
`register_sound_sample` and exact path sibling both stay at 100.00%.

2026-07-16 ownership replay: this loader now borrows the canonical
`g_registered_sound_sample_handles[RSHELL_SOUND_MAX]` declaration from
`audio_system.h`. The exact 256-element extent is proved by the registration
guard and the separate, unreferenced word at `0x753be0`; the normalized object
remains byte-identical.
