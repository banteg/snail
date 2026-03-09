# Port Status

This page is the short ledger for what the Zig runtime currently treats as verified, partial, fallback, scaffold, or debug-only.

Code-level convention:

- `PORT(verified)`: backed by static RE or runtime captures strongly enough to treat as ported behavior
- `PORT(partial)`: on the right path, but still missing some semantics or coverage
- `PORT(fallback)`: deliberate approximation or candidate layer, not the original runtime behavior yet
- `PORT(scaffold)`: temporary shell or structural placeholder to support forward-pass work
- `PORT(debug)`: intentionally non-shipping tooling or inspection code

Current high-signal entries:

- boot and main-menu shell: `scaffold`
  - evidence: original loading-screen assets and recovered main-menu labels are now wired, but the overall front-end flow and most handlers are still not at original parity
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: title flow, menu assets, menu actions, and front-end copy are ported
- loading-screen composition: `verified`
  - evidence: Binary Ninja decompile of `sub_418b50` and `sub_418e80`, plus the shipped `SPRITES/LOADING.TGA` and `SPRITES/LOADINGBARON.TGA` assets
  - implementation: [`loading_screen.zig`](../../zig/src/loading_screen.zig), [`main.zig`](../../zig/src/main.zig)
- loading-screen progress driver: `partial`
  - evidence: Binary Ninja decompile shows `update_loading_screen` is called from archive or file readers plus a startup initialization loop, so the original bar is activity-backed rather than time-backed
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: the port moves more of the original world-init and startup loops behind the loading screen instead of only the current front-end asset, script, music, and score loads
- window bootstrap and default windowed presentation size: `verified`
  - evidence: Binary Ninja decompile of `sub_4119d0`, which falls back to a 640x480 client area in windowed mode and only exposes 4:3 fullscreen presets
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - note: the current `snail` default is a deliberate development window (`1024x768`) over that verified base size
- top-level menu labels plus recovered `New Game` submenu: `partial`
  - evidence: Binary Ninja decompile of `sub_419b50` and `sub_417bc0`
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: deeper front-end progression and the remaining menu widget behavior are ported
- front-end options menu fields: `partial`
  - evidence: Binary Ninja decompile of `initialize_options`, `update_options`, `destroy_options`, and `apply_audio_config_volumes`, plus cross-port Android and iOS symbols for `cROptions::{Init, AI, UnInit}`
  - implementation: [`config.zig`](../../zig/src/config.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: the original slider widgets, audio test feedback, and any remaining option fields are ported
- help screen flow: `partial`
  - evidence: Binary Ninja decompile of `initialize_help`, `destroy_help`, and `update_help`, plus cross-port Android and iOS symbols for `cRHelp::{Init, AI}`
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: the original Help-screen teardown path and any missing transition details are ported
- delivery-route map flow: `partial`
  - evidence: Binary Ninja decompile of `initialize_galaxy`, `update_galaxy`, and `load_frontend_level_by_mode_and_index`, plus cross-port Android and iOS symbols for `cRGalaxy::{Init, AI}`
  - implementation: [`config.zig`](../../zig/src/config.zig), [`main.zig`](../../zig/src/main.zig)
  - note: selected and unlocked route values are now treated as verified 1-based route numbers, so route `1` maps to `ARCADE001`
  - replace when: the original Star Map widget layout, replay launch path, and remaining progression semantics are ported
- front-end background loading plus Distort-driven single-texture motion: `partial`
  - evidence: shipped `BACKGROUNDS/*.TXT` scripts and matching TGA assets, Binary Ninja decompile of `set_backdrop_distort`, `change_backdrop`, `initialize_backdrop`, `change_backdrop_real`, `draw_split_backdrop`, `render_backdrop`, and `update_backdrop`, plus cross-port Android and iOS symbols for `cRBackdrop::{SetDistort, Change, ChangeReal, Init, Render, AI}`
  - implementation: [`background.zig`](../../zig/src/background.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: the distortion grid state and any real `Landscape` model path are ported from the original RNG-driven renderer, and the split `_A` / `_B` crop semantics are verified against the original renderer
- intro and credits text-screen flow: `partial`
  - evidence: shipped `INTRO/INTRO.TXT`, `INTRO/CREDITS.TXT`, and Binary Ninja decompile of `initialize_intro_screen`, `destroy_intro_screen`, and `update_intro_screen`, plus cross-port Android and iOS symbols for `cRIntro::{Init, AI}` and Android `cRIntro::UnInit()`
  - implementation: [`intro.zig`](../../zig/src/intro.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: the remaining exact image-quad sizing and any non-intro users of the shared front-end transition overlay are ported
- high-score screen table branch: `partial`
  - evidence: Binary Ninja decompile of `initialize_high_score_screen`, `destroy_high_score_screen`, `update_high_score_screen`, `initialize_high_score_tables`, `initialize_high_score_entry`, and `exit_high_score_screen`, including the recovered 11-entry postal/challenge banks, 51-entry completion bank, and scratch entry, plus cross-port Android and iOS symbols for `cRHighScore::{Init, AI}` and Android `cRHighScore::{UnInit, Exit}`
  - implementation: [`high_score.zig`](../../zig/src/high_score.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: file-backed cRSubHighScore overlays, name-entry editing, and replay/submit actions are ported
- mutable config and score-file root: `partial`
  - evidence: Binary Ninja decompile of `initialize_default_runtime_config`, `load_high_scores_from_file`, `save_high_scores_and_config`, `load_config_file`, and `save_config_file`, which read and write `ScoreA.dat`, `ScoreB.dat`, `ScoreC.dat`, and `SnailMail.cfg`
  - implementation: [`runtime_state.zig`](../../zig/src/runtime_state.zig), [`config.zig`](../../zig/src/config.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: the remaining unknown config fields and high-score overlay serializer are ported onto that runtime root
- compact high-score overlay loading: `partial`
  - evidence: Binary Ninja decompile of `deserialize_compact_high_score_record`, `serialize_compact_high_score_record`, `load_high_scores_from_file`, and `save_high_scores_and_config`
  - implementation: [`high_score.zig`](../../zig/src/high_score.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: the port preserves the full replay payload arrays, supports writing overlays back out, and wires score mutation from the actual gameplay or front-end flow
- front-end font atlas registration, width measurement, and tutorial icon tokens: `verified`
  - evidence: Binary Ninja decompile of `sub_449d20`, `sub_449e90`, and `sub_449f50`, plus the shipped `OBJECTS/FONT/FONT-MENU-HOVER.TGA` atlas and tutorial `Message=` strings using `{`, `}`, `[`, `]`, `~`, `_`, `^`, and `;`
  - implementation: [`game_font.zig`](../../zig/src/game_font.zig), [`main.zig`](../../zig/src/main.zig)
- active segment `Sample=` / `Message=` routing in the default level path: `partial`
  - evidence: authored level metadata and current tutorial-level behavior
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: full front-end voice mixing, timing, and segment-transition behavior are ported
- level completion return overlay: `scaffold`
  - evidence: Binary Ninja decompile of `initialize_completion_screen`, `destroy_completion_screen`, `update_completion_screen`, and `update_cutscene`, plus cross-port Android and iOS symbols for `cRCompletion::{Init, AI, UnInit}` and `cRCutScene::AI()`
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: the original result, progression, and score-entry screens are ported
- runtime floor-height sampling and tile `0x16` floor slot: `verified`
  - evidence: [`docs/re/track-runtime.md`](../re/track-runtime.md)
  - implementation: [`track.zig`](../../zig/src/track.zig)
- common gameplay build preset `0x00f5cfff`: `partial`
  - evidence: March 8 Frida captures plus track-runtime notes
  - implementation: [`track.zig`](../../zig/src/track.zig)
  - replace when: per-mode or per-level build-flag normalization is fully ported
- ambient garbage and salt candidate overlay: `fallback`
  - evidence: trace-confirmed fallback tile families on `0x01`, `0x0f`, and `0x15`
  - implementation: [`track.zig`](../../zig/src/track.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: `populate_track_runtime_entities` spawn timing and windowing are ported
- debug asset browser and smoke path: `debug`
  - implementation: [`main.zig`](../../zig/src/main.zig)

Deferred plan:

- cross-port asset and content sweep
  - Windows remains the canonical behavior target
  - later, compare Android, iOS, and Wii assets against the Windows archive for higher-fidelity replacements, then evaluate whether any port-exclusive levels or content can be backported cleanly
  - defer until the core Windows gameplay and front-end loop is much closer to done, so content curation does not get mixed into behavior-port work
