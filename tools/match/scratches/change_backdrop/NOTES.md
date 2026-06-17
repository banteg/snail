# change_backdrop @ 0x410d50

Current scratch: 63.89% (34 target insns, 38 candidate insns), clean masks.

Stages one parsed landscape script for the backdrop renderer.

Recovered record fields:

- `LandscapeScriptRecord::backdrop_texture_id` at `+0x84` is the base sprite
  texture id written from the `Picture:` parser.
- `split_backdrop_texture_pair` at `+0x88` selects the `_A/_B` split backdrop
  pair path. In that mode the pending secondary texture is `texture_id + 1`.
- `distort` at `+0x120` is copied into `Backdrop::pending_distort`.

The helper only updates pending backdrop fields when `backdrop_texture_id` is
non-zero; otherwise it clears `backdrop_refresh_pending` and leaves the pending
distort/flip fields unchanged.

Open source-shape issue: native keeps `backdrop_refresh_pending`/zero in `edx`
and the initial texture id in `esi`, producing `cmp bl, dl` and
`cmp esi, edx`. The clean structured spelling currently gives VC6 the opposite
allocation (`refresh_pending` in `esi`, texture id in `edx`) and emits `test`.
Do not fix this with volatile or fake helper calls; resume from source shape or
an idiom probe.
