# Binary Ninja Import Headers

This directory holds small handwritten headers for Binary Ninja import, plus an
official vendored BASS 2.0 header set for higher-fidelity audio API recovery.

Import `snail_bn_import.h` in Binary Ninja. It is a flattened entrypoint because
BN's file importer does not reliably resolve sibling `#include` paths.

For the real upstream BASS header, import
`upstream/bass20/bass_bn_import.h`. That wrapper is derived from the official
`bass20.zip` SDK and stays close to upstream, while making the small changes BN
needs to parse it locally.

The split `*_min.h` files are the maintained sources behind that entrypoint:

- `win32_min.h`: 32-bit Win32 and COM base types used by the game
- `d3d8_min.h`: the Direct3D 8 surface currently recovered around `initialize_d3d8_device`
- `dinput8_min.h`: the DirectInput 8 surface currently recovered around keyboard, mouse, and controller setup
- `bass_min.h`: the BASS 2.0-era API subset resolved dynamically from `tBass.dll`

These are intentionally minimal. They are meant to make imported APIs, COM
vtables, and function-pointer wrappers readable in Binary Ninja, not to replace
the full DirectX or BASS SDK headers.

Current high-value targets for these headers:

- `initialize_d3d8_device`
- `enumerate_input_controllers`
- `initialize_keyboard_input`
- `initialize_mouse_input`
- `sub_449460` (`tBass.dll` loader)

Observed DLL facts behind `bass_min.h`:

- `tBass.dll` and the archive `BASS.DLL` are byte-for-byte identical
- the version resource reports `FileVersion = 2.0`
- the exported surface is still the older pre-2.1 API family used by the game
- the official `bass20.zip` SDK header parses to the same `100` named BASS functions
  once wrapped for BN import

Why this lives in-repo:

- no local Windows SDK headers were installed on this machine
- we only want the parts the game actually uses
- keeping the headers here makes them easy to extend as RE improves
- the `crimson/third_party/headers` bundle is a useful same-era reference set, but
  these copies stay curated and much smaller for BN import

## Narrow IDA Type Sync

We do not have a general BN-to-IDA type mirror or BinSync lane checked in.

For recovered struct surfaces where we want a durable second decompiler view,
we keep a narrow handwritten header and a matching IDA import script instead.

Current checked-in example:

- `frame_renderer_types.h`
- `uv run python tools/ida/sync_frame_renderer_types.py`
- `path_template_types.h`
- `uv run python tools/ida/sync_path_template_types.py`
- `click_start_types.h`
- `uv run python tools/ida/sync_click_start_types.py`
- `frontend_replay_types.h`
- `uv run python tools/ida/sync_frontend_replay_types.py`
- `ida_high_score_bank_types.h`
- `uv run python tools/ida/sync_high_score_bank_types.py`
- `ida_subgame_runtime_types.h`
- `uv run python tools/ida/sync_subgame_runtime_types.py`
- `star_manager_types.h`
- `uv run python tools/ida/sync_star_manager_types.py`
- `vapour_trail_types.h`
- `uv run python tools/ida/sync_vapour_trail_types.py`
- `ida_input_state_types.h`
- `uv run python tools/ida/sync_input_state_types.py`

Current checked-in Binary Ninja companion:

- `bn_frontend_widget_types.h`
- `uv run python tools/binja/sync_frontend_widget_types.py`
- `bn_frame_renderer_types.h`
- `uv run python tools/binja/sync_frame_renderer_types.py`
- `bn_input_state_types.h`
- `uv run python tools/binja/sync_input_state_types.py`
- `bn_player_presentation_types.h`
- `uv run python tools/binja/sync_path_template_types.py`
- `bn_selected_level_record_types.h`
- `uv run python tools/binja/sync_selected_level_record_types.py`
- `bn_garbage_hazard_types.h`
- `uv run python tools/binja/sync_garbage_hazard_types.py`
- `bn_high_score_bank_types.h`
- `uv run python tools/binja/sync_high_score_bank_types.py`
- `bn_subgame_runtime_types.h`
- `uv run python tools/binja/sync_subgame_runtime_types.py`
- `bn_overlay_types.h`
- `uv run python tools/binja/sync_overlay_types.py` (after the presentation/path-template lane)
- `bn_root_bod_catalog_types.h`
- `uv run python tools/binja/sync_root_bod_catalog_types.py`
- `star_manager_types.h`
- `uv run python tools/binja/sync_star_manager_types.py`

The presentation BN sync lane intentionally replays a narrow camera/render slice:
- sparse `Player` / `Game` field overlays that have already proven stable in `update_subgoldy` / `update_cameraman`
- the dependent `SnailVisual` / `PathTemplate` fields that keep those callers from falling back to raw offsets again
- the small matrix and presentation helper prototypes that materially change caller readability in BN

For projectile-only ownership work, use `uv run python
tools/binja/sync_path_template_types.py --golb-only`. It declares just the
missing `GolbPathFollowState`, replays the explicit `GolbShot` fields, and
updates the three previewable Golb/path-follow prototypes without reimporting
unrelated forward-declared presentation types.

The selected-record BN lane is even narrower:
- just the expanded in-memory selected replay/high-score entry
- the `Game.selected_level_record*` control fields
- the minimal `Player.game` / `Player.movement_state` overlays needed for replay consumers like `update_subgoldy`

The high-score bank and subgame-runtime BN lanes carry the recovered
`SubSolution`, `SubHighScore`, and sparse `SubgameRuntime` layouts that
make `complete_subgame` and the three `add_*_high_score` helpers readable.

The input-state BN/IDA lane carries the recovered `InputState` button edge
masks, controller-axis fields, pointer-authored coordinates, and the embedded
`GameInput.input` field proven by the exact Windows bridge and iOS
`cRGameInput::AI()` provenance. The root frame lane also places the two owned
records at `GameRoot +0x44` and their borrowed player backlinks at `+0x168`.
Each record now exposes its inherited 0x38-byte cRBod-compatible prefix as
`GameInputBodBase`; the constructor installs the one-entry
`g_game_input_callback_table`, whose only entry is `update_game_input`.
The same input lane separates the mouse platform globals from IDA's stale BSS
aggregate, including the two-slot live/screen coordinates, `MouseScreenRect`,
authored-coordinate scales, cursor-hide flag, and DirectInput interface/device
owners.

The overlay lane depends on the presentation types and adds the complete
`0x14c`-byte `Overlay` plus its owned `0xc8`-byte `RenderCamera`; the segment
catalog lane now carries the complete constructor-proven `0x25cfb4` owner and
uses it for both startup enumeration methods. The tiny `SubgameOwnerLink`
view keeps the folded challenge/thanks startup binding typed without asserting
a shared concrete screen base class.

The star-manager lane records the cross-port `cRStarManager` owner, its
constructed `BodBase` prefix, the `0x2c` entry stride, and the lifecycle fields
shared by the seven Windows helpers from destruction through per-frame update.
It deliberately carries the already proven complete `Sprite` and `TextureRef`
prerequisites too: BN treats forward-only redeclarations as destructive, so the
lane must remain monotonic instead of erasing those layouts while adding the
manager types.

That path mirrors the trusted `PathTemplate` / `PathTemplateSample` layouts and
their currently trusted helper prototypes into the tracked `.i64` database
without pretending to solve global type sync.
