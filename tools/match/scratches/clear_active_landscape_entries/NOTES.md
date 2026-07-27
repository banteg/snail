# clear_active_landscape_entries @ 0x418a30

Exact match: 49/49 instructions, clean masks.

This `LandscapeManager` helper clears its ten active landscape slots starting
at receiver `+0x00`.

Recovered layout evidence:

- slot stride is `0x90`, matching `ActiveLandscapeEntry`.
- linked slots have inherited `list_flags & 0x200` set.
- state at `+0x80` is cleared before unlinking.
- unlink borrows `GameRoot::active_bod_list`, then pushes the slot node to that
  list's free stack.

Source-shape note: the native loop uses a cursor at the inherited
`list_next` field (`this + 0xc`), so the typed `entry` cursor still compiles to
`lea esi, [ecx+0xc]`. The two `flags` reads are intentionally separate; native
reloads the flags after clearing state and before the guarded unlink.

Promoting the receiver from the false first-entry view to the complete manager
is codegen-neutral: focused matching remains exact at 49/49 with five clean
operands.

2026-07-14 root-list closure: the manager-owned entries now borrow the
canonical root active/free list instead of reconstructing it from `+0x5a8`.
The lifecycle remains exact at 49/49 with all five operands clean.

2026-07-14 extent ownership: the teardown loop now derives its bound from
`LandscapeManager::active_entries`. The normalized listing remains
byte-identical
(`a663ed2ee953e6f01b4857d201b800bc443ea2d205c28751ee62c5fecbe956f0`)
and exact at 49/49 instructions with five clean operands.

## 2026-07-27 mobile authored owner

Android and iOS retain the teardown boundary as
`cRLandscapeManager::UnInit()` from `Landscape.o`, but both bodies are empty.
This is a platform split rather than a rejected match: Android
`cRSubGame::UnInit()` calls warning teardown, landscape `UnInit`, times-up
teardown, and `RemoveBods` in the same order as Windows `destroy_subgame`
calls `uninit_warning`, this helper, `uninit_times_up`, and
`remove_subgame_bods`.

The mobile renderer has no Windows-style pool of ten repeated DirectX
landscape entries, so it has nothing to unlink. Windows' exact 49/49 body is
the desktop implementation of the shared authored `UnInit()` lifecycle.
