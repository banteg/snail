# Index

Snail Mail is a reverse-engineering project for the original Windows game. The
repo has three current goals:

- decompile and document how Snail Mail's original artifacts work
- preserve the original content formats and runtime behavior as primary evidence
- run the recovered source as a modern port, behind a deliberately small
  platform boundary

Matching decompilation comes first: the original executable stays the source of
truth. The port compiles the recovered source unchanged and is checked against
the original tick by tick; it plays in the browser at
[snail.banteg.xyz](https://snail.banteg.xyz). See the [port plan](port/README.md).

## Project Tracks

- [Original](original/index.md): verified facts about the shipped files, archive layout, and authored content formats
- [RE](re/index.md): deeper notes on the executable, runtime systems, path behavior, Binary Ninja workflow, and trace collection
- [Port](port/README.md): how the recovered source runs on modern platforms, its oracles, and the [divergences](port/divergences.md) it needs

## Current Shape

Today the repo is split roughly into three tracks:

- Python tooling for archive parsing, text-format inspection, wrapper unwrap, trace summarization, symbol-manifest validation, and the port's build and oracle commands
- C/C++ matching scratches, analyzer databases, decompile exports, and runtime captures for the original executable
- the port: the recovered source in `decomp/`, compiled with a small C++ shell in `port/` into wasm, with browser and native (SDL3) hosts

The workflow is intentionally iterative:

1. recover behavior from the original executable and content
2. document the findings here
3. prove source shapes against the shipped executable
4. run the proven source in the port and compare it with the original; a divergence points back at the recovered source

## Local Preview

Run the docs locally from the repo root:

```bash
zensical serve
```

Build static output into `site/` when needed:

```bash
zensical build --clean
```
