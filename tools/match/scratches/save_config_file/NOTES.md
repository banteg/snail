# save_config_file @ 0x42f540

Writes the config blob directly with `fopen("wb")`, `fwrite`, and `fclose`.
Unlike `save_file_bytes_with_optional_archive_scramble`, this helper does not
scramble data or report save failures; the failure path only calls `_getcwd`
into a 512-byte stack buffer and returns that CRT result.

Match status: 100%, 31/31 target instructions, 5 masked operands ok.

2026-07-15 CRT ownership: this helper now uses VC6's authentic `<stdio.h>` and
`<direct.h>` declarations, including `FILE*`, instead of an opaque `File` and
four local CRT prototypes. The focused 31/31 object and five clean masked
operands are unchanged.

2026-07-16 decompiler replay closure:

- The archive-shell replay now restores the `fopen`/`fwrite`/`fclose` contracts
  plus the real `char[512]` failure buffer and stream local in IDA. This removes
  a stale completion-screen overlay that had captured the outgoing call slots.
- The correction is durable and idempotent: a second replay reports every
  prototype and local unchanged, paired health checks pass, and the matcher
  remains exact at 31/31 instructions with five clean masked operands.
