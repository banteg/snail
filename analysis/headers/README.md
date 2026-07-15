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
- `logo_types.h`
- `uv run python tools/ida/sync_logo_types.py`
- `path_template_types.h`
- `uv run python tools/ida/sync_path_template_types.py`
- `click_start_types.h`
- `uv run python tools/ida/sync_click_start_types.py`
- `frontend_replay_types.h`
- `uv run python tools/ida/sync_frontend_replay_types.py`
- `ida_high_score_bank_types.h`
- `uv run python tools/ida/sync_high_score_bank_types.py`
- `uv run python tools/ida/sync_subgame_runtime_types.py`
  - Reuses canonical `path_template_types.h` while replaying the narrower
    subgame-helper prototype set, so it cannot replace the recovered runtime
    children with the older sparse compatibility view. This lane also persists
    the exact cRGUI owner and its void `Init`/`UnInit` versus result-bearing
    `AI` lifecycle contracts. The same replay owns the canonical `SubRing` /
    `SubRingStar` / `SubRingPool` graph and its six constructor, spawn, and
    update prototypes; the old IDA-only `RingEffectRateSource` shell is retired
    because the backlink borrows the enclosing `SubgameRuntime` directly.
- `star_manager_types.h`
- `uv run python tools/ida/sync_star_manager_types.py`
- `vapour_trail_types.h`
- `uv run python tools/ida/sync_vapour_trail_types.py`
- `ida_input_state_types.h`
- `uv run python tools/ida/sync_input_state_types.py`

Current checked-in Binary Ninja companion:

Repo-specific Binary Ninja scripts default to `SnailMail_unwrapped.exe.bndb`
so another project's focused GUI tab cannot receive these mutations by
accident. Pass `--target active` only when following the focused tab is
intentional.

- `bn_frontend_widget_types.h`
- `uv run python tools/binja/sync_frontend_widget_types.py`
  - Width-gates the complete `FrontendWidget` field owner, replays the unique
    `cRBorder::Draw()` receiver annotation, and records its authored void ABI as
    guarded function-recreation debt while Binary Ninja retains a stale
    explicit function type.
- `bn_frontend_menu_types.h`
- `uv run python tools/binja/sync_frontend_menu_types.py`
- `uv run python tools/ida/sync_frontend_menu_types.py`
  - Replays the exact MainMenu, Options, and Exit owners plus the adjacent
    standalone 0x38-byte root BodBase without redefining FrontendWidget. The
    same narrow header now feeds both databases.
- `bn_loading_bar_types.h`
- `uv run python tools/binja/sync_loading_bar_types.py`
  - Width-gates the exact 0x0c-byte global cRLoadingBar owner, names its
    `g_loading_bar` instance, and replays the caller-proven void Init, UnInit,
    and AI contracts without importing unrelated renderer state.
- `bn_backdrop_types.h`
- `uv run python tools/binja/sync_backdrop_types.py`
- `uv run python tools/ida/sync_backdrop_types.py`
  - Width-gates the exact 0x6cc-byte Backdrop and replays its authored
    lifecycle/render receiver contracts into IDA as well as Binary Ninja.
- `bn_frame_renderer_types.h`
- `uv run python tools/binja/sync_frame_renderer_types.py`
  - Promotes the complete `BorderManager` owner when available, including its
    final `float justify_centre` field and the exact void
    `SetJustifyCentre(float)` ABI. It also preserves the cross-port-authored
    `Track` (`cRTrack`) root subobject and the void `Change(int)` receiver ABI.
- `bn_object_render_types.h`
- `uv run python tools/binja/sync_object_render_types.py`
- `bn_input_state_types.h`
- `uv run python tools/binja/sync_input_state_types.py`
- `path_template_types.h`
- `uv run python tools/binja/sync_path_template_types.py`
  - Owns the canonical `SubSolution` replay record and nested `Player` layout.
    The older selected-level sync was retired because it recreated a parallel
    `Game` owner and flattened overlapping player fields.
- `bn_garbage_hazard_types.h`
- `uv run python tools/binja/sync_garbage_hazard_types.py`
- `bn_high_score_bank_types.h`
- `uv run python tools/binja/sync_high_score_bank_types.py`
- `bn_subgame_runtime_types.h`
- `uv run python tools/binja/sync_subgame_runtime_types.py`
  - Replays the exact 0x28-byte cRGUI owner, including its borrowed
    `SubgameRuntime*` and eight owned `FrontendWidget*` slots, plus the same
    `void`/`void`/`int` lifecycle split.
- `bn_overlay_types.h`
- `uv run python tools/binja/sync_overlay_types.py` (after the presentation/path-template lane)
- `bn_root_bod_catalog_types.h`
- `uv run python tools/binja/sync_root_bod_catalog_types.py`
- `uv run python tools/ida/sync_root_bod_catalog_types.py`
  - Width-gates the constructor-proven 352-entry, 0x4d00-byte catalog and
    composes it with the adjacent 0x5e10-byte `DirectXLoader` owner in IDA.
- `bn_subgame_hazard_pool_types.h`
- `uv run python tools/binja/sync_subgame_hazard_pool_types.py`
- `bn_subgame_pool_types.h`
- `uv run python tools/binja/sync_subgame_pool_types.py`
- `star_manager_types.h`
- `uv run python tools/binja/sync_star_manager_types.py`

The presentation BN sync lane selectively replays the authoritative camera/render slice:
- sparse `Player` / `Game` field overlays that have already proven stable in `update_subgoldy` / `update_cameraman`
- the dependent `SnailVisual` / `PathTemplate` fields that keep those callers from falling back to raw offsets again
- the small matrix and presentation helper prototypes that materially change caller readability in BN

The object-render lane owns the complete shared `Object`, `tColourSmall`, and
grouped-buffer layouts plus the trusted render contracts. It also replays the
complete `Direct3DRenderer` singleton, its nested buffer factories,
presentation/caps blocks, and the recovered Direct3D 8 COM vtable surface.
The same lane types the `cRObjects::ReTextureObjects` equivalent as the void
`ObjectList::replace_object_list_texture_refs` owner walk, including its two
borrowed texture references and retained grouped-render repair.
The index-buffer matcher alias at `0x5000fc` remains the renderer field at
`+0x8ca4`, and the device matcher alias at `0x502fec` remains the renderer field
at `+0xbb94`; the lane deliberately removes or avoids both standalone data
owners. The buffer allocators replay under their manifest names,
`create_vertex_buffer` and `create_index_buffer`, while the blend-state and
immediate-quad helpers replay their recovered void contracts. Its retained
`ObjectAnimation` record keeps a two-byte `ObjectAnimationFlags` field, while
the named stored-bit enum stays separate from the selector-only `-1`
preserve-current override. Its retained frame bank is consistently typed as
`ObjectAnimationFrame**` in both the object and presentation replay lanes. The live database
currently pins `pack_color_rgba_u8` to the retired `ColorBGRA8` tag: its
`tColourSmall` update previews correctly but is restored during live
verification, so that one prototype is intentionally deferred while the
checked-in header and IDA lane carry the recovered owner.

It also retains the complete canonical `SubgameRuntime` field map accumulated
by the path, player, hazard, landscape, and lifecycle slices. The stable
`reset_subgame` and `complete_subgame` receiver ABIs are replayed with that map.
Five older functions still carry a pinned user-defined `Game*` parameter in BN;
the sync reports those owner-only corrections as deferred because both the
prototype and local-retype APIs restore the old tag. Their exact/working match
sources and cross-port `cRSubGame` symbols remain the ownership authority. The
same reporting guard covers `get_track_runtime_cell_at_world_z`, whose exact
receiver ownership is pinned by the canonical `runtime_rows` array.

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

The subgame-hazard lane owns the canonical `SubLazer` / `SubLazerManager` and
`Salt` / `SaltManager` types. Its replay deliberately replaces the obsolete
sparse slot experiments, preserves complete shared types from other lanes, and
batches all field/prototype mutations behind one verified preview.

The adjacent subgame-pool lane owns the canonical `SubRing` / `SubRingStar` /
`SubRingPool` family. It records two inline `0x1f8` parents, ten inline `0x20`
children per parent, and the borrowed backlink from each parent to its enclosing
`SubgameRuntime`. The replay selectively replaces only the obsolete generic
ring shells, preserves complete shared owners, and batches the verified root
field and prototype changes. The paired IDA subgame-runtime replay consumes the
same canonical header, so both databases retain identical parent, child, pool,
and borrowed-runtime ownership after regeneration.

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
a shared concrete screen base class. The IDA frame-root replay mirrors the
same three overlays at `GameRoot +0x67c`, `+0x7c8`, and `+0x914`, replacing the
older opaque `0x4a8`-byte block without inventing fields past their exact end.
The shared frame-root replay now closes the rest of that exact prefix too: the
root callback/fog block through `+0x24`, the front-end link latch at `+0x568`,
and the standalone `RenderableBod +0xa60` between the overlays and texture-set
owner. The `+0xb24` object is now the exact `Track` / `cRTrack` owner rather
than a semantic-only selector shell. Replaying a later owner lane therefore no longer degrades these
independently bounded fields back into byte arrays.
The same replay now owns the complete `BorderManager +0xb4c`: its embedded
`BorderStack`, fixed 150-entry `BorderRecord` pool, and delayed-widget state.
`BorderRecord` remains the exact backing-storage identity while allocator and
front-end callsites deliberately consume each returned slot as a
`FrontendWidget`; the replay does not collapse those two proven views.

The star-manager lane records the cross-port `cRStarManager` owner, its
constructed `BodBase` prefix, the `0x2c` entry stride, and the lifecycle fields
shared by the seven Windows helpers from destruction through per-frame update.
It deliberately carries the already proven complete `Sprite`, `SpriteManager`,
and `TextureRef` prerequisites too. Its replay compares their exact expected
sizes, selectively repairs only missing or incomplete definitions, and batches
field/prototype verification. BN treats forward-only redeclarations as
destructive, so this lane remains monotonic instead of erasing complete shared
layouts while adding the star-manager types. The replay also records the void
`Init`, `UnInit`, `Hide`, and `UnHide` lifecycle ABI proven by their callers;
the count values left in EAX are loop-control residue rather than results. Its
IDA import refuses forward-only shared declarations and verifies the exact
`Sprite`, `StarManagerEntry`, and `StarManager` sizes before changing any
prototype.

The canonical IDA `path_template_types.h` lane remains useful beyond path
templates because it is the single accumulated `SubgameRuntime` and gameplay
owner graph. The front-end lifecycle slice reuses it for exact `Help`,
`Options`, and `LoadingBar` records instead of creating another broad GameRoot
header. Its narrow trusted declarations now preserve void Help/Options teardown
and the complete void LoadingBar lifecycle, while the frame-root lane owns the
separate exact-sized BorderManager projection and `KillBorders` contract.

That path mirrors the trusted `PathTemplate` / `PathTemplateSample` layouts and
their currently trusted helper prototypes into the tracked `.i64` database
without pretending to solve global type sync.

The IDA frame, object-render, root-catalog, front-end, path-template, and
subgame-runtime replays share
`tools/ida/game_root_owner.py` for the recovered root graph. Once its exact
component types are present, it composes the contiguous
`RootBodCatalog +0x44100`, `DirectXLoader +0x48e00`, `Backdrop +0x4ec10`,
`Intro`, `MainMenu`, `StarManager`, `Options`, `Exit`, standalone `BodBase`,
and `Logo` block through `+0x74618`, followed by the complete
`SubgameRuntime` (`0x1272838` bytes), `HighScore` at `+0x12e6e50`, the real
`0x14`-byte gap, `TipManager` at `+0x12e6f58`, and the final four-byte gap into
the exact `0x12e6ff4` root. Bootstrap databases missing the catalog/loader types
retain the front-end-plus-tail composition; databases also missing a front-end
type retain tail-only until the relevant narrow replay supplies it.
The helper refuses to replace a proved overlapping member, immediately
repairs the sparse frame compatibility view after imports, and reapplies the
`g_game_base` pointer because IDA retains the earlier pointed-to type snapshot
even when its rendered declaration is still `GameRoot *`.

The Binary Ninja path replay also retains three bounded register views in
`update_subgoldy`'s row-event block. Native code uses pre-biased byte addresses
for `SubTracks::segment_slots[event_id - 1]`; without those views HLIL
misattributes the same bytes to nearby `SegmentCache` and `Tutorial` members.
The replay deliberately keeps honest byte arithmetic instead of installing a
synthetic overlapping field solely to improve pseudocode.
