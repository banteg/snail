# Windows link order

Date: 2026-10-05. Data: [windows-link-order.json](windows-link-order.json).

The game objects were linked in **alphabetical order**, in two sequences:

- game, `0x401030`-`0x449460`: Border, Cheat, Completion, DatBuild, DirectX,
  Exit, (G0), Galaxy, Game, (GDX), GL, Golb, GUI, Help, HighScore, Intro,
  Landscape, LoadingBar, Logo, MainMenu, ObjectProc, Options, Path, Register,
  RObject, RShell, SegmentCache, Splash, Star, SubGame, Subtrack, TimeTrial,
  Tips, Tutorial, Voice;
- engine library, `0x449460`-`0x44fd90`: BassPlay, Font, Keyboard, Mouse,
  ObjectText, RMaths, RSound, RSprite, RString, RTexture, Viewport.

This is the order a sorted VC6 project and a static library produce. It gives
a Windows-side check on every per-function object label.

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

## Unresolved boundaries

Functions between two different objects are listed with both neighbours.
Two have a name candidate from the binary:

| start | functions | between | candidate |
|---|---|---|---|
| `0x406bc0` | 58 (startup, window, display modes, BASS window, runtime construction) | Exit, Galaxy | `G0`: the binary names `G0.cpp` as where ObjectList/TextureList are initialized |
| `0x4114b0` | 14 (vertex/index buffers, D3D8 device) | Game, GL | `GDX`: `create_index_buffer` reports `DX_INDEXBUFFER_MAX in GDX.h` |

The remaining gaps are 1-9 functions at a boundary (for example the BASS
backend before BassPlay, `load_png_image` between Path and Register). The
image has 56 C++ objects with backend 8447 and 10 with 8168; 46 objects are
named or nearly named here.

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
