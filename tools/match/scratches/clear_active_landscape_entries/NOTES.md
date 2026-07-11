# clear_active_landscape_entries @ 0x418a30

Exact match: 49/49 instructions, clean masks.

This `LandscapeManager` helper clears its ten active landscape slots starting
at receiver `+0x00`.

Recovered layout evidence:

- slot stride is `0x90`, matching `ActiveLandscapeEntry`.
- linked slots have inherited `list_flags & 0x200` set.
- state at `+0x80` is cleared before unlinking.
- unlink uses the active BOD list at `Game+0x5a8`, then pushes the slot node to
  that list's free stack.

Source-shape note: the native loop uses a cursor at the inherited
`list_next` field (`this + 0xc`), so the typed `entry` cursor still compiles to
`lea esi, [ecx+0xc]`. The two `flags` reads are intentionally separate; native
reloads the flags after clearing state and before the guarded unlink.

Promoting the receiver from the false first-entry view to the complete manager
is codegen-neutral: focused matching remains exact at 49/49 with five clean
operands.
