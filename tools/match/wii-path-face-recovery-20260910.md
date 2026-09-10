# Wii face-emission lead recovers Windows S-bend

`initialize_sbend_path_template_pair` (`cRPath::BuildSBend`, `0x42df00`)
now matches all **579 instructions**, all **39 positional references**, and the
complete **2,068-byte** Windows function after resolving its COFF relocations.
The unchanged starting source matched 91.10%, with a 443-instruction prefix.

The useful Wii evidence is a shared mesh operation inside the Slalom builder
at `0x8005cbc8`, not a claim that Slalom and S-bend are the same whole function.
Its face loop tests the winding at `0x8005d584`, writes indices and obtains the
texture, then tests the winding again at `0x8005d698` before publishing UVs.
All **765** instruction annotations in the [Wii listing](wii-path-face-recovery-20260910.s)
were compared directly against the pinned DOL.

The previous Windows source placed each side's UV writes in its index/texture
branch. Separating UV publication into the second winding dispatch recovers
99.65%, with 579/579 instructions. The remaining two differences are the
checkerboard branch directions: spelling the even case first recovers the full
function. Both Windows parity arms pass the same texture. Those otherwise
redundant tests are present in Windows and cannot be deleted merely because
Wii optimized them away.

The [receipt](wii-path-face-recovery-20260910.json) includes complete source
controls, compiler/configuration hashes, the Windows comparison and reference
audit, and the pinned Wii body identity. The controls distinguish the recovered
structure from unrelated choices:

- Keeping header stores inside the winding branches and using the second UV
  dispatch gives the accepted result.
- Moving those header stores outside, as Wii does, regresses Windows.
- Moving the UV calculations between the two dispatches and using integer
  index arithmetic also produces an exact control with even-first parity.

No shared type, compiler flag, or reference-normalization rule changes. The
source is evidence for a compatible reconstruction; exact code does not
uniquely establish the original variable names or declaration placement.
Other path builders remain separate matching targets.

## Encoded-body accounting

The extracted COFF body and the native function are both 2,068 bytes. All
**1,912 non-relocation bytes** agree. The remaining 156 bytes are 39 four-byte
COFF relocation fields, each associated with a clean reference at the same
instruction and byte position. There are **zero mismatched non-relocation
bytes and zero unexplained bytes**. The raw unlinked object is not claimed to
be identical to the linked executable.

## Reproduce

From the repository root, with the existing pinned Windows/Wii artifacts:

```sh
uv run snail match scratch initialize_sbend_path_template_pair
uv run snail match leads initialize_sbend_path_template_pair --json
```

Each receipt control carries its complete `source` and `source_sha256`.
Write that source to a temporary `.cpp` file and run:

```sh
uv run snail match probe initialize_sbend_path_template_pair --source /tmp/control.cpp
```
