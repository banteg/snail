# initialize_sound_bank @ 0x44dcb0

The exact Windows routine consumes a sentinel-terminated array of 12-byte
records. Each record owns a path pointer, the registered sample id written by
this initializer, and a normalization class. The shipped `g_sound_bank_entries`
table at `0x4a2140` has 51 live records followed by a record whose path points
at the shared empty string.

iOS symbols name the entry type `cRSoundBank` and the initializer
`cRSound::Init(cRSoundBank*)`; Android independently names its corresponding
global `gSFXBank` and uses the same 12-byte stride and field order. The shared
`SoundBankEntry` definition records that authored ownership while retaining the
repository's descriptive naming convention. `sample_id` is intentionally not
called a handle: `register_sound_sample` returns the registered table index,
which the cross-port `cRSound::Play` methods later read from `+0x04`.

The promoted type leaves this function exact at 21/21 instructions.
