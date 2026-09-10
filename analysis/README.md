# Analysis Artifacts

This directory is for repo-tracked reverse-engineering artifacts that support the work but do not belong in the published docs site.

Current contents:

- `ports/`: Windows-first build registry, per-build symbol indexes, cross-port source constraints, and reproducible lineage evidence; use `uv run snail ports --check` and `uv run snail match leads <function>`
- `symbols/gameplay-functions.json`: the curated gameplay function manifest used by the Binary Ninja sync workflow and the `snail symbols` validator
- `symbols/ios-ipa-gameplay-names.json`: compact symbol, source-object, class, and type-string evidence recovered from the iOS binaries
- `symbols/windows-ios-gameplay-crosswalk.json`: provenance map from stable Windows match names to recovered iOS C++ owner/method names
- `symbols/windows-constructor-support-runs.json`: bounded Windows emission-unit provenance for constructor helpers, with folded/shared exclusions
- `symbols/windows-mobile-gameplay-crosswalk.json`: the current Windows-to-mobile structural crosswalk used to corroborate names and ownership
- `decompile/`: repo-tracked Binary Ninja and IDA function exports for the curated manifest, so decompile improvements are visible in git instead of living only in the databases
- `headers/`: Binary Ninja import headers; use `headers/snail_bn_import.h` for the curated minimal bundle or `headers/upstream/bass20/bass_bn_import.h` for the official vendored BASS 2.0 header
