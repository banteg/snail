# World initializer source recovery

`initialize_game_assets_and_world` improves from **81.3425% to 83.7463%**.
The candidate still has **5,405/5,411 instructions**, with **1,880 clean aligned
references and two unaudited references**. This is partial source progress;
no new normalized or encoded-body exact match is claimed.

## Player matrix temporary

The player transform now copies from a `TransformMatrix` value constructed with
the existing sixteen-float constructor. The old source reused the earlier pillar
matrix through its compatibility method. The native call at `0x41014f` targets
the independently recovered constructor at `0x44cfe0`, and the following
`rep movsd` copies its sixteen dwords to the player transform.

This restores the distinct 64-byte player temporary: the candidate frame grows
from `0xec` to the native `0x12c`, and the constructor's argument-adjusted stack
address changes from `[esp+0x6c]` to native `[esp+0x13c]`. The epilogue agrees.
The matrix change alters those three instructions and four displaced branch
labels; the remaining normalized instructions are unchanged. The exact prefix
grows from zero to 43 instructions. This is an ordinary constructor expression,
with no padding or register-forcing storage.

The July 14 note rejected a separate typed temporary because the then-current
vector default constructor emitted extra initialization. The shared authored
math API now has the independently recovered empty default constructor. That
historical obstacle no longer applies; neither shared header changed in this pass.

## Empty-list branch order

The inline overlay linker now handles `first == 0` before its nonempty-list
case. All existing stores, head reloads, flag updates, and the error path are
preserved. Native uses this same empty-case fallthrough and a conditional jump
to the nonempty block in all three overlay insertions. The new branch order
also changes subsequent compiler register allocation. The receipt preserves
both the local native comparisons and the complete before/after assembly diff.

The matrix change adds 12.80 fuzzy-weighted bytes and branch ordering adds
541.82, for **554.62 fuzzy-weighted bytes** overall. These are similarity
weights, not newly certified code bytes.

## Bounded controls

Six replayable controls run against the retained source. Reloading the node in
the linked branch is byte/relocation-equivalent to the baseline. A named temporary
plus the compatibility call preserves the metrics but has a different relocation
identity. The named constructor value loses
4.27 fuzzy-weighted bytes; reusing the pillar matrix loses 12.80 and the entire
43-instruction prefix.

Indexed input-array expressions and a scoped input-owner reference both recover
the interior input-field cursor, but remove six candidate instructions and change
later register scheduling. Both fall to 81.3691%, with unchanged reference debt,
so neither is promoted. These results constrain the tested forms only.
The [mutation recipe](scratches/initialize_game_assets_and_world/initialization-lifetimes-20260911.json)
and append-only ledger preserve the controls and their source identities.

## Scope and verification

The full 785-scratch status sweep changes only this initializer. Core fuzzy
progress rises **91.09% to 91.27%**, while core exact counts remain **600/662**
and platform exact counts remain **112/120**. The native report remains at
**711 normalized-matched owners / 164,402 code bytes** and **700 encoded-body
matched owners / 149,475 code bytes**, out of 2,261 owners and 596,823 code bytes.
Target, inventory, ownership, scoring, and toolchain identities are unchanged.
There are no newly exact or regressed bytes. Linked code remains zero; standalone
data and final-image identity remain unmeasured.

All **1,046 tests pass**. Full status and source-bound report checks pass; the
strict experiment ledger validates 2,454 records without errors and 13 active
runnable specifications. The [receipt](world-initializer-lifetimes-20260911.json)
preserves the source diff, baseline and candidate identities, stack diagnostics,
complete aligned reference audit, native constructor call, retained assembly
diffs, all six control results, and the comparable public-report identities.
The two remaining reference entries are the known Golb vapour-object stride;
partial-function reference alignment is diagnostic, not exact positional proof.
