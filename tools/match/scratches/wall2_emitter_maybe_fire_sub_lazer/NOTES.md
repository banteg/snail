# Pinned — 42.34%, 172/187 insns (structure aligned, register golf remains)

Really a fringe runtime object update, not just the emitter. It shares the
BOD/color prefix used by pooled `FringeObject`, but extends past the pooled
`0x38` object with owner/tile/runtime flags, so keep it separate. Semantics
complete:

- gate: flags & 0x2000 plus `Game::pause_gate`
- tile 14 (wall2): fires only once the active row start
  (game+0x74668) is past the player z; 4% per-tick roll
  (random_float_below(100) < 4); spawn at the fringe position with
  y+8 and a lane offset from the flag nibble ((flags>>8 & 0xF) * 0.5);
  aimed at the player with +/-3 vertical jitter +8 z lead; fires only
  when the z delta < -4; direction normalized and scaled to 0.4/tick
  through the pinned shoot_subgoldy; then the cull check
- tile 22: cull when behind the plane (game+0x4326fc)
- tiles 29/30 (attachment skirts): WORM owners fade by rate/30 with a
  fixed alpha; the skirt color syncs into the row-record +0x34 color
  lane (game+0x6411b8, 244 stride); cull at row_count+5 behind
- default: cull behind the plane when also past active_row_end - 5

RNG call convention is a debug/tag argument, not an RNG state pointer. Raw
image disassembly shows `random_float_below(100)` pushes `0x4a4dc8`, which
resolves to the one-character `"W"` tag, and the vertical jitter
`random_signed_float_below(3)` pushes `0x4a4dc0`, which resolves to `"Wall2"`.
The normalizer masks both pointers as `ADDR`, so the match percentage does not
expose this assumption.

Notable: this TU CACHES the game base (non-volatile pattern, reload
after calls) unlike the seed block in the swept entry — base-caching
behavior is per-function, worth remembering when modeling globals.

2026-06-16 pin audit: focused matcher verifies 42.34%, 172/187 insns.
Keep pinned; RNG tags, emitter cadence, projectile spawn direction, and cull
semantics are recovered, with only source-shape/register golf remaining.
