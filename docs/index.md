# Index

Snail Mail is a reverse-engineering project for the original Windows game. The
repo has two current goals:

- decompile and document how Snail Mail's original artifacts work
- preserve the original content formats and runtime behavior as primary evidence

Matching decompilation comes first. A future implementation can consume the
recovered core behind a deliberately small platform boundary, but no port is an
active source of truth today.

## Project Tracks

- [Original](original/index.md): verified facts about the shipped files, archive layout, and authored content formats
- [RE](re/index.md): deeper notes on the executable, runtime systems, path behavior, Binary Ninja workflow, and trace collection

## Current Shape

Today the repo is split roughly into two evidence tracks:

- Python tooling for archive parsing, text-format inspection, wrapper unwrap, trace summarization, and symbol-manifest validation
- C/C++ matching scratches, analyzer databases, decompile exports, and runtime captures for the original executable

The workflow is intentionally iterative:

1. recover behavior from the original executable and content
2. document the findings here
3. prove source shapes against the shipped executable
4. defer implementation until the recovered core has stable boundaries

## Local Preview

Run the docs locally from the repo root:

```bash
zensical serve
```

Build static output into `site/` when needed:

```bash
zensical build --clean
```
