# Matched

`parse_next_space_delimited_token` is instruction-exact at 27/27 instructions.
It skips leading spaces, copies through the next space or CR, terminates the
output, and advances the caller-owned cursor.

## 2026-07-27 authored RText ownership

Android and iOS preserve this helper as void
`RTextExtractString(char**, char*)` in `RShell.o`. Mobile `ObjectTextLoad`
calls it in the identical face-texture position used by Windows
`load_object_definition`, and the helper occupies the matching slot between
`RTextAppend` and `RTextExtractInt`.

The sole Windows caller discards EAX. Natural void transcriptions were tested
and rejected because VC6 recolors the cursor owner and output registers,
dropping the exact score as low as 22.22%. The scratch therefore retains its
existing result-shaped compiler harness and states that limitation explicitly;
the shared source contract and both analyzer databases use the proven void
API. No dummy branches, volatile values, or other new coercions were added.
