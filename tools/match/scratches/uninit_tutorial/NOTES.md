# Exact match

`Tutorial::uninit_tutorial` @ `0x448dd0` is the Windows
`cRTutorial::UnInit()`. It delegates tutorial UI teardown to the root
`TipManager`; the embedded tutorial object owns no tip allocation.

The primary 0x1c-byte `Tutorial` owner remains exact at 3/3 instructions with
both operands clean.

The teardown call now names `GameRoot::tip_manager`, the exact 0x98-byte root
tail owner, instead of reconstructing it from `root + 0x12e6f58`. The global
receiver load and exact three-instruction body are unchanged.
