# build_track_fringe_mesh reconstruction notes

`build_track_fringe_mesh` creates the generated side/fringe strip mesh for an
attachment path template. It allocates an `Object` into the template's second
`BodBase` slot at `+0x60`, copies the current track skirt colour into that BOD,
requests four vertices and two facequads per segment, extrudes the outer edge by
0.4 units along the normalized edge direction, optionally clamps X by side, and
builds the two textured facequads for each segment.

Current focused result:

- match: 69.92%
- target/candidate instructions: 318 / 317
- prefix: 18 / 318
- masked operands: 23 clean, 0 unresolved, 0 mismatched

Important type notes:

- `Path +0x60` is a second `BodBase`, corroborating the
  `initialize_path_template_record_pair` constructor and this mesh builder.
- The source mesh for sampled track vertices remains the first BOD/object slot
  at `Path +0x24`; the generated mesh lives in the second
  BOD's `object` field at `+0x84`.
- Non-mirrored templates use source columns `1/0` for the first edge and
  `width_cells - 1 / width_cells` for the opposite edge; mirrored templates swap
  those pairs.
- `clamp_side == -1.0f` clamps positive generated X values to zero;
  `clamp_side == 1.0f` clamps negative generated X values to zero. Android's
  authored `cRPath::BuildFringe` independently preserves the same two exact
  sentinel cases.

Remaining gap:

The remaining gap is now register and store scheduling. The exact `0x68` stack
frame, row-centered generated-vertex cursor, vector temporary family, and face
loop lifetime are recovered. Native keeps the retained generated `Object` in
`ebx`, assigns the two sampled columns to the opposite `ecx`/`edx` pair, and
schedules face index/UV stores differently from the current candidate.

## 2026-07-12 authored vector and clamp recovery

- Android's named `cRPath::BuildFringe` independently confirms the Windows
  algorithm. The two edge extrusions are real vector expressions:
  `outer = inner + normalize(inner - outer) * 0.4f`. Recovering the local-result
  subtraction and by-value scale/add operators raises the candidate from
  `281` to `317` instructions and restores the target's `0x68` frame.
- The skirt-colour return object is scoped only across the colour copy, so VC6
  reuses its dead stack storage for later vector temporaries. Generated rows
  read directly through the owned `Path::strip_mesh`; the redundant generic
  source-object alias is gone.
- The geometry and face loops share one integer cursor, and UV corner `3` is
  written before corners `0..2`, matching the Android owner and the Windows
  store family.
- The old `clamp_side != 1.0f` branch was a semantic reconstruction error.
  Both native ports clamp positive X only for `-1.0f`, clamp negative X only
  for `+1.0f`, and leave X untouched for every other value.

These source-backed changes improve the focused match from `42.07%` to
`69.92%`, with `317/318` instructions, an `18/318` prefix, and all `23` masked
operands clean.
