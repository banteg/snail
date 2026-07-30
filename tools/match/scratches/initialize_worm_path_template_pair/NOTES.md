# initialize_worm_path_template_pair @ 0x420170

This scratch reconstructs the worm attachment-path constructor and its generated
strip mesh using the shared native `AttachmentSample`, `Path`, and
`ObjectFaceQuad` owners.

Current focused result:

- match: **72.81%**;
- target/candidate instructions: **736 / 728**;
- common prefix: **0 / 736**;
- masked operands: **37 clean, 0 unresolved, 0 mismatched**;
- native/candidate local frames: **0x80 / 0x68**.

The zero common prefix is solely the honest frame-size mismatch in the first
instruction (`sub esp, 0x80` versus `sub esp, 0x68`), not a missing constructor
prefix. The following constructor stores and allocation call are strongly
aligned.

## Recovered behavior

The implementation covers the complete high-level body visible in the native
function:

- assigns kind `24`, clears mirror/exit state, selects 16 radial cells, a
  4-unit segment width/radius scale, 24 samples, and the 96-unit total span;
- allocates primary and secondary sample arrays and clears the runtime flag;
- initializes all 24 samples at y `0.49`, with z advancing by four units,
  identity transforms, unit lateral scale, and zeroed rotation/special fields;
- rebuilds forward/right/up basis rows for the middle sample range, preserving
  the distinct first-iteration identity path seen in the target;
- computes and normalizes primary and secondary deltas, then supplies the
  terminal `(0, 0, 1)` direction and four-unit length;
- allocates a 25-by-16 vertex grid, 768 double-sided facequads, and per-vertex
  colours on the strip mesh, with `OBJECT_FLAG_USE_VERTEX_COLOURS` selecting
  their grouped diffuse values and `OBJECT_FLAG_TEXTURE_TRANSFORM` selecting
  the renderer's authored U/V offset path;
- generates each tube row from the sample position and basis using sine/cosine,
  a radius of `4 * lateral_scale`, and an alpha wave of
  `0.5 - 0.5 * cos(2 * row_angle)`;
- extrapolates the terminal row from the previous row, scales vertices below
  y zero by `0.3`, and emits two opposite windings for every row/column cell;
- wraps the final radial column, assigns U coordinates from the 16-column
  fraction, advances V by `0.125` per path row, resolves the supplied texture,
  and calls `calc_path_length_z`.

The constructor and finalizer are intentionally declared `void`. The related
matched finalizer shows that the apparent non-void decompiler result is stale
EAX state rather than a source-level return value.

## Source-shape findings

The useful gains came from ordinary source spelling rather than stack padding
or compiler tricks:

- Direct sample-array expressions and repeated natural indices recover the
  native SIB/register plan better than long-lived sample aliases.
- A zero-based `middle_index` with `if (middle_index != 0)` recovers the native
  first-iteration branch and induction register.
- Direct primary/secondary delta loops preserve the native normalize-call
  layout.
- Scalar-left vector operators, plus real `up_radius`, `up_component`,
  `base_plus_right`, and `vertex` temporaries, substantially improve the x87
  tube-generation block.
- Keeping the ordinary vertex row as the fallthrough and the extrapolated row
  in the `else` branch gives the target's branch polarity.
- Converting the column once, writing colours inside each row branch, and using
  a real `lowered_y` temporary preserve native temporary lifetimes.
- The face loop works best with a two-iteration `side` loop and a direct
  `if (side == 0)` winding/UV branch.

Measured milestones from the focused pass were:

| Source-shape stage | Match |
|---|---:|
| Starter skeleton | 0.27% |
| Complete semantic first pass | 22.59% |
| Direct array/index and vector-temporary pass | 34.11% |
| Native-shaped middle branch | 36.63% |
| Direct delta and face-side loops | 46.06% |
| Zero-based middle induction | 51.82% |
| Direct vertex-grid indexing | 59.78% |
| Scalar-left vector expression shape | 67.17% |
| Named radius/y temporaries and direct texture call | 67.90% |
| Native vertex-row branch polarity | 72.28% |

## Residuals

The remaining mismatch is compiler shape rather than a known missing semantic
lane:

- The target reserves `0x80` bytes while this source naturally reserves
  `0x68`. The target keeps additional vector/x87 staging copies around the
  trigonometric expression.
- The candidate is 11 instructions shorter. The broad vertex-expression region
  is `target[461:525]` versus `candidate[460:518]` at 57.38%.
- The largest remaining tail is the face/UV loop,
  `target[556:736]` versus `candidate[549:725]` at 45.51%. It differs in
  temporary stack slots, register lifetimes, and a native parity-looking branch
  before the texture lookup.
- Both sides of that native texture branch ultimately pass the sole
  `texture_path` argument. Reproducing it with a redundant source branch is not
  justified and measured worse, so the clean direct call is retained.
- Some early sample loops still differ only in equivalent base/index operand
  ordering and spill-slot placement.

A by-value vector-operator experiment did recover the exact `0x80` frame, but
it lowered the full-function result to 66.85%, grew the candidate to 739
instructions, and introduced a masked sine/cosine alignment mismatch. It is
rejected rather than using frame size as a metric-only goal. Likewise, an
explicit duplicated texture-parity branch fell to 62.27%; face aliases,
alternate `for` spellings, and several operator-return variants were neutral or
regressive.

## 2026-06-20 shared type pass

The sample and owner overlays now use the shared `AttachmentSample` and
`Path` declarations from `track_attachment_types.h`. The
matcher stayed at the accepted baseline:

```text
match: 72.28%
target: 736 insns, candidate: 725 insns
masked operands: 37 ok, 0 unresolved, 0 mismatch
```

## 2026-07-14 facequad ownership pass

The scratch now uses the `Object::facequads` element type directly instead of a
duplicate `WormFaceQuad`. The shared `ObjectFaceQuad` exposes both its canonical
`uv[4]` array and the native constructor's flat `u0/v0` through `u3/v3` view.
That preserves the source shape identified by the earlier rejected indexed-UV
experiment while recovering the real allocation owner. The 16-bit constructor
store uses `header_word`, rather than the byte-sized runtime `flags` view.

The focused result is byte-for-byte unchanged from the accepted baseline:

```text
match: 72.28%
target: 736 insns, candidate: 725 insns
masked operands: 37 ok, 0 unresolved, 0 mismatch
```

## 2026-07-17 Path ABI closure

The guarded analysis replay now uses `void __thiscall Path*`, consistent with
the authored member, `cRPath::BuildWorm(char*)`, and the native `ret 4` calling
shape. Recreating the stale Binary Ninja function also removes its exact
user-defined stack-8 `arg2`: all native callers pass only `texture_path`, while
the old variable was a pinned decompiler artifact. Focused matching remains
72.32%, 727/736 instructions; no source-shape padding or synthetic argument
was introduced.

## 2026-07-20 two-stage basis and mesh lifetimes

Live Binary Ninja inspection recovers fifteen complete owners across Worm's
distinctive two-cross basis construction and cylindrical strip mesh. Each side
keeps its basis-up vector and reloads the enclosing sample for both cross
products; the tail owns both terminal deltas, the lateral-scale/basis-up mesh
sample, its basis-right reload and position vector, the ordinary and copied
terminal vertices, and one facequad cursor reused across the winding branch.

The two byte-biased forward-vector candidates were rejected because typing
them introduced eight backward `__offset` expressions in adjacent position
reads. The retained transaction previews with zero offsets. Matcher source and
bytes remain unchanged at the honest 72.32% frontier (727/736 instructions,
37 clean masked operands); this is ownership recovery, not matching coercion.

## 2026-07-26 branch-local UV completion

The native face loop computes one `ObjectFaceQuad*` cursor before the winding
branch and keeps that owner live through both arms. Each arm then completes its
own fourth UV pair: the front path writes `face->v3` at `0x420bc7`, while the
back path writes it at `0x420bef`. Moving that final V store into the two
authored branches raises focused matching from 72.32% to 72.81% and grows the
candidate from 727 to 728 instructions, with all 37 masked operands still
clean.

The parity-looking native texture branch still supplies the same sole
`texture_path` on both sides. Reintroducing it explicitly now falls to 58.38%
(737 instructions, 0x6c frame, 35 clean operands), so the direct lookup remains
the honest source. Explicit right-radius/right-component names compile
byte-identically, while a copied sample position and declaration-then-
assignment for the final vertex regress to 67.85% and 68.49% respectively;
none are retained.

## 2026-07-26 colour-owner propagation check

Android proves the exact colour allocator owner as
`cRObject::RequestColours()`, and the allocator itself is now written as an
exact `Object` member. Propagating member-call syntax into this unresolved
constructor is nevertheless rejected for now: VC6 broadly changes the register
and temporary schedule while leaving the aggregate score coincidentally
unchanged. The local fastcall-compatible declaration therefore remains solely
to preserve this caller's better native source shape; it does not challenge the
recovered callee ownership. Restoring it returns the accepted 72.81%, 728/736
baseline with all 37 operands clean.

## 2026-07-27 mobile-backed path-kind ownership

The matcher now carries the guarded Windows `PathTemplateKind` enum used by the
analysis type replay, and `Path::kind` owns that type instead of an anonymous
integer. Exact Android/iOS `cRPath::Build*` symbols corroborate the constructor
identities, including `cRPath::BuildWorm(char*)`; the numeric discriminants
remain Windows-derived because the mobile ports do not share this ABI.

All proven constructor stores and downstream comparisons now use the named
Windows members. Dynamic LoopBow/P variants remain explicit enum conversions
rather than receiving invented labels. Representative focused recompilation is
codegen-neutral: Worm stays at 72.81% (728/736, 37 clean operands), FollowState
at 72.89% (698/726, 63 clean operands), and the projection consumer remains
exact at 100.00% (106/106).

## 2026-07-28 mobile-backed control ownership

The exact Android and iOS `cRPath::BuildWorm(char*)` bodies independently
preserve the portable 24-sample prefix also present in Windows: entrance
samples 0 through 3, exit samples 20 through 23, a middle 4-through-19 basis
pass with a distinct first iteration, and a fresh delta pass through
`segment_count - 1`. The ports end after path-length calculation and do not
contain Windows' cylindrical mesh tail, so no mobile claim is made for those
mesh controls.

Windows MLIL supplies the exact native definitions and 0xa8-byte cursors for
`entrance_sample_index`/`entrance_sample_offset`,
`exit_sample_index`/`exit_sample_offset`,
`middle_index`/`middle_sample_offset`, and
`delta_index`/`delta_sample_offset`. Transactional preview also proves that
the exit counter's EBX lifetime and its x87 stack spill are one logical
source variable. The preview produces four clean named loops with no new
`__offset` expressions; matcher source and bytes remain unchanged at the
honest 72.81% frontier.

After the control splits, Binary Ninja folds the already-current basis-up,
terminal-delta, and ordinary mesh-vertex locals into five address-pinned
`Vec3` aggregate assignments. A post-export replay confirms that all fifteen
earlier user-owned lifetimes remain current in the database. Health therefore
checks the five exact Windows aggregate sites rather than requiring stale
temporary-name rendering.

The IDA 9.4 refresh independently renders the same 0-through-3,
20-through-23, 4-through-19, and `segment_count - 1` Windows ranges. It also
replaces the stale tracked `strip_mesh`/non-void artifact with the already
proved `Path*`, `bod.object`, and void finalizer ABI. A paired IDA health check
now pins that second-opinion owner and control shape.

## 2026-07-30 bounded Windows mesh-tail pass

The redundant-looking native texture branch is now semantically grounded:
LoopOut, Hump, Dump, Screw, LoopBow, Twister, Wibble, and other sibling
constructors preserve the same checkerboard `(column ^ row) & 1` generator
branch even when each arm passes the same texture argument. Six Worm source
spellings restore that behavior, but none can be retained while the earlier
mesh frame remains wrong. Duplicated-call forms fall to 58.38-58.42%; selecting
a path before the common lookup reaches 68.35%.

Seven vector-staging variants confirm that the retained ordinary-row
expression is already the best natural schedule. Explicit right-side
temporaries are byte-identical; component-wise, copied-position, in-place, and
shared-angle forms regress. Five sibling-style face-index variants, including
the family’s `(unsigned short)width_cells` multiplication vocabulary, are
byte-identical at 72.81%.

The new ledger contains 18 unique variants: zero better, six neutral, and
twelve worse, with no repeats or tradeoffs. Three consecutive non-improving
sweeps mark this region stalled. The next justified attempt must recover the
native `0x80` vector/x87 lifetime first and then combine it with the proven
checkerboard branch; padding or branch-only byte shaping would be
fakematching.
