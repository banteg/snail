# Residual diff — 91.23%, 27/30 insns

Our build cross-jump-merges the two identical `last_coin = coin; return`
tails; the original duplicates them (zero-jump hot path). Three-insn
layout-only residual; every compare, threshold, and store matches.

Semantics pinned: coin strictly `random_float_below(1.0f, "Mirror") > 0.5f`
(confirms the 06-10 strict-threshold Zig fix), streak counter at +0x04
increments on repeat and resets on alternation, four repeats force an
inversion (`coin = !coin`) with streak reset, last coin persists at
+0x02. RNG call is cdecl with a debug/tag argument: raw image disassembly
pushes `0x4a4c90`, which resolves to the `"Mirror"` string. This is not an
RNG state object; the normalizer masked the address either way, so the score
did not expose the earlier wrong assumption.
