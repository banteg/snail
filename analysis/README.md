# Analysis Artifacts

This directory is for repo-tracked reverse-engineering artifacts that support the work but do not belong in the published docs site.

Current contents:

- `symbols/gameplay-functions.json`: the curated gameplay function manifest used by the Binary Ninja sync workflow and the `snail symbols` validator
- `headers/`: Binary Ninja import headers; use `headers/snail_bn_import.h` for the curated minimal bundle or `headers/upstream/bass20/bass_bn_import.h` for the official vendored BASS 2.0 header
