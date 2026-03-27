# Parse Helper Prototypes 2026-03-27

This pass closes the parser-helper cursor drift with the conservative signatures that verify live in the Binary Ninja bridge and persist cleanly into the tracked BN/IDA lanes.

## Closed signatures

- [`parse_next_int32`](../decompile/binja/functions/004320f0-parse_next_int32.c):
  `int32_t __cdecl parse_next_int32(char** cursor)`
- [`parse_next_space_delimited_token`](../decompile/binja/functions/00431ed0-parse_next_space_delimited_token.c):
  `char** __cdecl parse_next_space_delimited_token(char** cursor, char* out)`
- [`parse_next_float32`](../decompile/binja/functions/00431f20-parse_next_float32.c):
  `double __cdecl parse_next_float32(char** cursor)`

## Why `double` for `parse_next_float32`

The helper parses a decimal token into an x87 result and returns through the FPU stack. Binary Ninja preview accepted a narrower `float(char** cursor)` spelling, but live verification was brittle there and repeatedly canonicalized the helper back to a wider floating return. `double(char** cursor)` is the stable live spelling that:

- preserves the recovered `char** cursor` semantics
- survives Binary Ninja live verification
- avoids another x87-driven prototype regression in tracked exports

This is a decompiler-facing compromise, not a claim that the native helper is semantically a high-level IEEE `double` API.

## Refreshed callers

The immediate readability payoff is in the parser-driven callers:

- [`initialize_intro_screen`](../decompile/binja/functions/004191e0-initialize_intro_screen.c)
- [`load_level_definition_file`](../decompile/binja/functions/00447480-load_level_definition_file.c)
- [`load_landscape_script_by_name`](../decompile/binja/functions/00432b20-load_landscape_script_by_name.c)
- [`load_segment_definitions`](../decompile/binja/functions/00431a50-load_segment_definitions.c)
- [`load_x_mesh`](../decompile/binja/functions/00405640-load_x_mesh.c)

The x87-heavy float consumers are still noisy, but the helper calls now consistently expose cursor ownership instead of raw `char* arg1` drift.

## Tooling note

Binary Ninja bridge verification is stricter than preview for these helpers. Parser/helper prototype changes should therefore be replayed through the narrow sync lane in [`tools/binja/sync_parse_helper_prototypes.py`](../../tools/binja/sync_parse_helper_prototypes.py) instead of only previewing them in the GUI.
