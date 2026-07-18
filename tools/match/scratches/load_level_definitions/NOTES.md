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
  `SMTracks` receiver used by `load_segment_definitions`. This method's
  current body does not read `this`; it writes the separate level-definition
  store at `GameRoot +0x224804`. Keeping the thiscall receiver records the
  native ownership without inventing a cdecl shim.

2026-07-11 ownership closure: `GameRoot +0x224804` is exactly
`GameRoot::subgame.level_definition_scratch` (`SubgameRuntime +0x1b01ec`). It
is the second complete `0x1a5978` `SubTracks` constructed beside
the active gameplay definition. Typing the nested receiver preserves the exact
`100.00%`, 30/30 result with all six operands clean.

2026-07-11 cross-port owner closure: symbol-preserving iOS builds name this
void member `cRSMTracks::OpenLevels()`. Renaming the exact 0x25cfb4-byte owner
to `SMTracks` and removing the synthetic count result preserves proof grade at
100.00%, 30/30 instructions, with all six operands clean.

2026-07-14 canonical level-store root: the enumerator now reaches the second
owned `SubTracks` through `g_game->subgame.level_definition_scratch`, without
discarding the root type at the singleton reload. It remains exact at 30/30
instructions with all six operands clean.

## 2026-07-18 cross-tool replay closure

Strict six-function export now preserves the exact void `SMTracks` member in
IDA and the nested root-owned `SubTracks` receiver in both decompilers. Replay
verifies the full catalog and level-definition owner sizes before applying the
six member prototypes, preventing the 150-entry catalog or 100-slot active
definition from silently drifting across adjacent root storage. Dedicated
health checks reject the former incidental `int32_t` return and raw
`g_game_base + 0x224804` view. The source remains proof-grade at 100.00%,
30/30 instructions, with all six operands clean.
