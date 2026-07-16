# apply_audio_config_volumes @ 0x41b070

Exact match: 100.00%, 11/11 instructions, with seven masked operands clean.

The two callers seed `ecx` with the root-owned `Options` receiver even though
this compact body does not read `this`. Spelling it as a void member preserves
the exact code and removes the previous free-function ownership fiction.

Android and iOS expose the broader `cROptions::Apply(bool)` lifecycle member.
Windows' no-argument helper is the audio-volume subset rather than a
signature-identical port mapping, so the authored provenance is recorded with
that ABI distinction instead of forcing the mobile parameter.

## 2026-07-16 aggregate analysis owner

Binary Ninja and IDA now both own `g_audio_backend` as the exact recovered
0x1c-byte `AudioBackend` prefix. That makes the music, SFX, and voice scales
members of one aggregate in analysis. The matching header deliberately retains
the three scalar aliases because those spellings preserve the native codegen;
they are compatibility views, not separate runtime objects.
