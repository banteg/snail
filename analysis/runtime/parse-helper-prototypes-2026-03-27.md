# RText Helper Prototypes

The original 2026-03-27 pass stabilized three anonymous parser prototypes.
Android/iOS evidence added in July now resolves the complete authored
`RShell.o` family and supersedes two conservative analyzer-only return types.

## Closed signatures

- `void __cdecl copy_c_string(char* destination, char* source)`
  (`RTextCopy`)
- `bool __cdecl strings_equal_case_insensitive(char* left, char* prefix)`
  (`RTextCompStart`)
- `void __cdecl skip_to_next_line(char** cursor)` (`RTextNewLine`)
- `void __cdecl append_c_string(char* destination, char* source)`
  (`RTextAppend`)
- `void __cdecl parse_next_space_delimited_token(char** cursor, char* out)`
  (`RTextExtractString`)
- `int __cdecl parse_next_int32(char** cursor)` (`RTextExtractInt`)
- `float __cdecl parse_next_float32(char** cursor)` (`RTextExtractFloat`)

The matcher keeps stable Windows harness names; the parenthesized mobile names
record original source vocabulary.

## 2026-07-27 ownership correction

Windows places these seven bodies contiguously from `0x431da0` through
`0x431f20`, in exactly the Android/iOS symbol order. Mobile
`ObjectTextLoad` invokes the family in the same section-marker, vertex, face,
texture-token, and texture-path roles as Windows `load_object_definition`.

That evidence corrects two earlier assignments:

- the prefix-friendly comparator is `RTextCompStart`, not strict `Rstrcmp`
- the canonical adjacent float parser is `RTextExtractFloat`, not the later
  code-equivalent `Rstrfloat` sibling in `RString.o`

Mobile bodies and Windows callsite use also prove that copy, newline, append,
and string extraction return `void`. The first three natural void
transcriptions remain instruction-exact. `parse_next_space_delimited_token`
retains a documented result-shaped matcher harness because removing it changes
VC6 register allocation; the analyzer databases still use the real void API.

## Retired `double` compromise

The 2026-03-27 Binary Ninja bridge repeatedly widened the x87 return of
`parse_next_float32` to `double`, so the old narrow lane recorded that stable
spelling as an analyzer compromise. Current Binary Ninja accepts and verifies
the mobile-proven `float(char**)` contract. The old `double` declaration and
standalone `bn_parse_helper_prototypes.h` are retired so broad replay lanes
cannot reintroduce the stale type.

## Replay

Use the focused scripts:

- [`tools/binja/sync_rtext_types.py`](../../tools/binja/sync_rtext_types.py)
- [`tools/ida/sync_rtext_types.py`](../../tools/ida/sync_rtext_types.py)

Both replay all seven owners and refresh the parser-driven callers. The
canonical declaration source is
[`tools/match/include/rtext.h`](../../tools/match/include/rtext.h).
