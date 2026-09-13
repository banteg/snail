# ReleaseWeapons: recover the first vector component's storage

`cRSnail::ReleaseWeapons` improves from 92.80% to 94.40%, retaining 125/125
instructions and all 33 clean references. This is a partial improvement,
with no additional complete-body match credit. The same batch separately
[closes Dump](dump-lead-bank-publication-20260914.md).

The first channel now constructs its input vector directly from the random X,
random Y and owner velocity expressions. Previously the explicit X scalar
occupied a separate stack slot. Native uses the first vector component's slot
for both the pre-RAND spill and its later reload. The compiled constructor
preserves the original RNG call order, owner read and floating operations.

An independent raw comparison finds exactly two changed bytes across the
entire 560-byte candidate allocation:

| Body byte | Previous displacement | Native and retained instruction |
| --- | --- | --- |
| 55 | `0x0c` | `fstp dword [esp+0x1c]` at offset 52 |
| 92 | `0x0c` | `fld dword [esp+0x1c]` at offset 89 |

Both complete changed instructions now equal native bytes. Every other
candidate byte and the complete reference audit remain unchanged. The body
ends at offset 554; the six following NOP bytes remain accounted for. The
remaining differences are post-RAND scheduling in the first and third blocks
and the third block's vector-store schedule.

The [receipt](release-component-and-bank-controls-20260914.json) preserves
171 compiling controls over 11 functions, plus three explicit construction
errors from passing const bank references to P's mutable endpoint helper.
Corrected mutable controls compile. The receipt includes all source edits,
measured diagnostics, full native and candidate captures, the two-byte proof,
and forward/reverse native probes. Reversal restores the previous code hash.

The other controls test integer conversion ownership, loop-counter lifetimes,
phase-local bank references, curve and output ownership, and scalar/vector
temporaries. These are bounded observations rather than exhaustion claims.
In particular, Cage2's primary-bank reference recovers instruction-count
parity while leaving broader differences; first-channel scalar references
improve some scheduling but add copies. Neither is promoted on score alone.

All 785 scratches pass validation, along with 1,140 tests, the exact-reference
audit, extern lint and strict experiment/spec checks. All 171 source
reconstructions validate, and the retained source freshly replays. The refreshed
public evidence changes only ReleaseWeapons' ratios, apart from COFF timestamps;
Dump remains fully matched. No compiler, shared header, ABI, reference rule,
function extent or acceptance policy changes.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/release-component-and-bank-controls-20260914.json \
  --function release_snail_weapons --batch retained-component-owner-final \
  --label canonical-retained --replay
```
