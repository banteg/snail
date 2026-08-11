# apply_distort_to_object

`Object +0x80` is a five-float, 0x14-byte `Distort` subobject used only
when the object has dynamic vertex data (`flags & 0x800000` in
`refresh_object_vertex_buffer`). The first three floats are the recovered
controls below; the final two remain unknown.

- `z_wave` offsets vertex Y from absolute Z with a sine envelope over the
  object's Z bounds.
- `y_squash` stretches X while squashing Y around `bounds_min.y`.
- `xyz_scale` grows X/Y slightly while squashing Z.

Every active pass writes into `copied_vertices`; later passes read from that
copy. If any pass ran, `vertices` is redirected to `copied_vertices` and the
simple face-quad normals are recomputed.

Current scratch status:

- 95.43% instruction match, 197 target insns vs. 197 candidate insns, up from
  52.15% and 198 candidate instructions.
- Masked operands: 26 ok, 0 unresolved, 0 mismatch.
- Native repeatedly loads each bound before and after its x87 comparison and
  reloads the selected bound after the max comparison. That is the VC6 shape
  of expanded `ABS_FLOAT` and `MAX_FLOAT` expressions, not stored min/max
  temporaries.
- The Z-envelope pass copies through the chained `source` view, but its
  absolute-Z input reloads `object->vertices`. Expressing that owner distinction
  recovers the native induction registers and exact instruction count.
- All three passes use direct indexed writes into `copied_vertices`; removing
  synthetic per-iteration `in`/`out` pointers and phase locals recovers the
  native loop scheduling.
- The final pass is positively guarded by `xyz_scale != 0.0f`, with the
  no-distortion return in the `else` arm. This reproduces the native fallthrough
  and post-pass jump.
- The remaining nine differing instructions are only equivalent base/index
  orderings in scale-1 x86 SIB addresses. No ownership, control-flow, call, or
  data-flow mismatch remains, so the source deliberately avoids artificial
  pointer arithmetic to choose an encoding.
- 2026-06-21 owner-local retry: adding an explicit `Distort* self = this`
  and reading all three distort fields through it is codegen-neutral at 52.15%.
  VC6 still anchors `this` in `ebp` instead of native `edi`; a simple owner
  name does not free `ebp` for the loop/index role.

## 2026-07-15 receiver replay

The repeatable Binary Ninja sync now records both real owners:
`Distort*` is the `this` receiver and `Object*` is the borrowed geometry
target. The refreshed artifact names all three distortion controls, the Object
bounds/live/copy views, and the final simple-normal rebuild. This replaces the
old `int(float*, float)` interpretation without changing the honest 95.43%
matcher frontier or its nine equivalent SIB base/index order residuals.

## 2026-07-18 checked-in IDA owner closure

The IDA replay now owns this helper by address as well as name, verifies the
0x14-byte `Distort` and 0xdc-byte `Object` layouts before applying the
prototype, and refreshes `refresh_object_vertex_buffer` as its sole caller.
The tracked IDA artifact now exposes all three distort controls, the borrowed
live vertex view, the owned copy buffer, bounds, and final normal rebuild.

No matcher source changed. Focused Wibo remains `95.43%`, exactly `197/197`
instructions with 26 clean masks; all residuals are still equivalent x86 SIB
base/index encodings rather than ownership or behavior differences.

## 2026-07-25 borrowed vertex-z cursor replay

All three distortion passes carry the interior `Vec3::z` address while
reading x/y/z and advancing by exactly `sizeof(Vec3) == 0x0c`. The
analysis-only `ObjectVertexZCursorView` records that borrow;
`Object::vertices` and `Object::copied_vertices` remain the only buffer owners.

Binary Ninja has stable standalone locals for the Z-wave and XYZ-scale walks
at register identities `(177, 69)` and `(562, 67)`, so the guarded replay names
and types those two cursors. Its Y-squash ECX walk spans two split definitions;
both merge orientations were tested under undo and degraded HLIL to an
uninitialized `void*`. That lifetime deliberately remains automatic rather
than checking in misleading analysis.

Hex-Rays independently exposes all three locals. The IDA replay binds their
actual definition addresses `0x41ab02`, `0x41abe0`, and `0x41ac83` as shifted
borrowed pointers and verifies every name/type readback. The tracked artifact
therefore distinguishes the Z-wave, Y-squash, and XYZ-scale source walks
without changing the matcher. Focused Wibo remains honestly at `95.43%`,
`197/197` instructions, with the same nine equivalent SIB encodings.

## 2026-07-26 Android authored owner

Android exports the exact-demangled `cRDistort::Build(cRObject*)`. Its body
confirms the five-float `cRDistort` owner, the borrowed render-object argument,
the three leading optional controls, and the same ordered rule that each active
pass writes the owned copy bank and feeds that bank into the next pass. This
turns the Windows owner/argument model from inference into cross-port
provenance.

The ports deliberately diverge after that shared core: Windows uses its
recovered object bounds in the envelopes and rebuilds simple face normals after
redirecting the live vertex view, while Android's rendering path has a
different tail. No mobile offset or tail is transplanted. The honest Windows
frontier remains 95.43%, 197/197 instructions, with only the nine equivalent
SIB base/index encodings outstanding.

## 2026-07-28 dual-mobile class identity

Android's exact `cRDistort::Init` and `cRDistort::Build(cRObject*)` symbols,
plus iOS's exact `cRDistort::Init` and `cRDistort::BuildMatrix` symbols, recover
the authored class identity independently of the Windows machine-code work.

The three ports agree on the five-float extent, but recovered consumers touch
only `z_wave`, `y_squash`, and `xyz_scale`. The `+0x0c` and `+0x10` words are
initialized and otherwise unread, so they remain explicitly unknown rather
than being named from constants or neighboring mobile code. Windows remains
authoritative for its embedded `Object +0x80` layout and Build behavior.

## 2026-07-29 primary cRDistort ownership

The matcher now emits `cRDistort::Build(cRObject*)` directly and embeds the
primary `cRDistort` type at `cRObject +0x80`. The analyzer-facing `Distort` and
`ObjectDistort` spellings remain compatibility aliases, so replay scripts do
not churn. Binary Ninja confirms the sole Windows caller forms ECX as
`object + 0x80` and passes the same object on the stack. The ownership change
leaves the honest frontier at 95.43%, 197/197 instructions and 26 clean
relocations; no mismatch is hidden.

## 2026-07-29 destination-SIB compiler boundary

Three recorded mutation sweeps evaluated 43 unique source variants around the
nine remaining stores. None improved the 95.43%, exact 197/197-instruction,
prefix-58 baseline: 31 variants were byte-identical and 12 degraded.

- The Z-wave sweep changed each destination lane independently through pointer
  addition in both orders, index-first subscripting, explicit dereference,
  address-of-element, and byte-offset forms. All 18 variants compile to the
  retained bytes, including every deliberately reversed expression tree.
- The Y-squash sweep tested pass-local destination pointers, const pointers,
  pointer references, member pointers, explicit object ownership,
  per-iteration element pointers/references/byte offsets, and an incremented
  destination cursor. The reference, member-pointer, and object-owner forms are
  neutral. Materializing a destination or element cursor perturbs allocation
  from the prologue and regresses; none changes an isolated SIB role.
- The XYZ-scale sweep covered signed, unsigned, long, and register-qualified
  indices; equivalent positive-entry guards; and eight increment/backedge
  spellings. Ten are neutral and six regress. Unsigned comparisons alter the
  branch opcode, while stronger lifetime/control rewrites disturb otherwise
  exact scheduling.

The experiment ledger records three consecutive non-improving sweeps. Native
and candidate still differ only where scale-one x86 SIB permits
the same two registers to exchange base and index roles. All surrounding
instructions, effective addresses, control flow, and 26 masked operands agree.
Changing the honest direct indexed stores would therefore add source
artifice without recovering evidence of a different owner or algorithm.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and verified
Android `cRDistort::Build(cRObject*)` body establish the five-float Distort
owner, borrowed Object, three ordered optional controls, bounds, live and copy
vertex banks, chained-pass policy, and final Windows normal rebuild. The target
and candidate both contain 197 instructions and all 26 references are clean.

The nine differing instructions only exchange base and index registers in
scale-one SIB encodings with identical effective addresses. They do not change
data flow, behavior, or ownership, so the residual is compiler-only and the
old sweep streak has no classification force.
