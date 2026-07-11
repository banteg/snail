# `initialize_runtime_pools_and_path_template_bank` notes

- This scratch intentionally uses byte offsets into the subgame runtime blob.
  The function is a constructor pass over many unrelated pools; promoting a
  monolithic shared type would obscure more than it clarifies.
- The call at +0x10013dc targets the small object-constructor thunk at
  0x42f6e0 on the embedded height-field animator's `FrameSequence`, not
  `initialize_object` directly.

## 2026-07-10 path-bank ownership

- The pass at `SubgameRuntime +0xff2914` initializes exactly `126` records at
  stride `0xa8`: 63 adjacent primary/secondary pairs of stride `0x150`.
- `SubgameRuntime` itself is `GameRoot +0x74618`, so this is the same address as
  the world initializer's constructor base `GameRoot +0x1066f2c`; no install
  copy or transfer exists.
- The four bytes immediately before the bank now split into the authored empty
  `cRPathManager` at `+0xff2910` and three alignment bytes. Its one-byte size is
  independently printed by `construct_game_runtime`; naming the boundary keeps
  this constructor exact at 227/227 with all 72 operands clean.
- The `63 * 0x150 = 0x52b0` extent ends exactly at the embedded barrier at
  `SubgameRuntime +0xff7bc4`.
- Despite its retained historical name, `initialize_path_template_record_pair`
  initializes one record's leading `BodBase` and fringe `BodBase` at `+0x60`.

## 2026-07-11 live-list sentinels

- Ten consecutive constructor calls from `SubgameRuntime +0x355b64` through
  `+0x355d5c` build complete `0x38`-byte `BodBase` objects. Their exact
  `0x230` extent ends at `active_level_score +0x355d94` with no gap.
- Windows consumers identify five inherited node prefixes: the shared
  fringe/attachment head, track-body head, barrier/sub-lazer head, salt-hazard
  head, and tile-29/30 special-cell head. The other five remain explicitly
  unknown `BodBase` owners; mobile builds have a different group count and
  ordering, so their names are not transplanted.
- Replacing all ten raw offsets with these embedded owners leaves this function
  exact at `227/227` with all 72 operands clean.

## 2026-07-11 player presentation owner

- The sole call to `0x4086d0` receives `Player +0x2984`, exactly the shared
  `PlayerPresentationController` member.
- Its four former "enemy groups" begin at presentation `+0x64c`, `+0xa28`,
  `+0xe04`, and `+0x11e0`: the three weapon channels and jetpack channel, each
  with the proven `0x3dc` stride.
- The callback slots prove a no-op presentation root, four no-op animation
  channels, and the `update_invincible_shell` child at `+0x1894`. The old
  enemy-manager constructor name and local receiver are retired.

## 2026-07-11 paired cRSubTracks owners

- The constructor builds two consecutive, identically shaped regions at
  `SubgameRuntime +0xa874` and `+0x1b01ec`. Each is exactly `0x1a5978`, the
  independently reported size of `cRSubTracks`/`SubTracks`.
- Both regions construct 100 `0x4220` segment slots, the 256 authored-row
  arrays inside their `First:` and `Last:` slots, and their tail `Color4f`.
  The second extent ends exactly at the BodBase sentinel at `+0x355b64`.
- The first object is the selected gameplay level. The second is reused as a
  startup level-enumeration receiver and then seeded from the built-in segment
  table, so it is named `level_definition_scratch` rather than assigned a
  speculative persistent gameplay role.
- Replacing all six raw constructor offsets with the two shared owners leaves
  this function exact at `100.00%`, `227/227`, with all 72 operands clean.

## 2026-07-11 segment catalog boundary

- The catalog receiver is `SubgameRuntime +0x10014cc`; the constructor starts
  150 records at `+0x10014d0`, exactly four bytes into that object.
- `150 * 0x4088 + 4 = 0x25cfb4`, the reported `cRSMTracks` size, and the result
  ends exactly at the parcel pool at `+0x125e480`.
- This proves a leading count followed by the entry array, replacing the old
  overlapping entry-0 alias and speculative terminal word.

## 2026-07-11 landscape manager boundary

- Ten `0x90`-byte active entries begin at `SubgameRuntime +0xff7c00`, the
  script count follows at `+0xff81a0`, and 128 `0x124`-byte script records
  begin at `+0xff81a4`.
- `10 * 0x90 + 4 + 128 * 0x124 = 0x97a4`, exactly the reported
  `cRLandscapeManager` size, ending at `+0x10013a4`.
- A typed constructor cursor preserves the exact 227/227 native code while
  retiring the overlapping `ActiveLandscapePool` and `LandscapeScriptBank`
  views.

## 2026-07-11 SMTrack height-field animator boundary

- The constructed object at `SubgameRuntime +0x10013a4` is one `0x38`-byte
  `BodBase` followed by a `0xf0`-byte `FrameSequence` at `+0x38`.
- Its exact `0x128` extent ends at `SMTracks +0x10014cc`, closing the
  entire post-landscape gap without padding.
- The typed local receiver retains the native `edi` owner and leaves this
  constructor exact at 227/227 with all 72 operands clean.

## 2026-07-11 GalaxyRoute arrays

- `GalaxyRoute +0x10` owns 101 constructor-visited `0x2a0` slots, ending
  exactly at `route_names +0x10930`; this replaces 100 overlapping record
  bodies plus a hidden `0x29c` tail.
- Each slot has a four-byte prefix and a `0x29c` record body. Ten `0xa0` route
  names then fill `+0x10930..+0x10f70` exactly.
- The callback at `0x408880` constructs `GalaxyRouteNameRecord::color +0x84`,
  so the unsupported `initialize_solution_record` name is retired. The parcel,
  route-slot, route-name, and contact-entry constructor arrays now all use
  their shared owners while the function remains exact at 227/227.

## 2026-07-11 cRSubRow constructor loop

- The 3200-record pass at `SubgameRuntime +0x5ccac8` now walks the owned
  `SubRow runtime_rows[3200]` array directly rather than a generic runtime-slot
  cursor with a literal `0xf4` increment.
- Each call reaches the exact `SubRow` initializer that owns the embedded
  renderable body at `+0x04` and attachment body at `+0xb0`.
- The typed loop remains exact at 227/227 instructions with all 72 masked
  operands clean.
