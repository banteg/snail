# Screw exact body through borrowed mesh inputs

`initialize_screw_path_template_pair @ 0x41eda0` now matches its complete
**2,495-byte native body**, improving from **99.12408759% to 100%**. All
**685 instructions** agree in position, size and normalized text. All **40
external references** pass strict positional checks, and all **28 local
branches** have identical instruction-boundary destinations.

The [complete receipt](screw-exact-mesh-inputs-20260913.json) contains full
baseline/retained sources, raw and relocation-audited bytes, instruction arrays,
reference checks, branch checks, reversible controls and source witnesses.
The official source-overlay promotion has no tradeoffs.

## Source recovery

The mesh construction is extracted into `build_strip_mesh`, borrowing its live
width, segment count, mesh pointer and primary sample bank. Read-only references
preserve member reloads around allocation and texture calls. Both texture inputs
remain explicit. The vertex arithmetic, face topology, UV writes, traversal and
allocation operations are unchanged.

This operation boundary and its field inputs recover the native multiplication
operand selection. The earlier allocation-only forms could recover four bytes
but left face indexing different; the complete mesh operation recovers all
nine remaining bytes. The existing field-input experiments on Sweep provided
a relevant source hypothesis to retest after Screw's counter/curve recovery.
The result establishes a matching representation, not a unique original helper
signature or parameter spelling.

Screw's inactive template branches, selector macros, unused helpers and unused
height local are removed. The six-argument constructor is now concrete. That
cleanup preserves every raw extracted function byte, including the excluded
terminal padding. The compiler, flags, shared headers, ABI, target extent and
matching policy are unchanged.

## Full-body proof

The native extent is `[0x41eda0,0x41f760)`. Comparison covers `[0,2495)`; only
one recognized terminal padding byte is excluded. The cold texture branch
after `ret 0x18` remains in the compared body. There are no inline or unexplained
ranges. Native and candidate both allocate a `0x50` stack frame.

Each external relocation is handled only after matching its instruction index,
byte offset, operand kind, operand slot and resolved identity. Every relocation
is accounted for. All other body bytes remain compared literally, including
SIB bytes and local branch displacements. The independently audited native and
candidate bodies are equal.

Exactly nine raw candidate bytes change from the baseline, at offsets
**1581, 1584, 1601, 1608, 2072, 2073, 2074, 2075 and 2076**. These are the
previously documented allocation and face-index differences; every one now
equals native. All other raw candidate bytes are unchanged.

This adds 2,495 bytes of normalized and encoded-body credit. The curated extent
is 2,496 bytes including padding. Final-image linking is a separate measurement.

## Controls and replay

The receipt records **27 compiling observations / 26 distinct sources**:
19 Screw controls and eight transfers to other partial builders.

| Control | Result |
| --- | --- |
| Allocation-only helper, length then width references | 99.70802920%; face-index difference remains |
| Complete helper, width then length references | Complete encoded match |
| Complete helper, length then width references | 99.41605839%; allocation differences remain |
| Restore the Path-owner helper | 99.12408759% |
| Read-only versus mutable reference bindings | All tested complete width-first forms are encoded-exact |
| Remove inactive source and make the constructor concrete | Raw function bytes unchanged |
| Complete reversal | Baseline deterministic fingerprint restored |

These are bounded controls. They do not establish exhaustion of other source
representations or a compiler limit.

The same field-input transfer is tested in both dimension orders on Slalom
Double, Sweep, LoopOut and Hill/Valley. None improves its normalized score.
The neutral Slalom Double, Sweep and LoopOut controls also preserve every raw
and relocation-audited body byte and every positional reference; they retain
31, 22 and nine unequal body bytes respectively. Those complete comparisons
are included in the receipt. All four canonical sources remain unchanged.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/screw-exact-mesh-inputs-20260913.json \
  --function initialize_screw_path_template_pair \
  --batch cleanup --label concrete-source --replay
```

## Validation

All **785 scratch checks** and **1,140 tests** pass, with zero type findings.
The strict ledger check passes **2,558 records**, and all 14 active specs remain
runnable. Extern lint and the exact-reference audit are clean. All 27 source
reconstructions validate, and the retained native replay agrees.

The full compilation-evidence refresh and separate saved-evidence check pass.
Only Screw gains exact credit; all other measurements, native extents and
measurement identities are unchanged. Core exact functions rise **612 to 613**,
and public normalized functions rise **725 to 726**, adding **2,495 code bytes**
to both normalized and encoded-body credit. Template pairs reach **12 normalized
matches / 17 partials**, including **five encoded-exact bodies**. Linked-image
credit remains unchanged.
