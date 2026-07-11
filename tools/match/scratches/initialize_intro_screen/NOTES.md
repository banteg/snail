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

- `IntroScreenRuntime` is now the exact `0x25218`-byte root owner at
  `GameRoot +0x4f400`: a `0x18`-byte state header, 1024 `0x90`-byte crawl
  renderables, and 32 `0x90`-byte logo renderables. The second bank begins at
  receiver `+0x24018`, and the complete object ends exactly at
  `SubgameRuntime +0x74618`.
- `IntroLogoRenderable` is shared across its exact constructor, pinned updater,
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
