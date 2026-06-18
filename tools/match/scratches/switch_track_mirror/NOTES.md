# Residual diff — 91.23%, 27/30 insns

Our build cross-jump-merges the two identical
`track_mirror_enabled = mirror_enabled; return` tails; the original duplicates
them (zero-jump hot path). Three-insn layout-only residual; every compare,
threshold, and store matches.

Semantics pinned: the new mirror state is strictly
`random_float_below(1.0f, "Mirror") > 0.5f` (confirms the 06-10
strict-threshold Zig fix), `track_mirror_repeat_count` at +0x04 increments on
repeat and resets on alternation, four repeats force an inversion
(`mirror_enabled = !mirror_enabled`) with the repeat count reset, and
`track_mirror_enabled` persists at +0x02. `populate_runtime_track_cells_from_segments`
clears both fields before the row build and reads +0x02 to set the runtime row
mirror flag, so this is a narrow `Game` prefix view rather than a standalone
RNG state object. RNG call is cdecl with a debug/tag argument: raw image
disassembly pushes `0x4a4c90`, which resolves to the `"Mirror"` string. This is
not an RNG state object; the normalizer masked the address either way, so the
score did not expose the earlier wrong assumption.

2026-06-13 pin audit: focused matcher still verifies 91.23%, 27/30 insns.
Keep pinned; the remaining diff is only the duplicated native return tail
versus VC6 cross-jump merging.

2026-06-16 source-shape recheck: rewriting the tail as
`if (track_mirror_repeat_count >= 4)` with the non-inversion store/return
afterward compiled identically. VC6 still cross-jump-merged the two
`track_mirror_enabled = mirror_enabled; return mirror_enabled` tails, so keep
the clear strict-threshold source.

2026-06-18 name correction: the scratch now spells this as `Game::switch_track_mirror()`.
The callsites in `populate_runtime_track_cells_from_segments` and the row-flag
consumer prove +0x02 is the current track mirror flag, not a generic
`last_coin`, and +0x04 is the repeat guard for that flag.
