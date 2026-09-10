# Snake: separate face dispatch and branch-local lateral computation

`initialize_snake_path_template_pair` (`cRPath::BuildSnake`, `0x423580`)
now matches all **652 normalized instructions and 40 positional references**.
The baseline was 88.19%, with a 387-instruction prefix. Compiler, shared types,
ABI, and matching rules are unchanged.

The [Wii face-dispatch evidence](wii-path-face-recovery-20260910.md) first
separates index/texture publication from UV publication. Using direct sample
expressions in the ordinary vertex branch then reaches 99.54%, leaving only
three operands for one compiler-generated integer-to-float temporary.
Computing lateral displacement inside each vertex branch resolves them.
Separate float locals, separate double locals, and inline arithmetic each
produce the full match. The accepted source uses float locals; the result
does not identify a unique original spelling.

The [receipt](snake-branch-lateral-recovery-20260910.json) contains complete
source controls, hashes, the reference audit, and encoded-body accounting.
A helper that computes the generated position regresses this candidate.
The Wii evidence concerns only the shared mesh operation inside Slalom; it
is not asserted to be a whole-function counterpart of Snake.

## Encoded-body accounting

Both bodies are 2,436 bytes. Of the 2,276 non-relocation bytes, **2,274 are
literally identical**. The remaining two bytes select equivalent scale-one
SIB encodings under the matcher's existing default-DS rule:

| Windows address | Native effective address | Candidate effective address |
| --- | --- | --- |
| `0x423a22` (`lea`) | `edi + edx + 0x80` | `edx + edi + 0x80` |
| `0x423a31` (`fstp`) | `edi + eax + 0x8c` | `eax + edi + 0x8c` |

All 160 relocation bytes belong to 40 four-byte COFF fields with clean
references at matching instruction and byte positions. There are **zero
unexplained bytes**. This is a proof-grade normalized instruction match,
not literal encoded-body byte identity or a linked-executable claim.

## Reproduce

```sh
uv run snail match scratch initialize_snake_path_template_pair
uv run snail match leads initialize_snake_path_template_pair --json
```

To replay a receipt control, write its complete `source` to a temporary file,
verify `source_sha256`, and run:

```sh
uv run snail match probe initialize_snake_path_template_pair --source /tmp/control.cpp
```
