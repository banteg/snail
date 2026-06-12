# Original Bugs

Catalog of bugs in the native game that the port has positively identified
through matched source or pinned asm. Policy:

- **the port fixes obvious bugs by default**
- `--preserve-bugs` reproduces the original behavior for differential
  testing against the Windows build (switch:
  `zig/src/gameplay/native/original_bugs.zig`, set from app options at
  startup)
- every entry needs: an id, the native evidence (matched scratch or asm
  address), the observable consequence, the fixed behavior, and whether
  fixed and preserved behavior actually differ observably
- a mirror module that branches on the switch cites the entry id at the
  branch

Do not add suspected bugs here — only ones proven by matched/pinned code.
Suspicions stay in scratch NOTES until settled.

## OB-1: salt spawn corrupts velocity.z with a byte write

- evidence: `spawn_salt_hazard` @ 0x441560 (pinned 74%) executes
  `mov byte [slot+0x94], 1` where `update_salt_hazard` @ 0x4417d0 (pinned
  48%) reads +0x94 as the velocity.z float
- consequence: velocity.z is a denormal (~1.4e-45); salt falls with no
  depth drift
- fixed behavior: `velocity.z = 0`
- observable difference: **none** — the denormal contributes ~1e-41 over a
  full level; fixed and preserved behavior are identical, so the mirror
  has no branch (documented in `native/salt_pool.zig`)

## OB-2: salt progress/step overlap the next slot and are never seeded

- evidence: `update_salt_hazard` accumulates progress/step at slot
  +0x98/+0x9c, one and two dwords past the 0x98 pool stride
  (`initialize_salt_hazard_pool` @ 0x441540, matched 100%, fixes the
  stride); `spawn_salt_hazard` never initializes either field
- consequence: the step reads the next slot's header (typically flag bits
  reinterpreted as a denormal float), so the progress > 1.0 despawn
  almost never fires and live salt persists until collision, y < 0, the
  kill plane, or the tile-14 floor exit; slot 39 additionally writes one
  dword past the pool
- fixed behavior: dedicated zero-initialized fields inside the slot — same
  observable lifetime, no out-of-bounds traffic
- observable difference: **effectively none** (the despawn lane stays
  dormant either way); no mirror branch

## Adding an entry

When a future match reveals a bug whose fix *does* change observable
behavior, the mirror branches like:

```zig
if (original_bugs.preserve) {
    // OB-n: original behavior
} else {
    // fixed
}
```

and the differential-test harness runs the Zig build with
`--preserve-bugs` when comparing against native captures.
