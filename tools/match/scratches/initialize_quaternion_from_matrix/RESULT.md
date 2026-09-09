# `initialize_quaternion_from_matrix` match result

The typed matrix-to-quaternion constructor is now **proof-grade exact** under
`msvc6.5 /O2 /G5 /W3`.

| Metric | Previous | Current |
| --- | ---: | ---: |
| Match | 92.47% | **100%** |
| Instructions | 186/186 | **186/186** |
| Common prefix | 42/186 | **186/186** |
| Positional references | 23 clean | **23 clean** |
| Accounted body bytes | partial instruction match | **579/579** |

The Wii constructor at `0x8000a968` supplies the decisive source evidence:
select an integer X/Y/Z axis using a `right.x >= up.y` outer comparison and
then execute ordinary equality-based output bodies. This recovers Windows'
branch topology without explicit labels. Shared exits also match; switch
bodies regress to 66.15% and are not retained.

The positive trace formula, native diagnostic spellings, fallback sums, and
caller-side `float Sqrt(float)` contract remain intact. All 487 non-relocation
bytes agree, and the remaining 92 bytes are 23 positionally audited relocations.
There are no unexplained bytes. Raw unlinked bytes are not identical.

The original-code runtime comparison passes all ten fixtures and rejects its
fallback-difference control. Full status preserves every other function, and
939 tests plus strict experiment/spec checks pass.

See the [evidence report](../../quaternion-wii-dispatch-20260909.md),
[machine-readable receipt](../../quaternion-wii-dispatch-20260909.json), and
[Wii disassembly](../../quaternion-wii-dispatch-20260909.asm). Earlier experiments
remain in `experiments.jsonl` and the chronological notes.
