# Exact quaternion constructor from Wii axis selection

`tQuaternian::tQuaternian(const tMatrix&)` at Windows `0x44d5d0` now matches
**186/186 instructions**, the complete **186-instruction prefix**, and **23
positional references**. This completes the two-function target: the earlier
[level loader](level-native-loop-20260909.md) advanced 595/662 to 596/662, and
this constructor advances **596/662 to 597/662**. Proof-grade coverage is now
**141,220/294,937 bytes (47.88%)**.

The decisive source structure came from the retained WiiWare executable.
Its quaternion constructor at `0x8000a968` selects an integer axis using a
`right.x >= up.y` outer condition, then dispatches through X/Y/Z equality
checks. At `0x8000aa08`, `fcmpo` plus `cror eq,gt,eq` implements that first
comparison. The five-comparison tree writes `r0 = 0`, `1`, or `2`; the tests
at `0x8000aa64`, `0x8000ab08`, and `0x8000abac` select the output bodies.
The two diagnostic strings and all three unusual fallback `w` sums independently
corroborate the correspondence with Windows.

The recovered source retains this axis-selection tree and ordinary
`if / else if` output bodies. Compiling it with the existing
`msvc6.5 /O2 /G5 /W3` profile eliminates the previous branch-placement mismatch.
No shared declarations, compiler flags, or registered source groups change.
The Wii port establishes a plausible source shape; the Windows matcher provides
the exactness proof. The two architectures do not receive joint matching credit.

| Control | Windows match | Instructions | Prefix |
| --- | ---: | ---: | ---: |
| Previous label-based source | 92.47% | 186/186 | 42 |
| Wii axis tree, equality bodies, arm returns | 100% | 186/186 | 186 |
| Same tree and bodies, shared exit | 100% | 186/186 | 186 |
| Same tree, switch bodies, either exit form | 66.15% | 201/186 | 42 |

The [receipt](quaternion-wii-dispatch-20260909.json) accounts for all **579
Windows body bytes**: **487 identical non-relocation bytes** and **92 bytes in
23 audited four-byte relocations**. Every reference occupies the same instruction
index and byte offset. There are zero non-relocation mismatches and zero
unexplained bytes. The raw unlinked body is **not byte-identical**, because its
relocations still need resolution.

The unchanged original-code comparison passes all ten fixtures, producing the
same 160 serialized quaternion bytes. Both executables reject the control that
changes the shipped fallback `w` sum to a difference. These fixtures cover the
trace path, each fallback axis, ties, and asymmetric off-diagonal values; they
do not exhaust non-finite or negative-radicand inputs. Exact Windows instruction
and reference evidence is independent of that finite runtime sample.

All **785 status rows** were compared with the previous commit; only this
constructor's row changes. Platform coverage remains **114/120**. Validation
passes **939 tests**, the strict experiment audit, and all active mutation-spec
anchors. The original-code and micro-oracle tools remain intact.

The Wii content `01_00000017.app` is LZ11-compressed. It was decoded with the
MIT-licensed [nlzss decoder](https://github.com/magical/nlzss/blob/master/lzss3.py).
The receipt pins the compressed content, decoder source, decompressed DOL,
synthetic ELF, and function body hashes. All ten initialized ELF load segments
were checked against the DOL's original virtual addresses and bytes. The
[PowerPC listing](quaternion-wii-dispatch-20260909.asm) was exported with Ghidra
12.1.2; the synthetic ELF is only an import container, not an original artifact.
The existing Wii extraction manifest's DOL label alone is not sufficient to
identify decompressed executable content.

```sh
uv run snail match scratch initialize_quaternion_from_matrix
WIBO=/Users/banteg/dev/banteg/crimson/tools/match/bin/wibo uv run tools/match/compare_quaternion_native.py --runtime-library /Users/banteg/dev/banteg/crimson/tools/native/providers/build/vc6-sp6/vc98/lib/msvcrt.lib --out artifacts/match/quaternion-wii-runtime-20260909
uv run snail match status --check --write tools/match/STATUS.md
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```
