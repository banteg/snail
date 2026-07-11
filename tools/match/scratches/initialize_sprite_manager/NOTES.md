# initialize_sprite_manager

Proof-grade 100.00% match: 45/45 instructions, one clean masked call operand.

The exact source recovers the whole `SpriteManager` pool owner without raw
offsets:

- `paused` is cleared before any list setup;
- a five-iteration source loop clears `active_heads`; VC6 unrolls this loop into
  the five direct manager-relative stores present in the native function;
- `free_head` points at `sprites[0]`;
- every one of the 3000 embedded `Sprite` entries is initialized; and
- `prev`/`next` link the pool into a null-terminated free list, with typed
  first, middle, and last-node cases.

The key source-shape correction was replacing the earlier decompiler-shaped
`memset` with the bounded `active_heads` loop. The `memset` form materialized a
temporary bucket pointer and stalled at 50.55%; the owner-aware loop produces
the native unrolled stores and register schedule. Using typed `sprites[index]`
accesses for initialization and list linking remains exact, including the
native last-node store order. No scheduling-only or assembly-shaped constructs
are retained.

The owner and layout are corroborated by `allocate_sprite`, `kill_sprite`,
`kill_game_sprites`, `run_frame_update`, and the iOS symbol
`cRSpriteManager::Init()`:

- `paused` at `+0x00000`;
- `sprites[3000]` at `+0x00004`, stride `0xb4`;
- `active_heads[5]` at `+0x83d64`; and
- `free_head` at `+0x83d78`.
