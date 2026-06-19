# destroy_intro_screen @ 0x419920

Unlinks each intro/credits crawl renderable from the shared BOD active list and
pushes it back onto the shared free list before the intro screen exits.

Layout recovered from the target loop:

- `+0x0c`: render flags restored into `g_render_flags` (`data_4df934`);
- `+0x14`: renderable count;
- `+0x18`: first renderable slot;
- renderable slot stride: `0x90`;
- each slot starts with a `BodNode`, so the native loop cursor at slot `+0x0c`
  is the node's `list_next` field.

The retained source mirrors the existing matched BOD list removal idiom and
uses the native `node->list_next` cursor shape. The remaining mismatch is
source-shape noise: VC6 merges the two `report_errorf` error-call sites in the
candidate, while the target keeps separate calls before the shared loop tail.
