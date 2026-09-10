# Exact hotspot extraction from Wii normalization

`cRSnail::ExtractHotSpots()` at Windows `0x445d50` now matches **74/74
instructions**, the complete prefix, and **7/7 positional references**. This
advances Windows core coverage from **597/662 to 598/662**, with
**141,428/294,937 bytes (47.95%)** proof-grade. All other 784 status rows remain
unchanged, including platform coverage at **114/120**.

## What the new workflow recovered

`snail match leads extract_snail_local_hotspots` locates the named Android and
iPhone bodies. Their existing decompilations corroborate the texture-name walk,
first matching face, first vertex, missing-hotspot diagnostic, and final 0.3 Y
adjustment. They do not expose the normalization needed to explain six redundant
Windows load/store instructions. The new registry keeps those mobile build
identities and the Wii relationship separate from Windows acceptance.

The Wii routine at `0x80052a00` preserves a floating count and an averaging step:

1. Initialize the count to zero (`0x80052a70`).
2. Accumulate the first matching face's first vertex, increment the count, and
   leave the face loop (`0x80052c58`–`0x80052c5c`).
3. Report the missing hotspot if the count is zero (`0x80052c6c`).
4. Otherwise compute `1.0f / count` (`0x80052c98`) and multiply X/Y/Z separately
   (`0x80052ca0`, `0x80052cac`, `0x80052cb8`).

The zero and one constants were read directly from DOL addresses `0x808f5378`
and `0x808f537c`, using the verified startup `r2 = 0x808fc860`. All 216 instruction
annotations in the [PowerPC listing](hotspot-wii-normalization-20260910.asm) were
checked against the original DOL bytes. The [receipt](hotspot-wii-normalization-20260910.json)
pins the build, function, source, compiler, constants, and complete control sources.

The retained C++ follows that count-and-normalize structure. MSVC 6.5 folds the
successful count to one, yet retains the six native component load/store
instructions. This recovers both those instructions and the error-call register
choice. It requires no explicit self-copy, compiler flag change, or altered vector
operator. The count is bounded to zero or one because the search breaks after the
first match.

The Wii port has compressed vertices, different object offsets and hotspot-record
layout, different table termination, and additional post-adjustments. Those
changes are not imported into Windows. Its preserved normalization supplies a
source constraint; Windows instruction, reference, and byte checks establish the
accepted result.

## Bounded controls

| Source form | Windows match | Candidate instructions | Prefix |
| --- | ---: | ---: | ---: |
| Previous source | 91.55% | 68/74 | 31 |
| Floating count, component normalization | 100% | 74/74 | 74 |
| Integer count, component normalization | 100% | 74/74 | 74 |
| Either count, vector value multiplication | 34.78% | 87/74 | 0 |
| Either count, vector `*=` | 48.72% | 82/74 | 0 |
| Either count, old pointer search plus vector value multiplication | 31.06% | 87/74 | 0 |

Both count types produce the same Windows result. Wii's floating operations favor
the floating source hypothesis but do not uniquely establish the original C++
spelling. The initial literal-one/vector-temporary mechanism control also
regressed and was not retained; its probe remains in the experiment ledger.

The complete Windows body has **208 bytes**: **180 identical non-relocation
bytes** and **28 bytes in seven audited four-byte relocations**. Every reference
has identical instruction and byte positions. There are no non-relocation
mismatches or unexplained bytes. The raw unlinked object body is not byte-identical
because relocation values remain unresolved in that representation.

Validation passes **989 tests**, the strict audit of **2,429 experiment records**,
and all **13 active mutation specs**, with no stale active anchors. Historical
negative controls remain historical evidence. No new runtime fixture was added;
the acceptance evidence here is the complete native Windows body and references.

```sh
uv run snail ports --check
uv run snail match leads extract_snail_local_hotspots
uv run snail match scratch extract_snail_local_hotspots
uv run snail match status --check -j 8 --write tools/match/STATUS.md
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```

Each control's full source and SHA-256 are stored in the JSON receipt. A source
can be extracted and rerun with `snail match probe ... --source <file>`; its
comparison baseline will be the current canonical source.
