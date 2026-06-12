# update_track_attachment_follow_state @ 0x420cb0

Best current source-shaped baseline for the native attachment-follow update helper.

Current matcher result:

- 42.71% match
- target: 726 instructions
- candidate: 646 instructions

Recovered shape:

- thiscall `FollowState::update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion)`, returns the mode code consumed by `update_subgoldy`
- advances `progress` by `path_factor * secondary_samples[sample_index].delta_length`
- consumes sample overflows until the active sample can hold the remaining delta
- terminates at `sample_index == template->segment_count`, clears `active`, returns `3`, and handles the Supertramp launch special case
- normal path interpolates the path center/lateral/special scalars, builds either kind-42 nonlinear transform or ordinary interpolated secondary-sample transform, stores output position and camera basis scratch vectors, then checks side exits
- special-runtime row updates use the typed row-slot table at `g_game_base + 0x641184 + 0xf4 * row_index`
- Supertramp launch path reloads the subgame rate from `g_game_base + 0x74650`

Known residuals after the current source shape:

- stack layout still differs (`sub esp, 0x180` target vs `sub esp, 0x15c` candidate)
- the overflow loop still uses a different x87 subtract shape and keeps the template record in `ebx` instead of freeing `ebx` for the `0x80` row flag constant
- special-runtime row writes are semantically typed, but row lookup/store ordering and registers still differ in both milestone branches
- normal interpolation now follows the target's scalar and output temporary flow, but matrix-copy stack offsets and camera-basis stores remain different
- `orientation_b` is intentionally overwritten by the installed-heading lane, matching the native semantic result; exact dead/intermediate stores still need source-shape work

## Cross-findings (2026-06-12, second agent)

- the "camera basis" globals at 0x42fdb4/c4/d4 are the **player's
  live_matrix rows**: player block at game+0x42fd7c, TransformMatrix at
  +0x38, position row = the position vector at +0x68 — same shape as the
  hazard slots. Worth folding into the mirror's Player model even though
  the normalized addressing is identical either way.
- FollowState +0x18..+0x20 is output_position (the swept entry zeroes
  its x/y), orientation block spans +0x24..+0x34;
  tools/match/include/track_attachment.h updated.
- sample +0x8c renamed delta_length across the headers (the swept-entry
  "depth limit" gate is z < segment length); swept scratch updated, score
  holds at 79.80%.
- target preloads ebx=0x80 and edi=0x3f19999a (0.6f) in the prologue —
  loop-invariant constant hoisting; the candidate can only mirror it once
  those callee-saved registers are free across the overflow loop.
