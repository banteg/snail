# Path UV and Screw source ownership recovery

Three partial path builders improve through native-backed source recovery.

| Builder | Before | Retained | Candidate/native instructions | Prefix | Clean references |
|---|---:|---:|---:|---:|---:|
| Cage2 | 69.7388633% | 75.5760369% | 654/648 | 10 | 46 |
| Screw | 71.7119765% | 86.9438366% | 686/685 | 58 | 40 (previously 38 + 2 unaudited) |
| Turnunder | 78.1659389% | 78.4570597% | 687/687 | 56 | 45 |

The total gain is **529.4137 fuzzy-weighted bytes** across fixed scratch
comparison spans. This diagnostic does not add normalized or encoded exact
credit. All three retain their prefixes and native prologue allocations
(Cage2/Turnunder 0x54, Screw 0x50).

## Source and reference evidence

All three separate face topology/texture selection from UV selection. The
native face pass and the recovered Snake, Twister and Start source structures
support this dispatch. The local face index cannot change across the texture
call. Cage2 preserves the branch-selected face pointer across that call; only
its declaration moves outside the branch. A pointer-declaration-only control
has the baseline normalized code hash and score, isolating the UV improvement.
The existing shared final V store in Turnunder remains after both branches.

Screw previously reused one cosine/sine pair for both previous-sample up
vectors. The Windows body calls them separately for each lane, and the verified
Android and iOS bodies independently retain both pairs. The retained source
explicitly calls Cos then Sin for the primary lane, constructs its up vector,
subtracts adjacent positions into its forward vector, normalizes, and crosses;
it then repeats these operations with fresh calls for the secondary lane.
Direct sample fields preserve native owner reloads across those calls.

The previously missing native calls at **0x41f151** (cosine, target instruction
239) and **0x41f15b** (sine, instruction 242) now pair with candidate instructions
244 and 247 at offsets **0x3c9** and **0x3d3**. Their COFF relocations resolve to
Cos/Sin and match the native functions at **0x44c980/0x44c9d0**. All 40 audited
references are clean. Screw's `references` residual is therefore removed;
`analysis` and the partial matching state remain.

The curve loop now initializes its logical counter before the outer guard and
uses a guarded do/while with the existing physical sample cursor. This removes
two excess candidate instructions, from 688 to 686, while preserving the
positive-count domain and every sample write. The native has 685 instructions.
No compiler flags, shared headers, target ranges, reference mappings, or matcher
rules change.

## Independent reversals and bounded controls

Rejoining topology and UV returns Cage2 to **69.7388633%** and Turnunder to
**78.1659389%**. On the retained Screw source, independently:

| Reversal | Match | Instructions | References |
|---|---:|---:|---|
| Restore for-loop guard | 85.9431901% | 688 | 40 clean |
| Restore shared trig and helper owners | 79.8529412% | 675 | 38 clean + 2 unaudited |
| Reuse primary trig with direct owners | 79.4721408% | 679 | 38 clean + 2 unaudited |
| Rejoin topology and UV | 79.2700730% | 685 | 40 clean |

The six canonical forward recipes contain **40 compiling variants**: six
initial UV transfers, six face-owner controls, and 28 Screw trig, vector-owner,
curve-guard, direction-owner and departure-index controls. Six reverse variants
are separately recorded. UV-only transfer regresses Invert, Toad and Turnover,
so their sources are unchanged. Toad's indexed-face plus split-UV lead reaches
74.3764% but loses prefix instructions (89 to 16); it is preserved for further
source/prologue investigation rather than promoted on score alone.

Screw still differs in entrance register ownership, the departure loop's native
precomputed negative base, and the cold identity branch placement. The measured
ordinary predicates and local lifetimes do not resolve those differences.
These are bounded observations, not evidence of a compiler limit.

## Inspectable proof

The [receipt](path-uv-and-screw-owners-20260911.json) contains both complete
sources and source hashes, full native and unlinked candidate bytes, separate
addressed instruction arrays, complete positional reference audits, compared /
excluded / unexplained ranges, stack diagnostics, all forward/reverse results,
Windows and mobile source witnesses with hashes, and the proof-generation
script. It makes no contiguous encoded-region or whole-function equality claim.

## Validation and progress

All **785** scratch builds/status checks pass. A full forced source/evidence
refresh and separate saved-evidence validation pass. The strict experiment
ledger has **2,474 records**, zero malformed or current strict errors, and all
13 active recipes runnable. `git diff --check` passes.

Core fuzzy matching rises **91.52% to 91.70%**; the residual fuzzy gap falls
**19,977 to 19,448 bytes**. Exact core functions remain **602/662**. Public
normalized credit remains **714 functions / 165,216 bytes**; encoded credit
remains **703 / 150,289 bytes**. Only the three intended function ratios change.
There are no exact gains or regressions, changed measurement identities, or
changed target spans. Linked-code credit remains zero; separate data and final
image identity remain unmeasured.
