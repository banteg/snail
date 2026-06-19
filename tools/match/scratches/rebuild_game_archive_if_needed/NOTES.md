# `rebuild_game_archive_if_needed`

Archive rebuild helper at `0x405370`.

Recovered behavior:

- returns immediately when `SnailMail.dat` already exists, or when `SnailMail.dam` is absent;
- allocates a 40,000,000-byte rebuild buffer and loads `SnailMail.dam`;
- toggles the DAM high-bit encoding in place, copies the archive header/index region into the rebuild buffer, and starts appending payload bytes at the header size stored at offset `+8`;
- walks 12-byte archive records: path offset, source data offset, byte count;
- TGA-class entries are written to `0.png`, loaded through the PNG/image helper, converted into a bottom-up BGR(A) TGA-like payload with a 20-byte native header, and their rebuilt byte count is updated;
- all other entries are copied byte-for-byte from the DAM payload;
- payload alignment keeps the native signed remainder expression instead of normalizing to conventional padding;
- writes `SnailMail.dat`, deletes `SnailMail.dam` and `0.png`, then frees the rebuild buffer.

The image loader at `0x42f0a0` is unusual at this callsite: BN shows the archive base in `esi` and entry path in `edi`, with the remaining seven arguments on the stack. The scratch declares the visible seven-argument stack surface and records this as a remaining call-shape issue rather than inventing fake hidden parameters.

No inline assembly, stack padding, dummy symbols, or normalizer-specific tricks are used.
