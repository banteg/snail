# change_backdrop @ 0x410d50

Current scratch: 100.00% (34/34 instructions), clean masks.

Stages one parsed landscape script for the backdrop renderer.

Recovered record fields:

- `LandscapeScriptRecord::backdrop_texture_id` at `+0x84` is the base sprite
  texture id written from the `Picture:` parser.
- `split_backdrop_texture_pair` at `+0x88` selects the `_A/_B` split backdrop
  pair path. In that mode the pending secondary texture is `texture_id + 1`.
- `distort` at `+0x120` is copied into `Backdrop::pending_distort`.

The helper only updates pending backdrop fields when `backdrop_texture_id` is
non-zero; otherwise it clears the persistent `backdrop_render_enabled` draw
gate and leaves the pending distort/flip fields unchanged.

2026-06-20 exact update: the scratch now re-reads
`record->backdrop_texture_id` in both branch guards instead of preserving an
initial `texture_id` local. That source shape gives VC6 the native zero lane in
`edx`, path split byte in `bl`, and texture id in `esi`, recovering the
`cmp bl, dl` / `cmp esi, edx` guards without volatile state or fake
dependencies.

## 2026-07-26 authored backdrop owner

Android and iOS independently retain this exact lifecycle method as
`cRBackdrop::Change(cRLandscape*, bool)`. Their bodies stage the landscape
texture, split-pair flag, Distort value, and flip flag through the same
`cRBackdrop` owner. This closes the original class/method identity while the
Windows void transcription remains exact at 34/34 instructions.
