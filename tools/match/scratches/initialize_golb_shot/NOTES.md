# Exact match

`initialize_golb_shot` @ 0x408690 constructs one 0x2e8-byte Golb shot slot.
`initialize_runtime_pools_and_path_template_bank` seeds 12 of these slots, and
`update_movement_flag_emitters` later iterates that same 12-slot bank before
calling `create_golb`.

The callback tables pin the ownership:

- `data_49734c` starts at `update_golb_ai`;
- `data_49731c` starts at `update_vapour`, so the old
  `g_track_jetpack_body_vtable` name was too narrow;
- `data_497350` starts at `noop_runtime_ai` for the tertiary embedded body.

## 2026-07-13 Player projectile-bank closure

The three independent lifecycle passes now close the parent boundary:

- construction initializes 12 `sizeof(GolbShot) == 0x2e8` records beginning
  at `Player +0x450`;
- movement dispatch scans those same 12 records and calls `create_golb` only
  when `GolbShot::state` at `+0x244` is inactive; and
- subgame teardown walks the identical bank and calls `kill_golb` for active
  records.

`12 * 0x2e8` ends exactly at `Player +0x2730`, the next independently named
movement-fire field. The bank is therefore owned storage in `Player`, not a
borrowed emitter view or a separate SubgameRuntime pool.

## 2026-07-16 lifecycle receiver contract

The exact constructor body, its `sizeof(GolbShot) == 0x2e8` array-constructor
caller, and the independent mobile `cRSubGolb` class symbols close the ABI as
`GolbShot* __thiscall initialize_golb_shot(GolbShot*)`. The Binary Ninja and
IDA replay catalogs now preserve that concrete receiver and same-slot return
instead of their legacy `BodBase*` inference. The exact 17/17 match is
unchanged.

## 2026-07-17 nested projectile-owner closure

The exact constructor resolves the former `+0x000..+0x197` overlap. It builds
the primary `RenderableBod` at `+0x000`, then a complete `sizeof(Vapour) ==
0x94` child at `+0x080`, followed by the enclosing-shot backlink at `+0x114`
and the tertiary `RenderableBod` at `+0x118`. The old direct matrix view at
`+0x150` is precisely `tertiary_body.transform`.

The checked C/C++ owners, Binary Ninja replay, and guarded IDA UDT refresh now
agree on those four non-overlapping members. The constructor remains exact at
17/17 instructions; no code-shape or score-only alias was introduced.
