# Halfpipe: retain the live bank across node allocation

Halfpipe improves from **86.32175762% to 87.19037509%**, with **706/707**
instructions instead of 704/707. The existing 137-instruction, 575-byte encoded
prefix remains exact, with 29 strict positional references. All 55 full-body
alignment references remain clean. This is still a partial match.

The middle section now borrows the primary bank through a reference to its
live pointer field. The reference is bound before `GetNodes()`, so allocation
can replace the bank and later middle-section accesses still read the current
field. This restores three native source/receiver relationships together:

- the middle primary Identity receiver uses the native three-instruction setup;
- the transform copy into the secondary bank uses native's source setup; and
- the secondary offset calculation takes the up-vector address before loading
  its first component.

Binding the reference after allocation, at function entry, or only after the
cross product produces different partial results. The selected lifetime is
supported by the complete diff, not instruction-count parity alone. A separate
signed comparison and even-parity spelling restore three native conditional
branch opcodes. These three opcode bytes are the only changes relative to the
selected bank control; its reference audit and branch displacements are unchanged.

The [receipt](halfpipe-live-bank-and-release-diagnostic-20260914.json) contains
native and candidate bodies, complete reference audits, literal-byte local
certificates, source reconstruction recipes, and forward/reverse probes.
Reversal restores the previous compiled-function hash; the forward probe
reports no tradeoffs. In addition to the preserved prefix, the retained source
has two independently certified native regions:

| Native region | Meaning | Instructions | Bytes |
| --- | --- | ---: | ---: |
| `0x429e52..0x429eab` | Middle Identity, position and up-vector publication | 27 | 89 |
| `0x429efe..0x429f6e` | Matrix copy and secondary offset | 32 | 112 |

These certificates cover entire selected regions, including four strict
reference fields. They do not mean all 201 bytes are newly recovered. The
full native `0x429b20..0x42a540` extent remains compared without exclusions;
no whole-function credit is added. Departure receiver preparation, temporary
storage and mesh-loop details remain unresolved.

## ReleaseWeapons: byte-equal diagnostic, source still open

A separate control reproduces all **554 native body bytes**, **125
instructions**, **33 strict positional references** and the literal gate
branch. The six terminal NOPs remain separately accounted for. This is a
verified property of that diagnostic source, not a promoted match.

The control requires two redundant float-to-double-to-float conversions around
the first and third vertical sums, plus a named float reference for the third
RAND result. Removing either retained conversion or replacing that reference
with a float value loses byte equality. Conversions in the already matching
second and fourth channels can both be removed. Ordinary named values, wider
arithmetic literals, component arrays and complete vector owners did not
supply a plausible equivalent source shape in this batch.

The numeric conversions have no recovered authored purpose. Under the
[no-fakematching rule](README.md#no-fakematching), this source remains a
diagnostic seed. Canonical ReleaseWeapons stays at **94.40%**, and its public
exactness status is unchanged. The seed establishes a concrete candidate
compiler path for the desired scheduling; it does not establish source
recovery or exclude other source shapes.

Preserving C2 observations were captured for canonical ReleaseWeapons and the
minimal byte-equal diagnostic. Normal, captured, replayed and observed whole
COFF objects agree except for timestamps in each run. Missing-stream replay
fails, and compiler decisions are not modified. Each trace has 12 events; the
receipt retains all event opcode-count deltas, selected snapshots at events
0, 2 and 11, input hashes and adapter receipts. At the final observed boundary
the diagnostic still has three additional nodes with opcode `0x162`. No
semantic meaning is assigned to that opcode here, and these traces earn no
matching credit.

## Controls and validation

The batch records **161 compiling controls**: 77 Halfpipe, 72 ReleaseWeapons,
and 12 Draw controls. One delta-scope generator initially selected the wrong
sample-index declaration; its syntax error is recorded separately. The
corrected declaration-anchored version compiles and is neutral.

Halfpipe's branch-local lateral calculation is retained as an **88.46426044%**
diagnostic seed. It restores some primary-vector storage while changing other
live temporary slots, so its higher score is not used to replace the narrower
bank/branch recovery. Draw's dimension-field reference controls do not close
its two-instruction shadow-width residual. These are bounded observations,
not exhaustion claims.

All 785 scratch checks and 1,140 tests pass, together with the exact-reference
audit, extern lint and strict experiment/spec checks. All 161 source recipes
validate, and both principal sources freshly replay. The refreshed public
evidence validates and changes only Halfpipe's two ratio fields, apart from
COFF timestamps. Published counts remain 731 normalized matches and 727
byte-exact bodies; ReleaseWeapons is not promoted. No shared header, compiler,
ABI, function extent or acceptance rule changes.

Reconstruct and freshly replay either principal source:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/halfpipe-live-bank-and-release-diagnostic-20260914.json \
  --function initialize_halfpipe_path_template_pair \
  --batch retained-source-format --label canonical-format --replay

uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/halfpipe-live-bank-and-release-diagnostic-20260914.json \
  --function release_snail_weapons --batch named-vertical-inputs \
  --label remove-second-and-fourth --replay
```
