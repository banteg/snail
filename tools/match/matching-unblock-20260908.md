# Source ownership, native storage, and executable matching controls

The immediate blocker was the gap between address-compatible scratches and
source objects that can be linked and executed together. Individual instruction
matches do not establish one C++ API, one storage definition, or ownership of
compiler-generated helpers. This pass finishes and verifies the allocator and
transform work already present in the checkout, repairs more ABI boundaries,
and adds checks that expose these gaps directly.

The port board remains **593/662 exact functions**, **137,047/294,937 exact
curated bytes**, and **88.41% fuzzy**. No additional function is promoted to
exact in this pass. The progress below is separately measured integration,
data, ownership, and behavioral evidence. Original translation-unit boundaries,
full-executable layout, and public linked/data credit remain unclaimed.

## Concrete source and ownership changes

* `tMatrix::Orthoganalize` now calls the recovered const-reference
  `tVector::Cross` API. Its old pointer-parameter compatibility spelling passed
  native reference normalization but had no linked implementation. All 26
  instructions and five references remain exact.
* BOD list methods use the reporter's C ABI through the narrow `rerror.h`. The three list
  bodies preserve every object-code byte; four relocation symbols change to
  the real `_report_errorf`. A reverse link with one old object fails with the
  obsolete decorated C++ symbol. The shared header reaches 393 scratches,
  which were included in the complete native regression pass.
  Exposing the whole debug header also introduced overload conflicts in the
  runtime constructor and score display. Converting the constructor's calls
  directly to the variadic overload regressed it to 89.75% and 298 instructions;
  that change was rejected. The narrow declaration preserves both exact callers.
* The quaternion constructor uses the same shared C reporting ABI and named
  matrix fields. Its native result stays **92.47%, 186/186 instructions,
  prefix 42, 23 clean references**. It can now link to the actual recovered
  reporter and square-root implementation.
* `load_galaxy_layout` expresses both preprocessing bounds through their
  owning arrays and the `y` field offset. The original hard-coded image
  addresses become real `DIR32` relocations at object offsets `0x28` and
  `0x61`. It retains **99.14%, 233/233 instructions, prefix 194, 42 clean
  references**. Only the native route cursor's precise `+0x32c` sentinel is
  added to the reference contract; the 101-point owner remains `0x328` bytes.
* The Windows allocator is an **8-byte header followed by 15,000 twelve-byte
  records**, each beginning with an unnamed word, pointer, then size. Its
  **180,008-byte** extent ends at `0x53c7e8`, where the music-buffer owner
  begins. Native Windows operands and both Android ELF symbol sizes support
  the correction. The last valid allocation preserves the unnamed word and
  a neighboring canary. The shipped post-store overflow check is preserved;
  the test uses valid indices and does not claim overflow safety.

See the [allocator and BOD evidence](bod-list-and-allocator-ownership-20260908.md),
[galaxy cursor evidence](scratches/load_galaxy_layout/NOTES.md), and
[quaternion evidence](scratches/initialize_quaternion_from_matrix/NOTES.md).

## Linking and execution

The [receipt summary](linking-progress-20260908.json) deduplicates overlapping
groups by native address. They contain **65 distinct exact recovered
functions / 5,222 native body bytes**, up from the prior S-bend group's 44
exact functions / 2,904 bytes. The added transform and BOD coverage accounts
for **21 functions / 2,318 bytes**. These are separately linked groups, not a
claim that one rebuilt game executable contains all 65 functions.

| Group | Exact functions | Exact native bytes | Runtime checks |
| --- | ---: | ---: | ---: |
| Math | 14 | 1,118 | 23 |
| Allocator | 11 | 643 | 24 |
| Mesh storage | 21 | 1,270 | 21 |
| Path nodes | 31 | 2,150 | 15 |
| Transforms | 32 | 3,096 | 40 |
| BOD lists | 5 | 421 | 21 |
| S-bend dependencies, plus one diagnostic partial builder | 44 | 2,904 | 60 |

All **204 assertions** pass in seven independent positive processes. Each
group also runs a separate deliberate corruption; all seven controls fail
exactly one assertion and return failure. Runtime scopes are recorded in
the receipts. Linked-but-unexercised functions are not silently treated as
behaviorally covered by an unrelated fixture.

The verifier now checks:

* Every selected function against the original image using the immutable
  object copy that is actually linked, independently of the shared scratch
  build cache.
* All linked `DIR32` and `REL32` relocations, including static data. Static
  names require a proven input owner or an unambiguous owner in the map;
  map entries must agree with the linked COFF table.
* Complete source code sections, including Cross's compiler-generated
  destructor helper, and complete initialized/uninitialized source data
  sections. Missing anchors remain explicit debt. The seven completed
  groups have **zero unverified source code/data sections**.
* Real PE section extents, rather than accepting bytes in image alignment
  padding. COFF BSS parsing now creates zero-filled virtual storage instead
  of reading the object-file header as an initializer.
* Compiler, nested support includes, source/config, native manifest/image,
  linker, runtime library, runner, copied objects, executable, and map
  identities. Changing inputs invalidates the receipt. Concurrent writers
  to one integration output directory are rejected.

The complete validation also reproduced a separate shared-cache race: parallel
status/report builders deleted or read one another's `scratch.obj`. Compilation
now uses per-scratch thread/process locks, a private output directory and atomic
publication. Failed or input-invalidated builds leave the previous successful
object intact. Scoring and code fingerprints use the same captured bytes.
Nine deterministic tests cover threads, processes, forked locks, failed builds,
changed inputs and replacement between scoring and fingerprinting.

## Data evidence

Eight selected owners reproduce **278,324 bytes of initial native storage**:

| Owners | Bytes |
| --- | ---: |
| Sine/cosine arrays, random table and cursor | 98,304 |
| Allocation stack and total-byte counter | 180,012 |
| Two one-entry callback-table projections | 8 |

This compares source-built storage to the original PE, rather than merely
showing that the new linker preserved its own inputs. Each contract requires
the known native extent, exact accessor/constructor witnesses, and the complete
compiler-emitted `sizeof` value. Size metadata is integration evidence and
earns no native data credit itself. In particular, it separates the allocator
counter's four bytes from the next object's four bytes of alignment.

Initial BSS must be all zero. Callback pointers must be emitted relocations
to exact recovered function entry points and must equal the original pointers
after translating those entry-point addresses. Nonzero BSS, oversized owners,
wrong pointer destinations/addends, and overlapping owners are rejected.
The two tables remain explicit callback-table projections, not recovered
compiler-generated C++ virtual-table ownership. These selected spans do not
establish original object ordering, full data coverage, or runtime-state equality.

## Native behavioral discrimination

The new quaternion oracle compares ten trace/dominant-axis/tie/non-symmetric
matrix fixtures, yielding **160 identical output bytes** from recovered source
and relocated original code. Deliberately replacing the shipped fallback
`w` sums with conventional differences fails both native and source controls.
This is concrete evidence to preserve an unusual shipped formula. It does not
resolve the two remaining instruction continuations or award exactness.

The existing S-bend oracle still produces **18,204 identical geometry bytes**
across four fixtures. Extracted original code remains confined to diagnostic
oracle objects; it is never included in source matching or linked credit.
Four additional `ReleaseWeapons` component-lifetime hypotheses regressed and
were recorded without changing the canonical source.

## Reproduce

With the existing VC6 runtime import library, choose any group from the table:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run tools/match/link_path_math.py \
  --group transforms --run --out artifacts/match/unblock-transforms \
  --runtime-library /path/to/vc6/MSVCRT.LIB
```

S-bend additionally requires `--diagnostic-sbend`. The independent native
comparisons use `tools/match/compare_sbend_native.py` and
`tools/match/compare_quaternion_native.py`; their `--help` output documents
the runtime-library and output arguments.

`uv run tools/match/link_frontier.py` builds a source-object dependency report
from actual COFF relocations. It separates literal symbol resolution from
explicit native aliases, heuristic canonical-name candidates, missing storage,
runtime imports and unresolved COMDAT selection. It considers all 785 canonical
objects and 12,274 selected-function relocations. Supporting integration storage
and auxiliary-body edges are explicitly outside this report's linkage scope.

An address-compatible alias can name a distinct folded method, so the tool
never treats matching native addresses as authorization to replace receiver
classes. Examples include Splash/GUI `Open` and several no-op constructors.
The current scan retains 12 explicit-alias mismatch references, 610 heuristic
owner candidates, and 2,980 missing-storage references. These are dependency
edges, not counts of broken functions. Inspection of the RText edge found a
documented limitation in the nominally exact callee: it uses a pointer return
to obtain VC6's register allocation although the recovered contract is void.
The correct void caller was preserved; spreading the callee workaround would
conceal the source-recovery debt.
The next large storage gaps include the game root, object lists, rendering
device and runtime configuration. The largest heuristic API groups include
`Identity`, `Cross`, and the reporting functions. Each needs an actual source
ABI/owner contract and whole-function checks before a link migration.

The remaining work is to close additional real symbol/storage boundaries,
recover the remaining source lifetime and continuation shapes, and establish
original TU/initialization ordering. A tested linked dependency group and an
original-code behavioral oracle provide stronger controls for that work than
another unmotivated source permutation sweep.

Final validation: **886 tests pass**; the full status check, exact-reference
audit, extern lint and strict experiment/spec audit pass. The refreshed public
report validates **705/2,261 function owners and 151,309/596,823 native code
bytes (25.35%)**. Its code denominator includes libraries and unclassified code;
the smaller port-relevant board above is a different measure. Public linked
credit remains zero, and public data progress remains omitted.
