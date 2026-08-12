# read_repeating_text_input_key_code

First scratch for `read_repeating_text_input_key_code @ 0x4327e0`.

The helper maps held DirectInput scancodes to the same text-input byte codes as
`read_pressed_text_input_key_code`, then applies the native autorepeat state:

- `g_text_input_repeat_accumulator` gates the initial held-key delay;
- `g_text_input_repeat_step` controls the later repeat cadence;
- `g_text_input_last_repeat_code` is compared case-insensitively so shifted
  letters do not reset the held-key lane.

The source keeps the native two-byte shape: `result` is the active return code,
while `repeat_code` preserves the pre-repeat comparison byte.

## Current match notes

Focused matcher result: 99.09%, 440 candidate instructions versus 440 target
instructions, 386-instruction prefix, and 73 clean masked operands.

Swapping the operands in the case-fold equality is source-equivalent and nudges
VC6 toward the native comparison order, reducing the repeat-tail residual
without changing the autorepeat behavior.

Remaining residuals:

- Enter/Ctrl byte-code addition: native widens the final add to `ebx`, while
  clear byte-shaped source compiles as the equivalent `add bl, 5`.
- The repeat comparison still loads `g_text_input_last_repeat_code` before the
  stack `repeat_code`; a named `char` temporary fixed call order but worsened the
  preservation register, and an `int` temporary or subtraction-style comparison
  changed the stack frame. Leave those variants rejected.
- 2026-06-19 repeat-tail audit: the exact sibling
  `read_pressed_text_input_key_code` still matches 100.00%, 338/338, with 55
  clean masked operands. Focused Wibo for this repeat helper remains 99.09%,
  440/440, 386/440 prefix, and 73 clean masked operands. Swapping the
  case-fold equality operands regresses to 98.86% by changing only the final
  compare. A named folded-repeat byte recovers the native call order but
  regresses to 98.75% because VC6 preserves the first folded value through a
  stack byte instead of `dl`; widening that temporary to `int` changes the
  frame and collapses the prefix. Widening the top-level `result` to `int`
  also collapses the prefix by turning every `mov bl, imm8` into `mov ebx,
  imm32`. Enter/Ctrl variants using direct result assignment, a single
  expression, assignment through `repeat_code`, or swapped result/repeat stores
  are all codegen-neutral and keep `add bl, 5`. Keep the current byte-shaped
  baseline.
- 2026-06-20 near-proof retry: swapping the case-fold equality operands again
  regresses to 98.86% by changing the final compare direction without fixing
  the call/load order. Widening only the Enter/Ctrl `enter_code` temporary to
  `unsigned int` is codegen-neutral and still emits `add bl, 5`, confirming the
  full-register `add ebx, 5` residual is not recoverable through a narrow
  local type change while preserving the byte-shaped function body.
- 2026-06-20 text-input repeat-family audit: exact sibling
  `read_pressed_text_input_key_code` remains 100.00% and confirms the same
  scancode-to-byte mapping. Mirroring its Enter/Ctrl `char ctrl_down` idiom is
  codegen-neutral and still emits `add bl, 5`; removing the explicit `!= 0`
  regresses to 97.84% by replacing native `test/setne` with `mov bl, al`.
  Making `repeat_code` unsigned or declaring `ascii_upper_if_lowercase` as
  returning `unsigned char` is codegen-neutral. A named folded repeat byte
  regresses to 98.75% by spilling the folded value to the stack, and rewriting
  the tail as a decompiler-shaped `!=` reset-first branch regresses to 97.27%
  by moving the reset block before the accumulator block. Keep the current
  byte-shaped equality tail; the two remaining residuals are caller-side
  register/load-order artifacts, not evidence for different text-input state.
- 2026-06-20 larger near-proof pass: focused Wibo still reports 99.09%,
  440/440 instructions, 386/440 prefix, and 73 clean masked operands. Writing
  the Enter/Ctrl boolean directly into `result` before `result += 5` is
  codegen-neutral and still emits `add bl, 5`, so the native full-register
  `add ebx, 5` is not recovered by making the active result byte the add
  carrier. Keep the existing `enter_code` spelling because it is clearer and
  no worse.
- 2026-06-20 larger case-folding pass: helper-call and promotion probes did not
  produce a retained source change. Re-swapping the equality operands regressed
  to 98.86%, changing the compare direction without fixing the stack/global
  load order. Declaring `ascii_upper_if_lowercase` with an `int` parameter
  regressed to 71.96% by changing the stack frame from the first instruction;
  declaring its parameter as `unsigned char` was codegen-neutral. A
  no-parameter declaration would model old C promotion, but the `.cpp` scratch
  correctly rejects the calls with C2660, so it is not a valid source-shape lead
  here. Keep the exact helper's `char` prototype and the current byte-shaped
  repeat tail.
- 2026-06-20 larger near-proof continuation: focused Wibo still reports 99.09%,
  440/440 instructions, 386/440 prefix, and 73 clean masked operands. Collapsing
  the Enter/Ctrl path into `result = (is_key_down(0x1d) != 0) + 5`, commuting it
  to `5 + (...)`, and assigning the expression through `repeat_code` first are
  all codegen-neutral and keep `add bl, 5`. Re-swapping the repeat-tail
  case-fold call order again regressed to 98.86% by changing the compare to
  `cmp al, dl`; naming `folded_repeat` regressed to 98.75% by spilling the
  first folded byte instead of preserving it in `dl`. Changing
  `g_text_input_last_repeat_code` from unsigned to signed `char` is neutral.
  The retained source remains the best shape; native's full-register
  `add ebx, 5` and stack/global repeat-fold load order are caller scheduling
  artifacts, not evidence for different text-input state.
- 2026-06-21 Enter/Ctrl retry: spelling the Enter/Ctrl byte code as the explicit
  ternary `is_key_down(0x1d) ? 6 : 5` improves focused Wibo from 99.09% to
  99.32% and extends the exact prefix from 386/440 to 408/440 while preserving
  all 73 clean masks. This recovers the native full-register add cluster without
  widening the top-level `result` byte. The remaining residual is only the
  repeat-tail fold order: target folds the stack `repeat_code` first and then
  the global last-repeat byte, while the best candidate folds the global first.
  Named folded-byte temporaries recover the call order but spill the first fold
  result to the stack and regress to 98.98%; `int` folded temporaries change the
  frame from the prologue. Keep the ternary and leave the repeat-tail residual
  pinned.
- 2026-07-16 ownership replay: the symbol-bearing iOS and Android ports identify
  this helper as authored `RShellInkeyInput()` in `RShell.o`, alongside
  `gRShellKeyRepeatLife`, `gRShellKeyRepeatLifeRate`, and `gRShellOldKey`.
  Those globals correspond to the Windows accumulator, step, and last-code byte.
  The input-state replay now preserves all three scalar extents and the byte
  return ABI in both analysis databases; IDA's stale `float[5]` and `char[3]`
  items are split only behind exact name/type/size guards. The focused matcher
  remains honestly pinned at 99.32%, 440/440 instructions, a 408/440 exact
  prefix, and 73 clean masked operands. The remaining repeat-tail call order is
  still a scheduling residual, not evidence for a different owner or source
  model.

- 2026-07-16 shared-state closure: those three authored RShell globals now
  live in one canonical matcher header consumed by both `RShellInit()` and
  `RShellInkeyInput()`. The function remains at the honest 99.32% baseline,
  440/440 instructions, 408/440 prefix, and 73 clean operands; no rejected
  fold-order coercion was reintroduced.

## 2026-07-29 bounded repeat-fold audit

Twenty additional comparison and sequencing forms were swept. Equality,
negated inequality, subtraction, XOR, casts, and operand swaps do not improve
the 99.32%, 440/440 baseline. Named `char` folds recover native's first call
argument and extend the local aligned region, but spill the first folded byte
and reduce the whole-function score to 98.98%; `int` and in-place
normalization forms disturb the frame more broadly.

The remaining byte-level blocker begins at instruction 408. Native loads the
stack `repeat_code`, calls `ascii_upper_if_lowercase`, then loads the global
last-repeat byte; the candidate loads the global first, calls, then loads the
stack byte. Both call the same exact out-of-line helper twice and compare the
same folded bytes. The two unaudited operands are those displaced global/stack
loads, not unresolved ownership. Because retaining an out-of-line call is
already part of the native body, same-TU placement cannot legitimately
provide a hidden inline relationship; no TU grouping is introduced.

## 2026-07-29 recorded repeat-fold lifetime bound

Three recorded sweeps now cover 44 unique, compiling source forms around the
last fold comparison: 16 direct expression shapes, 16 explicit-local
lifetimes, and 12 assignment-inside-condition forms. None improves the
99.32%, 440/440 baseline; one negated-inequality spelling is byte-identical
and the other 43 regress. This history does not close the scratch.

The result cleanly separates the two available schedules. Direct equality,
casts, XOR/subtraction comparisons, and operand commutation retain native
instruction-count parity but VC6 still folds the global byte first, leaving
the same two displaced operands unaudited. Every viable `char`, `signed
char`, `unsigned char`, `register`, two-local, one-byte-array, and
assignment-expression lifetime folds the stack byte first and audits all 74
references, but stores AL before pushing the second argument. That removes
native's `mov dl, al` plus delayed spill, yields 439 instructions, and
regresses to 98.98%.

Both mobile implementations independently preserve the intended stack-code
then global-code fold order, but neither source family reproduces the Windows
DL lifetime. The retained byte-shaped comparison therefore remains the best
whole-function transcription; no volatile barrier, fake dependency, helper
inline, or global-state mutation is introduced to force the last schedule.

## 2026-08-11 VC6 profile boundary

The canonical `msvc6.5` build remains the proof-bearing `99.32%`,
`440/440`-instruction result with prefix 408 and all 74 references clean.
Profile probes recorded in `experiments.jsonl` reproduce that exact residual
under `msvc6.0` and `msvc6.6`; `msvc6.5pp` regresses to `97.61%`, 439
instructions, and prefix 386 while retaining the same clean references.

The 44 recorded source forms and independent Android/iOS control-flow
confirmation leave no semantic ambiguity. This scratch is classified
`RECOVERY=semantic-complete` with `RESIDUAL=compiler`; the remaining fold-call
schedule is not forced with an artificial dependency.
