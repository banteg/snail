# initialize_garbage_hazard

`initialize_garbage_hazard` @ 0x408550 is exact and now uses the authored
`SubGarbage` view instead of a one-off local `GarbageHazardRuntime` shell.

The initializer calls the shared renderable-BOD initializer on the same zero
offset object, then installs the garbage vtable. This cross-confirms that
`SubGarbage` inherits `RenderableBod`, whose zero-offset `BodNode` in turn
inherits the `ContactTargetObject` prefix. The same object can therefore
participate in the active/free BOD list and be passed to
`append_subgame_contact_target` for the `list_flags & 0x1000` contact-suppress
gate. The slot has list links at `+0x08/+0x0c` and a renderable transform at
`+0x38..+0x77`; the live collision position used by spawn/update/collision is
`RenderableBod::transform.position` at `+0x68`.

## 2026-07-11 cRSubGarbage ownership

- Android preserves the authored owner as `cRSubGarbage`; the Windows table
  installed here at `0x497328` points directly to `update_garbage_hazard`, the
  cross-port `cRSubGarbage::AI()` callback.
- The exact runtime constructor walks 50 inline `sizeof(SubGarbage) == 0xc4`
  records. Their `0x2648` extent is exactly the Windows
  `Size of cRSubGarbage` ledger value.
- `GarbageHazardSlot` remains only a compatibility alias for older scratch
  vocabulary. The primary shared owner is now `SubGarbage`.

## 2026-07-14 renderable inheritance closure

`SubGarbage` now derives directly from the `RenderableBod` initialized here.
This retires its duplicated `BodBase + TransformMatrix` fields without a union
alias or raw prefix. The constructor remains exact at 7/7 instructions with
both operands clean, independently proving the zero-offset base call.

## 2026-07-15 analysis-lane replay

The narrow Binary Ninja replay now declares `SubGarbage` as a 0xc4-byte owner
with `RenderableBod body` at `+0x00`, and `SubGarbagePool` as a 0x264c-byte
wrapper with 50 inline records. Binary Ninja and IDA both read this constructor
back as `SubGarbage* __thiscall(SubGarbage*)`; the old flattened
`GarbageHazardRuntime` analysis shell is retired.
