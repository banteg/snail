# append_subgame_contact_target

append_subgame_contact_target @ 0x415ef0 appends one contact target to the
per-frame subgame registry at `game+0x1270fd4`.

Recovered semantics:

- thiscall owner is a count-prefixed registry;
- stack arguments are `(position, radius, kind, object)`;
- `object+0x04 & 0x1000` suppresses the append;
- each entry is 24 bytes after the leading count, laid out as
  `{kind, position.xyz, radius, object}`.

Residuals:

- 2026-06-13: exact under the standard `msvc6.5 /O2 /G5 /W3`
  configuration. The matching source shape uses repeated `entries[count]`
  member access instead of caching `count` or an entry pointer; that matches
  the native reloads of the registry count before the kind, position, radius,
  object, and final increment stores.
- 2026-06-16 contact-target consolidation: `ContactTargetObject`,
  `ContactTargetEntry`, and `ContactTargetRegistry` now live in
  `include/contact_target.h`. The skip bit is named as
  `ContactTargetObject::list_flags & 0x1000`, and the focused match remains
  exact at 100.00%, 34/34 instructions.
- 2026-06-16 BOD/contact prefix correction: `ContactTargetObject +0x00` is now
  named as the shared vtable pointer rather than an unknown integer. This keeps
  the exact append helper unchanged and aligns the contact prefix with
  `GarbageHazardSlot` initialization through the renderable-BOD path.
