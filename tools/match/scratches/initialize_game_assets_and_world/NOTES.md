# initialize_game_assets_and_world @ 0x40acf0

Starter scratch for the large root-world bootstrap.

This is intentionally a semantic partial, not a line-for-line transcription. It
captures the recovered early root defaults, texture/object-list startup, overlay
registration, landscape/menu/audio/font/sprite setup, the first backdrop/pillar
world-object islands, and a small track-template setup island. Recovered root,
subgame, viewport, overlay, player-camera, landscape, catalog, and menu owners
are typed; unrecovered later islands remain raw-offset based.

Expected residuals:
- most later path-template, pickup, replay, score, and frontend pools are not
  modeled yet;
- several list-link operations are expressed through a local helper, while the
  target has the inline intrusive-list sequence;
- string literals are used for concrete asset paths recovered from the binary,
  so masked-operand audit may still need reference-manifest promotion later.

2026-06-20 font bootstrap audit: the native FONT-MENU-HOVER setup call pushes
`0x3f400000` (`0.75f`) for the width scale and `0x3f800000` (`1.0f`) for the
height scale. The old scratch used `0.800000012f` and a `double` height
argument, which produced an extra high-dword push. The call now targets the
named startup wrapper at `0x432d20`:

```asm
00432d20  mov eax, [esp+0x10]
00432d24  mov ecx, [esp+0x0c]
00432d28  mov edx, [esp+0x08]
00432d2c  push eax
00432d2d  mov eax, [esp+0x08]
00432d31  push ecx
00432d32  push edx
00432d33  push eax
00432d34  call register_font_texture_sheet
00432d39  add esp, 0x10
00432d3c  ret
```

2026-06-20 reference audit: promoted the remaining raw startup globals used by
this semantic partial: `g_sprite_depth_buckets` (`0x4f7050`), the DirectX loader
scratch buffer (`0x74eb18`), and the startup sound-bank table
`g_sound_bank_entries` (`0x4a2140`). The existing built-in segment table is now
referenced as `g_builtin_segment_definitions`. Focused Wibo is still `4.73%`,
but masked audit now has no unresolved operands.

## 2026-07-10 path-constructor ownership

The constructor island spans the same embedded bank initialized through the
subgame view:

```text
GameRoot + 0x1066f2c
= GameRoot + 0x74618 + 0xff2914
= SubgameRuntime + 0xff2914
```

- Public `Path=` slots `0..50` occupy consecutive `0x150` pairs.
- The call at `0x40cda0` targets pair `42` (`game +0x106a64c`) and proves
  `initialize_halfpipe_path_template_pair` is the Windows `HALFPIPE` builder.
- Public pair `30` (`WARP`, `game +0x106968c`) has no constructor or later
  direct authored-code reference; it remains only generically initialized.
- Pairs `51..62` duplicate public families `0..7`, `25..27`, and `41`. Their
  strip meshes are installed as the public records' `+0xa0` transition meshes;
  `+0xa4` points back to the public records' own strip meshes.

## 2026-07-11 early subgame ownership

The bootstrap now uses the embedded `SubgameRuntime` directly for its pause
gate, blink-table initialization, rate setup, and `level_mode_arg` handoff.
This corrects two stale raw offsets in the semantic partial:

- the pause gate is root `+0x74621` (`SubgameRuntime +0x09`), not `+0x74659`;
- the mode argument is root `+0x7465c` (`SubgameRuntime +0x44`), not
  `+0x74654`.

The recovered thiscall shape removes the scratch's cdecl blink/rate shims and
raises the focused partial from 4.73% to 4.84% while keeping all operands
resolved (55 clean, 21 expected residual mismatches). This is still a semantic
partial of the 5,411-instruction bootstrap; the score change is supporting
evidence, not a completeness claim.

The Binary Ninja runtime sync was also made field-only when
`SubgameRuntime` already exists. Its sparse import header can seed a fresh
database, but it no longer flattens later `BodBase`, pool, and `Player`
ownership when adding these blink fields.

## 2026-07-11 root viewport and startup-service ownership

The early bootstrap now follows the constructor-proven `GameRoot` layout:

- `player_count +0x40`, `frontend_link_latch +0x568`, the constructed inactive
  BOD sentinel at `+0x570`, and the active/free list anchor at `+0x5a8` replace
  duplicate raw words;
- three complete `Overlay` objects live at `+0x67c/+0x7c8/+0x914`, with their
  embedded cameras at `+0x6fc/+0x848/+0x994`;
- viewport 0 borrows overlay 0, viewport 2 borrows overlay 1, viewport 3
  borrows overlay 2, and viewports 1/4 borrow player 0/1 cameras. The recovered
  sort keys, scene flags, viewport rectangles, and player camera masks are now
  source-spelled through those owners;
- the inline BOD linker correctly reaches the global root list at `+0x5ac`.

The same target island proves the startup-service receivers and corrects stale
offsets in the old semantic partial:

- `LandscapeScriptBank` at root `+0x106c218` owns reset plus the Starmap,
  Splash, Help, and Menubg script loads;
- the exact `0x25cfb4`-byte `SegmentCatalog` at `+0x1075ae4` owns both segment
  and level enumeration calls;
- challenge setup at subgame `+0x125ffe0` and thanks at `+0x126000c` use the
  same folded `bind_subgame_owner`, while galaxy and the embedded player's
  cameraman keep their distinct methods;
- audio configuration is owned by `OptionsMenu +0x4f388`, and the built-in
  level slot store is root `+0x224804` rather than the stale `+0x224a04`.

Focused Wibo is now 5.65%, with 358/5,411 candidate/target instructions,
prefix 0/5,411, 73 clean masked operands, no unresolved operands, and 18
expected mismatches across the still-sparse semantic partial. The native
`0x12c` frame and its first stack-local `noop_this_constructor` remain absent,
as do most later world and path-template islands; no score-only scaffolding was
added to imitate them.

## 2026-07-11 sprite render workspace ownership

The startup clear now uses the shared typed
`g_sprite_depth_buckets[SPRITE_DEPTH_BUCKET_COUNT]` owner rather than a local
`char[]` declaration and magic `0x400` size. `render_game_frame` proves all 256
heads and the adjacent 3000-entry `g_sprite_depth_nodes` workspace; using
`sizeof(g_sprite_depth_buckets)` preserves the native clear exactly.

## 2026-07-11 root frame counters

The early zero stores at root `+0x518/+0x51c` now use
`fixed_update_accumulator` and `frame_counter`. `run_frame_update` proves their
per-frame increment/consume behavior, `allocate_border` independently reads
the frame counter as a creation timestamp, and `update_game_input` proves the
adjacent `input_sampling_gate +0x520`. This naming is codegen-neutral within
the still-semantic startup partial, which remains at 5.65%.

## 2026-07-11 config selector ownership

The early handoff into `SubgameRuntime::level_mode_arg` now reads
`RuntimeConfig::landscape_backdrop_variant_selector` at config offset `+0xa4`
instead of the raw `unk_4DF9BC` spelling. The instruction stream and 5.65%
semantic score are unchanged, while the masked audit improves from 73 clean / 18
mismatched operands to 74 clean / 17 mismatched operands.
