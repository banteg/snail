# scramble_archive_bytes_in_place

Exact 25-instruction helper at `0x405270`, called only by
`save_file_bytes_with_optional_archive_scramble`. For every index below the
signed byte count it XORs the byte in place with the low-byte polynomial
`(i * i) ^ (i * 3)`.

## 2026-08-12 authored RShell contract

Android exports the corresponding body as
`RShellScrambleFileDat(void*, int)`. It maintains the `i * 3` term as an
eight-bit accumulator advanced by three and computes the same low-byte
`i * i` term, so overflow and the complete modulo-256 mask agree with Windows.
Both implementations are void and mutate only the caller-owned buffer.

iOS does not retain a standalone helper: its exact
`SaveFile(char*, void*, int, bool)` body in the STABS-marked `DatBuild.o` unit
inlines the complete polynomial immediately before the same fopen/write/close
sequence as the Windows caller. That enclosing function, the sole Windows
caller, and the cohesive archive-builder linker run recover `DatBuild.o` as the
Windows source unit. The Android name still recovers the authored
`RShellScrambleFileDat` vocabulary and distinguishes this DAT polynomial from
the simpler `RShellScrambleFile` index XOR used by high-score files.

The stable Windows matcher name is retained as an alias, and its focused
scratch remains exact at 25/25 instructions with no masked operands. The
Binary Ninja and IDA archive-shell replays now preserve its void-pointer ABI.
