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
