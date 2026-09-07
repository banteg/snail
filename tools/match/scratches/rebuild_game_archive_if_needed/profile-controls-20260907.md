# 2026-09-07 unchanged-source compiler controls

The checksum-valid canonical Rich header contains ordinary VC6 C++ records
for build families 8168, 8447, and 8966. This independently motivates a bounded
comparison with the available 8168 and 8447 component sets after the source
investigations; it does not assign any function to a compiler build. See the
limitations in the [matching README](../../README.md).

The local `msvc6.3` profile contains these versioned components:

| Component | File version | SHA-256 |
| --- | --- | --- |
| CL.EXE | 12.0.8168.0 | `91ca0dde4ef7fb4b4c1f5c6ebe1921d903f6149aa69f7f68a4323d375a14696c` |
| C1XX.DLL | 12.0.8472.0 | `28c355499c2f8090910624734faff31fe719a69a8aac7dd44b2ce64addf96ee2` |
| C2.DLL | 12.0.8447.0 | `a0cc45f83fd0ed009aa4f43df5598105a1049ad9675de0b1089be7cce7d3c153` |

Recorded `msvc6.3 /O2 /G5 /W3` probes preserve the current generated code of
all five C++ platform candidates below. They do not resolve any reference debt:

| Function | Match | Candidate / target instructions | Prefix | References: clean / mismatched / unaudited |
| --- | ---: | ---: | ---: | ---: |
| game_startup_and_main_loop | 93.83% | 323 / 325 | 176 | 162 / 0 / 1 |
| initialize_game_window_and_input | 92.48% | 266 / 266 | 6 | 57 / 0 / 0 |
| set_immediate_blend_mode | 89.30% | 135 / 136 | 2 | 21 / 1 / 1 |
| draw_textured_quad_immediate | 98.34% | 331 / 332 | 111 | 26 / 0 / 0 |
| enumerate_matching_archive_or_fs_entries | 92.31% | 182 / 182 | 9 | 26 / 0 / 0 |

For the rebuild helper, the current C source remains 66.38%, 232/232
instructions, prefix 5, with 22 clean references under `msvc6.3` and `/TC`.
The ordinary C++ library-declaration control is also 66.38%. The previously
recorded structured C++ seed remains 73.87%, 231/232, prefix 5, with all 22
references clean. Thus neither language-correct control nor the structured
source gains anything from this alternate component set.

Twelve unchanged neighbors retain complete normalized instruction equality and
clean references under `msvc6.3` (557 native instructions total):

| Control | Instructions |
| --- | ---: |
| initialize_direct3d_renderer | 12 |
| set_blend_mode | 92 |
| render_game_frame_scene | 24 |
| present_backbuffer | 9 |
| configure_sprite_render_state | 109 |
| bind_texture_ref | 62 |
| game_window_proc | 141 |
| show_and_focus_game_window | 33 |
| minimize_game_window | 10 |
| initialize_main_loop_display_state | 8 |
| classify_archive_entry_extension | 46 |
| toggle_archive_high_bit_in_place | 11 |

The rendering subset contributes 308 instructions. These controls support the
component comparison but do not distinguish the original compiler of the
partial functions: both the controls and their residuals are unchanged.

Three additional core residuals were checked with unchanged source under both
`msvc6.0` and `msvc6.3`, keeping `/O2 /G5 /W3`:

| Function | Match | Candidate / target instructions | Prefix | Clean references |
| --- | ---: | ---: | ---: | ---: |
| switch_track_mirror | 91.23% | 27 / 30 | 20 | 3 |
| border_mouse_test | 98.29% | 117 / 117 | 73 | 5 |
| load_galaxy_layout | 99.14% | 233 / 233 | 194 | 42 |

All six core probes preserve the current extracted-code hash. The duplicated
mirror return, mouse row-product destination, and galaxy latch ordering remain
unresolved. No compiler setting or source change is promoted from this pass.
Each function's `experiments.jsonl` retains the source, dependency, and code
hashes plus complete comparison metrics. These results bound the tested
profiles and source forms; they do not establish source exhaustion.
