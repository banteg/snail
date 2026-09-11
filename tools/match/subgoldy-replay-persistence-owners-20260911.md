# SubGoldy replay cursor and persistence ownership

`update_subgoldy @ 0x43b120` (`cRSubGoldy::AI`) improves from
**83.36118405% to 84.76599809%**. The candidate falls from **2,094 to 2,093
instructions** against **2,087 native**, retains its **12-instruction prefix**
and **64-byte frame**, and now has **315 clean references with no debt**.
The function remains partial.

The [complete receipt](subgoldy-replay-persistence-owners-20260911.json)
contains original, intermediate and retained sources and complete byte arrays,
all 39 successful formal forward sources, two preserved compile errors, three
reversals, native/mobile witnesses and selected positional encoded proofs.
Compiler, flags, headers, ABI, matcher policy and function extent are unchanged.

## Source recovery

The ghost path updates its clamped replay cursor in place using the record's
start minus the player's replay anchor, then indexes the delta-Z sample with
that cursor. This preserves arithmetic order, signed clamping and the existing
short conversion. Windows carries the same cursor in ECX, the count and anchor
in EDX, and the relative start in EDI. The recovery also restores native ESI
zero ownership through the later AI blocks, without a register directive or
artificial dependency. Both mobile bodies support the first-sample versus
accumulated-sample behavior; their different record layout and clamp placement
are not imported into Windows.

Each completion persistence branch copies the current frontend state to the
saved state before publishing 26 or 27. Both mobile bodies place the copy inside
those branches. VC6 merges the repeated copies and emits the native Windows
sequence: test persistence, load the root and copy state, reload the root,
then branch to either state publication and return. The former shared source
copy produced a root load before the persistence test and separate root loads
inside the final arms. The extra load was unaudited; it is now removed.

| Independent reversal | Agreement | Candidate instructions | Unaudited references |
| --- | ---: | ---: | ---: |
| Previous shared persistence copy | 85.7484% | 2,094 | 1 |
| Previous separate offset cursor | 82.5215% | 2,093 | 0 |
| Complete baseline | 83.3612% | 2,094 | 1 |

The higher-scoring first reversal loses the exact native persistence block and
restores reference debt, so it is rejected. The complete reversal reproduces
the original reference-aware function fingerprint. Fuzzy score alone does not
determine source retention.

## Selected encoded proof

The native extent is `[0x43b120,0x43d230)`, **8,464 bytes**. The matcher compares
`[0,8456)` and excludes only **eight terminal padding bytes**. Its comparison
includes the 16-byte switch table at `[8440,8456)` and internal alignment.
There are no unexplained native ranges. The retained candidate table is at
`[8456,8472)`; its ordered destinations remain in the complete reference audit.

The two selected regions are equal after strict positional operand-slot, kind
and identity checks. Only audited external relocation fields are masked.
Local branches land on the corresponding instructions within each region.
Offsets below are relative to function start; intervals are half-open.

| Region | Native range | Candidate range | Instructions | References | Branches |
| --- | --- | --- | ---: | ---: | ---: |
| Persistence test, copies, publications and returns | `[6369,6438)` | `[6378,6447)` | 21 | 2 | 1 |
| Clamped cursor and anchor load/test | `[7172,7198)` | `[7185,7211)` | 7 | 0 | 1 |

These certificates cover **95 native instruction bytes**. They do not certify
the rest of the function or imply that only these regions agree. All remaining
bytes stay compared. The full 315-reference alignment is diagnostic outside
these selected regions. Public whole-function exact and linked credit do not
increase, and no complete native execution harness is claimed.

## Bounded controls

There are **41 forward observations**: **39 distinct successful sources** and
two failed attempts to reuse a historical player-owner recipe with the wrong
`Player` typedef. Both complete failed sources and errors are preserved outside
the formal recipe; the corrected `cRPlayer` control compiles. Fourteen forward
observations retain or introduce reference debt and remain diagnostics.

Direct ghost-global assignments, a borrowed float reference, compound cursor
updates, direct anchor checks and braced conditions did not recover the native
physical ghost branch order. Nested zero cases introduce reference debt; a
shared zero label changes scalar register choices. Conditional frontend stores
remove debt but lose the native two-return structure. None of those alternatives
is retained. A historical register-qualified player control is also preserved
only as a rejected diagnostic.

Record-Z ownership, entry-tile and follow-speed lifetimes, cruise comparison
ordering, ghost branch order, stack-slot coloring and other remaining
instruction differences stay open. These finite controls establish no compiler
limit.

## Validation

All **1,104 tests** and **785 scratch checks** pass, with zero type findings.
The strict ledger has **2,520 records**, zero malformed/current errors and
**14/14 active specs runnable**, with no stale active specs. Full public refresh,
separate saved-evidence validation and `git diff --check` pass. The receipt binds
the canonical source and COFF to the public row and isolated byte proof.

Only this function's public ratio changes. Core exact functions remain
**606/662**; fuzzy agreement rises **93.98% to 94.02%**, and the rounded residual
gap falls **12,613 to 12,494 bytes**. The source-weighted gain is
**118.9035 bytes**. Public totals remain
**718 normalized functions / 172,474 bytes** and **706 encoded functions /
155,114 bytes**. Exact classifications, target ranges and measurement identities
are unchanged.
