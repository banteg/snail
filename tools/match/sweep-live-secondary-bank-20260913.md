# Sweep complete native body match

`initialize_sweep_path_template_pair` advances from **99.69325153%** to
**100% normalized and encoded-body equality**. All **652 instructions / 2,428
body bytes** match. The template family reaches **13 solved / 16 open**, with
**seven byte-exact builders**.

The source binds one local `PathTemplateSample *const &secondary_bank` to the
live `secondary_samples` member before sample generation. The lead, departure
and curve initialization calls all pass this reference to the existing
secondary helper, whose parameter now expresses its read-only use of the
pointer member. The helper still rereads the member through the reference
around `Identity()` and its subsequent stores. No pointer snapshot, new call,
extra dependency or change to the function ABI is introduced.

This source ownership recovers the last normalized difference: the departure
receiver copies the physical offset into ECX before the primary Y/Z stores,
then adds the secondary bank. It also recovers six ordinary addressing bytes.
The existing primary-position helper and all mesh/delta source remain intact.
Snake's preceding live-bank result motivated this local experiment; it does
not imply that every builder uses the same declarations.

## Controls and reversals

| Source / independent reversal | Normalized | Prefix | Byte-exact |
| --- | ---: | ---: | --- |
| Previous source | 99.69325153% | 90 | No |
| Only const-qualify the secondary helper parameter | 99.69325153% | 90 | No |
| Shared secondary bank reference, mutable | 100% | 652 | Yes |
| Shared secondary bank reference, const | 100% | 652 | Yes |
| Restore direct member argument in lead call | 99.69325153% | 45 | No |
| Restore direct member argument in departure call | 99.69325153% | 90 | No |
| Restore direct member argument in curve call | 99.69325153% | 147 | No |

The mutable and const forms generate identical raw function bytes. The const
form reflects actual read-only pointer use. Moving the binding after the lead
phase or using it only for the curve regresses to 99.07975460%. Borrowing the
primary bank too introduces three instructions and regresses to 94.10864575%.
Only the independently verified secondary-bank change is retained. The official
forward probe has no measurement tradeoffs; full reversal restores the previous
deterministic code fingerprint.

## Whole-body proof

The [receipt](sweep-live-secondary-bank-20260913.json) includes fresh independent
compilations of the baseline, retained source, mutable-reference control and
const-signature-only control. Each has complete raw bytes, separate instruction
arrays and a strict reference audit. The embedded auditor verifies every
reference's kind, operand slot, identity, instruction index, byte offset and
four-byte encoded relocation field before masking. All **37 references** pass,
and every candidate body relocation is consumed.

The retained source has the native **0x54 stack frame**, equal instruction
positions and sizes, and no literal body differences after that audit. All
**26 local branches** have equal positions, bytes and destinations at verified
instruction boundaries. The entire audited native and candidate bodies have
equal SHA-256 hashes.

Exactly **22 raw candidate bytes** change from the baseline, and every changed
byte now equals native. Sixteen are in the reordered receiver region
**[378,394)**. The remaining six are SIB bytes at offsets **418, 425, 436, 895,
995 and 1059**. None lies in a masked relocation field; all other raw candidate
bytes are unchanged. Ordinary address bytes and local branch displacements
remain literal.

Comparison covers **[0,2428)**, native **[0x422c00,0x42357c)**. The unchanged
2,432-byte curated extent ends at **0x423580**; its final four recognized
terminal-padding bytes are separately excluded. There are no unexplained
ranges. Compiler, flags, shared headers, target spans and matcher policy are
unchanged. Whole-function body proof does not add linked-image, standalone-data
or runtime claims.

## Campaign and replay

The receipt preserves **85 observations (84 compile-valid) / 82 distinct
full sources** across Sweep, Turnover, Turnover Double and Twister. One Twister
control has an invalid const-to-mutable reference binding; its compiler error
and the corrected controls remain distinct. One Turnover Double destination
control captures an address across `Sin` and is explicitly ineligible without
callee side-effect evidence. Neither contributes matching credit or evidence against valid source forms.

Turnover's live interpolation-bank reference recovers its endpoint-read SIB
byte but leaves its center-store byte different. This partial finding and the
other builders' controls remain unpromoted, with their encoded diagnostics
preserved for later work. These finite controls do not establish exhaustion.

Validate every source reconstruction and replay the retained result with:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/sweep-live-secondary-bank-20260913.json \
  --function initialize_sweep_path_template_pair \
  --batch independent-reversals --label retained --replay
```

## Validation and progress

All **785 scratch checks**, **1,140 tests**, extern lint and the exact-reference
audit pass. The strict ledger passes **2,569 records**, zero strict errors and
all **14 active specifications runnable**. All 85 source reconstructions and
fresh retained/baseline replays agree. The full public report refresh and a
separate saved-evidence validation pass; only Sweep's source binding and match
result change. No other function regresses, and extents and measurement
identities remain unchanged.

Core normalized matching rises to **614/662** functions and
**182,281/299,952 curated bytes (60.77%)**. Public normalized and encoded credit
each gain one function and **2,428 code bytes**. The difference between curated
extent and public body sizes is the four audited padding bytes above.
