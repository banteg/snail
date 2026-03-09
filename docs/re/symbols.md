# Binary Analysis Symbol Workflow

The canonical gameplay Binary Ninja target is [`SnailMail_unwrapped.exe.bndb`](../../artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb).
The canonical Windows IDA target now lives at [`artifacts/ida/SnailMail_unwrapped.exe.i64`](../../artifacts/ida/SnailMail_unwrapped.exe.i64).

Tracked function names live in `analysis/symbols/gameplay-functions.json`. That JSON is the version-controlled source of truth for the gameplay renames we have high confidence in. [`SnailMail.RWG.bndb`](../../artifacts/binary_ninja/SnailMail.RWG.bndb) is now just the historical source we mined those names from.

When a manifest entry also has a `description`, the sync tools treat that text as the function comment for the target database.

Recommended workflow:

1. Open [`SnailMail_unwrapped.exe.bndb`](../../artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb) in Binary Ninja and do new renaming work there.
2. Export the current curated names back into the tracked manifest from Binary Ninja's Python environment:
   - `python tools/binja/sync_symbols.py export`
3. Validate the manifest in the repo:
   - `uv run snail symbols --manifest analysis/symbols/gameplay-functions.json`
4. Apply the tracked manifest onto a fresh unwrapped database when needed:
   - `python tools/binja/sync_symbols.py apply`
5. Apply the same manifest onto the colocated IDA database when you want the Windows names available there too:
   - `uv run tools/ida/sync_symbols.py`
6. Export targeted IDA pseudocode artifacts when a single function needs a second-opinion decompile view:
   - `uv run tools/ida/export_function.py update_subgoldy`
7. Refresh the whole named Windows gameplay slice under `artifacts/ida/functions/` when you want `rg`-friendly second-opinion pseudocode for every curated symbol:
   - `uv run tools/ida/export_manifest_functions.py`

The Binary Ninja script uses only identifier-like curated names from the open database. It intentionally skips default `sub_*` labels, jump thunks, and mangled compiler symbols so the manifest stays readable and reviewable in version control.

The IDA sync path is intentionally one-way. Do new rename work in Binary Ninja, validate and commit the manifest, then replay that manifest into `artifacts/ida/SnailMail_unwrapped.exe.i64` so the Windows decompiler views stay aligned across tools.

The targeted export path writes pseudocode artifacts under `artifacts/ida/functions/` by default. The manifest-backed export now writes the whole curated gameplay set to that same directory, which is the preferred way to keep an `rg`-friendly second-opinion snapshot without regenerating a giant whole-program C dump of unrelated runtime code.
