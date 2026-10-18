# Snail Mail

Snail Mail (Sandlot Games, 2004) puts you in charge of Turbo, a snail who
delivers the mail at breakneck speed along highways in space: grab the
packages, dodge the salt, blast the slugs and don't fall off.

This project rebuilds the game from its original Windows executable, one
function at a time, so it plays again in a modern browser.

**▶ [Play at snail.banteg.xyz](https://snail.banteg.xyz)**

## Playing

The game runs in desktop browsers; the first visit downloads about 9 MB. Click
once to start (browsers keep sound off until you do), and the intro plays from
the beginning.

- **Controls:** steer Turbo with the mouse and hold the mouse button to shoot.
  Escape opens the in-game menu. The tutorial, at the top of the New Game
  menu, walks you through packages, salt, hearts, weapons and invincibility.
- **Saves:** progress, options and high scores stay in your browser between
  visits. Add `?reset` to the address to start over, or `?mute` to play
  silently (`?mute=0` turns sound back on).

### Original or Ultimate

The ⚙ button in the corner picks how the game plays. Switching reloads the
page, and each keeps its own progress and high scores.

- **Ultimate** (the default) is the most complete Snail Mail: every course
  and track style from the later Android release, its ten-level Pro-Challenge
  galaxy, its rules and pacing, and fixes for the original's bugs, with the
  PC's art, voices and mouse controls.
- **Original** is the 2004 PC release exactly as it shipped, its quirks
  included. It is checked tick for tick against the original program.

### Comfort options

The same menu has options that change only how the game looks and feels; all
start on:

- **Sharp rendering** draws at your display's resolution instead of 640×480.
- **Fullscreen** lets the game's own Fullscreen option fill the screen.
- **Trap the mouse** keeps the pointer inside the game; Escape lets it go.

### Playing natively

The same build also runs in a native window on macOS (SDL3), with your own
copy of the game files. See
[Playing natively](docs/port/README.md#playing-natively-macos).

## How it works

The project is a matching decompilation of the gameplay executable: C++ source
written to compile, with the original Microsoft Visual C++ 6 compiler, into
byte-identical machine code. The playable port compiles that recovered source
for WebAssembly and replaces only the original's platform layer: Direct3D 8
and the BASS audio library are emulated underneath it, so the game logic is
the original's own.

- **Matching:** 646 of 662 game functions are byte-proven against the
  original, and the other 16 are close partials
  ([STATUS.md](tools/match/STATUS.md)).
- **Original, checked against the original:** two oracles compare the port
  with the 2004 executable tick by tick, and both match bit for bit: 20 of 20
  recorded high-score runs, and 10 of 10 sessions captured from the original
  (56,977 ticks of menus, tutorial, postal, challenge and time trial play).
- **Ultimate, checked against Android:** `snail android trace` runs the
  Android release's own game library headless and compares what it builds and
  draws with the port. See [Gameplay profiles](docs/port/README.md#gameplay-profiles)
  and [Oracles](docs/port/README.md#oracles).
- **Next:** comparing rendered frames with the original, native builds for
  Linux and Windows, and 64-bit builds ([port plan](docs/port/README.md#stages)).

## Contributing

Matching help is welcome: pick a function from the
[matching challenges](https://github.com/banteg/snail/issues/24); partial
improvements and new findings count too.

- [DEVELOPING.md](DEVELOPING.md): local setup, daily workflow, validation
  commands and contribution rules.
- [decomp/README.md](decomp/README.md): the recovered source, one file per
  function in link-order units.
- [tools/match/README.md](tools/match/README.md): the matching harness,
  toolchain setup and the no-fakematching rules.
- [docs/port/README.md](docs/port/README.md): the port, its profiles, patches
  and oracles.
- [docs/index.md](docs/index.md): original formats and reverse-engineering
  notes.

The matching target is hosted publicly and kept out of Git. From a fresh
checkout, fetch and verify it with:

```sh
uv run tools/match/fetch_target.py
```

That saves [`SnailMail_unwrapped.exe`](https://reflexive.banteg.xyz/snail/d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5/SnailMail_unwrapped.exe)
(724 KiB, SHA-256 verified) to `artifacts/bin/`; no game installation or
login is needed. Asset work and the port also need `SnailMail.dat` from the
original game in `artifacts/bin/`, and Ultimate needs `SnailMailExtras.dat`,
built by `uv run snail port extras` from the Android release.

```sh
uv run snail match status --write tools/match/STATUS.md
tools/match/match.sh tools/match/scratches/<function>
uv run pytest
```

To build and play the port locally:

```sh
uv run snail port link && uv run snail port data
cd port && zig build && cd ..
uv run snail port serve
```

[![Game & Engine progress](https://decomp.dev/banteg/snail.svg?mode=shield&category=game&label=Game%20%26%20Engine)](https://decomp.dev/banteg/snail?category=game)
[![Port core progress](https://decomp.dev/banteg/snail.svg?mode=shield&category=game.port-core&label=Port%20core)](https://decomp.dev/banteg/snail?category=game.port-core)
[![Full-executable progress](https://decomp.dev/banteg/snail.svg?mode=shield&label=Full%20executable)](https://decomp.dev/banteg/snail)

[Public reporting policy](analysis/progress/README.md) ·
[Library and ownership findings](analysis/ownership/README.md)
