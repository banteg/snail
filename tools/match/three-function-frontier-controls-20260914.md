# Other controls from the three-function batch

The [receipt](three-function-frontier-controls-20260914.json) preserves 199
compiling source controls across 13 unchanged functions. They cover source
ownership and operation boundaries in repeat-key input, transition state,
galaxy/star/firework setup, projectile creation, path motion, LoopOut,
TurnoverDouble, loading resources and cache building. None adds a full match.
Three malformed runtime-borrow controls are recorded separately as construction
failures. All 199 valid source recipes reconstruct and verify their hashes.

These controls remain useful diagnostic stages, including the LoopOut
radius-parameter variant that recovers the first conversion while changing
later stack reuse. Their scores are not source-exhaustion or compiler-provenance
claims. The canonical sources are unchanged from the receipt's baseline.

The three completed functions have separate full-byte proof receipts:

- [Built-in segment loader](glyph-row-count-ownership-20260914.md)
- [Render-cache initializer](cache-family-counter-lifetime-20260914.md)
- [Mouse hit test](mouse-pixel-coordinate-lifetimes-20260914.md)

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/three-function-frontier-controls-20260914.json
```
