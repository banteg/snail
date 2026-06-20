# Result: health_collect_particles

## Measurement

- Before: `69.61%`; target `104` instructions, candidate `100`; common prefix
  `1/104`; masked operands `13 ok, 0 unresolved, 0 mismatch`.
- After: `100.00%`; target `104` instructions, candidate `104`; common prefix
  `104/104`; masked operands `13 ok, 0 unresolved, 0 mismatch`.
- Command:
  `tools/match/match.sh tools/match/scratches/health_collect_particles --regions --max-regions 18 --region-context 6`
- The exact result reproduced in two final runs. The companion
  `update_track_health_pickup` target remained at its baseline `71.88%`,
  `128/128`, prefix `6/128`, with all `15` masks clean.
- `uv run pytest`: `63 passed, 1 skipped`.

## Accepted changes

- Reused one angle local for both trig calls instead of keeping a duplicate
  angle temporary.
- Constructed the burst velocity as a named `Vector3` and assigned it to the
  sprite, recovering the native z/cosine/sine evaluation order, stack frame,
  loop-index spill, and dword flag update.
- Declared the angle after the source-position copy to recover the native
  position-copy/x87 scheduling.
- Default-constructed the pickup offset and assigned x, y, and z in order.
- Advanced the loop after the final position update, closing the last x87 tail
  scheduling difference.

## Rejected trials

- Shared angle without the burst `Vector3`: `77.83%`, candidate `99`, prefix
  `1/104`, masks `13/13` clean.
- Burst `Vector3` while retaining the duplicate angle temporary: `75.60%`,
  candidate `105`, prefix `5/104`, masks `13/13` clean.
- Component-wise burst construction in z/y/x order: `76.70%`, candidate `102`,
  prefix `1/104`, masks `13/13` clean.
- Direct player-velocity offset expressions without a pickup vector: `81.37%`,
  candidate `100`, prefix `1/104`, masks `13/13` clean.
- Pickup component order x/z/y: `96.15%`, candidate `104`, prefix `79/104`,
  masks `12/12` clean.
- Keeping the increment before the final z update after all other accepted
  changes: `99.04%`, candidate `104`, prefix `91/104`, masks `13/13` clean.

## Next region

None in this target: the normalized instruction stream and masked-operand audit
are exact. The next contained lane is the state-1 bob-tail placement in
`update_track_health_pickup`.
