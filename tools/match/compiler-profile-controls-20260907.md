# 2026-09-07 selector/search compiler controls

The canonical image has a checksum-valid Rich header with ordinary VC6
records for 10 C++ contributions from build 8168, 56 C++ contributions from
build 8447, and 23 C contributions from build 8966. That motivates this bounded
unchanged-source comparison after the source-lifetime probes; it does not
assign a compiler build to an authored translation unit. The current default
remains `msvc6.5 /O2 /G5 /W3`. The earlier platform/three-core controls are
recorded [separately](scratches/rebuild_game_archive_if_needed/profile-controls-20260907.md).

These components were read from the local PE version resources and hashed
before compilation:

| Profile | Component | File version | SHA-256 |
| --- | --- | --- | --- |
| msvc6.0 | CL.EXE | 12.0.8168.0 | `91ca0dde4ef7fb4b4c1f5c6ebe1921d903f6149aa69f7f68a4323d375a14696c` |
| msvc6.0 | C1XX.DLL | 12.0.8168.0 | `71554a7688395ff592f5ac0f2e0413788d256bb869123e39e81b6da5e12c086e` |
| msvc6.0 | C2.DLL | 12.0.8168.0 | `74c7ed7d01461785766e73812a4c3420ed728e2048ae3c9d525c2e347376c670` |
| msvc6.3 | CL.EXE | 12.0.8168.0 | `91ca0dde4ef7fb4b4c1f5c6ebe1921d903f6149aa69f7f68a4323d375a14696c` |
| msvc6.3 | C1XX.DLL | 12.0.8472.0 | `28c355499c2f8090910624734faff31fe719a69a8aac7dd44b2ce64addf96ee2` |
| msvc6.3 | C2.DLL | 12.0.8447.0 | `a0cc45f83fd0ed009aa4f43df5598105a1049ad9675de0b1089be7cce7d3c153` |

Both profiles give the following results under `/O2 /G5 /W3`. All source files
are unchanged; their probe receipts are retained in each scratch ledger.

| Function | Match | Candidate / native instructions | Prefix | References ok / mismatch / unaudited |
| --- | ---: | ---: | ---: | --- |
| set_snail_jetpack | 86.18% | 61 / 62 | 0 | 8 / 0 / 0 |
| select_level_track_texture_set | 76.19% | 41 / 43 | 0 | 6 / 1 / 0 |
| try_enter_track_attachment_from_swept_motion | 95.78% | 199 / 204 | 16 | 47 / 0 / 0 |
| update_frontend_state_machine | 100.00% | 180 / 180 | 180 | 69 / 0 / 0 |
| calc_path_length_z | 100.00% | 113 / 113 | 113 | 9 / 0 / 0 |
| is_point_inside_track_attachment | 100.00% | 111 / 111 | 111 | 6 / 0 / 0 |
| build_snail_world_hotspots | 100.00% | 44 / 44 | 44 | 1 / 0 / 0 |

The two profiles also preserve each other's extracted-code hashes for all
seven functions. The four exact controls cover 448 native instructions. The
selector/default parameter reloads and the swept-search miss epilogue remain
unresolved. There is no compiler-profile promotion.

Full comparisons against the default profile confirm identical normalized
instruction streams for all three partials. The texture selector's private
COFF jump-table name differs (`$L1232` versus `$L1181`), but its same default
destination mismatch remains exposed by the reference audit.

## Path-builder controls

An unchanged-source comparison also covers five partial path builders and two
exact path controls. Each was compiled with the default profile and the same
two independently identified VC6 profiles above, using `/O2 /G5 /W3`.

| Function | Match under all three profiles | Candidate / native instructions | Prefix | Clean references |
| --- | ---: | ---: | ---: | ---: |
| initialize_sbend_path_template_pair | 91.10% | 578 / 579 | 443 | 39 |
| initialize_snake_path_template_pair | 88.19% | 652 / 652 | 387 | 40 |
| initialize_sweep_path_template_pair | 84.66% | 652 / 652 | 32 | 37 |
| initialize_slalom_path_template_pair | 80.66% | 695 / 696 | 48 | 40 |
| initialize_twister_path_template_pair | 85.78% | 680 / 677 | 129 | 49 |
| calc_path_length_z | 100.00% | 113 / 113 | 113 | 9 |
| get_path_nodes | 100.00% | 23 / 23 | 23 | 4 |

All seven normalized instruction streams are identical across the three
profiles. The extracted-code hashes also agree except for Twister, whose
complete normalized disassembly was compared separately. Twister's row is the
source before the subsequent face-column scope recovery. The exact controls
cover 136 native instructions. No compiler override is retained; these results
do not identify the compiler of an individual original translation unit.

## Preserved VC7 archive identity

The canonical Rich header also records build 9178 with product IDs 28 and 29
(four C and 67 C++ contributions). The
[preserved compiler release](https://github.com/OmniBlade/decomp.me/releases/tag/msvcwin9x)
offers an asset named `msvc7.0.tar.gz`. Downloading that exact asset and reading
the archived PE resources establishes that its name is insufficient provenance:
`Bin/cl.exe`, `Bin/c1.dll`, `Bin/c1xx.dll` and `Bin/c2.dll` all report
**13.10.3077.0**, rather than build 9178.

The archive is 33,368,894 bytes with SHA-256
`49eba7f9f72644f6f872a4176baeac544e8b5dfb2be1f47bb4d439b1136ffeac`.
Its C++ frontend hash is
`353f3d5dcd050b876e1c044b99c4bf47958d255f395a4919f406a19921be4dfa`;
its backend hash is
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
It was inspected in temporary storage and was neither installed as a compiler
profile nor used for matching. This check does not resolve the ownership of
the image's build-9178 contributions.
