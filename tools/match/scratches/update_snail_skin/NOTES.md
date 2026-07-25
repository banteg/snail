# update_snail_skin @ 0x445cd0

Exact Windows counterpart of Android `cRSnail::BuildHotSpots()`. The stable
Windows name predates cross-port ownership recovery; this promotes the
cross-confirmed Snail hotspot fields:

- `snail_hotspot_source_body.transform` at `+0x1604`;
- `snail_hotspot_body.transform` at `+0x1684`;
- `snail_hotspots_local[19]` at `+0x16cc`;
- `snail_hotspots_world[19]` at `+0x17b0`.

Recovered behavior: each tick transforms the 19 local hotspots into world
space. Slots `0..10` use source matrix B; slots `11..18` use source matrix A.
The world bank feeds `update_cutscene`, including the known camera anchors
`CameraSkidStop` at slot `12`, `CameraSlugDeath` at slot `17`, and
`CameraIntroTalk` at slot `18`.

2026-06-21 index-loop pass: rewriting the loop as a plain indexed transform
over `snail_hotspots_local[index]` into `snail_hotspots_world[index]` exact
matches the native function: 100.00%, 44/44 instructions, 44/44 prefix, and the
single masked operand clean. The index-driven source keeps the native loop
index in `ebx`, the world-hotspot cursor in `ebp`, and preserves the by-value
`TransformMatrix` stack copy before `multiply_vector_by_matrix`. Earlier
pointer-walk and dual-pointer forms either swapped `ebx`/`ebp` ownership or
changed the prologue.

2026-07-13 index-owner closure: the exact loop now uses
`SNAIL_HOTSPOT_COUNT` and switches source matrices at
`SNAIL_HOTSPOT_PARCEL_POINT`, the first body/camera anchor after the eleven
weapon hotspots. This is codegen-neutral and ties the transform-bank split to
the same authored texture ordering used by extraction and cutscene consumers.

2026-07-14 source-body ownership: the `+0x1604` matrix is now reached through
the complete `RenderableBod` initialized at Snail `+0x15cc`, matching the
already-owned body at `+0x164c`. Focused Wibo remains exact at 44/44
instructions with its masked operand clean.

2026-07-14 vector operator ownership: the hotspot transform now uses the real
void by-value `Vector3::operator*=` directly. The caller remains exact at 44/44;
the decorated operator alias keeps its sole call operand audited.

2026-07-18 analysis replay: Binary Ninja and IDA now pin the exact
`void cRSnail::BuildHotSpots()` receiver as `Snail*`, retiring the synthetic
`PlayerPresentationController` view. Both decompilers expose the two complete
`RenderableBod` source matrices and the local/world 19-entry `Vec3` banks; IDA
also recovers the by-value `TransformMatrix` and `Vec3` temporaries. The focused
replay imports the complete `Object` dependency explicitly and verifies the
nine transitive owner sizes before applying presentation ABIs. Matching remains
exact at 100.00%, 44/44, with no source or code-shape change.

2026-07-25 hotspot element borrows: native EBP walks the 19-entry world bank
at `Snail +0x17b0` in `sizeof(Vec3) == 0xc` steps. EAX borrows the
corresponding local slot exactly `0xe4` bytes (19 `Vec3` records) behind it,
and ECX retains the pre-increment world destination for the three component
writes. IDA independently renders this as `world[-19]`, `world++`, and writes
through the saved `Vec3*`.

Binary Ninja's exact register lifetimes now replay as `Vec3*` for EBP
(`RegisterVariableSourceType`, index `13`, storage `71`), EAX (index `25`,
storage `66`), and ECX (index `97`, storage `67`). HLIL folds the local EAX
borrow into the raw native `0xe4` bias, but no longer widens any
cursor to `Vec3 (*)[19]` or subtracts back to the enclosing `Snail` for world
writes. The replay guards both complete source bodies, both hotspot banks, and
all relevant type widths. No matcher source changes: 44/44 instructions and
the one masked operand remain clean.
