# Turnover Double and Wibble source recovery

Two more template-pair builders reach **100% whole-function normalized
matching**, taking the family from **8/29 to 10/29 matched**. Nineteen remain
unsolved at that tier. Neither new match is byte-exact; the family still has
three encoded-body matches.

| Builder | Before | After | Instructions | Strict positional references | Compared body |
| --- | ---: | ---: | ---: | ---: | ---: |
| Turnover Double | 94.27312775% | 100% | 682 to 680/680 | 46/46 | 2,458 bytes |
| Wibble | 89.14473684% | 100% | 608/608 | 39/39 | 2,213 bytes |

The [complete receipt](house-style-pair-recovery-20260912.json) contains
reconstructible sources, recorded measurements, independent reversals,
raw native/candidate bytes, complete body comparisons and positional reference
audits. Compiler, flags, shared headers, ABI, target extents and matching rules
remain unchanged. No source-object grouping, assembly or synthetic side effects
are introduced.

## Patterns recovered from solved builders

The solved builders provide evidence for operation boundaries and variable
lifetimes, rather than one universal spelling. See the earlier
[Turnover](turnover-endpoint-face-vector-owners-20260911.md),
[Invert](invert-curve-frame-texture-recovery-20260911.md) and
[Slalom](slalom-exact-20260912.md) recoveries.

Turnover Double now gives the departure phase a shared `tail_start` local.
Both the logical sample index and initial physical sample offset derive from
that value. Its relative bound is declared after the offset and retains the
independent `-6 - curve_segments` expression. This recovers the native loop
without the extra candidate counter. As in Turnover, a persistent `Vector3 up`
owns the zero Z component while each curve iteration assigns X and Y from the
existing trigonometric results. The builder's doubled/folded roll, center
trajectory and sample counts remain distinct from Turnover.

Wibble uses a physical sample cursor and separate logical phase index, as in
the solved Slalom/Invert families. Primary metadata and Identity initialization
form one operation that borrows the live bank. A second operation borrows both
banks and owns the secondary transform copy plus lane-offset update. Nested
trigonometric arguments preserve the native phase lifetime. The delta pass
also follows live bank accesses instead of retaining a primary sample pointer
across `Normalize()`, matching the native reloads. Both banks retain their
terminal forward direction and unit length.

Unused helpers are removed and the changed Wibble operations are formatted.
These cleanup steps independently preserve every relocation-audited body byte.
The evidence does not identify unique original helper names or signatures.

## Independent controls

| Reversal from retained source | Normalized result |
| --- | ---: |
| Turnover Double: remove shared departure start | 94.35069699% |
| Turnover Double: move relative bound before physical offset | 99.26470588% |
| Turnover Double: rebuild the up-vector temporary each iteration | 99.85294118% |
| Wibble: inline the primary initialization operation | 96.13804437% |
| Wibble: inline the secondary copy/offset operation | 96.13804437% |
| Wibble: restore the shared roll-phase local | 95.22240527% |
| Wibble: restore the captured primary delta pointer | 84.34925865% |

Full reversals reproduce the original sources and baseline results. Merely
copying Slalom's typed delta traversal or width borrow does not solve the other
builders. On the normalized-exact Turnover Double, typed delta arrays actually
introduce ten encoded differences; its original physical delta traversal is
retained. Wibble's physical delta form recovers five bytes versus its first
normalized-exact logical-array candidate. These controls make the limits of a
universal source-style transfer visible.

The receipt preserves **121 compiling observations / 117 unique sources**
across ten builders. Forty-five observations concern Turnover Double and 52
concern Wibble. The remaining eight builders have bounded initial transfer
controls only, and their canonical sources remain unchanged. Several diagnostic
Wibble scalar controls regress reference quality; they are preserved as
rejected controls, never used for exact credit. A source-construction assertion
was caught and corrected before compilation, and is documented separately.
No finite set of controls establishes source exhaustion.

## Encoded evidence and remaining work

Every normalized instruction agrees at the same body offset and encoded
length. Each external relocation field is audited for operand kind, slot,
identity and position before masking. Local branch relocations are resolved;
ordinary instruction bytes, including addressing bytes, remain literal.

Turnover Double compares `[0,2458)` in its 2,464-byte native extent; the final
six bytes are recognized terminal padding. Its single remaining SIB difference
is at body offset **691**: the native center store uses `3b`, the candidate
uses `1f`, exchanging EBX and EDI as scale-one base/index. All other audited
body bytes agree.

Wibble compares `[0,2213)` in its 2,224-byte native extent; the final eleven
bytes are recognized terminal padding. Thirteen scale-one SIB differences
remain at offsets **540, 547, 564, 642, 668, 672, 676, 735, 901, 908, 912,
967 and 982**. Their exact native/candidate bytes are retained. There are no
unexplained target ranges in either body. No encoded-body, linked-image or
runtime equality is claimed.

## Replay

All sources are reconstructed from the receipt's full baselines and ordered
line replacements, then checked against their SHA-256 hashes. The existing
replay tool accepts an optional receipt path; its original default still works.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/house-style-pair-recovery-20260912.json

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/house-style-pair-recovery-20260912.json \
  --function initialize_wibble_path_template_pair \
  --batch cleanup --label canonical-format --replay
```

The same selection with `--source-out FILE` exports a control for the official
`snail match probe` command. Forward and full reverse probes are also recorded
in both scratch experiment ledgers.

## Validation and progress

All **785 scratch checks** and **1,140 tests** pass. The exact-reference audit
and extern lint are clean. Strict validation passes **2,542 ledger records**
and all **14 active specifications**. All 121 reconstructed sources verify,
both final sources replay successfully, and Ruff/whitespace checks pass.

The complete source/evidence refresh and separate saved-evidence validation
pass. Only these two builders change their native matching result; all other
results, native spans and measurement identities remain unchanged. Each public
row is bound to the retained source hash and independently audited target and
candidate body hashes. COFF container timestamps are recorded separately.

Core normalized matching rises **609 to 611 of 662 functions**. Public matching
rises **722 to 724 functions**, with **4,671 newly normalized-matched code
bytes** and zero regressions. Encoded-body and linked credit remain unchanged.
