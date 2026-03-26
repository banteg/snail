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
- `index.json`: top-level refresh summary, including combined mismatch counts

Each per-tool index also records mismatch data:

- `mismatch_count`
- `mismatches`

The top-level `index.json` also records:

- `bn_mismatch_count`
- `ida_mismatch_count`
- `total_mismatch_count`
- `has_mismatches`
- `health_check_ran`
- `health_check_count`
- `health_failing_check_count`
- `health_passed`
- `bn_mismatches`
- `ida_mismatches`
- `failing_checks`
- `selected_functions`

Those entries flag cases where the tracked manifest does not line up with what the
tool actually exported, for example:

- manifest name differs from the live Binary Ninja name at the same address
- an IDA selector resolves to a different function start or name than the manifest expects

Refresh the tracked snapshots with:

```bash
uv run python tools/export_tracked_decompiles.py --sync-ida-symbols
```

Refresh only a narrow touched subset and fail fast on mismatch or health regressions with:

```bash
uv run python tools/export_tracked_decompiles.py --only update_subgoldy --only update_cameraman --strict
```

Run just the hotspot health checks with:

```bash
uv run python tools/check_decompile_health.py --strict
```

Notes:

- the Binary Ninja lane exports from the active target by default; pass `--bn-target` if needed
- the IDA lane exports from the tracked `.i64` unless `--ida-db` is provided
- reruns prune stale `.c` files from the tracked output trees when a manifest name changes
- inspect mismatch entries first when one tool appears to “miss” a function; they often indicate real database drift rather than an export failure
- the health check is intentionally narrow and only guards a few high-value tracked exports where type/prototype regressions have caused real readability loss before
- `--only` matches manifest names or hex addresses and is forwarded to both export lanes
- `--strict` exits nonzero when either lane reports mismatches or any health check fails
