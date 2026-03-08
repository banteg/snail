# Binary Ninja Symbol Workflow

The canonical gameplay Binary Ninja target is [`SnailMail_unwrapped.exe.bndb`](/Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb).

Tracked function names live in `analysis/symbols/gameplay-functions.json`. That JSON is the version-controlled source of truth for the gameplay renames we have high confidence in. [`SnailMail.RWG.bndb`](/Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail.RWG.bndb) is now just the historical source we mined those names from.

When a manifest entry also has a `description`, the Binary Ninja sync script treats that text as the function comment for the target database.

Recommended workflow:

1. Open [`SnailMail_unwrapped.exe.bndb`](/Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb) in Binary Ninja and do new renaming work there.
2. Export the current curated names back into the tracked manifest from Binary Ninja's Python environment:
   - `python tools/binja/sync_symbols.py export`
3. Validate the manifest in the repo:
   - `uv run snail symbols --manifest analysis/symbols/gameplay-functions.json`
4. Apply the tracked manifest onto a fresh unwrapped database when needed:
   - `python tools/binja/sync_symbols.py apply`

The Binary Ninja script uses only identifier-like curated names from the open database. It intentionally skips default `sub_*` labels, jump thunks, and mangled compiler symbols so the manifest stays readable and reviewable in version control.
