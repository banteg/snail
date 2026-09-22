# Turnover interpolation-bank ownership — 2026-09-22

Turnover has **one remaining encoded-byte difference**, down from two. Its
normalized result remains 100%, with 671/671 instructions and 41 clean
same-position references. This is a partial encoded improvement, not another
complete match.

The circular interpolation now borrows the live primary sample-bank field
through `AttachmentSample* const& curve_samples`. The same bank reference owns
both input endpoints and the destination sample for this call-free operation.
It adds no storage, computation, artificial dependency or register constraint.
The reference preserves the field's live identity; it does not snapshot the
bank pointer across calls.

The extracted candidate changes exactly **one byte, at offset 628**. The
endpoint load now uses the native SIB encoding. Every other body and padding
byte, and every COFF relocation record, is unchanged. The destination store at
offset **653** still uses candidate SIB `18` instead of native `03`.

Independent Capstone verification accounts for all **2,433 body bytes plus 15
padding bytes**, all **41 positional relocation fields**, and all **25 literal
local branches**. The encoded prefix grows **626 → 651 bytes**; the existing
**1,775-byte suffix** from offset 658 remains equal. The checker rejects body,
reference-value, relocation-addend and padding corruption, and a falsely set
`body_byte_exact` flag. The full body remains `body_byte_exact=false`.

## Evidence and limits

The [receipt](turnover-bank-20260922.json) freezes baseline commit `7ef5a08ae`,
**67 observations / 66 distinct full sources**, input hashes, source recipes,
native/candidate captures, and forward/full-reversal probes. All 67 source
controls compile. The forward probe has no metric tradeoffs; the reversal
reproduces the original extracted code hash.

The source controls distinguish this improvement from superficially similar
alternatives:

- A value bank pointer leaves both original bytes different. A live bank
  reference or a complete interpolation helper borrowing that bank fixes only
  the endpoint load. The simple local reference is retained.
- Borrowing only the reads, only the endpoint, or only the destination regresses
  normalized agreement. Both halves of the operation must share the bank.
- Moving the bank lifetime, reusing lead/tail counters, splitting the returned
  interpolation value, or naming the destination does not close the final byte.
  Typed logical sample traversals change broader instruction and stack layout.
- The same live-bank transfer yields no complete match in LoopOut or
  TurnoverDouble; no source is retained there.
- Loading-screen resource operations and archive-result ownership, star-field
  motion/sprite operations and division precision, and Tip alignment forms do
  not improve their current baselines. CreateGolb and the two weapon selectors
  are baseline-only observations.

The uncatalogued-code review finds five jump-to-return stubs and three ranges
containing only eight NOPs each before the library region, rather than an
unexamined substantive game routine. The NOP ranges are at `0x410bf8`,
`0x43a2f8` and `0x43d228`; their saved function names do not describe executable
behavior in the canonical image. Raw instruction captures are retained in the
receipt. They are not added as substitute matching targets, and the inventory
is not changed in this source-matching patch. The mobile symbol catalog has no
surviving scalar vector-division symbol that settles member versus free-function
ownership, so no shared vector contract is changed.

These finite results do not establish source exhaustion or a compiler limit.
Compiler profiles, shared headers, ABI, native extents, reference identities
and matcher rules are unchanged.

```sh
uv run tools/match/check_turnover_bank_20260922.py
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/turnover-bank-20260922.json \
  --batch final_source10 --label live_interpolation_bank --replay
```

Validation: all **785 scratches** check and **1,140 tests** pass. Exact-reference
audit, extern lint, type consolidation and Ruff are clean. The ledger has
**2,639 records**, zero strict errors and **14/14** active specifications runnable.
All source recipes reconstruct and the retained source replays its code hash.
The refreshed report's normalized function rows and totals are unchanged;
only Turnover's tracked byte evidence changes after excluding COFF timestamps.
