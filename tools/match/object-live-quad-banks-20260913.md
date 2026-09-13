# Complete object texture bank matches

`cRObject::CalcTextureGroups` and `cRObjects::ReTextureObjects` now reproduce their
complete native encoded bodies with the standard `msvc6.5 /O2 /G5 /W3` profile.
Both already had 100% normalized instruction scores; this change adds **256
relocation-audited byte-exact body bytes**, without adding normalized coverage.

| Function | Instructions | Body / native extent | Positional references | Local branches | Previously unequal byte offsets |
|---|---:|---:|---:|---:|---|
| `calc_object_texture_groups` | 55 | 127 / 128 | 1 | 10 | 42 |
| `replace_object_list_texture_refs` | 53 | 129 / 144 | 1 | 6 | 59, 63 |

The source binds a local reference to each object's face-quad pointer and uses
that binding for the contested access. A reference retains the live member read:
`CalcTextureGroups` reads the texture after updating the quad's byte flags, and
`ReTextureObjects` reads each quad's texture slot while traversing an object.
These are ordinary typed pointer accesses. The retained change does not cache a
bank pointer across an operation where the original reloads it.

This follows the live-bank ownership clue from the recovered path builders.
The observation is reproducible; it does not establish the VC6 optimizer's
internal reason for choosing one base/index encoding over its commuted form.

The [replayable receipt](object-live-quad-banks-20260913.json) contains 19 complete
source reconstructions, measurements, baseline and retained bytes, forward and
reverse probes, and an independent audit script. Mutable references produce the
same complete matches. Restoring direct member reads while keeping the bindings
restores the original mismatch. A typed read without the reference also fails
to fix `CalcTextureGroups`; a pointer snapshot regresses it. Typed array access
without a live bank reference does not fix `ReTextureObjects`.

Only three raw candidate bytes change, all ordinary SIB bytes, and each becomes
identical to its native counterpart. The independent audit verifies every
four-byte relocation against its same-index, same-offset reference identity,
consumes all candidate body relocations, and compares every other body byte.
All local branches retain their literal native encodings and land on verified
instruction boundaries. The trailing 1 and 15 bytes remain excluded terminal
padding; there are no unexplained body bytes. This proves function bodies, not
a linked executable or runtime behavior.

Validation: all 785 scratch checks, 1,140 tests, strict experiment/spec checks,
extern lint, retained-source receipt replays, and the exact-reference audit pass.
The public report is refreshed from native compilation; normalized coverage and
all other function bodies retain their previous status.
