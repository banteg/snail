# `initialize_frontend_sprite_button` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **100.00%** |
| Target instructions | 157 | 157 |
| Candidate instructions | 0 | 157 |
| Common prefix | 0 / 157 | **157 / 157** |
| Masked operands | none | **10 clean, 0 unresolved, 0 mismatched** |

The scratch now exactly matches the sprite-button constructor. It pins the
border-list insertion, tooltip reset fields, style/padding/color
initialization, texture-dimension reads, authored anchors, and final layout
call.

## Exact Shape

The final shape keeps an `idle_fill` color pointer live from the `font_id`
store, orders the post-`unhide_border_init` flag/text/anchor writes to recover
the native color-copy register ownership, and uses typed texture-dimension
fields plus an adjusted-anchor temporary to reproduce the x87/table-reload
tail.

Final matcher command:

```sh
tools/match/match.sh tools/match/scratches/initialize_frontend_sprite_button --full
```
