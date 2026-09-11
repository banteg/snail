# Loopbow recovery and Toad coupled-owner diagnostic

Loopbow improves from **74.55919395% to 84.25692695%**, gaining **285.5013
fuzzy-weighted bytes** on its fixed 2,944-byte scratch span. The retained
candidate keeps its **792/796 instructions**, **10-instruction prefix**, native
**0x9c prologue allocation**, and all **63 references clean**. It remains
partial and receives no normalized or encoded exact credit.

## Retained Loopbow source

The face pass now separates topology/texture selection from UV selection.
The two tests use the same local winding index, which cannot change across the
texture call. This preserves every field write and both checkerboard call
paths while recovering more of the native face layout.

Mesh generation uses `primary_samples[row]` and `primary_samples[row - 1]`
directly, removing the decompiler-style physical sample cursor. The ordinary
row is the first branch, with the endpoint row in the else arm, matching the
native branch at **0x42c2a4** into the endpoint path at **0x42c304**. The endpoint
is an ordinary three-component vector constructor, with Z extended by one.
Both geometry branches retain their lateral scales, addition order and vertex
index. All changes are confined to the scratch; there are no shared header,
compiler flag, reference mapping, target range, or matcher changes.

| Source stage | Match | Candidate instructions |
|---|---:|---:|
| Previous source | 74.55919395% | 792 |
| Separate topology and UV | 79.29515419% | 793 |
| Direct mesh sample arrays | 81.15577889% | 796 |
| Ordinary row first | 83.41708543% | 796 |
| Endpoint constructor (retained) | 84.25692695% | 792 |

The exact native instruction count at the fourth stage is a diagnostic, not
proof of a more faithful complete body. The endpoint constructor improves the
full canonical comparison and has the same instruction-count distance as the
previous committed source. Its full byte and reference evidence remains
inspectable alongside the 796-instruction control.

Four independent reversals on the retained source isolate the contributions:

| Reversal | Match | Candidate instructions |
|---|---:|---:|
| Rejoin topology and UV | 77.63074984% | 791 |
| Restore physical sample cursor | 82.49370277% | 792 |
| Restore endpoint-first branch | 82.24181360% | 792 |
| Restore endpoint field assignments | 83.41708543% | 796 |

All retain the 10-instruction prefix and 63 clean references. Twelve distinct
forward sources include UV field aliases, float/double lateral types and all
seven nonempty combinations of the three mesh changes. They are bounded source
controls, not evidence of a compiler limit.

## Toad diagnostic remains outside the canonical scratch

Toad's canonical source stays at **66.81749623%, 663/663 instructions, prefix
89**, with **33 clean references**. The earlier indexed-face / split-UV lead
was 74.37641723%. Coupling that lead with direct sample owners in both delta
lanes, a complete vector offset, direct mesh array access and a vector position
sum reaches **83.37095561%, 666/663 instructions, prefix 16**, still with 33
clean references and the native 0x54 prologue allocation.

This is a useful diagnostic, not promoted source or added matching credit.
The first mismatch changes the turn-sign local's stack home from **0x1c to
0x20**, and the lead Identity address preparation also changes. The shorter
prefix is therefore more than branch-target renumbering. The candidate is also
three instructions farther from the native count than the committed source.
The exported [diagnostic source](diagnostics/toad-owners-20260911.cpp) makes
this unresolved interaction directly reviewable.

The owner recovery itself has concrete native evidence: the original reloads
the primary bank after Normalize at target instruction **300** and the
secondary bank after Normalize at **323**, before storing each returned length.
The diagnostic reproduces both reloads, at candidate instructions **306** and
**329**. Its lane-offset vector also represents the native three scaled basis
components before destination updates. Complete Windows and mobile source
witnesses are included in the receipt.

The investigation records **102 observations / 90 distinct Toad sources**.
Duplicate source labels are mapped explicitly. The five coupled owner sites
have all **31 nonempty combinations** tested; separate controls cover face-index
placement, checkerboard branch order, tail/curve/mesh array owners, vector
operators, helper flattening and local scope. Flattening the helper boundaries
is neutral for the examined sources. No source group or matching rule is
changed to hide the remaining prefix and instruction-count tradeoffs.

## Inspectable evidence

The [receipt](loopbow-and-toad-owners-20260911.json) retains complete source and
hashes for both baselines, Loopbow's retained source and Toad's diagnostic;
full native and unlinked candidate bytes; separate addressed instruction arrays;
complete reference audits with target/candidate positions; compared, excluded
and unexplained ranges;
stack diagnostics; canonical forward/reverse results; duplicate-source aliases;
Windows/mobile witnesses and the proof-generation script. Neither function is
claimed to have an encoded-exact subregion or whole body.
The partial reference audit uses diagnostic alignment; clean references alone
do not grant exact credit.

## Validation and progress

All **785** scratch builds/status checks pass. A full forced source/evidence
refresh and separate saved-evidence validation pass. The strict experiment
ledger has **2,477 records**, zero malformed or current strict errors, and all
13 active recipes runnable. `git diff --check` passes.

Core fuzzy matching rises **91.70% to 91.80%**, and the residual fuzzy gap falls
**19,448 to 19,162 bytes**. Exact core functions remain **602/662**. Public
normalized credit remains **714 functions / 165,216 bytes**; encoded credit
remains **703 / 150,289 bytes**. Only Loopbow's public ratio changes. Toad's
canonical source and public credit are unchanged. There are no exact gains or
regressions, changed measurement identities, or changed target spans.
Linked-code credit remains zero; data and final image identity remain unmeasured.
