# Complete face normal body match

`cRObject::CalcFaceQuadNormals` (`0x42fcb0`) now reproduces its entire **1,397-byte
native body** with the standard `msvc6.5 /O2 /G5 /W3` profile. All 437 normalized
instructions and 22 positional references already matched; this closes 17
ordinary SIB encoding differences without changing normalized coverage.

Each face iteration now binds a local reference to the object's face-quad bank.
`CURRENT_FACE` uses that live binding for its flags and vertex indices. The
reference preserves member reloads across normal calculations and vector writes;
it does not retain a snapshot pointer across those operations. The normal
accumulation, tallying, validation, and final normalization passes are unchanged.

The [replayable receipt](face-normals-live-quad-bank-20260913.json) contains 17
source reconstructions and measurements, full baseline and retained byte records,
forward/reverse probes, and an independent audit. A mutable bank reference gives
the same complete match. Keeping the reference while restoring direct member
reads restores the original mismatch. Replacing the reference with a cached
pointer regresses the body. Other tested bank and binding scopes are recorded,
including exact alternatives and rejected changes to the vertex-normal bank.
The particular optimizer mechanism behind the address-encoding change is not
established by these observations.

Only the 17 previously unequal raw candidate bytes change: offsets 309, 312,
612, 660, 708, 752, 776, 800, 824, 852, 900, 948, 996, 1040, 1064, 1088, and 1112.
All become the literal native SIB bytes. The independent audit verifies each
relocation identity at the same instruction index and byte offset, consumes every
candidate body relocation, and compares all remaining encoded bytes. All ten
local branches match literally and target instruction boundaries. Eleven terminal
padding bytes remain excluded from the 1,408-byte native extent; there are no
unexplained body bytes. This does not claim linked-executable or runtime parity.

Validation passes all 785 scratches, 1,140 tests, strict experiment/spec checks,
extern lint, baseline and retained receipt replays, and exact-reference auditing.
The public report is refreshed from native compilation and only this function
gains encoded-body exactness.
