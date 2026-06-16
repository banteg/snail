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

## Current Entries

None.

The earlier salt entries were removed after the 2026-06-16 vtable/name
correction: `0x4417d0` is `update_sub_lazer_projectile`, not
`update_salt_hazard`, and the real salt updater at `0x441c10` does not
consume `+0x94` as velocity.z or use `+0x98/+0x9c` progress fields.

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
