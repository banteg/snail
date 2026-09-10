# Twister pair: sample-bank reset ownership

Both Windows functions now match all **677 normalized instructions and 49
positional references**, up from 86.94% with 678 candidate instructions.

| Function | Windows address | Samples | Final sample | Angle factor |
| --- | --- | ---: | ---: | ---: |
| `initialize_twister_path_template_pair` | `0x42a540` | 34 | 33 | `0.19634955f` |
| `initialize_twister2_path_template_pair` | `0x42af30` | 52 | 51 | `0.25132743f` |

The [Wii shared-mesh evidence](wii-path-face-recovery-20260910.md) separates
index/texture dispatch from UV dispatch. A physical sample cursor and direct
sample expressions then recover the curve and mesh structure to 96.24%,
leaving one extra instruction in the first matrix-identity receiver setup.

The accepted inline initialization helper takes the sample bank by reference,
then the byte offset and center. It initializes the same center and scalar
fields and calls the existing void `tMatrix::Identity()` member. Borrowing the
bank preserves the repeated bank reads across those stores; it does not cache
a sample pointer or add a dependency. This resolves the extra register copy.
The native receiver sequence is `mov ecx, [esi+0x58]; add ecx, edi; call`.

The [receipt](twister-bank-reset-recovery-20260910.json) independently replays
five complete source controls for each function. The direct body, path-pointer
helper, and center-first bank-reference helper remain at 96.24%. Bank-first
helpers with either a float center or const-float-reference center match.
These controls establish a valid source form, not a unique original helper
name or signature. Twister2 keeps all its own counts, endpoints, kind and
angle constant; it is verified against its own complete Windows body.

Compiler profile, shared headers, ABI and matcher rules are unchanged. The Wii
receipt constrains the shared mesh operation inside Slalom; this report does
not claim that Slalom is a whole-function counterpart of either Twister.

## Encoded-body accounting

Each native and candidate body is **2,540 bytes**. Each comparison accounts for:

- **2,329 identical non-relocation bytes**;
- **15 equivalent scale-one SIB bytes**, with exchanged base/index registers
  and the same effective address and default DS segment;
- **196 relocation bytes**, comprising 49 four-byte COFF fields whose
  references match at the same instruction and byte positions;
- **zero unexplained bytes**.

The JSON lists every SIB instruction's native address, both encoded forms and
all relocation offsets, alongside native-image, source and body hashes. These
are proof-grade normalized instruction matches, not literal raw-body identity
or a linked-executable claim. No normalization rule was changed.

## Reproduce

```sh
uv run snail match scratch initialize_twister_path_template_pair
uv run snail match scratch initialize_twister2_path_template_pair
```

For a control, write its complete `source` to a temporary file, verify the
recorded `source_sha256`, and run `uv run snail match probe FUNCTION --source
/tmp/control.cpp` with that function's recorded compiler and flags.

## Validation

The full status refresh reaches **602/662** port-relevant matches and
**151,012/294,937 proof-grade bytes (51.20%)**. Comparing all 785 function rows
against the start of the four-function request changes only S-bend, Snake,
Twister and Twister2. The platform total remains 114/120.

All 989 tests pass. The strict experiment audit checks 2,433 records across
184 files with zero errors or strict errors; all 13 active mutation specs are
runnable. Build/evidence identity checks and `git diff --check` also pass.
