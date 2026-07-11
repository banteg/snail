# load_level_definitions @ 0x448900

Initial shape:

- Enumerates `Levels/*.txt` through `enumerate_matching_archive_or_fs_entries`
  into a 0x4000-byte stack buffer.
- Walks the resulting names as 0x80-byte entries.
- Loads each entry through `load_level_definition_file(game+0x224804, name)`.

Status:

- 2026-06-18: 100%, 30/30 target instructions, 6 masked operands ok.
- The large stack frame emits the VC runtime `chkstk` stack-probe helper at
  `0x48bf30`; the shared reference manifest now names it so the masked audit
  remains proof-grade.
- Startup sets `ecx = GameRoot +0x1075ae4` before this call, the same complete
  `SegmentCatalog` receiver used by `load_segment_definitions`. This method's
  current body does not read `this`; it writes the separate level-definition
  store at `GameRoot +0x224804`. Keeping the thiscall receiver records the
  native ownership without inventing a cdecl shim.

2026-07-11 ownership closure: `GameRoot +0x224804` is exactly
`GameRoot::subgame.level_definition_scratch` (`SubgameRuntime +0x1b01ec`). It
is the second complete `0x1a5978` `SubTracks` constructed beside
the active gameplay definition. Typing the nested receiver preserves the exact
`100.00%`, 30/30 result with all six operands clean.
