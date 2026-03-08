# Index

Snail Mail is a reverse-engineering and rewrite project for the 2006 Windows game. The repo has three goals that feed each other:

- decompile and document how the original game bundle works
- preserve the original content formats and runtime behavior closely enough to reproduce them
- port the game from scratch to Zig with a native runtime that can load the original assets directly

This is not a texture rip or asset-conversion project. The long-term target is a clean-room Zig port that understands the shipped archive, scripts, meshes, textures, and audio without requiring a Python conversion pipeline at runtime.

## Project Tracks

- [Original](original/index.md): verified facts about the shipped files, archive layout, and authored content formats
- [Rewrite](rewrite/index.md): the architecture and fidelity rules for the Zig port
- [RE](re/index.md): deeper notes on the executable, runtime systems, path behavior, Binary Ninja workflow, and trace collection

## Current Shape

Today the repo is split roughly into two implementation tracks:

- Python tooling for archive parsing, text-format inspection, wrapper unwrap, trace summarization, and symbol-manifest validation
- Zig runtime work for the actual port, with direct support for `SnailMail.dat`, `.tga`, `.ogg`, `.txt`, and `.x2`

The workflow is intentionally iterative:

1. recover behavior from the original executable and content
2. document the findings here
3. reimplement the same behavior in Zig
4. use the original assets to verify that the port still matches the game

## Local Preview

Run the docs locally from the repo root:

```bash
zensical serve
```

Build static output into `site/` when needed:

```bash
zensical build --clean
```
