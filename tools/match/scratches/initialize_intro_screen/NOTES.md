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
