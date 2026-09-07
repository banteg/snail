# initialize_intro_screen @ 0x4191e0

Starter scratch for the intro/credits crawl initializer.

Models the SpaceRed backdrop/music setup, render matrix/FOV setup, mouse release,
script parsing between `Text Start:` and `Text End:`, image records beginning
with `*`, text glyph records, and duration-derived per-renderable scroll step.

Current result: 38.30%, 304/521 candidate/target instructions, 40 clean masked
operands, one unresolved masked operand, and six masked operand mismatches. The
`0 < count` spelling on parsed text lines is required for the native glyph-count
branch/register shape; the older `count > 0` gate regressed to 26.42%.

Expected residuals:
- renderable/BOD layout is scratch-local and only partially named;
- list insertion and object-geometry vertex edits are semantic but incomplete;
- image and glyph setup use the real helpers but still need exact object-slot
  offsets before this can be promoted beyond a relationship scratch.

## 2026-07-11 full intro runtime ownership and field correction

- `Logo` is now the exact `0x25218`-byte root owner at
  `GameRoot +0x4f400`: a `0x18`-byte state header, 1024 `0x90`-byte crawl
  LogoLetters, and 32 `0x90`-byte image donors. The second bank begins at
  receiver `+0x24018`, and the complete object ends exactly at
  `cRSubGame +0x74618`.
- `LogoLetter` is shared across its exact constructor, pinned updater,
  intro initializer, teardown, constructor loop, and logo loader. It owns the
  inherited `RenderableBod` through `+0x7f`, velocity at `+0x80`, and the
  glyph/image marker at `+0x8c`.
- The old starter scratch based position, color, and object reads `0x18` bytes
  too late, treated the 32-slot logo bank as a four-byte pointer array, and
  wrote the final velocity vector one record beyond the active renderable.
  Typed field access now lands on transform position `+0x68`, color `+0x28`,
  object `+0x24`, velocity `+0x80`, and logo-bank object `+0x2403c + n*0x90`.
- Native mutates `renderable_count +0x14` during parsing and uses it for both
  bank indices. Removing the scratch-local counter recovers that ownership and
  materially improves the stream. The initial step is the target's exact
  `1/600`, and the shared blank buffer plus native virtual update dispatch are
  now explicit.
- The small source helper is force-inlined because the native body contains
  the list/link, setup, and callback sequence in both image and glyph paths;
  this restores body shape without a compiler barrier or dummy dependency.

Focused Wibo now reports **41.91%**, `400/521` candidate/target instructions,
with 47 clean masked operands and four alignment-driven mismatches. The prior
starter was 38.30%, `304/521`, with 41 clean operands, one unresolved operand,
and five mismatches. Remaining debt is dominated by native's separately
authored image/glyph setup and stack-local scheduling, not unknown slot offsets.

## 2026-07-12 font3d consumer and image-record recovery

- The two raw font globals were false views. `0x7770e8` is the shared
  `g_font3d_scales[128]` cache, and `0x77550c + slot*0x38` is
  `g_font3d_bods[slot].object`, the borrowed Object lane inside the fixed
  `BodBase` array.
- Image records do not index `logo_renderables` by the total crawl-renderable
  count. Native seeds a separate cursor at the first logo-bank Object lane and
  advances it by one `0x90`-byte `LogoLetter` only after an image.
  Glyph records leave that donor cursor untouched.
- Image and glyph setup are separately authored in native code. Expanding the
  old shared helper recovers their different ordering: images bind their
  texture before matrix setup and resize geometry before the velocity/update
  callback, while glyphs perform their second font-slot lookup only after the
  callback to advance the horizontal cursor.
- Typed `Object::vertices` access exposed a concrete source bug in the starter:
  it omitted vertex 2 x and wrote the final three values into the wrong float
  lanes. The recovered quad sets x/z for all four corners to `+/-width/2` and
  `+/-height/2`, matching all eight native stores without a nullable vertex
  branch that native does not have.
- The final scroll pass assigns a single `Vector3(0, 0, step)` value across the
  active bank, and the list insertion is expressed with native's empty-head
  fallthrough. Both are ownership/control-flow facts rather than scheduling
  shims.

Focused Wibo now reports **88.23%**, `524/521` candidate/target instructions,
prefix 88/521, and 66 clean masked operands with no unresolved or mismatched
names. The remaining delta is dominated by three compiler instructions and
stack-slot choices for the image dimensions, loop bound, and temporary vectors;
those are left visible rather than forced with dummy locals or aliasing tricks.

## 2026-07-12 glyph countdown lifetime recovery

- Native proves the parsed character count is positive, snapshots it into a
  separate stack countdown, and enters the glyph construction loop without a
  second zero test. Keeping the line-scan count distinct from the destructive
  render countdown recovers that authored lifetime and removes the candidate's
  redundant entry branch.
- Focused probes confirmed that folding the two lifetimes back together, or
  spelling the loop as a direct `do/while`, perturbs the wider allocator and
  stack frame. The distinct countdown is the smallest semantic source shape
  supported by the target; no volatile barrier, padding local, or dummy data
  dependency is used.

Focused Wibo now reports **88.31%**, `523/521` candidate/target instructions,
prefix 88/521, and 66 clean masked operands with no unresolved or mismatched
names. The two remaining candidate instructions are honest allocator residuals:
early cleanup of the two image-dimension parser arguments and a final reload of
the owned file buffer after the velocity-copy loop consumes `esi`.

## 2026-07-12 authored cRLogo correction

- The symbol-bearing iOS body identifies this exact filename-taking lifecycle
  method as `cRLogo::Init(char*)`, not `cRIntro::Init()`. It independently
  performs the same IntroText music, SpaceRed backdrop, star unhide, Text
  Start/Text End parse, glyph/image construction, Duration pass, and final
  `RShellMemoryFree`. The no-argument `cRIntro::Init()` body instead constructs
  an unrelated border-heavy intro screen.
- The root owner is therefore promoted to `Logo`, with 0x90-byte `LogoLetter`
  entries and a compatibility alias for the earlier synthetic type name. The
  Windows layout remains locally proven; mobile uses different BOD prefixes,
  row counts, and field offsets.
- `RShellMemoryFree(void*)` is void, and both Windows callsites discard EAX.
  `initialize_intro_screen` now has the real void member contract and ends with
  a plain free call. Focused Wibo remains honestly unchanged at 88.23%,
  524/521, with 66 clean operands.

## 2026-07-13 shared BOD AI dispatch

The two LogoLetter slot-zero calls now use the shared, 4-byte
`BodAiDispatch` ABI overlay instead of a scratch-local virtual class. The
overlay is cast-only because LogoLetter retains its explicit cRBod-compatible
vtable word and must not acquire a second C++ vptr. Focused Wibo remains
88.31%, 523/521 instructions, prefix 88/521, with all 66 operands clean.

## 2026-07-13 root and active-list ownership

- The SpaceRed landscape, backdrop, border manager, star field, and mouse
  lifecycle now flow through their canonical `GameRoot` members. The two
  formerly raw player writes are `players[0].transform` and the owned camera's
  `fov_degrees`, closing the root-side scene setup without a byte-offset view.
- LogoLetter insertion now reuses the shared force-inlined
  `GameRoot::active_bod_list.add_bod` operation. The emitted list splice is
  unchanged, but the source no longer duplicates `BodNode` link offsets or
  reconstructs the root list head at `+0x5ac`.
- The ownership cleanup is codegen-neutral: focused Wibo remains 88.31%,
  523/521 instructions, prefix 88/521, with all 66 masked operands clean. The
  two documented allocator instructions remain visible rather than being
  forced through synthetic lifetimes.

## 2026-07-23 script, buffer, list, and velocity lifetimes

- `load_file_bytes` returns the allocated intro script owner. The original
  EAX definition and its retained EDI copy are now separately named
  `loaded_script_bytes` and `script_bytes`; the latter reaches the final
  `free_tracked_memory` call without a generic `void*` lifetime.
- The image name and `"Intro/%s"` texture path are independently bounded
  128-byte stack arrays. Their typed ownership also lets the recovered
  variadic `sprintf` ABI show the image-name argument directly.
- Image and glyph construction each splice a borrowed pair of `BodNode*`
  values through the process-owned active-BOD list. These are distinct reload
  lifetimes, not a new list owner or shared synthetic insertion variable.
- Native's final EAX cursor begins at `LogoLetter::velocity` and advances by
  one full `0x90`-byte letter record. The checked-in
  `LogoLetterVelocityCursor` is an analysis-only projection with a leading
  `Vec3`; the current element remains a direct `Vec3*`.
- A direct `Vec3*` cursor was rejected because Binary Ninja rendered the native
  stride as `velocity_cursor[0xc]`. Splitting and merging the surrounding EAX
  definitions also degraded the loop to an undefined integer pointer. The
  remaining partial LogoLetter stores stay unresolved instead of introducing
  an unsupported overlay.

This is codegen-neutral ownership recovery: focused Wibo remains **88.31%**,
`523/521` candidate/target instructions, prefix 88/521, with all 66 masked
operands clean.

## 2026-07-27 line-scan lifetime order

Windows initializes the per-line glyph count in `EDI`, reuses that same zero
to initialize the width accumulator, and only then snapshots the line cursor.
Declaring those three owners in that order recovers the exact loop-entry
sequence. The verified Android and iOS `cRLogo::Init(char*)` bodies preserve
the same distinct count, width, and line-cursor roles even though their later
mobile-only logo batching diverges from Windows.

Focused Wibo rises from **88.31%** to **88.89%** (`523/521`, prefix `88/521`)
with all 66 masked operands still clean. Separate image-dimension declarations
and a wider image-position lifetime were byte-neutral and were rejected; the
remaining two candidate instructions are still the honest parser-argument
cleanup and final script-buffer reload residuals.

## 2026-07-29 two-instruction residual audit

The focused result remains **88.89%**, `523/521` instructions, prefix
`88/521`, with all 66 masked operands clean. Three recorded mutation sweeps
bound the two excess candidate instructions:

- six declaration, assignment, comma-expression, and initializer forms for
  the image width/height parser results were all byte-identical; none delayed
  VC6's eight-byte argument cleanup into the following `sprintf` cleanup;
- the four well-typed loaded-buffer owner/view combinations were
  byte-identical, while the four deliberately unmatched matrix combinations
  failed to compile as expected; none preserved the final free argument in a
  register through the velocity loop;
- indexed, pointer-`while`, countdown, end-pointer, and pointer-`for` velocity
  loops were compiled. Indexed and pointer-`while` forms were byte-identical;
  the other three regressed by roughly 8, 25, and 29 weighted bytes.

The two residual instructions are therefore bounded to whole-function stack
cleanup and register allocation. The retained source is the clearest authored
form supported by the Windows and mobile bodies; no alias-only owner, volatile
qualifier, dummy dependency, or raw cursor projection is kept.

## 2026-08-09 authored owner promotion

The primary matcher method is `cRLogo::Init(char*)`, symbol
`?Init@cRLogo@@QAEXPAD@Z`. The stable `initialize_intro_screen` harness name and
the existing `LogoLetter` compatibility spellings inside the retained body are
retained so all three historical mutation anchors remain byte-identical. No
shape search was needed for that ownership-only change. Focused matching is
unchanged at **88.89%**,
`523/521`, prefix `88/521`, with all 66 references clean.

## 2026-08-12 recovery classification

The current Windows match, verified Android/iOS `cRLogo::Init(char*)` bodies,
and live Binary Ninja readback account for the complete lifecycle: root scene
setup, script ownership, text/image parsing, separate image-donor and glyph
construction paths, active-list insertion, object/vertex ownership, duration
scaling, the sequential `LogoLetter` velocity pass, and the final free. The
`Logo` receiver and all 66 audited references are clean in the current
artifacts.

The two excess candidate instructions are the already-isolated parser argument
cleanup and final script-buffer reload. They are allocator residue, not missing
authored behavior or ownership. Recovery is `semantic-complete` with compiler
residue.

## 2026-09-05 whole-function source-lifetime probes

Eleven combined final velocity-copy and per-glyph position variants test indexed copies, float-pointer constructors, and inline vector construction. None improves 88.89%. Direct indexed copies and per-glyph construction are neutral, while other forms regress. The parser/stack and final buffer lifetimes remain unresolved.

## 2026-09-05 whole intro object ownership probes

Fifteen combinations of indexed image donors, indexed final velocity
publication, aggregate velocity initialization and indexed glyph traversal
do not improve 88.89%. Donor and final velocity indices are neutral; the
other forms regress. Canonical source is unchanged.

## 2026-09-05 additional operation-boundary probes

Six image-dimension parser operations test reference outputs and a real width/height pair, with pointer or reference cursor ownership. Scalar reference outputs are neutral at 88.89%; pair forms regress. No parser helper or local pair type is retained.


## 2026-09-07 five-function campaign evidence

Fifty-nine image-vector, dimension, and final velocity ownership forms do
not improve 88.89%. They do not recover the native text-end/temporary stack
layout or deferred parser-call cleanup. No source change is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.
