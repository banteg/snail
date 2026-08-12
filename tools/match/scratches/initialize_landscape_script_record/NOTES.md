# initialize_landscape_script_record @ 0x408840

Exact Windows constructor helper: 7/7 instructions with its masked tColour
constructor operand clean. It constructs the parsed fog color at
`cRLandscape +0x110` and returns the 0x124-byte record.

The helper itself has no verified mobile counterpart, so its descriptive name
is retained. The primary `cRLandscape` owner is instead proven at the exact
`cRBackdrop::Change(cRLandscape*, bool)` boundary preserved by Android and iOS;
`LandscapeScriptRecord` remains a compatibility typedef for analysis prose.
