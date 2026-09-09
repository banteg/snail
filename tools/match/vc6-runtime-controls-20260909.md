# VC6 runner and precompiled-header controls

The same VC6 SP5 compiler emits identical function bytes and relocation
identities under patched Wibo and CrossOver Wine for all 16 tested functions.
Twelve partial functions retain their existing mismatches, and four exact
controls remain exact. These results do not add exact-function credit or prove
that either runner implements every Windows API correctly.

The [receipt](vc6-runtime-controls-20260909.json) records the source commit,
source and dependency hashes, compiler/runtime hashes, complete probe recipes,
function fingerprints, raw-body hashes, instruction counts, prefixes and
reference audits. The recorded objects and current inputs were independently
re-read before preserving the receipt.

## Runner comparison

Both runners execute the same `CL.EXE`, `C1XX.DLL` and `C2.DLL` with the
scratch's unchanged `msvc6.5 /O2 /G5 /W3` profile. Source generation preserves
registered translation-unit context for the two exact controls which need it.
CrossOver 26.1.0.39808 runs in an isolated temporary Windows 10 bottle; the
comparison does not modify existing bottles. Wibo is `1.2.0-3-g08b7997`, with
SHA-256 `917017253dac31557825aecffb117fc0c96221271b5c812fac3f704407fd0cc7`.

The partial functions are `draw_frontend_widget`, `create_golb`,
`update_golb_ai`, `read_repeating_text_input_key_code`, `switch_track_mirror`,
`set_snail_jetpack`, `load_galaxy_layout`, `border_mouse_test`,
`initialize_star_field`, `firework_shoot`, `initialize_quaternion_from_matrix`
and `sample_smtrack_heightmap`. The exact controls are
`read_pressed_text_input_key_code`, `initialize_galaxy`,
`play_subgoldy_shoot_sfx` and `load_frontend_level_by_mode_and_index`.

Identity here includes raw extracted function bytes and COFF relocation
metadata, not just normalized assembly or the fuzzy score. It establishes
runner-independent emission for these inputs. It does not identify the
original source or explain the remaining native scheduling differences.

## Precompiled-header comparison

The same twelve partials were also compiled normally, while creating a PCH
with `/Yc`, and while reusing it with `/Yu`. The boundary is a `#pragma hdrstop`
inserted after the scratch's last literal include. This is a controlled header
boundary, not a claim to have recovered the original project's PCH.

All twelve extracted function bodies are byte-identical across the three
modes. Eleven also retain identical relocation fingerprints. In
`update_golb_ai`, PCH reuse renames the compiler-local jump-table symbol from
`$L6063` to `$L6062`; the instruction bytes and audited ordered destinations
remain unchanged. The receipt retains both relocation records so that this
symbol-name difference is not silently normalized away.

These controls show that using this PCH boundary does not repair the tested
partials. Other original source or header contexts remain untested. No
canonical C++ source, compiler profile, or matching threshold is changed.
