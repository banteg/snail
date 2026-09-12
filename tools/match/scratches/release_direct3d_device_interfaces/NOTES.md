# release_direct3d_device_interfaces @ 0x411960

Owns teardown of the two Direct3D COM interfaces stored by
`Direct3DRenderer`:

- `device` at `+0xbb94` is released first and cleared;
- the `Direct3D8` interface at `+0xbb90` is then released and cleared.

Native calls vtable slot `+0x08` for both objects, the COM `Release` slot. The
shared `Direct3DDevice8Vtbl` and `Direct3D8Vtbl` now expose that inherited COM
slot directly, so teardown no longer recasts either owned interface into a
scratch-local release-only shell. The exact teardown remains the regression
oracle for the shared ABI; the repository-wide exact audit covers all other
consumers of both vtables.

## 2026-07-15 Binary Ninja replay

Live readback now shows a `Direct3DRenderer*` receiver and typed `Release`
calls for both owned interfaces, followed by clears of `renderer->device` and
`renderer->d3d`. The device address `0x502fec` resolves as the singleton's
`+0xbb94` field and has no independent symbol or data variable.

## 2026-09-12 native extent certification

The default next-curated-function extent, `0x411960..0x4119c0`, included
unrelated code after this member's return. Its comparison was **64.29%**,
18/38 candidate/target instructions, with the complete candidate as an exact
18-instruction prefix. The source needed no change.

The [native receipt](evidence/native-extent-20260912.json) records the original
bytes, addressed disassembly, compiler/source/object hashes, and both extent
controls against the pinned image. The two conditional branches target
`0x41197d` and `0x411997`; both Release calls are indirect COM calls. The final
`pop esi; ret` is at `0x411997..0x411999`. This agrees with the retained
[Binary Ninja export](../../../../analysis/decompile/binja/functions/00411960-release_direct3d_device_interfaces.c).

Seven alignment NOPs follow. At `0x4119a0`, a separate jump thunk leads to a
bare return at `0x4119b0`, consistent with the independently inspected
[uncurated entries](../../uncurated-entry-check-20260907.md). Neither belongs
to the teardown's control flow. `END=0x411999` now pins the member's exclusive
return endpoint instead of relying on the next curated function.

The standard `msvc6.5 /O2 /G5 /W3` build is **100%**, **18/18 instructions**,
with all **57 body bytes identical** and no COFF relocations to mask. Its
seven compiler-emitted terminal NOPs also equal the native alignment bytes;
they are separate from the 57-byte body proof. This restores one platform
helper's exact certification, without adding a gameplay function or claiming
newly recovered C++ behavior.

`inspect` now reports a target-only suffix after a completely matching
candidate return, including its native addresses. This is diagnostic only:
post-return code still participates in matching until its boundary is
independently verified. Regression tests retain the overlong native suffix as
a mismatch and check that a branch into post-return cold code is not trimmed.

Recheck with:

```sh
uv run snail match scratch release_direct3d_device_interfaces
uv run pytest -q tests/test_match_tail.py
```

For the overlong control, run `uv run snail match diff
tools/match/scratches/release_direct3d_device_interfaces/build/scratch.obj
release_direct3d_device_interfaces` after the scratch build. This direct
object comparison uses the next curated function as its endpoint.

Validation: 1,140 tests pass; full status, exact-reference audit, extern lint,
and strict experiment/spec checks pass. Ruff reports the same 15 pre-existing
findings in `match.py` as HEAD; changed code introduces none. Platform proof
increases from 113 to 114 helpers and from 17,576 to 17,633 bytes. The fixed
curated denominator remains 23,008 bytes. Fuzzy progress decreases slightly
(96.83% to 96.81%) because the old 96-byte comparison gave fractional credit
to the now-excluded neighboring bytes. Gameplay metrics do not change.
