# Residual diff — 91.23%, 27/30 insns

Our build cross-jump-merges the two identical
`track_mirror_enabled = mirror_enabled; return` tails; the original duplicates
them (zero-jump hot path). Three-insn layout-only residual; every compare,
threshold, and store matches.

Semantics pinned: the new mirror state is strictly
`random_float_below(1.0f, "Mirror") > 0.5f`,
`track_mirror_repeat_count` at +0x04 increments on
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

2026-06-18 owner correction: the scratch first moved this onto `cRSubGame`;
the later mobile-symbol replay recovers the authored spelling
`cRSubGame::SwitchMirror()`.
The callsites in `populate_runtime_track_cells_from_segments` and the row-flag
consumer prove +0x02 is the current track mirror flag, not a generic
`last_coin`, and +0x04 is the repeat guard for that flag.

2026-06-21 tail-duplication retry: explicit `>= 4` branching, returning the
stored field on either arm, volatile stores on either arm, result locals, hot
and cold temporary result locals, and boolean-expression inversion all compile
to the same 91.23% object. VC6 continues to cross-jump-merge the identical
`track_mirror_enabled = mirror_enabled; return` tails, leaving the native
duplicated hot return tail unrecovered.

## 2026-07-27 Android owner and void ABI

Android retains the authored name `cRSubGame::SwitchMirror()` and the same
strict `RAND(1.0f, "Mirror") > 0.5f` choice, repeat counter, and forced
inversion after four repeats. Its raw ARM exits leave RAND's float bits in
`r0`, not the selected mirror byte. The two Windows call sites likewise
overwrite EAX immediately or jump away without consuming it, proving the
member is void.

Projecting that real ABI into the natural scratch preserves the honest 91.23%
result, 27/30 instructions, and the same three-instruction VC6 tail-folding
residual. No source was distorted to imitate the duplicated native return
tail.

Binary Ninja's durable prototype replay now reanalyzes
`populate_runtime_track_cells_from_segments`, and readback confirms a `void`
callee. Its first HLIL call nevertheless assigns the caller-clobbered EAX
residue into a temporary phi seed; raw x86 immediately overwrites EAX with
`selected_segment->row_count`, while IDA 9.4 renders the call as a plain
statement. That decompiler artifact is not evidence for a return contract.

## 2026-07-29 mobile control-flow audit

Six variants transcribed Android's repeated-state nesting around the forced
inversion, using direct field, local boolean, XOR, `>= 4`, and `> 3` forms.
None improves the 91.23%, 27/30-instruction Windows baseline. The local-toggle
forms retain only 68.85%; direct field forms fall below 51% because VC6
collapses the repeated-state body much more aggressively.

The cross-port body still proves the strict threshold, repeat count, inversion,
and void ownership, but its ARM-oriented nesting is not the source of
Windows' duplicated ordinary-store return tail. The remaining three target
instructions are therefore bounded to VC6 tail duplication; no volatile store
or artificial dependency is introduced to defeat cross-jump merging.

## 2026-07-29 tail-publication closure

Two further bounded sweeps close the ordinary source-shape alternatives around
the residual. Eight tail-publication variants cover hot-first and cold-first
branches, explicit stores on both arms, a common store, direct inversion, and
separate selected-state locals. All eight compile to the same 91.23%,
27/30-instruction object with the same mismatch at target offset `0x3b`; VC6
cross-jump-merges the identical store/epilogue independently of those lexical
choices.

Seven random-state owner variants then test the shapes supported by the Android
byte-state body: a separate float result, separate or const bool owners, signed
and unsigned byte owners, an integer owner, and reversed comparison spelling.
Three ordinary bool/float lifetime forms are neutral. The narrower or wider
scalar owners and reversed comparison regress to 87.10% or below, with the
reversed comparison also introducing two unaudited references.

The ledger records three complete sweeps and 21 unique variants: zero
improvements, 11 neutral results, and ten regressions, with no
errors, repeats, or tradeoffs. The retained void source remains the
mobile-authored semantic form. Recovering the native duplicated hot return
would require defeating VC6's tail merge rather than expressing a missing
program property, so no source change is retained.

## 2026-09-05 additional operation-boundary probes

Four forced-inversion operation forms preserve both reset and inversion with game or field ownership. All are byte-neutral at 91.23%; no helper is retained.

## 2026-09-07 continuation: unchanged-source compiler comparison

Recorded msvc6.0 and msvc6.3 probes preserve the current extracted code and
comparison metrics. No compiler setting or source change is retained. See the
[profile controls](../rebuild_game_archive_if_needed/profile-controls-20260907.md)
for component provenance, exact neighbors, and the limits of this comparison.
