# set_current_directory_with_drive_fallback @ 0x430f30

Changes the current directory unless the caller passes the shared blank string.
For `X:` paths it first switches to the drive root (`X:\`), treats bare drive
roots as success, then attempts the remaining subpath. On failure it captures
the current directory and reports the missing target.

Focused match: 100%, 48/48 instructions, with six clean masked operands. The
single `success` tail keeps VC6 from duplicating the zero-return epilogue.
