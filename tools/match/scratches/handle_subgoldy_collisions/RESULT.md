# Exact collision handling

`cRSubGoldy::Collision()` at `0x444cf0` matches all **673/673 native
instructions**, including the complete prefix, with **89 clean references**
and the native **0x74 stack frame**, using `msvc6.5 /O2 /G5 /W3`.

The final recovery keeps salt and sub-lazer access through their owning game
banks, initializes the salt delta and normalization probe within the active
slot, and computes the slug-hit firework position with the shared vector
multiplication and addition operators. The salt probe's bounded lifetime lets
the compiler reuse its stack storage for the later firework sum. This removes
the extra salt copies and restores the native firework publication schedule.

The immediately preceding baseline was 89.45%, 673/673 instructions, prefix
18, with 89 clean references. A coupled expression candidate first restored
the instruction order at 84.40% but used an extra vector slot; localizing the
salt probe completed the match. Earlier conclusions that these differences
required compiler-specific workarounds were disproved by this source shape.
The dated notes and experiment ledger preserve the full measured history.

No inline assembly, volatile storage, dummy dependencies, compiler flag
changes, shared-operator substitutions, or reference-audit exceptions are used.
