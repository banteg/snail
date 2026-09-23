# LoopBow interpolation and pivot ownership

LoopBow now compiles to **796/796 matching normalized instructions**, with all
**63 references at their native instruction positions**. It remains a partial
match: one indexed-address SIB byte at body offset `809` is `18` in the
candidate and `03` in the native body. The body is therefore **not byte-exact**.

The curve interpolation now borrows the live primary sample bank through a
reference and names the last sample's center value. The pivot subtract keeps
its old Z value in a local before publishing the changed position. Those are
ordinary sample and transform lifetimes; neither changes the interpolation or
rotation behavior. Together they recover the complete native pivot schedule
and one of the two prior interpolation SIB bytes. The previous source had
99.62% normalized agreement, 796/796 instructions, 62/63 positional
references, and 24 unequal literal bytes after reference masking.

The independent byte checker recompiles the source, audits the 2,939 body
bytes, all 63 relocations, 28 local branches, and five terminal padding bytes,
and rejects corrupt body, reference, relocation, and padding controls. It
reports only offset `809` unequal. The preserving C2 observer confirms that
the borrow gives the bank cost `0x17f40`, above the endpoint offset cost
`0x17ec0`; the current-sample offset costs `0x152c0`, so this bank lifetime
alone cannot select the native offset-first destination encoding. This is a
source-search clue, not a compiler ceiling.

The status command now requires `body_byte_exact` before labeling a scratch
proof-grade. It consequently also reclassifies the already documented
LoopOut, Turnover, and TurnoverDouble address-encoding residuals as audit
needed. The byte-exact core count is **620/662**; LoopBow remains open.

Reproduce the current proof:

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/check_loopbow_interpolation_20260923.py
```
