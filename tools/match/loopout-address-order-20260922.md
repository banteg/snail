# LoopOut interpolation address ordering

LoopOut still has one unequal encoded byte. Two preserving VC6 observations
explain why the tested bank borrow moves that mismatch instead of removing it.
No source or matching credit is changed.

Both sources have **718/718 normalized instructions**, a 718-instruction
prefix and **52 strict positional references**. Independent byte comparison
covers the complete **2,615-byte body**, all 26 literal local branches and
nine separately accounted terminal padding bytes in the 2,624-byte extent.

| Source | Endpoint load, byte 745 | Destination store, byte 770 |
| --- | --- | --- |
| Canonical local bank | `01`, unequal | Native `07` |
| Interpolation helper borrowing the field | Native `08` | `38`, unequal |

These are the only two changed raw candidate bytes. References, relocations,
instruction boundaries and all other body bytes are identical. The borrowed
source fixes the complete `fld [eax + ecx + 0x90]` encoding and loses the
complete `fstp [edi + eax + 0x90]` encoding. Neither body is encoded-exact.

## Compiler evidence and bounded inference

Both fresh captures preserve the complete ordinary, captured, replayed and
observed COFF objects, ignoring only timestamp bytes 4–7. Missing-stream
replay is rejected. Compiler decisions are not patched. The receipt binds
all four extracted function bodies to the independently audited byte captures.

At the entry to `C2+0x281cd`, the two address sums have these packed costs:

| Source | Bank | Endpoint offset | Destination offset | Emitted bank position |
| --- | --- | --- | --- | --- |
| Canonical | `0x102a0` | `0x16ec0` | `0x14a80` | Second in both sums |
| Field borrow | `0x16f00` | `0x16e80` | `0x14b00` | First in both sums |

The saved dataflow follows each address to its field access and follows the
interpolation value through subtraction, conversion, multiplication, division,
addition and the final store. In the canonical expression the endpoint's
`+0x90` member displacement has already folded into its offset symbol; in the
borrowed expression it follows the address sum. The compiler node addresses
are identities within one event, not stable identities across observations.

The [previously inspected comparator](c2/README.md) orders these packed costs
in descending unsigned order. Native's load requires bank-first, while its
store requires offset-first. **For either captured pair of index trees**, a
single bank cost would have to be above the endpoint cost and below the
smaller destination cost. That interval is empty. This bounds bank-only
changes on these trees; it does not establish a compiler limit or identify the
unavailable original source. The index trees or their separate ownership are
the next relevant source questions.

## Source controls

The [receipt](loopout-address-order-20260922.json) contains **76 source
controls**, 43 pinned build inputs, both complete byte captures and both
preserving observations. Every source compiles; none is encoded-exact.

The controls cover whole interpolation and scalar helpers, endpoint and
destination references, direct versus borrowed banks, independent logical
indices, a physical sample cursor, loop setup/advance order, scalar/reference
inputs and endpoint accessors. Index controls recover neither complete body:
the closest physical-cursor variant still moves initialization across the
curve guard and leaves both interpolation SIB bytes wrong. Other independent
indices alter the logical-counter setup and loop advance order. Returning
endpoint values can add instructions; returning references is neutral here.
Normalized 100% controls still retain a literal mismatch. No diagnostic
helper, extra counter or unused declaration is promoted.

## Reproduce

The checker uses the existing independent positional byte auditor, verifies
the expression/address chains and rejects six corruptions covering address,
value, cost, instruction byte, reference target and padding. Both ordinary
source replays reproduce their recorded compiler, code fingerprint, counts,
score and references:

```sh
uv run tools/match/c2/loopout.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loopout-address-order-20260922.json \
  --batch interpolation-operation --label baseline --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loopout-address-order-20260922.json \
  --batch interpolation-operation --label field-borrow --replay
```

To repeat both preserving observations, use a new output directory:

```sh
uv run tools/match/c2/loopout.py --out /private/tmp/snail-loopout-order-replay
```

This uses the existing sibling Crimson observer dependency described in
[c2/README.md](c2/README.md). The checker itself reads the tracked receipt
without that checkout. Canonical scratch source, headers, compiler flags,
reference maps, target ranges and public progress remain unchanged.
