# cRSubTracks::ImportSegment @ 0x447300

Exact match: 100.00%, 125/125 instructions, with all five masked operands
clean.

This authored member finds a root-owned `cRSMTracks` catalog entry by filename,
transposes its column-major eight-lane glyph grid into one caller-selected
`cRSubSegment`, and copies the per-row flags, object metadata, position and
velocity vectors, parcel id, local position, path template, and ring speed.
The Windows destination is a 0x4220-byte inline record; only `source_name`
borrows storage from the catalog.

Android and iOS `Subtrack.o` independently export
`cRSubTracks::ImportSegment(char*, cRSubSegment*)` and preserve the copy
sequence. Live Windows analysis confirms a void two-argument thiscall. Its
otherwise-unused receiver is established by all three calls, which import an
ordinary slot, `first_segment`, or `last_segment`.

Direct authored-row subscripts recover the native interior cursor scheduling;
whole-row assignment would instead emit `rep movsd`. The stable matcher
identity remains `copy_segment_definition_to_level_slot`; source and
relocations now use the authored method and destination type.
