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
  `SubgameRuntime +0x74618`.
- `LogoLetter` is shared across its exact constructor, pinned updater,
  intro initializer, teardown, constructor loop, and logo loader. It owns the
  inherited `RenderableBod` through `+0x77`, velocity at `+0x80`, and the
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
