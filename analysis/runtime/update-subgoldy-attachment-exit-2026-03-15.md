# `update_subgoldy` Attachment Exit Branches (2026-03-15)

This note preserves the Windows `cdb` session conclusions from `ARCADE007` in a repo-tracked artifact that can be replayed onto another Binary Ninja or IDA database later.

## Runtime-confirmed attachment lifecycle

- `ARCADE007` / `To Infinity!` is a valid shipped `HalfPipe` repro level.
- `begin_track_attachment_follow_state` (`0x420c40`) produced a corrected initialized begin snapshot with:
  - active flag `1`
  - template `0x0df70d14`
  - owner cell `0x0d34c184`
  - segment `0`
  - entry progress `0x3d134000` -> `0.03594971f`
  - entry height `0`
- `update_track_attachment_follow_state` (`0x420cb0`) later produced a mid-follow sample with:
  - segment `0`
  - progress `0`
  - height `0xbefae148` -> `-0.49f`
  - template `0x0df72e8c`
  - owner `0x0d33dcd0`
- `initialize_subgoldy_fall_state` (`0x43af60`) produced multiple post-exit anchor samples:
  - `0x42bad90b` -> `93.42391f`
  - `0x425c6801` -> `55.10157f`
  - `0x440dc5e2` -> `567.0919f`
- every captured post-exit step used `0x3c888889` -> `0.01666667f` (`1/60`)

## Post-exit gates in `update_subgoldy`

`update_subgoldy` consumes the fall-state fields seeded by `initialize_subgoldy_fall_state`:

- `player + 0x434` is accumulated by `player + 0x438` each tick
- `0x43ce9c` compares the accumulated progress against `0.7f`
- `0x43cea9` is the first visible `gate_a` block
- `0x43cef7` starts the deeper `gate_b` block

Captured gate samples:

- `gate_a` stop:
  - progress `0x3f377777` -> `0.7166666f`
  - gate_a `1`
  - gate_b `0`
- `gate_b` stop:
  - progress `0x3f2aaaab` -> `0.6666667f`
  - player z `0xc0e5f0e6` -> `-7.185657f`
  - both gate bytes still read zero in the stop payload

Conservative interpretation:

- the `gate_a` breakpoint is landing after the first `>= 0.7f` transition has already set `player + 0x44c`
- the `gate_b` breakpoint is landing at the start of the deeper threshold block, before all gate writes complete
- `gate_b` is real runtime behavior, but it is not mandatory for every clean-finish run

## Direct `initialize_subgoldy_fall_state` callsites inside `update_subgoldy`

`bn callsites 0x43af60 --within update_subgoldy --caller-static` identified four direct callsites:

- `0x43b9b8`
- `0x43c008`
- `0x43c34b`
- `0x43c507`

Current static read:

### `0x43b9b8`

- reached from the `update_track_attachment_follow_state` switch when the helper returns cases `1` or `3`
- only calls `initialize_subgoldy_fall_state` when `player + 0x384` is still `1`
- this is the most direct "attachment update requested fall handoff" path

### `0x43c008`

- guarded by a local float compare against a branch-selected threshold (`0` or `0.2`)
- only calls the helper when `player + 0x41d == 0`
- this is an update-side airborne or settle transition, but the exact gameplay label is still open

### `0x43c34b`

- reached through the current-grid-cell-type `0x16` branch
- calls the helper after a compare between the attachment-owner sample and the player state at `ebp + 0x6c`
- exact gameplay label is still open, but this is distinct from the direct attachment-update return path

### `0x43c507`

- reached after a transient accumulator at `player + 0x328` advances to `1.0`
- only calls the helper when `player + 0x41d == 0`
- nearby grid-cell checks cover types `2`, `4`, `5`, `7`, `8`, `0xa`, and `0xb`

## Clean-finish implication

One full `ARCADE007` replay was run with exact probes on all four direct `update_subgoldy` callsites above. The level finished cleanly without hitting any of them.

That means:

- at least one ordinary level-complete path retires attachment-follow without going through `update_subgoldy -> initialize_subgoldy_fall_state`
- the fall helper and its post-exit progress gates are real and important, but they are not the only attachment-retirement lane active during normal play
