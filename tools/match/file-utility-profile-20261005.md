# File-utility run compiler profile

Date: 2026-10-05

The native run `0x430f30`-`0x431d60` (archive/file access, tracked allocation,
and the `report_*f` wrappers) had per-function profiles that alternated:

| address | function | previous profile |
|---|---|---|
| `0x430f30` | `set_current_directory_with_drive_fallback` | msvc6.5 `/TC` |
| `0x431030` | `load_file_bytes_fixed_size_from_archive_or_fs` | msvc6.0 C++ |
| `0x431250` | `find_archive_entry` | msvc6.5 `/TC` |
| `0x4312d0` | `load_file_bytes_from_archive_or_fs` | msvc6.0 C++ |
| `0x431540`-`0x4319c0` | `delete_file_path_with_directory_walk`, `write_file_bytes`, `load_archive_index` | msvc6.5 `/TC` |
| `0x431cc0`-`0x431d60` | `report_errorf`, `report_warningf`, `report_messagef` | msvc6.5 `/TC` |

The `/TC` choices were justified only by codegen shape (cdecl cleanup
coalescing). One linked object is one language, so C-only and C++-only
profiles cannot interleave function by function. The two msvc6.0 members and
the tracked-allocation helpers do not compile as C at all.

Control: every scratch in the run compiled with its unchanged source under
four profiles.

| profile | exact in the run |
|---|---|
| recorded (mixed) | 23 of 24 |
| msvc6.0 C++ | 23 of 24 |
| msvc6.5 C++ | 15 of 24 |
| msvc6.0 C | 14 of 24 (9 fail to compile) |

`enumerate_matching_archive_or_fs_entries` is 92.31% under every profile.
Only msvc6.0 compiling C++ explains the whole run, and the Rich header records
msvc6.0's build 8168 for C++ objects. All 24 scratches now use
`COMPILER=msvc6.0` without `/TC`; every exact match holds.

The six `/TC` scratches outside this run (`0x4051d0`-`0x405370`, `0x406d30`,
`0x42f490`, `0x448960`) keep their profile. Build 8966 appears in the Rich
header only on C objects, so msvc6.5 `/TC` has aggregate support there, and no
neighbouring evidence contradicts it. msvc6.0 C++ also reproduces the five
exact ones; `rebuild_game_archive_if_needed` falls from 66.38% to 25.22%.
