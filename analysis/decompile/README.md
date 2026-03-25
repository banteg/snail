# Tracked Decompiled Function Snapshots

This tree stores repo-tracked function exports for the curated symbol manifest in
[analysis/symbols/gameplay-functions.json](/Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json).

Purpose:

- make Binary Ninja and IDA pseudocode changes observable in git
- preserve decompile improvements that would otherwise live only in the open databases
- keep both decompiler lanes aligned to the same named-function set

Layout:

- `binja/functions/`: Binary Ninja decompile exports for every named manifest function
- `binja/index.json`: Binary Ninja export index
- `ida/functions/`: IDA pseudocode exports for every named manifest function
- `ida/index.json`: IDA export index
- `index.json`: top-level refresh summary

Refresh the tracked snapshots with:

```bash
uv run python tools/export_tracked_decompiles.py --sync-ida-symbols
```

Notes:

- the Binary Ninja lane exports from the active target by default; pass `--bn-target` if needed
- the IDA lane exports from the tracked `.i64` unless `--ida-db` is provided
- reruns prune stale `.c` files from the tracked output trees when a manifest name changes
