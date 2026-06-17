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

- `path_template_types.h`
- `uv run python tools/ida/sync_path_template_types.py`
- `click_start_types.h`
- `uv run python tools/ida/sync_click_start_types.py`
- `vapour_trail_types.h`
- `uv run python tools/ida/sync_vapour_trail_types.py`

Current checked-in Binary Ninja companion:

- `bn_player_presentation_types.h`
- `uv run python tools/binja/sync_path_template_types.py`
- `bn_selected_level_record_types.h`
- `uv run python tools/binja/sync_selected_level_record_types.py`

That BN sync lane intentionally replays a narrow presentation/camera slice:
- sparse `Player` / `Game` field overlays that have already proven stable in `update_subgoldy` / `update_cameraman`
- the dependent `SnailVisual` / `PathTemplate` fields that keep those callers from falling back to raw offsets again
- the small matrix and presentation helper prototypes that materially change caller readability in BN

The selected-record BN lane is even narrower:
- just the expanded in-memory selected replay/high-score entry
- the `Game.selected_level_record*` control fields
- the minimal `Player.game` / `Player.movement_state` overlays needed for replay consumers like `update_subgoldy`

That path mirrors the trusted `PathTemplate` / `PathTemplateSample` layouts and
their currently trusted helper prototypes into the tracked `.i64` database
without pretending to solve global type sync.
