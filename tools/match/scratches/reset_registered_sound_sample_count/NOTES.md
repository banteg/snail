# reset_registered_sound_sample_count @ 0x432d40

Single-store owner that clears the 256-entry registered sound-sample table count
before game-data archive initialization registers voice and effect samples.

## 2026-07-16 authored owner closure

Android retains this body as the void `RShellSoundInit()` helper and performs the
same single store to `RShellSoundCount`. Both Android ABIs export that count at
exactly four bytes immediately before the separately named, 0x8000-byte
`RShellSoundName` matrix. The Windows store therefore owns an independent scalar;
it is not evidence for a synthetic sound-registry struct.
