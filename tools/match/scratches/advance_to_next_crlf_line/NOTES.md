# advance_to_next_crlf_line

Initial scratch for the CRLF-only resource text cursor helper at `0x44e690`.

Recovered relationships:

- Called by level, segment, and voice definition loaders.
- This is distinct from the exact `skip_to_next_line` helper at `0x431e30`.
- It searches for a Windows `\r\n` line break and returns the first character
  after it, but returns null when no CRLF is found or when the CRLF is the final
  text in the buffer.

The name is intentionally narrow until the loader callsites identify the
original class or parser family more strongly.

Focused Wibo result: 79.07%, 21/22 candidate/target instructions, no masked
operands. Semantics match the native CRLF scan. The residual is the native
duplicated entry zero-test (`test al, al; je ...; mov dl, 0xa; je ...`) and the
resulting branch-label distances; a duplicated source guard made the block
layout worse, so this scratch keeps the plausible single-condition form.
