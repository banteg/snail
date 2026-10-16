# Recovered Snail Mail source

This tree is the canonical home of the recovered source for
`SnailMail_unwrapped.exe`: all 785 tracked functions (the game, its engine
library and three d3dx8 matrix functions the port builds from), one file per
function. Matcher scratches under `tools/match/scratches/<function>/` keep their
`scratch.conf`, `NOTES.md` and experiments, and their `SOURCE=` fields point
here. The port ([docs/port/README.md](../docs/port/README.md)) builds from this
tree too.

```
decomp/
  layout.json            units, their link-order evidence, and every source
  game/<Unit>/           the game objects, 0x401000-0x449460 (36 units, 628 functions)
  engine/<Unit>/         the engine library, 0x449460-0x44e950 (14 units, 154 functions)
  d3dx8/d3dxmath/        d3dx8.lib's d3dxmath.obj, from 0x44e950 (3 functions)
    <function>.cpp       one recovered function, named like its scratch
  include/               the shared recovered headers, on both the matcher's and the port's include path
```

## Units

A unit directory is one original object file, recovered from the alphabetical
link order in
[`analysis/ownership/windows-link-order.json`](../analysis/ownership/windows-link-order.json)
(see [windows-link-order.md](../analysis/ownership/windows-link-order.md)):
first the game objects (Border, Cheat, ... SubGame, ... Voice), then the engine
library (BassPlay, Console, Font, ... RMaths, ... Viewport), then d3dx8.lib.
`layout.json` records how strong each unit's evidence is:

| `layout_evidence` | units | functions | meaning |
|---|---|---|---|
| `link-order-object` | 44 | 702 | the object name comes from mobile source labels that fit the Windows link order |
| `binary-name-candidate` | 2 | 72 | an unnamed run whose own strings name its file: `G0` (G0.cpp initializes the object and texture lists) and `GDX` (`GDX.h` in the index-buffer error) |
| `mobile-source-file` | 2 | 2 | a mobile source file names the object: `Png` (iOS `Png.mm` defines `PngLoadImage`) and `Console` (iOS `Console.cpp` defines the `wprintf` this release build stubs out) |
| `sdk-sample-candidate` | 2 | 6 | code taken from a DirectX SDK sample, named after its file: `GetDXVer` (`GetDXVersion`) and `Joystick` |
| `library-member` | 1 | 3 | a member of a linked library: `d3dxmath` from d3dx8.lib (`library-attribution.json`) |

Of the `link-order-object` functions, 33 carry no mobile label of their own and
sit in their unit by a recorded placement (`placements` in `layout.json`):

| unit | functions | placement evidence |
|---|---|---|
| Border | 1 | `comdat-placement`: the `??_H` vector constructor iterator, kept from the first object that emits it |
| DatBuild | 9 | `mobile-source-file`: iOS `DatBuild.cpp` defines `LoadFile`, `SaveFile` and `DatBuild()` |
| GL | 3 | `position-and-content`: renderer state, defined out of line between GL and the golb-only Golb |
| RShell | 2 + 1 | `mobile-source-file`: the `RShellMemory` initializer (Android `_GLOBAL__I_RShell.cpp`); `position-and-content`: `launch_alpha72_url`, which has no mobile counterpart |
| Splash | 1 | `mobile-source-file`: the fold of `cRGUI::Open` and `cRSplash::Open`, which iOS defines in `Splash.cpp` |
| BassPlay | 16 | `owner-class`: `AudioBackend` (`cRBass`) methods, whose home iOS puts in `BassPlay.cpp` |

`position-and-content` is the weakest placement: the function sits at the
unit's edge and does its kind of work, but nothing in a binary names its file.
G0, GDX, GetDXVer and Joystick are name candidates (`object` is null); the last
two come from the code's SDK origin, not from a string naming the file. No
`between-*` placeholder units remain. Each source entry also records its
address and `port_scope` (`core`, `boundary`, `replaceable-platform`,
`third-party`), which decides what the port compiles.

Every function keeps its own file. Functions the compiler emits from one
definition (a global's constructor and its registration thunk) share that
definition's file, and both scratches point at it.

Units listed in `tools/match/translation_units.json` compile as one
translation unit: the matcher concatenates their files in address order into
one object, and each member must match in that context. 44 units compile this
way (see
[whole-tu-compilation-20261015.md](../tools/match/whole-tu-compilation-20261015.md)),
and so do two SubGame pairs. Path's shared helpers live once in
`decomp/include/path_helpers.h`; a builder whose code differs carries its
copy written out. SubGame still compiles one object per function until its
in-context matches are reconciled. Png, Console and GetDXVer hold one function each, and
d3dxmath is library code built with mixed profiles. Register
a unit with `uv run tools/match/whole_tu_experiment.py units <Unit>`, and only
when scores are unchanged.

## Port guards

The port compiles this tree with `SNAIL_PORT` defined. A guard on it is allowed
only where a matched VC6 shape relies on x86 ABI leniency (for example returning
a callee's leftover `eax`), never to change behaviour; every guard is listed in
[docs/port/divergences.md](../docs/port/divergences.md). Larger port changes are
patches applied to copies of this tree (`port/patches/`), so it stays as VC6
matches it. Declarations of one function must agree across files, as a portable
linker checks signatures.

## Maintenance

`uv run snail decomp layout` checks that `layout.json` matches the link-order
data, that the game and engine objects keep their alphabetical order, that every
listed file exists, that every scratch's `SOURCE` points at its
file, and that no stray source sits in the tree (`tests/test_decomp_layout.py`
runs the same check). After a link-order or ownership change, regenerate the
layout with `uv run snail decomp layout --write` and move the affected files.
