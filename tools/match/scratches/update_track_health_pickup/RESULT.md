# Result: update_track_health_pickup

## Measurement

- Before: `71.88%`; target `128` instructions, candidate `128`; common prefix
  `6/128`; masked operands `15 ok, 0 unresolved, 0 mismatch`.
- After: `87.94%`; target `128` instructions, candidate `129`; common prefix
  `6/128`; masked operands `21 ok, 0 unresolved, 0 mismatch`.
- Command:
  `tools/match/match.sh tools/match/scratches/update_track_health_pickup --regions --max-regions 18 --region-context 6`
- The improved result reproduced in two final runs. The exact companion
  `health_collect_particles` target remained at `100.00%`, `104/104`, prefix
  `104/104`, with all `13` masks clean.
- `uv run pytest`: `63 passed, 1 skipped`.

## Accepted changes

- Structured the state-1 cull as the positive
  `world_position.z < owner->interaction_max_z` arm, keeping the sine-bob tail
  in the native final position instead of scheduling it before state-1
  teardown.
- Split the two state-2 list errors into explicit cold exits, ordered so VC6
  retains both native report/kill tails rather than folding them together.
- Snapshotted the state-1 sprite once for its two diagnostic exits. This keeps
  both state-1 report/kill tails distinct with one additional candidate
  instruction, while the successful unlink path continues to use the live
  sprite member.

## Rejected trials

- Positive state-1 arm with direct duplicated error code: `58.47%`, candidate
  `108`, prefix `6/128`, masks `12 ok, 0 unresolved, 0 mismatch`; VC6 folded
  the diagnostic tails aggressively.
- Separate state-1 sprite snapshots in both error arms: `80.95%`, candidate
  `124`, prefix `6/128`, masks `19 ok, 0 unresolved, 0 mismatch`; this fixed
  bob placement but still merged the two state-2 errors.
- Reverse-ordered state-2 error labels plus two state-1 snapshots: `87.60%`,
  candidate `130`, prefix `6/128`, masks `21 ok, 0 unresolved, 0 mismatch`;
  both state-2 tails matched, but each state-1 exit added a snapshot load.
- Explicitly shared successful-unlink labels: `58.47%`, candidate `108`, prefix
  `6/128`, masks `12 ok, 0 unresolved, 0 mismatch`; this did not stop error-tail
  folding.
- Force-inlined removal helper: `62.81%`, candidate `114`, prefix `6/128`,
  masks `14 ok, 0 unresolved, 0 mismatch`; inlining merged too much teardown
  control flow.
- Null-guarded state-1 snapshots: best `70.97%`, candidate `120`, prefix
  `2/128`, masks `17 ok, 0 unresolved, 1 mismatch`; rejected for both score and
  masked-operand regression.
- Snapshotting all four diagnostic exits: `58.96%`, candidate `123`, prefix
  `6/128`, masks `13 ok, 0 unresolved, 1 mismatch`; rejected for string-mask
  misalignment and broad layout regression.

## Next region

Eliminate the single state-1 sprite snapshot load while preserving the four
separate diagnostic tails. The desired post-report form reloads
`sprite` directly into `ecx`; recovering it would remove the remaining
one-instruction count delta and realign the final bob-tail branch targets.
