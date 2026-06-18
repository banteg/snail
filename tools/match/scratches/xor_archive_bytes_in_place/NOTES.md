# xor_archive_bytes_in_place

Applies the archive XOR mask in place over a byte span whose logical index
starts at `start_offset`. This is the archive-read counterpart to the exact
`scramble_archive_bytes_in_place` helper.

The helper is modeled as `void`: all known callers consume only the in-place
side effect, and preserving a synthetic `short` return forces VC6 to save
`count`, which is not present in the native body. The native loop naturally
leaves the last byte-mask multiply in `ax`.
