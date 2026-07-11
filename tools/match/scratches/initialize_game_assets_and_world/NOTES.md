# initialize_game_assets_and_world @ 0x40acf0

Starter scratch for the large root-world bootstrap.

This is intentionally a semantic partial, not a line-for-line transcription. It
captures the recovered early root defaults, texture/object-list startup, overlay
registration, landscape/menu/audio/font/sprite setup, the first backdrop/pillar
world-object islands, and a small track-template setup island. The body remains
raw-offset based because the cRGame/cRSubGame root layout is far larger than the
currently shared headers expose.

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
