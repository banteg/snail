# Exact match

`initialize_landscape_script_record` @ 0x408840 constructs one
0x124-byte `LandscapeScriptRecord` in the 128-entry landscape-script bank at
`game+0xff81a4`. The only emitted work is the no-op `Color4f` constructor for
the parsed fog color at `+0x110`, which matches the shared record layout in
`landscape_script.h`.
