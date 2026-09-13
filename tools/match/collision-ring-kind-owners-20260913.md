# Complete player collision body match

`cRSubGoldy::Collision` (`handle_subgoldy_collisions`, `0x444cf0`) now matches its
entire **2,887-byte native body** with `msvc6.5 /O2 /G5 /W3`. Its 673 normalized
instructions and 89 positional references already matched. Two ordinary SIB
bytes remained unequal, at offsets 2518 and 2575.

Both differences belong to ring-kind reads. The source already selects
`effect_game` for the velocity effect and `ladder_game` for the reward ladder.
The corresponding kind reads now use those existing local owners instead of
spelling a new read through the player's `game` member. No call or write occurs
between either local selection and its kind read. This preserves the native
single game-pointer load and its subsequent consumers in each block.

The [replayable receipt](collision-ring-kind-owners-20260913.json) contains 15
source reconstructions, native measurements, complete baseline and retained
instruction/byte records, forward/reverse probes, and an independent audit.
Reversing only the effect-owner read restores byte 2518's mismatch; reversing
only the ladder-owner read restores byte 2575's mismatch. Reversing both restores
the exact baseline code hash. Live references combined with the corresponding
owner reads also match, while broader game-reference controls regress and remain
unpromoted. The retained change uses the existing local pointers and adds no
bindings or helpers.

Only the two previously unequal raw candidate bytes change, and both become
identical to the literal native SIB bytes. The independent audit verifies all
89 reference identities at the same instruction index and byte offset, consumes
all body relocations, and compares every other encoded body byte. All 83 local
branches match literally and target verified instruction boundaries. Nine bytes
of terminal padding remain excluded from the 2,896-byte native extent; there
are no unexplained body bytes. This proves the function body, not a linked image
or runtime behavior.

All 785 scratch checks, 1,140 tests, strict experiment/spec checks, extern lint,
baseline and retained receipt replays, and exact-reference auditing pass. The
public report is refreshed from native compilation; only this function gains
encoded-body exactness.

This completes the requested five additional complete body matches, following
[object texture banks](object-live-quad-banks-20260913.md),
[distorted vertices](distort-live-vertex-banks-20260913.md), and
[face normals](face-normals-live-quad-bank-20260913.md). Together they cover
5,188 newly byte-exact body bytes. All five were already normalized matches,
so normalized coverage remains unchanged. No further target is promoted in this
five-match request.
