# Recovered Snail Mail source

This tree is the canonical home of the recovered source for
`SnailMail_unwrapped.exe`: all 785 game and engine functions, one file per
function. Matcher scratches under `tools/match/scratches/<function>/` keep their
`scratch.conf`, `NOTES.md` and experiments, and their `SOURCE=` fields point
here. The port ([docs/port/README.md](../docs/port/README.md)) builds from this
tree too.

```
decomp/
  layout.json            units, their link-order evidence, and every source
  game/<Unit>/           the game objects, 0x401000-0x449460 (43 units, 628 functions)
  engine/<Unit>/         the engine library, 0x449460-0x44fd90 (15 units, 157 functions)
    <function>.cpp       one recovered function, named like its scratch
```

Shared headers stay in `tools/match/include/`, which the matcher already puts
on the include path.

## Units

A unit directory is one original object file, recovered from the alphabetical
link order in
[`analysis/ownership/windows-link-order.json`](../analysis/ownership/windows-link-order.json)
(see [windows-link-order.md](../analysis/ownership/windows-link-order.md)):
first the game objects (Border, Cheat, ... SubGame, ... Voice), then the engine
library (BassPlay, Font, ... RMaths, ... Viewport). `layout.json` records how
strong each unit's evidence is:

| `layout_evidence` | units | functions | meaning |
|---|---|---|---|
| `link-order-object` | 44 | 669 | the object name comes from mobile source labels that fit the Windows link order |
| `binary-name-candidate` | 2 | 72 | an unnamed run whose own strings name its file: `G0` (G0.cpp initializes the object and texture lists) and `GDX` (`GDX.h` in the index-buffer error) |
| `unresolved-boundary` | 12 | 44 | one to nine functions between two known objects, named `between-<Prev>-<Next>` until the binary says more |

Directory names are the original object names where the evidence supports
them; the `between-*` units are placeholders, not claims about the original
files. Each source entry also records its address and `port_scope` (`core`,
`boundary`, `replaceable-platform`, `third-party`), which decides what the port
compiles.

Within a unit every function is still its own file and compile object, so each
function matches independently. Functions the compiler emits from one
definition (a global's constructor and its registration thunk) share that
definition's file, and both scratches point at it. Functions that must compile together (the
groups in `tools/match/translation_units.json`) keep separate files; the
matcher concatenates them.

## Port guards

The port compiles this tree with `SNAIL_PORT` defined. A guard on it is allowed
only where a matched VC6 shape relies on x86 ABI leniency (for example returning
a callee's leftover `eax`), never to change behaviour; every guard is listed in
[docs/port/divergences.md](../docs/port/divergences.md). Declarations of one
function must agree across files, as a portable linker checks signatures.

## Maintenance

`uv run snail decomp layout` checks that `layout.json` matches the link-order
data, that every listed file exists, that every scratch's `SOURCE` points at its
file, and that no stray source sits in the tree (`tests/test_decomp_layout.py`
runs the same check). After a link-order or ownership change, regenerate the
layout with `uv run snail decomp layout --write` and move the affected files.
