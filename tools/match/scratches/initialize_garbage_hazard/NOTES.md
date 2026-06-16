# initialize_garbage_hazard

`initialize_garbage_hazard` @ 0x408550 is exact and now uses the shared
`GarbageHazardSlot` view instead of a one-off local `GarbageHazardRuntime`
shell.

The initializer calls the shared renderable-BOD initializer on the same zero
offset object, then installs the garbage vtable. This cross-confirms that
`GarbageHazardSlot` now inherits the shared `BodNode` view. `BodNode` itself
inherits the `ContactTargetObject` prefix, so the same zero-offset object can
participate in the active/free BOD list and can be passed to
`append_subgame_contact_target` for the `list_flags & 0x1000` contact-suppress
gate. The slot has list links at `+0x08/+0x0c` and a renderable transform at
`+0x38..+0x77`; the live collision position used by spawn/update/collision is
the transform position row at `+0x68`.

Implementation caveat: the shared header keeps the transform rows field-by-field
instead of as a `TransformMatrix` union alias because VC6 rejects unions whose
members have constructors. That preserves the proven `world_position` member and
keeps all garbage-family match baselines unchanged.
