# rstrcpy_checked_ascii

Initial scratch for the resource-string copy helper at `0x44e5b0`.

Recovered relationships:

- Copies a null-terminated resource string and reports `"Dodgy Rstrcpy %s"` for
  non-ASCII/high-bit bytes while continuing the copy.
- Empty input writes one null byte to the destination. The scratch treats the
  helper as `void`; BN may show an incidental zero return because AL still holds
  the null byte.
- The diagnostic receives the current source cursor, not necessarily the
  original string pointer.

Focused Wibo verifies this as exact: 100.00%, 31/31 instructions, with 2 masked
operands OK.
