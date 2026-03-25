# Binary Analysis Symbol Workflow

The canonical gameplay Binary Ninja target is [`SnailMail_unwrapped.exe.bndb`](../../artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb).
The canonical Windows IDA target now lives at [`artifacts/ida/SnailMail_unwrapped.exe.i64`](../../artifacts/ida/SnailMail_unwrapped.exe.i64).

Tracked function names live in `analysis/symbols/gameplay-functions.json`. That JSON is the version-controlled source of truth for the gameplay renames we have high confidence in. [`SnailMail.RWG.bndb`](../../artifacts/binary_ninja/SnailMail.RWG.bndb) is now just the historical source we mined those names from.

When a manifest entry also has a `description`, the sync tools treat that text as the function comment for the target database.

Recommended workflow:

1. Open [`SnailMail_unwrapped.exe.bndb`](../../artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb) in Binary Ninja and do new renaming work there.
2. Export the current curated names back into the tracked manifest from Binary Ninja's Python environment:
   - `uv run python tools/binja/sync_symbols.py export`
3. Validate the manifest in the repo:
   - `uv run snail symbols --manifest analysis/symbols/gameplay-functions.json`
4. Apply the tracked manifest onto a fresh unwrapped database when needed:
   - `uv run python tools/binja/sync_symbols.py apply`
5. Apply the same manifest onto the colocated IDA database when you want the Windows names available there too:
   - `uv run python tools/ida/sync_symbols.py`
6. Refresh the tracked Binary Ninja and IDA decompile snapshots under [`analysis/decompile`](../../analysis/decompile/README.md) when you want version-controlled pseudocode diffs for every curated symbol:
   - `uv run python tools/export_tracked_decompiles.py --sync-ida-symbols`
7. Export targeted IDA pseudocode artifacts when a single function needs a second-opinion decompile view:
   - `uv run tools/ida/export_function.py update_subgoldy`

The Binary Ninja script uses only identifier-like curated names from the open database. It intentionally skips default `sub_*` labels, jump thunks, and mangled compiler symbols so the manifest stays readable and reviewable in version control.

The IDA sync path is intentionally one-way. Do new rename work in Binary Ninja, validate and commit the manifest, then replay that manifest into `artifacts/ida/SnailMail_unwrapped.exe.i64` so the Windows decompiler views stay aligned across tools.

The preferred tracked snapshot lane now lives under `analysis/decompile/`:

- `analysis/decompile/binja/functions/`: Binary Ninja exports for every manifest function
- `analysis/decompile/ida/functions/`: IDA exports for every manifest function
- the per-tool `index.json` files keep the export set reviewable in git
- those indexes now also flag manifest-to-tool mismatches so selector drift shows up as tracked data instead of a silent export surprise
- the top-level `analysis/decompile/index.json` rolls those counts up so a full refresh immediately shows whether either lane drifted

The targeted IDA export path still writes to `artifacts/ida/functions/` by default, which remains useful for one-off second-opinion checks without refreshing the whole tracked snapshot.
