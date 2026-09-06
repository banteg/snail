# initialize_star_field

Current recovery: semantic-complete (`analysis` residual). Exact Android/iOS
`cRStarManager::Init()` bodies and the live Windows StarManager method establish
the complete entry allocation, camera-relative position, randomized direction,
speed/travel, Sprite setup, and virtual `AI()` handoff. The retained result is
**98.38%**, 247/247 instructions, prefix 126, and all 26 references clean.
Only the travel-store/color-argument scheduling window remains non-exact.

- Source-shaped initializer for the `cRStarManager` entries and backing
  `Sprite` objects. Windows owns the manager at `GameRoot +0x4f33c`; its first
  `0x38` bytes are the constructed `BodBase` prefix and the manager-specific
  state begins at `+0x38`.
- The final call is the first vtable slot on the star-field object; the scratch
  models that slot as `update_star_field_callback()` while the named
  `update_star_field()` body remains the concrete callback at `0x4346f0`.
  Because that installed callback and both direct initializer callsites are
  void-valued, `cRStarManager::Init()` and its inherited callback slot are now
  modeled as `void`; the tail call remains byte-identical.

## Recovered source shape

- `StarManagerEntry` is a real `0x2c` record. The initializer uses array
  indexing rather than retaining one entry pointer; this reproduces native's
  byte-offset loop and leaves `esi = this`, `edi = index * 0x2c`, and `ebp = 0`.
- Camera-relative spawn position is the by-value vector expression
  `overlay_0.transform.basis_forward * 50 + overlay_0.transform.position`.
  Together with the later vector multiply/divide/add expression, this recovers
  the native `0x60` frame and its vector temporaries instead of padding it.
- The initial direction is a temporary `Vector3(random_x, random_y, 0)` copied
  into the entry. VC6's right-to-left argument evaluation explains native's
  first-random-is-y call order and the three-dword temporary copy.
- Velocity scaling is the in-place `Vector3::operator*=` idiom. Promoting that
  semantic operator raises the scratch from 84.34% to 98.38% and exactly
  recovers the scale-once x87 sequence.
- `travel_distance +0x24` advances by `speed +0x20` and wraps after `35`; the
  per-entry `alpha_scale +0x28` feeds sprite alpha directly in
  `update_star_positions`. These replace the weaker `phase`/`twinkle` labels.

Current focused result after the shared vector-operator consolidation: 97.57%,
247/247 candidate/target instructions, a 126-instruction prefix, and 25 masked
operands clean at that stage. The six residual instruction-order differences are VC6
scheduling around the random travel store/color arguments and the corner-scale
sprite dereference; the candidate otherwise has the exact instruction count
and semantics. A retained tail-entry pointer probe regressed to 66.80% by
changing register ownership, so it was rejected rather than forcing the final
scheduling differences.

## 2026-07-11 cRStarManager ownership

Android and iOS preserve the complete `cRStarManager` lifecycle and the
`Star.o` source object. The shared match type now uses `StarManager` and the
already-proven `StarManagerEntry` vocabulary consistently with the BN/IDA
header. Its exact 0x4c extent closes between `MainMenu` and `Options` in
`GameRoot`; the rename is codegen-neutral at the same 98.38% near match.

## 2026-07-14 root ownership cleanup

The camera transform now comes through the canonical `GameRoot* g_game`
owner instead of a raw `char*` base followed by a local cast. This is
byte-identical at 98.38%, 247/247 instructions, with all 25 operands clean;
the remaining differences are still only the documented random/color and
corner-scale scheduling windows.

## 2026-07-19 entry and Sprite lifetimes

Binary Ninja now preserves each materialized `StarManagerEntry*`, its borrowed
`Sprite*`, and the `Vec3*`/`tColour*` children used by the position, velocity,
color, size, and final copy phases. The refreshed listing consequently exposes
the entry's speed/travel/position/velocity fields and the Sprite flag, color,
size, position, and velocity fields instead of `void*` plus numeric offsets.
The manager remains the owner of the entry bank; every entry merely borrows its
Sprite from `SpriteManager`.

The native EDI value is deliberately left as an automatic byte offset. A live
integer retype initially made the decompiler index the final
`facing_refresh_progress` store with the already incremented EBX loop counter,
even though EDI still addressed the prior entry. That annotation was removed
before export; only the independently materialized pointers are retained. The
guarded replay verifies all five owner widths and their exact fields before
setting the stable register lifetimes, and a second run is idempotent.

Matcher source is unchanged at the honest 97.57%, 247/247-instruction frontier,
prefix 126, with all 25 operands clean. Reversing the commutative corner-scale
multiply was codegen-neutral and was reverted; the remaining six instructions
are scheduling only.

## 2026-07-19 remaining Sprite member lifetimes

Eight additional SSA definitions reload the same entry-owned borrowed
`Sprite*` for isolated member stores. They now retain that type through
`progress`, `progress_step`, `gravity_step`, `color`, `size_start`,
`corner_scale`, and `facing_refresh_progress`; the corner-scale path also
materializes its true `StarManagerEntry*` before following `entry->sprite`.
This removes the last raw Sprite `+0x60/+0x68/+0x6c/+0x78/+0x88/+0x8c`
offsets from the Binary Ninja listing.

These are borrowed lifetimes into sprites allocated by `SpriteManager`; they
do not move ownership into `StarManagerEntry`. The EDI induction remains an
automatic byte offset for the previously documented reason. The replay now
guards nineteen stable definitions and remains idempotent. Matching source and
the honest 97.57%, 247/247-instruction, 25-clean-operand result are unchanged.

## 2026-07-28 mobile RNG range provenance

Android and iOS preserve the authored random-range hierarchy in
`cRStarManager::Init`: alpha is
`(rand - 16384) * (1 / 16384) * 0.1 + 0.4`, speed is
`rand * (1 / 32768) * 0.6 + 0.3`, and travel is
`rand * (1 / 32768) * 35`. The Windows compiler folded those products into
single literals; restoring the normalized factors compiles byte-identically
at 97.57%, 247/247 instructions, prefix 126, with all 26 masks clean.

The mobile sine/cosine direction construction is deliberately not transferred:
Windows proves independent x and y random draws, so that platform-specific
source shape remains authoritative.

## 2026-07-29 bounded field-borrow audit

Five additional value, pointer, and reference shapes for the entry's
`travel_distance` and `speed` fields were tested. Every form regresses the
97.57%, 247/247 baseline; a temporary `Sprite` field reference also changes
register ownership across the function and was fully reverted.

The six differing instructions remain confined to two documented schedules:
travel initialization versus the color-call argument loads, and the borrowed
Sprite corner-scale dereference versus the final multiply. Android and iOS
prove the same authored manager/entry/Sprite relationships but use different
platform layouts, so there is no missing Windows inline helper to recover by
co-location. The current function-local source remains canonical and no TU
cluster is introduced.

## 2026-07-29 recorded scheduling frontier

Eight bounded mutation sweeps now preserve the remaining search rather than
leaving it as manual probe history: 83 variants were evaluated and 66 compiled.
The tested scalar and ownership alternatives did not improve that baseline.
Moving the `tColour` lifetime, naming its call result or components, folding the
travel scale, naming the random/travel values, and nine localized corner
value/pointer/reference shapes were all byte-identical. Extending entry,
Sprite, or destination ownership changed register allocation and regressed.

One forced intermediate travel multiply rises to 98.18%, but it has 248/247
instructions, only 25 clean masks plus three unaudited constants, and a
29-instruction prefix. It is rejected as a multi-axis tradeoff rather than
ranked above the proof-clean 97.57%, 247/247, prefix-126 baseline.

Replaying the pre-consolidation constructor-return vector addition confirms
the historical 98.38% score comes only from the camera-position sum. Combined
with a named corner speed it reaches a 124-instruction prefix and leaves four
scheduling moves in two regions, but the helper is deliberately not retained:
sixteen addition consumers and multiple exact callers prove the shared
explicit-result `operator+`, and a per-caller constructor implementation would
reintroduce the operator fakematch rejected during shared arithmetic
ownership. The canonical scratch therefore remains source-unchanged at
97.57%, 247/247 instructions, prefix 126, with all 26 masks clean.

## 2026-07-29 corner-neighborhood probes

A ninth recorded sweep tests the adjacent source neighborhood around the
second residual. Ten variants move or rename the speed, Sprite, entry,
destination, size, and constant lifetimes across the preceding size stores.
Nested scope and named corner constants are byte-identical; the other eight
forms regress, often by extending ownership far enough to alter allocation
from the first vector-expression region. None recovers either remaining
scheduler window.

The ledger now contains 93 unique variants: 49 neutral, 41 degrading, and
three fuzzy improvements that retain documented metric tradeoffs. The canonical
lane remains at **97.57%** (`247/247`, prefix 126,
26 clean references). The retained source keeps the shared, independently
proven vector operator and exact instruction and reference counts; the
remaining travel/color and corner-scale reorderings are bounded VC6 scheduling
debt.

## 2026-08-09 primary cRStarManager::Init promotion

The primary matcher method is `cRStarManager::Init()`, symbol
`?Init@cRStarManager@@QAEXXZ`. Its final authored `AI()` call remains virtual
through the manager's slot-zero table. Only owner and method spellings changed:
the body remains at **97.57%**, 247/247, prefix 126, with all 26 references
clean. All seven mutation specs and the nine-record experiment ledger remain
byte-identical. Those records bound the tested source shapes, not future
native-backed hypotheses; their count does not close the lane.

## 2026-09-05 bounded source-expression probes

Seven vector-position and colour-scope combinations do not improve the 97.57% baseline. Named offsets and a shared colour local can be byte-neutral; the remaining call-argument/store scheduling is unresolved.

The recorded specifications and experiment receipts preserve these negative
results. They do not establish source exhaustion or compiler provenance.

## 2026-09-05 whole-function source-lifetime probes

Fifteen whole-entry variants combine typed allocation indexing, direct root/flag access, and call-local colors. None improves 97.57%, with all 26 references clean. The travel/colour argument schedule remains open.

## 2026-09-05 continued source-shape investigation

Two diagnostic XYZ constructor-body forms are non-improving. XYZ assignment is neutral and reversed assignment regresses. The shared vector header remains unchanged.

## 2026-09-05 shared vector operator ownership diagnostics

Four `whole-vector-operator-ownership-20260905-mutations.json` variants embed
an unchanged vector header control and move addition, subtraction, or both
from free const-reference functions to const members with identical explicit
result bodies. All are neutral in this caller. The same four-way replay in
S-bend, star-field initialization, CreateGolb, and exact LookAt also stays
neutral, with unchanged instruction counts, prefixes, and clean references.

These results do not independently prove free-versus-member authored spelling;
they show that this distinction does not explain the tested native differences.
No shared header or caller-specific operator implementation is changed.

## 2026-09-05 additional coupled source controls

Six explicit coordinate-construction combinations and six follow-up corner-value forms retain the shared vector header unchanged. Camera coordinate construction plus a named corner speed reaches 98.38%, 247/247 instructions, and 26 clean references, but moves the first mismatch from instruction 126 to 124. The new source still has four scheduling moves across travel/color setup and corner publication. It remains a diagnostic seed, not a retained gain. Travel coordinate construction regresses. Precision and destination-borrow follow-ups do not remove those remaining differences.

## 2026-09-06 division result ownership recovery

The scratch-local vector division still returned a three-argument constructor,
unlike the explicit-result addition, subtraction, and multiplication in the
shared vector header. Giving division the same ordinary result ownership
preserves all three scalar divisions and the by-value result, without changing
the shared operators, compiler profile, or caller's vector expression.

`vector-division-result-20260906-mutations.json` tests explicit-result and
copy-then-divide bodies, independently and with a named corner speed. The
explicit-result body alone improves **97.57% to 98.38%** (**840 to 847 / 861**
fuzzy bytes), retaining **247/247 instructions**, **prefix 126**, and **26 clean
references**. It makes the complete corner-scale load/add/multiply/publication
window exact. The native and candidate still allocate the same `0x60` frame.
This is a gain without the shortened prefix of the earlier coordinate-
construction seed or a caller-specific replacement of shared vector addition.

The full diff now contains only the travel-store/color-argument window.
Copy-then-divide regresses to 75.50%; adding a named corner speed to the retained
explicit-result body regresses to 97.98%. Neither is retained.

On the improved baseline,
`division-followup-travel-color-20260906-mutations.json` crosses named random
and complete travel values with named `Set` results and separate `Set`/copy
statements. All eight combinations were evaluated: five reproduce the new
baseline's exact code identity; three separate-Set/copy forms regress to
85.02%. No further source change is retained. These results constrain those
particular ownership forms, not other source shapes or compiler provenance.
