# select_level_track_texture_set

Small level texture-set mutator at `0x410730`.

- `TextureSetSelector +0x00` and `+0x10` are two four-entry texture-ref banks.
- `+0x20` stores the active texture-set index.
- Argument `5` selects a random set in `[0, 4)`.
- A changed set rewrites both texture banks through
  `replace_object_list_texture_refs` on `g_object_list`.

The native caller ignores the return register, and the changed path only leaves
whatever the texture-replacement helper leaves in `eax`, so this is modeled as a
`void` mutator rather than a meaningful `int`-returning getter.
