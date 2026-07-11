# apply_audio_config_volumes @ 0x41b070

Exact match: 100.00%, 11/11 instructions, with seven masked operands clean.

The two callers seed `ecx` with the root-owned `Options` receiver even though
this compact body does not read `this`. Spelling it as a void member preserves
the exact code and removes the previous free-function ownership fiction.

Android and iOS expose the broader `cROptions::Apply(bool)` lifecycle member.
Windows' no-argument helper is the audio-volume subset rather than a
signature-identical port mapping, so the authored provenance is recorded with
that ABI distinction instead of forcing the mobile parameter.
