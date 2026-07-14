# initialize_player_presentation_controller

Exact constructor helper for the 0x19b4-byte authored `Snail` (`cRSnail`)
embedded at `Player +0x2984`.

Recovered ownership:

- `Snail` inherits the complete `RenderableBod` prefix through `+0x77` and owns ten
  `0x80`-byte cutscene visual slots beginning at `+0x14c`;
- the three `PresentationAnimationChannel` weapon owners begin at `+0x64c`
  and the jetpack channel begins at `+0x11e0`, all at the proven `0x3dc`
  stride;
- two complete renderable hotspot sources begin at `+0x15cc/+0x164c`, with
  their inherited transforms at `+0x1604/+0x1684`;
- authored `cRInvincible` begins at `+0x1894` and receives the callback
  whose sole target is exact `update_invincible_shell`;
- the Snail and animation-channel callback slots both resolve to
  `noop_runtime_ai`.

Authored-name proof is convergent rather than guessed from this constructor:
iOS retains cRSnail typeinfo and vtable plus `AIGoldy`, `ReleaseWeapons`,
`SetAnimation`, `SetJetPack`, `SetWeapon`, and `ExtractHotSpots`; Android
retains the same family plus `BuildHotSpots`. Their bodies consume the same
animation-channel, hotspot, cRInvincible, and cRCutScene subowners recovered in
the Windows object. The Windows extent ends exactly at `Player +0x4338`, where
the separately proven `parcels_collected` field begins.

The former `initialize_enemy_manager_runtime` name was stale: the sole caller
passes `Player +0x2984`, while the actual Windows `cREnemyManager` is the
separate `0x1804` contact-target registry at `SubgameRuntime +0x1270fd4`.

Each 0x80-byte animation slot is a complete `RenderableBod` plus eight tail
bytes. Its inherited `object +0x24` is the animated `Object*`; the AnimManager
stores the actual slot base, not a pointer biased 0x24 before it. The five-slot
channel extents (`+0x150..+0x3d0`) and ten-slot Snail extent
(`+0x14c..+0x64c`) close exactly against the next owned fields.

Focused Wibo remains proof-grade at 100.00%, 79/79 instructions, full prefix,
and 27 clean masked operands.

## 2026-07-14 RenderableBod inheritance closure

The exact constructor now calls the inherited
`RenderableBod::initialize_renderable_bod()` directly. `Snail` no longer
duplicates the vtable, list flags, `Object*`, color, or transform fields in its
own declaration; its first presentation-owned field remains the borrowed
animation-manager pointer at `+0x78`, and the complete object remains exactly
`0x19b4` bytes. Focused Wibo is byte-identical at 100.00%, 79/79 instructions,
full prefix, and 27 clean masked operands.

## 2026-07-14 animation-channel inheritance closure

All four `PresentationAnimationChannel` owners now inherit the same complete
`RenderableBod` prefix initialized here. Their first channel-owned field is
the borrowed animation-manager pointer at `+0x78`; selected state remains
`+0x104`, the owned manager `+0x108`, five owned slots `+0x150`, and release
step `+0x3d0`. The typed channel receivers leave this exact constructor
byte-identical at 79/79 instructions with all 27 operands clean.

## 2026-07-14 trivial channel-subobject constructor identity

The calls at weapon-channel `+0xc0` and jetpack-channel `+0x80/+0xc0` target
the exact shared `noop_runtime_slot_constructor` at `0x408600` (`mov eax, ecx;
ret`). The old scratch-local `IostreamInit` name asserted an owner the binary
does not support; these lanes remain opaque channel-owned subobjects until a
consumer gives them semantics. The constructor now uses the canonical neutral
call surface and remains exact.

## 2026-07-14 owned render-subobject closure

Binary Ninja's native address formation and the exact constructor calls agree
on the full owner graph: the ten Snail slots and each five-slot channel bank
are arrays of `PresentationAnimationSlot`, while `+0x15cc` and `+0x164c` are
complete `RenderableBod` children. The first child owns the source transform at
`+0x1604`; it is no longer represented as anonymous bytes plus a detached
matrix.

The authored `Invincible` at `+0x1894` now inherits the same complete
`RenderableBod` prefix instead of manually repeating its transform after a
`BodBase`. Its constructor call and callback store therefore use the embedded
member directly. Removing the raw `+0x14c`, `+0x150`, `+0x15cc`, `+0x164c`, and
`+0x1894` address expressions leaves focused Wibo byte-identical at 79/79
instructions with all 27 masked operands clean.

## 2026-07-14 presentation-slot extent derivation

The ten-child Snail constructor loop and all four five-child channel
constructor loops now derive their bounds from the owned
`PresentationAnimationSlot` arrays. The normalized listing remains
byte-identical
(`778a1842100ba2dd19cc4f47d86ee7b31199cb7ae1ac3d0bbd068e0ca088f808`)
and exact at 79/79 instructions with 27 clean operands.
