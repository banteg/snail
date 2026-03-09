# Analysis Artifacts

This directory is for repo-tracked reverse-engineering artifacts that support the work but do not belong in the published docs site.

Current contents:

- `symbols/gameplay-functions.json`: the curated gameplay function manifest used by the Binary Ninja sync workflow and the `snail symbols` validator
- `headers/`: handwritten minimal import headers for Binary Ninja; import `headers/snail_bn_import.h` to pull in the currently recovered Win32, Direct3D 8, DirectInput 8, and BASS 2.0-era surfaces used by the game
