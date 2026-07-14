# update_track_jetpack_pickup @ 0x43efb0

Current match: **100.00%**, `127/127` candidate/target instructions, full
`127/127` prefix, and `20` clean masked operands.

2026-06-16 vtable correction: this is the jetpack pickup parent updater, not
the sub-lazer projectile updater. `initialize_track_jetpack_pickup_runtime`
installs parent vtable `data_497318`, and `data_497318` points at `0x43efb0`.
The same parent slot starts at `game + 0x355e64`.

Layout facts now shared with `track_jetpack_pickup.h`:

- parent list prefix at `+0x00`, with live/free-list flags at `+0x04`
- inherited `BodBase::position` at `+0x10`; the updater uses y as the sprite bob base and
  z for the owner kill-plane compare
- state `+0x38`, owner `+0x3c`, containing `SubgameRuntime*` backlink `+0x44`
- sprite `+0x64`, source row cell `+0x68`, bob phase/step `+0x6c/+0x70`
- embedded renderable bodies at `+0x74` and `+0x108`, initialized by the
  constructor but not directly advanced by this updater

The shared-list recovery below closes the former duplicated-remove
block-layout residual.

2026-06-16 pickup/Sprite slice: the scratch-local `FreeAnchor` duplicate was
removed in favor of the shared `BodList` view from `bod_list.h` via
`track_jetpack_pickup.h`. Focused Wibo remains 72.44%, 127/127 insns, with
15 masked operands OK and no unresolved or mismatched operands.

2026-06-17 symbol sync: the tracked IDA/BN decompile exports and the live BN
session now name `0x43efb0` as `update_track_jetpack_pickup`, matching the
gameplay manifest and this scratch. The old shifted labels at `0x43ee50` and
`0x43efb0` were corrected as part of the pickup/sub-lazer vtable cleanup.

2026-06-16 bob-tail layout retry: inverting the state-1 z test so the removal
block was nested under `world_position.z < owner->interaction_max_z` regressed
to `58.12%` (`107/127`). VC6 merged the two unlink blocks just like the health
pickup rejection notes warned. Keep the duplicated state-1/state-2 unlink
source shape until the health pickup's anti-merge shape can be applied.

2026-06-20 health-family transfer: applying the accepted
`update_track_health_pickup` teardown shape to this updater improves the match
from `72.44%`, `127/127`, `15 ok` to `87.84%`, `128/127`, `20 ok`. The retained
source uses the positive state-1 removal arm so the bob tail stays in the native
final position, splits the two state-2 error exits into cold labels, and keeps
one state-1 `Sprite*` snapshot shared by the two diagnostic exits so VC6 does
not merge the duplicated teardown blocks.

Rejected in the same pass: removing the state-1 snapshot and calling
`sprite->kill_sprite()` directly in the diagnostics regresses to `58.12%`,
`107/127`, `11 ok`; this exactly mirrors the health pickup residual. The
remaining difference is the extra state-1 sprite snapshot load before the two
diagnostic tails, with otherwise clean masked operands.

2026-07-11 owner-view retirement: `owner_game +0x44` now points directly to
the containing `SubgameRuntime`; the duplicate pickup-only owner view added no
ownership information and was removed. Focused code generation is unchanged.

2026-07-11 authored owner: the receiver and intrusive-list neighbors now use
the primary `JetPack` type. The exact constructor table at `0x497318` points
directly here, while Android and iOS retain `cRJetPack::AI()`. Focused Wibo
remains 87.84%, 128/127 instructions, with all 20 masked operands clean.

## 2026-07-12 shared list removal recovery

Android spells both teardown paths as `cLinkedList<cRBod>::Remove`, followed by
`cRSprite::Kill`. Recovering that operation on the owned `BodList` lets VC6
inline the body separately at both callsites and reproduces the Windows
diagnostic, neighbor-patch, free-stack, and flag-clear blocks exactly. The
synthetic state-one `Sprite*` snapshot is gone; focused matching is now exact
at `127/127`.

2026-07-14 root-list closure: both removal arms now borrow
`GameRoot::active_bod_list` directly. Matching remains exact at 127/127 with
all 20 operands clean.

2026-07-14 BOD-base ownership: the parent now directly inherits `BodBase`;
the kill plane and bob base read `position.z/y`, while list removal continues
through inherited `BodNode`. Matching remains exact at 127/127 with all 20
operands clean.

## 2026-07-14 shared pickup lifecycle ownership

The authored `cRJetPack` parent now shares `TrackPickupState` with
`cRSubSpeedUp` and `cRSubHealth`. Its live state bobs and culls the pickup;
collision requests teardown, and the exact next AI tick removes the inherited
BOD and sprite before returning to inactive. Matching remains exact at 127/127
instructions with all 20 operands clean.
