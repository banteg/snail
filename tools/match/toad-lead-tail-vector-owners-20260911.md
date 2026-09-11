# Toad lead, tail and vector recovery

`initialize_toad_path_template_pair @ 0x42cbf0` improves from
**66.81749623% to 95.46827795%**, while retaining its strict
**89-instruction / 371-byte encoded prefix**, native **0x54** stack frame
and **33 clean references**. Candidate/native instruction counts change from
**663/663 to 661/663**. Both whole bodies remain partial.

The [complete receipt](toad-lead-tail-vector-owners-20260911.json) preserves
all sources, native/candidate bytes, explicit region mappings, positional
reference proofs, observations, reversals and four source witnesses. Compiler,
flags, headers, ABI, native extent and matcher are unchanged.

## Source recovery

The lead loop now carries its physical sample cursor inside the positive-count
guard. It advances the logical index before the final secondary delta-length
store and the physical cursor after that store; the sample Z value was already
captured from the old index. This reproduces the native address and store
schedule while preserving the existing prefix.

A fixed `tail_start = lead_count + 26` initializes the separate absolute tail
index and its negative control base. The existing physical tail and curve
traversal remains. The tail body and latch now follow native instruction order;
the candidate preheader still computes the negative base with `neg`, leaving
two fewer instructions and nine fewer bytes than native.

Direct sample arrays preserve the native bank reloads after both Normalize
calls. Primary subtraction, curve orientation, lane scaling/addition and both
mesh point calculations use the recovered vector operators. Mesh vertices use
row-relative arrays. Face topology uses indexed records followed by a separate,
complete two-branch UV dispatch.

The delta loop also carries its byte cursor inside a positive-count guard.
This change is normalized-score neutral but resolves ten SIB encoding
differences. Initializing the cursor outside the guard moves its zeroing before
the native test; the retained guarded form restores that schedule. Formatting
preserves the complete reference-aware function fingerprint.

These recoveries combine the earlier diagnostic dependencies with a lead
schedule that preserves the stronger canonical prefix. The source witnesses
support the control and data graph, not unique original variable names or
spelling. Mobile bodies do not establish the Windows-only mesh or fourth stack
argument; native instructions and `ret 0x10` establish that surface.

| Independent reversal | Normalized agreement |
| --- | ---: |
| Primary delta vector and direct array | 84.1150% |
| Secondary delta direct array | 88.9561% |
| Mesh sample arrays | 94.0377% |
| Ordinary mesh point addition | 95.3172% |
| Endpoint vector addition | 93.9486% |
| Complete indexed face / separate UV dispatch | 77.5019% |
| Curve orientation subtraction | 95.3172% |
| Lane vector scaling and addition | 93.9486% |
| Guarded lead traversal and increment schedule | 94.5701%; prefix 38 |
| Fixed tail-start lifetime | 85.9293%; prefix 16 |
| Guarded physical delta traversal | 95.4683%; ten SIB differences return |
| All eleven | 66.8175%; baseline fingerprint restored |

## Positional byte proof

The native extent is **2,432 bytes**, `[0x42cbf0,0x42d570)`. The compared body
is `[0,2419)`; only 13 bytes of recognized terminal padding are excluded.
There are no unexplained or inline ranges.

Two separately audited regions have equal encoded bytes after strict external
relocation checks:

| Region | Native / candidate instruction ranges | Native / candidate body offsets | Bytes | Strict references |
| --- | --- | --- | ---: | ---: |
| Tail, curve, deltas and allocation | `[99,397)` / `[97,395)` | `[410,1546)` / `[401,1537)` | 1,136 | 19 |
| Mesh vertices | `[407,477)` / `[405,475)` | `[1583,1814)` / `[1574,1805)` | 231 | 2 |

Every paired instruction has equal size, native index = candidate index + 2,
and native offset = candidate offset + 9. These are explicit region mappings,
not equal global instruction positions. All seven local branches land inside
their own region; their actual displacements remain compared. No SIB bytes are
masked. The separate whole-body reference alignment remains diagnostic.

The full mapped suffix `[99,663)` / `[97,661)` is also audited, including
30 strict references and every byte from native offset 410 to 2419. It has
exactly five differing bytes after relocation handling:

| Native / candidate offset | Native / candidate byte | Meaning |
| --- | --- | --- |
| 1568 / 1559 | `18` / `1c` | Mesh width stack home |
| 1582 / 1573 | `18` / `1c` | Mesh width stack home |
| 1817 / 1808 | `18` / `1c` | Mesh width stack home |
| 2091 / 2082 | `75` / `74` | First parity branch opcode |
| 2270 / 2261 | `85` / `84` | Second parity branch opcode |

The suffix is therefore not encoded-exact. Its shorter preheader is separately
outside that suffix comparison. The parity arms call the same texture for each
face in both source and native; their branch orientation still differs.
Separate exact regions do not establish equality of intervening code or mean
that all region bytes are newly recovered. No whole-function exact credit,
linked-code, data, final-image or runtime equality is claimed.

## Controls and remaining work

The forward receipt has **73 observations / 70 distinct full sources** and
three explicit aliases, followed by **12 final reverse controls**. All formal
sources compile with 33 clean references. Earlier ten-owner reversals and the
pre-cursor byte comparison remain in the receipt, alongside the final eleven
changes and their independent reversals.

Controls include guarded versus pre-tested traversal, lead increment placement,
logical/physical tail and curve interactions, fixed tail-start and relative
bounds, parity orientation, mesh width lifetime and face loops. These are
bounded observations. Earlier statements that these neighborhoods were closed
are historical; neither those records nor this investigation establish source
exhaustion or a compiler limit.

The remaining native differences are the tail preheader, mesh width stack home
and parity branch orientation. They remain open for further source evidence.

## Validation and progress

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,502 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence validation
and `git diff --check` pass.

Toad gains **696.79 fuzzy-weighted bytes**, reducing its gap from
**807.00 to 110.21 bytes**. Core fuzzy rises **92.96% → 93.19%**;
normalized-exact count remains **603/662** and the rounded residual gap falls
**15,685 → 14,988 bytes**. Only Toad's public ratio changes. Exact
classifications, target spans and measurement identities remain unchanged.

Public credit remains **715 functions / 167,649 normalized bytes** and
**703 / 150,289 encoded bytes**; linked-code credit stays zero. The receipt
reads the actual COFF from the completed public refresh, verifies its recorded
hash, and binds it to the isolated proof through the source hash, complete
extracted bytes and reference-aware function fingerprint.
