# strings_equal_case_insensitive_path

Initial scratch for the ASCII case-insensitive comparator at `0x44e6c0`.

Recovered relationships:

- Used by segment path lookup, level segment copying, landscape script lookup,
  mesh-cache lookup, and music stream path reuse.
- This helper requires both strings to terminate after a folded match. It is
  not the prefix-friendly `strings_equal_case_insensitive` at `0x431dc0`.
- Folding is ASCII-only and subtracts `0x20` for bytes in `a..z`.

The function was previously only present in
`analysis/symbols/gameplay-references.json` as a named target for exact caller
audits; this scratch promotes it into the primary function manifest.

Focused Wibo result: 100.00%, 33/33 instructions, no masked operands.

## 2026-07-27 authored RString ownership

Android and iOS preserve this exact algorithm as `Rstrcmp(char*, char*)` in
`RString.o`, adjacent to `Rstrnewline` and `Rstrint`. This closes the ownership
distinction introduced by the earlier parser helper: `RTextCompStart` accepts a
terminated prefix, while this function succeeds only when both folded strings
terminate together.

The mobile decompilers infer `bool`, but that return type is not encoded in the
C++ symbol. Windows emits `mov eax, 1` / `xor eax, eax`, and all six callers
test or compare the full EAX result. A direct Windows `bool` experiment changed
those writes to AL and regressed the focused match to 87.88%, so the canonical
Windows ABI remains `int` and the natural source stays exact at 33/33.
