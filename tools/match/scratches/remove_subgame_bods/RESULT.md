# `remove_subgame_bods` match result

Focused scratch for `Game::remove_subgame_bods @ 0x440910`.

Final focused run:

```text
match: 59.90%
target: 501 insns, candidate: 494 insns
prefix: 6/501 target insns
masked operands: 58 ok, 0 unresolved, 2 mismatch
```

The scratch covers the full side-effect sequence:

- 3200 runtime row BOD nodes plus each row's eight sub-lazer projectile slots;
- track render cache BOD cleanup;
- health, speedup, jetpack, garbage, slug, and ring/special-effect runtime slots;
- the singleton score/player body nodes around `game+0x3bb764`, `game+0x3be0e8`, `game+0x3bf2c8`, and `game+0x3be734`;
- helper recycling for the three late BOD nodes;
- Golb shot cleanup and final `SpriteManager::kill_game_sprites()`.

Known residuals:

- First structural register mismatch is the row-cell cursor:
  native keeps it in `edi` while the candidate keeps it in `ebx`.
- That cascades into the post-render-cache half: native reloads `this` into
  `ebx` and zeroes `ebp`; candidate keeps `this` in `ebp` and hoists
  `~0x200` into `ebx`.
- The two masked-audit mismatches are string-literal order mismatches in the
  speedup/jetpack singleton unlink blocks:
  - target `0x440a82`: `"List remove NEXTBOD"`, candidate aligned against
    `"List remove"`;
  - target `0x440af3`: `"List remove"`, candidate aligned against
    `"List remove NEXTBOD"`.

Rejected probes:

- Initial typed owner-loop version matched 46.54% with a clean masked audit,
  but left much more of the function shape unrecovered.
- The cursor-loop rewrite recovered the full row/slot cleanup topology and
  raised the score to 59.90%.
- A zero-aware list-removal macro, first-row declaration reordering, a
  `register` hint for the row-cell cursor, and a dedicated `zero` local did not
  improve the register allocation or masked audit.
