# Gameplay authored-ring publication recovery

`update_subgame @ 0x438b90` (`cRSubGame::AI`) improves from
**79.22016167% to 80.51453073%**. Candidate instructions fall from
**1,037 to 1,033** against **1,034 native**. The **60-byte frame**,
**nine-instruction prefix** and **129 clean references** are unchanged.
The function remains partial.

The [complete receipt](subgame-authored-ring-publication-20260911.json)
contains full baseline/retained sources and byte arrays, 19 distinct successful
forward sources, one reversal, failed-control diagnostics, mobile/native
witnesses and strict positional encoded proof. Compiler, flags, headers, ABI,
matcher and function extent are unchanged.

## Recovered source

Each authored ring branch now updates `player.last_ring_spawn_z` immediately
after its `AddRing` call. The flag priority, kinds **5, 8, 6, 7**, row-speed
argument, current cell and player owner remain the same. Each assignment reads
the cell position after the call. When no authored kind matches, there is no
call or position update. The old shared assignment and bypass `goto` disappear.

Android preserves these branch-local updates. iOS independently corroborates
the prioritized kind dispatch and post-call update with a merged call tail.
Their different layouts and floating-point calling conventions are not copied.
Windows instructions establish the exact shared argument and publication tail.

VC6 now shares that tail across all four authored kinds. It removes four
non-native instructions and restores the native register schedule throughout
the ring dispatcher. The reversal reproduces the complete baseline fingerprint,
1,037 instructions and 79.22016167% agreement, with the same clean references.

## Encoded proof

The selected certificate covers **766 native bytes / 201 instructions** at
`[0x439565,0x439863)`, corresponding to candidate offsets `[2509,3275)`.
It includes the ring gates, authored and ambient branches, calls, position
publication and lane-counter store. All **16 reference-bearing instructions**
pass strict positional operand-kind/index and identity checks. All **42 local
branches** retain their encoded displacements and land inside the certificate.
Only audited external relocation fields are masked; ordinary addressing bytes
remain compared. The lane-loop backedge lies outside this certificate.

This is a certificate for the entire region, including previously matching
ambient branches, not a claim that all 766 bytes are newly recovered. The
function's complete **3,748 compared bytes** include both inline jump tables
at `[3684,3748)` and internal alignment. Only **12 terminal padding bytes** at
`[3748,3760)` are excluded; no native range is unexplained. Whole-function
normalized/encoded exactness and linked credit remain unchanged.

## Bounded controls and remaining work

The 19 successful forward sources test configuration ordering, case-owned
results, positive/else-if result tests, pause-step lifetime, ring flag and speed
owners, cell references, local loop indices and a single kind dispatch.
One initial unscoped pause local failed because a case label skipped its
initialization; the error and source are preserved, and a scoped correction
was measured separately.

The scoped pause float reaches **80.7619%** when combined with the ring change,
but replaces a native integer move with an x87 load/store and changes early
dispatch scheduling. That higher score is not retained. Borrowed-cell and
speed-local controls disturb allocation and introduce reference debt; the
single kind dispatcher also regresses. These remain diagnostic observations,
not compiler limits. State-one scheduling, scan/list ownership, HUD tails and
whole-function branch layout remain open.

## Validation

All **1,104 tests** and **785 scratch checks** pass, with zero type findings.
The strict ledger has **2,524 records**, zero malformed/current errors and
**14/14 active specs runnable**, with no stale active specs. Full public refresh,
separate saved-evidence validation and `git diff --check` pass. The receipt binds
the canonical source and COFF to the public row and isolated byte proof.

Only this function's public ratio changes. Core exact functions remain
**606/662**; fuzzy agreement rises **94.04% to 94.06%**, and the rounded residual
gap falls **12,429 to 12,380 bytes**. The source-weighted gain is
**48.6683 bytes**. Public totals remain
**718 normalized functions / 172,474 bytes** and **706 encoded functions /
155,114 bytes**. Exact classifications, target ranges and measurement identities
are unchanged.
