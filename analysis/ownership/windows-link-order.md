# Windows link order

Date: 2026-10-05, boundaries resolved 2026-10-16. Data:
[windows-link-order.json](windows-link-order.json).

The game objects were linked in **alphabetical order**, in two sequences,
followed by d3dx8.lib:

- game, `0x401000`-`0x449460`: Border, Cheat, Completion, DatBuild, DirectX,
  Exit, (G0), Galaxy, Game, (GDX), GL, Golb, GUI, Help, HighScore, Intro,
  Landscape, LoadingBar, Logo, MainMenu, ObjectProc, Options, Path, Png,
  Register, RObject, RShell, SegmentCache, Splash, Star, SubGame, Subtrack,
  TimeTrial, Tips, Tutorial, Voice;
- engine library, `0x449460`-`0x44e950`: BassPlay, Console, Font, (GetDXVer),
  (Joystick), Keyboard, Mouse, ObjectText, RMaths, RSound, RSprite, RString,
  RTexture, Viewport;
- d3dx8.lib from `0x44e950`, starting with `d3dxmath.obj` (members in
  [library-attribution.json](library-attribution.json)).

This is the order a sorted VC6 project and a static library produce, compared
case-insensitively (Golb before GUI). It gives a Windows-side check on every
per-function object label; `snail decomp layout` checks that the named objects
and candidates keep it.

## Evidence

- 684 functions carry a mobile source-object label. In Windows address order
  they form 53 runs over 45 objects; the longest alphabetical chain keeps 44
  objects and explains all but 38 labels.
- The CRT initializer table (`0x4a1004`-`0x4a1060`) lists the 24 static
  initializer thunks in exactly their code-address order, an independent
  confirmation that code and data contributions share one object order.
- VC6 `/O2` emits each function as its own `.text` COMDAT padded with `0x90`
  inside the object, so padding cannot mark object boundaries. Literal pooling
  (shared format strings across objects) prevents a `.data` segmentation.

## Mobile drift

The mobile builds have drifted from this Windows build. A label is kept only
where the Windows order agrees. Labels the order rejects include:

- `Mac.o` on the startup, runtime-slot constructor and default-config
  functions. They sit between Exit and Galaxy, where `Mac` cannot sort.
- `Game.o` on `construct_game_runtime`, which precedes Galaxy.
- `RObject.o` on `get_or_append_object_texture_group_vertex` and
  `build_object_texture_group_buffers`, which sit inside GL.
- `HighScore.o` on the compact high-score serializers, which sit inside SubGame.
- `GUI.o` on `bind_subgame_owner` (an identical-code-folded `cRGUI::Open` /
  `cRSplash::Open` body that sits with Splash) and `SubGame.o` on the folded
  `noop_runtime_ai`. A folded body's address says nothing about its owners.

## Placed functions

Every function now has an object. Those without a mobile label of their own
carry their evidence in the data: an object's `evidence` (a run named as a
whole) or its `placements` (functions added to a labelled object), each with
a kind, a note and the sources it rests on.

| object | functions | kind | evidence |
|---|---|---|---|
| (G0) | 58 | `binary-name-candidate` | the binary names `G0.cpp` as where ObjectList/TextureList are initialized |
| (GDX) | 14 | `binary-name-candidate` | `create_index_buffer` reports `DX_INDEXBUFFER_MAX` from `GDX.h` |
| Border | 1, head | `comdat-placement` | `initialize_array_with_constructor` is the `??_H` vector constructor iterator. The linker keeps a COMDAT from the earliest object that emits it, and this copy precedes Border's first function. An earlier object with no other surviving code would fit too |
| DatBuild | 5 + 4 around the anchor | `mobile-source-file` | iOS `Source/DatBuild.cpp` defines `LoadFile`, `SaveFile(char*, void*, int, bool)` and `DatBuild()`, here `load_file_bytes_into_optional_buffer`, `save_file_bytes_with_optional_archive_scramble` and `rebuild_game_archive_if_needed`, with their file helpers |
| GL | 3, tail | `position-and-content` | renderer state (`query_direct3d_device_caps`, `reset_render_counters`, `replace_object_group_texture_refs`). None sits with its earliest caller, so none is inline; iOS `Golb.cpp` holds only the golb shot and enemy classes |
| Png | 1 | `mobile-source-file` | iOS `Source/Png.mm` defines `PngLoadImage(char*, char**, int*, int*, int*)` |
| RShell | 2, head | `mobile-source-file` | the `RShellMemory` static initializer: Android `_GLOBAL__I_RShell.cpp` stores 0 to `RShellMemory`, and iOS defines `_RShellMemory` in `Source/RShell.cpp` |
| RShell | 1, tail | `position-and-content` | `launch_alpha72_url` has no mobile counterpart. Its caller sits earlier in Exit, so it is out-of-line in RShell or SegmentCache; it is a Windows shell action, and Android's `RShell.cpp` also ends with `RShellGetScreenWidth/Height`, the functions before it |
| Splash | 1, head | `mobile-source-file` | `bind_subgame_owner` folds `cRGUI::Open` and `cRSplash::Open`; iOS defines `cRSplash::Open()` in `Source/Splash.cpp` |
| BassPlay | 8 + 8 around the anchors | `owner-class` | `AudioBackend` (`cRBass`) methods; iOS defines `cRBass` and `gBass` in `Source/BassPlay.cpp` |
| Console | 1 | `mobile-source-file` | iOS `Source/Console.cpp` defines `wprintf(char*, ...)`, stubbed out here as `debug_report_stub`; 11 of its 16 crosswalk-verified callers map to Android functions that call `wprintf` |
| (GetDXVer) | 1 | `sdk-sample-candidate` | `query_directx_runtime_version` is the DirectX SDK sample `GetDXVersion()` (`getdxver.cpp`), with its debug messages |
| (Joystick) | 5 | `sdk-sample-candidate` | the DirectX 8 SDK Joystick sample: enumeration callbacks, every axis range set to -1000..+1000, polling and release |
| d3dxmath.obj | 3 | `library-member` | d3dx8.lib's `D3DXMatrixTranslation`, `D3DXMatrixPerspectiveFovRH` and `D3DXMatrixLookAtRH`, kept in `decomp/` because the port compiles them |

`position-and-content` is the weakest kind: the function sits at the object's
edge and does its kind of work, but no binary names its file. The image has
56 C++ objects with backend 8447 and 10 with 8168; 50 objects are named or
nearly named here.

## Owner audit

Out-of-line methods of a class sit in its home object. A header-inline
function is emitted as a COMDAT by every object that uses it, and the linker
keeps the copy from the earliest of those objects in link order. So a function
outside its class's home object is either inline, and then sits with its
earliest caller, or misowned.

Of 121 owner classes recorded by decorated `SYMBOL`s or pinned `Owner_name`
aliases, 26 span more than one object. Most are explained by inline
placement: the SubGame-family constructors (`cRSlug`, `cRSalt`, `cRParcel`,
`cRSubLoc`, `cRFringe`, ...) and `cRPath`'s record-pair initializer sit in G0,
and G0 is their only caller. `initialize_border_stack` sits in Border with only
Game callers, but it is an identical-code fold of `cRBorderStack::Init` and
`cRFade::Init`, and the linker kept Border's earlier copy.

These owners fail the test: each function sits in an object other than its
earliest caller's, so it is not an inline copy and is defined out-of-line
where it sits.

| function | sits in | callers | recorded owner | question |
|---|---|---|---|---|
| `load_frontend_level_by_mode_and_index` | SubGame | Galaxy, GUI, SubGame | `cRSubTracks` (alias) | defined in SubGame, not Subtrack |
| `deserialize_/serialize_compact_high_score_record` | SubGame | HighScore | `cRSubSolution` | defined in SubGame; the mobile HighScore label is drift |

## Use

- Treat a mobile object label as evidence only when it agrees with this order.
- A recovered translation unit (`tools/match/translation_units.json`) must
  stay inside one object.
- Compiler profile is per object: see the
  [compiler identification](../../tools/match/compiler-identification-20261005.md).
