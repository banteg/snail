# Analysis Artifacts

This directory is for repo-tracked reverse-engineering artifacts that support the work but do not belong in the published docs site.

Current contents:

- `symbols/gameplay-functions.json`: the curated gameplay function manifest used by the Binary Ninja sync workflow and the `snail symbols` validator
- `symbols/windows-ios-gameplay-crosswalk.json`: provenance map from stable Windows match names to recovered iOS C++ owner/method names
- `decompile/`: repo-tracked Binary Ninja and IDA function exports for the curated manifest, so decompile improvements are visible in git instead of living only in the databases
- `headers/`: Binary Ninja import headers; use `headers/snail_bn_import.h` for the curated minimal bundle or `headers/upstream/bass20/bass_bn_import.h` for the official vendored BASS 2.0 header
- `runtime/`: repo-only session notes, branch maps, and raw reverse-engineering findings that are too detailed or provisional for the published docs
