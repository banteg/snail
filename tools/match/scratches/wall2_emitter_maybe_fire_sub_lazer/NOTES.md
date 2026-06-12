# Pinned — 40.43%, 189/187 insns (structure aligned, register golf remains)

Really the fringe-object update, not just the emitter. Semantics
complete:

- gate: flags & 0x2000 plus the suspend byte
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

Notable: this TU CACHES the game base (non-volatile pattern, reload
after calls) unlike the seed block in the swept entry — base-caching
behavior is per-function, worth remembering when modeling globals.
