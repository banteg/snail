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
