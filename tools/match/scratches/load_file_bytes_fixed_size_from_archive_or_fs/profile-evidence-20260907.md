# VC6 C++ profile evidence for the fixed-size archive loader

The retained loader at `0x431030` matches all 188 instructions and all 32
reference operands with the ordinary `msvc6.0 /O2 /G5 /W3` C++ profile.
The same recovered source produces 189 instructions at 97.08% under the
project-standard SP5-style C++ profile; the remaining difference is one early
cdecl argument cleanup around `_getcwd` and the following report call.

## Independent provenance and language evidence

- The canonical executable has SHA-256 `d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5`.
- Its Rich header checksum is valid (`0xc5bcc11a`). Product 11/build 8168
  (`0x000b1fe8`) has count 10, recording VC6 C++ contributions from that build.
- The verified Android `_Z20RShellLoadFileHeaderPcPvi` and iOS symbol of the
  same name establish `RShellLoadFileHeader(char*, void*, int)` in `RShell.o`.
  They support the C++ contract; mobile instruction bytes are not Windows
  compiler provenance.
- Rich entries aggregate objects and library members. They do not identify
  which object owns `0x431030`, so no exact original object/build mapping is
  claimed.

## Native control matrix

All controls use their unchanged canonical source and explicit C++ flags
`/O2 /G5 /W3`. Each profile replay is recorded with source and code hashes in
that control's `experiments.jsonl`. All 8168 results have full instruction
prefixes and clean references. Six controls distinguish the profiles; the
others verify compatibility across the same address neighborhood.

| Control | Native insns | SP5-style C++ | 8168 C++ | Clean references (8168) |
|---|---:|---:|---:|---:|
| initialize_game_data_archive | 47 | 100.00% (47) | 100.00% (47) | 20 |
| uninitialize_game_data_archive | 13 | 100.00% (13) | 100.00% (13) | 6 |
| set_current_directory_with_drive_fallback | 48 | 86.60% (49) | 100.00% (48) | 6 |
| archive_or_file_exists | 36 | 100.00% (36) | 100.00% (36) | 7 |
| find_archive_entry | 60 | 100.00% (60) | 100.00% (60) | 2 |
| load_file_bytes | 8 | 100.00% (8) | 100.00% (8) | 1 |
| delete_file_path_with_directory_walk | 84 | 91.57% (82) | 100.00% (84) | 14 |
| write_file_bytes | 74 | 93.33% (76) | 100.00% (74) | 10 |
| load_archive_index | 67 | 100.00% (67) | 100.00% (67) | 14 |
| report_errorf | 19 | 82.93% (22) | 100.00% (19) | 8 |
| report_warningf | 19 | 82.93% (22) | 100.00% (19) | 8 |
| report_messagef | 15 | 83.87% (16) | 100.00% (15) | 4 |

The twelve controls total 490 native instructions.
Their scratch configurations remain unchanged. In particular, this comparison
uses explicit C++ flags even for the older controls retained with `/TC`.
It does not silently relabel C output as C++ output or promote a translation unit.

## Reproduction component identities

The local profile components all report file version `12.0.8168.0`:

| Component | SHA-256 |
|---|---|
| CL.EXE | `91ca0dde4ef7fb4b4c1f5c6ebe1921d903f6149aa69f7f68a4323d375a14696c` |
| C1XX.DLL | `71554a7688395ff592f5ac0f2e0413788d256bb869123e39e81b6da5e12c086e` |
| C2.DLL | `74c7ed7d01461785766e73812a4c3420ed728e2048ae3c9d525c2e347376c670` |

Reproduce a control with:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run snail match probe \
  tools/match/scratches/report_messagef \
  --source tools/match/scratches/report_messagef/scratch.cpp \
  --compiler msvc6.0 --cflags '/O2 /G5 /W3' --json
```

The loader's source sweeps preserve the rejected buffer, linkage, result-width,
and loop alternatives. No extra helper is retained for cleanup scheduling,
and no volatile access, assembly barrier, or dummy symbol is introduced.
